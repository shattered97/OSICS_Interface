#include "VisaInterface.h"

#include "VisaInterface.h"
#include <QDebug>

VisaInterface::VisaInterface()

{


}

VisaInterface::~VisaInterface()
{

}

ViStatus VisaInterface::createDefaultRM(ViSession &defaultSession)
{
    /*******************************************************************************************
    The viOpenDefaultRM() function must be called before any VISA operations can be
    invoked. The first call to this function initializes the VISA system, including the Default
    Resource Manager resource, and also returns a session to that resource. Subsequent calls
    to this function return unique sessions to the same Default Resource Manager resource.
    When a Resource Manager session is passed to viClose(), not only is that session closed,
    but also all find lists and device sessions (which that Resource Manager session was used to
    create) are closed.
    ********************************************************************************************/
    //This function returns a session to the Default Resource Manager resource.
    theStatus = viOpenDefaultRM(&defaultSession);

    //Anything greater than 0 is a failure
    //VI_SUCCESS == 0 Operation completed succesfully
    if(theStatus < VI_SUCCESS)
    {
        Logging::getInstance()->logEntry(QString("Failed to open default resource, status:  %1").arg(theStatus));
    }
    else
    {
        Logging::getInstance()->logEntry("Successfully created Default Resource");
    }

   return theStatus;
}

void VisaInterface::displayResources(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViUInt32 *numInstr, ViPFindList &findList, FoundInstr &result)
{
    //Remove harded coded string and replace with variable
    createDefaultRM(defaultRMSession);
    if (findResources(defaultRMSession, "GPIB?*INSTR", numInstr, findList, instrumentLoc))
        createInstrMap(defaultRMSession, instrumentLoc, instrSess, numInstr, findList, result);
    closeDefaultSession(defaultRMSession);

}

bool VisaInterface::findResources(ViSession &defaultRMSession,
                              QString query,
                              ViUInt32 *numInstrs,
                              ViPFindList &findList,
                              QByteArray &instrumentLoc)

{
    /*
     * Find all the VISA resources in our system and store the number of resources
     * in the system in numInstrs.  Notice the different query descriptions a
     * that are available.
        Interface         Expression
    --------------------------------------
        GPIB              "GPIB[0-9]*::?*INSTR"
        VXI               "VXI?*INSTR"
        GPIB-VXI          "GPIB-VXI?*INSTR"
        Any VXI           "?*VXI[0-9]*::?*INSTR"
        Serial            "ASRL[0-9]*::?*INSTR"
        PXI               "PXI?*INSTR"
        All instruments   "?*INSTR"
        All resources     "?*"
     */

    //
    ViChar instrDescriptor[VI_FIND_BUFLEN];


    //Queries a VISA system to locate the resources associated with a specified interface.
    theStatus = viFindRsrc(defaultRMSession, query.toLatin1(), findList, numInstrs, instrDescriptor);

    if(theStatus < VI_SUCCESS)
    {
        Logging::getInstance()->logEntry(QString("Error Finding resources, status code: %1").arg(theStatus));
        return false;
    }
    else
    {
        QString response = "Found %1 instruments, First instrument address: %2";
        Logging::getInstance()->logEntry(response.arg(*numInstrs).arg(instrDescriptor));
        instrumentLoc = instrDescriptor;  //convert from char array to QByteArray to make things easier
        return true;
    }

}

ViStatus VisaInterface::createInstrMap(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViUInt32 *numInstr, ViPFindList &findList, FoundInstr &resultMap)
{

    ViChar instrDescriptor[VI_FIND_BUFLEN];
    strcpy_s(instrDescriptor, instrumentLoc); //QByteArray back to char array

    //Open default Session
    theStatus = viOpen(defaultRMSession, instrDescriptor, VI_NULL, VI_NULL, &instrSess);


    if(theStatus < VI_SUCCESS)
    {
        //We Failed log it and close default session
        Logging::getInstance()->logEntry(QString("Error opening session to %1").arg(instrDescriptor));
        closeSession(defaultRMSession);
    }
    else
    {
        //Opened Default Session Log it
        Logging::getInstance()->logEntry(QString("Opened session to: %1").arg(instrDescriptor));

        //Lets figure what instrument we are talking too
       theStatus = queryInstrument(instrumentLoc, instrSess, resultMap, 1);  //This is the first instrument in the list

       if(theStatus < VI_SUCCESS)
       {
          Logging::getInstance()->logEntry("Failed to get Instrument Identity, Closing Session") ;
       }
       else
       {
          Logging::getInstance()->logEntry("Found everything we need from first instrument");
       }

        closeSession(instrSess);
    }

    (*numInstr)--; //We found first istrument so lets decerment our count
    int index = 2;  //first instrument already found so we need to start at 2

    while(*numInstr > 0)
    {
        Logging::getInstance()->logEntry(QString("Number of instruments left: %1").arg(*numInstr));
        theStatus = findNextResource(defaultRMSession, instrumentLoc, instrSess, findList, resultMap, index);
        (*numInstr)--; //added next instrument decrement count
        index++;  //increase index by 1
    }

    return theStatus;
}

