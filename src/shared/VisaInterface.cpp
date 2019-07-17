#include "VisaInterface.h"


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
        logger->logEntry(QString("Failed to open default resource, status:  %1").arg(theStatus));
    }
    else
    {
        logger->logEntry("Successfully created Default Resource");
    }

   return theStatus;
}

void VisaInterface::displayResources(ViSession &defaultRMSession, FoundInstr &result)
{
    //Remove harded coded string and replace with variable

    if (findResources(defaultRMSession, ALL_RESOURCES))
        createInstrMap(defaultRMSession, result);
}

bool VisaInterface::findResources(ViSession &defaultRMSession, QString query)

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
    theStatus = viFindRsrc(defaultRMSession, query.toLatin1(), &findList, &numInstr, instrDescriptor);


    if(theStatus < VI_SUCCESS)
    {
        logger->logEntry(QString("Error Finding resources, status code: %1").arg(theStatus));
        return false;
    }
    else
    {
        QString response = "Found %1 instruments, First instrument address: %2";
        logger->logEntry(response.arg(numInstr).arg(instrDescriptor));
        instrAddr = instrDescriptor;  //convert from char array to QByteArray to make things easier
        return true;
    }

}

ViStatus VisaInterface::createInstrMap(ViSession &defaultRMSession, FoundInstr &resultMap)
{

    ViChar instrDescriptor[VI_FIND_BUFLEN];
    strcpy_s(instrDescriptor, instrAddr); //QByteArray back to char array

    //Open session to instrument
    theStatus = viOpen(defaultRMSession, instrDescriptor, VI_NULL, VI_NULL, &instrSession);

    int index = 1; // index of instrument in list

    if(theStatus < VI_SUCCESS)
    {
        logger->logEntry(QString("Error opening session to %1").arg(instrDescriptor));
    }
    else
    {
        //Opened instrument Session Log it
        logger->logEntry(QString("Opened session to: %1").arg(instrDescriptor));

        //Lets figure what instrument we are talking too
       theStatus = queryInstrument(instrAddr, instrSession, resultMap);

       if(theStatus < VI_SUCCESS)
       {
          logger->logEntry("Failed to get Instrument Identity, Closing Session") ;
          // if we can't talk to the first instrument, index into list will remain 1.
       }
       else
       {
          logger->logEntry("Found everything we need from first instrument");
          // if we can talk to first instrument, we increment our index by 1
          index ++;
       }

        closeSession(instrSession);
    }

    numInstr--; //We found first istrument so lets decerment our count

    while(numInstr > 0)
    {
        logger->logEntry(QString("Number of instruments left: %1").arg(numInstr));
        theStatus = findNextResource(defaultRMSession, resultMap);

        numInstr--; //added next instrument decrement count
        index++;  //increase index by 1
    }

    return theStatus;
}

ViStatus VisaInterface::closeDefaultSession(ViSession &defaultSession)
{
    logger->logEntry("Closing Default Session");
    return closeSession(defaultSession);
}

ViStatus VisaInterface::openInstrSession(ViSession &defaultSession, QByteArray instrAddr, ViSession &instrSess){
   ViStatus status = viOpen(defaultSession, instrAddr, VI_NULL, VI_NULL, &instrSess);
   if(status < VI_SUCCESS){
       logger->logEntry(QString(QString::number(__LINE__) + " Failed to open session on instrument"));
   }
   else{
       logger->logEntry(QString("Opened session to: %1").arg(QString::fromLatin1(instrAddr)));
   }
   return status;
}


ViStatus VisaInterface::findNextResource(ViSession &defaultRMSession, FoundInstr &resultMap)
{
    ViChar instrDescriptor[VI_FIND_BUFLEN];
    strcpy_s(instrDescriptor, instrAddr); //QByteArray back to char array

   theStatus = viFindNext(findList, instrDescriptor);

   if(theStatus < VI_SUCCESS)
   {
       logger->logEntry("Command to findNextResource Failed, Closing Session");
   }
   else
   {
       // open session
       theStatus = viOpen(defaultRMSession, instrDescriptor, VI_NULL, VI_NULL, &instrSession);
       if(theStatus < VI_SUCCESS){
           logger->logEntry(QString(QString::number(__LINE__) + " Failed to open session on instrument"));
       }
       else{
           logger->logEntry(QString("Opened session to: %1").arg(QString::fromLatin1(instrAddr)));
       }

       // convert char array to QByteArray
       instrAddr = QByteArray(reinterpret_cast<char*>(instrDescriptor));

       theStatus = queryInstrument(instrAddr, instrSession, resultMap);

       if(theStatus < VI_SUCCESS)
       {
          logger->logEntry("Failed to get Instrument Identity, Closing Session") ;
       }
       else
       {
          logger->logEntry("Found everything we need closing instrument Session");
       }
   }

   closeSession(instrSession);

   return theStatus;

}

ViStatus VisaInterface::queryInstrument(QByteArray &instrAddr, ViSession &instrSess, FoundInstr &resultMap)
{
    ViUInt32 rtnSize;
    InstrData firstInstr;

    //Ask the Instrument Identity
    theStatus = sendCmd(instrSess, instrAddr, IDENTITY, rtnSize);

    QString command(IDENTITY);  //Convert to string

    if (theStatus < VI_SUCCESS)
    {
        //We failed log it and close instrument session NOT the default session this is still open
        logger->logEntry("Failed to send command to instrument");
    }
    else
    {
        //Asked for Identity so lets read it
        QByteArray rsp;

        theStatus = readCmd(instrSess, instrAddr, rsp, rtnSize);

        QString responseFromCommand(rsp);  //Convert to string

        firstInstr.first = instrAddr;  //Record instrument address (Location)

        if(theStatus < VI_SUCCESS)
        {
            //We failed to read anything from instrument log it
            firstInstr.second = "No response from Instrument";
        }
        else
        {
            firstInstr.second = rsp;
        }

        resultMap.insert(resultMap.size() + 1, firstInstr);
    }

    return theStatus;
}

ViStatus VisaInterface::sendCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray scpiCmd, ViUInt32 &writeCount)
{
    ViChar buffer[VISA_MAX_BUFFER_SEND_SIZE];
    strcpy_s(buffer, scpiCmd);

    theStatus = viWrite(instrSession, (ViBuf)buffer, (ViUInt32)strlen(buffer), &writeCount);

    logger->logInstrSendCmd(instrAddr, theStatus, scpiCmd);

    if(theStatus < VI_SUCCESS)
    {
        logger->logEntry("Error writing to device");
    }

    return theStatus;
}

ViStatus VisaInterface::readCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray &response, ViUInt32 &retCount)
{
    unsigned char buffer[VISA_MAX_BUFFER_READ_SIZE];

    theStatus = viRead(instrSession, buffer, 100, &retCount);

    charArrayToByteArray(buffer, response, retCount);

    logger->logInstrReadCmd(instrAddr, theStatus, response);

    if(theStatus < VI_SUCCESS)
    {
        logger->logEntry("Error reading response from device");
    }
    else
    {
        logger->logEntry(QString("%1 Bytes Read:  %2").arg(retCount));
        charArrayToByteArray(buffer, response, retCount);
    }

    return theStatus;
}

ViStatus VisaInterface::closeSession(ViSession &sessionToClose)
{
    fflush(stdin);
    theStatus = viClose(sessionToClose);
    logger->logEntry("Closed Session");
    return theStatus;
}


//************************************* Helper Functions *******************************************


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