ViStatus VisaInterface::closeDefaultSession(ViSession &defaultSession)
{
    Logging::getInstance()->logEntry("Closing Default Session");
    return closeSession(defaultSession);
}

ViStatus VisaInterface::findNextResource(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViPFindList &findList, FoundInstr &resultMap, int indexOfInstr)
{
    ViChar instrDescriptor[VI_FIND_BUFLEN];
    strcpy_s(instrDescriptor, instrumentLoc); //QByteArray back to char array

   theStatus = viFindNext(*findList, instrDescriptor);

   if(theStatus < VI_SUCCESS)
   {
       Logging::getInstance()->logEntry("Command to findNextResource Failed, Closing Session");
   }
   else
   {

       // open session
       theStatus = viOpen(defaultRMSession, instrDescriptor, VI_NULL, VI_NULL, &instrSess);

       // convert char array to QByteArray
       instrumentLoc = QByteArray(reinterpret_cast<char*>(instrDescriptor));

       theStatus = queryInstrument(instrumentLoc, instrSess, resultMap, indexOfInstr);

       if(theStatus < VI_SUCCESS)
       {
          Logging::getInstance()->logEntry("Failed to get Instrument Identity, Closing Session") ;
       }
       else
       {
          Logging::getInstance()->logEntry("Found everything we need closing instrument Session");
       }
   }

   closeSession(instrSess);

   return theStatus;

}

ViStatus VisaInterface::queryInstrument(QByteArray &instrumentLoc, ViSession &instrSess, FoundInstr &resultMap, int indexOfInstr)
{
    ViUInt32 rtnSize;
    InstrData firstInstr;

    //Ask the Instrument Identity
    theStatus = sendCmd(instrSess, instrumentLoc, IDENTITY, rtnSize);

    QString command(IDENTITY);  //Convert to string

    if (theStatus < VI_SUCCESS)
    {
        //We failed log it and close instrument session NOT the default session this is still open
        Logging::getInstance()->logEntry("Failed to send command to instrument");
    }
    else
    {
        //Asked for Identity so lets read it
        QByteArray rsp;

        theStatus = readCmd(instrSess, instrumentLoc, rsp, rtnSize);

        QString responseFromCommand(rsp);  //Convert to string

        firstInstr.first = instrumentLoc;  //Record instrument address (Location)

        if(theStatus < VI_SUCCESS)
        {
            //We failed to read anything from instrument log it
            firstInstr.second = "No response from Instrument";
        }
        else
        {
            firstInstr.second = rsp;
        }

        resultMap.insert(indexOfInstr, firstInstr);
    }

    return theStatus;
}

ViStatus VisaInterface::sendCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray scpiCmd, ViUInt32 &writeCount)
{
    ViChar buffer[VISA_MAX_BUFFER_SEND_SIZE];
    strcpy_s(buffer, scpiCmd);

    theStatus = viWrite(instrSession, (ViBuf)buffer, (ViUInt32)strlen(buffer), &writeCount);

    Logging::getInstance()->logInstrSendCmd(instrAddr, theStatus, scpiCmd);

    if(theStatus < VI_SUCCESS)
    {
        Logging::getInstance()->logEntry("Error writing to device");
    }

    return theStatus;
}

ViStatus VisaInterface::readCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray &response, ViUInt32 &retCount)
{
    unsigned char buffer[VISA_MAX_BUFFER_READ_SIZE];

    theStatus = viRead(instrSession, buffer, 100, &retCount);

    charArrayToByteArray(buffer, response, retCount);

    Logging::getInstance()->logInstrReadCmd(instrAddr, theStatus, response);

    if(theStatus < VI_SUCCESS)
    {
        Logging::getInstance()->logEntry("Error reading response from device");
    }
    else
    {
        Logging::getInstance()->logEntry(QString("%1 Bytes Read:  %2").arg(retCount));
        charArrayToByteArray(buffer, response, retCount);
    }

    return theStatus;
}

ViStatus VisaInterface::closeSession(ViSession &sessionToClose)
{
    fflush(stdin);
    theStatus = viClose(sessionToClose);
    Logging::getInstance()->logEntry("Closed Session");
    return theStatus;
}


//******************Helper Functions*********************************************************************

void VisaInterface::charArrayToByteArray(unsigned char (&charArray)[VISA_MAX_BUFFER_READ_SIZE], QByteArray &byteArray, ViUInt32 size)
{
    for(ViUInt32 i = 0; i < size; i++ )
    {
        byteArray.append(static_cast<char>(charArray[i]));
    }
}

void VisaInterface::byteArrayToCharArray(char (&charArray)[VISA_MAX_BUFFER_SEND_SIZE], QByteArray &byteArray)
{
    for(ViInt32 i = 0; i < byteArray.size(); i++)
    {
        charArray[i] = byteArray.at(i);
    }

}
