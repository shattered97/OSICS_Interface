#include "DefaultInstrument.h"
#include "constants.h"
#include <QElapsedTimer>

DefaultInstrument::DefaultInstrument() :
    theIdentity(""),
    theInstrLoc("")
{
    theCommBus = VisaInterface();
}

DefaultInstrument::DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc){
    this->theIdentity = theIdentity;
    qDebug() << this->theIdentity;
    this->theInstrLoc = theInstrLoc;
    qDebug() << this->theInstrLoc;

}

QByteArray DefaultInstrument::getInstrIdentity(){
    return theIdentity;
}

void DefaultInstrument::setInstrIdentity(QByteArray theIdentity){
    this->theIdentity = theIdentity;
}

QByteArray DefaultInstrument::getInstrLocation(){
    return theInstrLoc;
}

void DefaultInstrument::setInstrLocation(QByteArray theInstrLoc){
    this->theInstrLoc = theInstrLoc;
}

VisaInterface DefaultInstrument::getCommBus(){
    return theCommBus;
}

void DefaultInstrument::setCommBus(VisaInterface theCommBus){
    this->theCommBus = theCommBus;
}


bool DefaultInstrument::querySTB(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*STB?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_STB;

    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool DefaultInstrument::execESE(ViSession &defaultSession, ViSession &instrSession, ViByte registerVal){
    // Command: "*ESE [registerVal]\n"
    // Params: 0 <= registerVal <= 255
    // Example: "*ESE 1\n"

    QByteArray baseCmd = EXEC_ESE;
    int paramPosition = baseCmd.indexOf('\n');
    QString param = QString(" %1").arg(registerVal);
    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    return sendCmdNoRsp(defaultSession, instrSession, command);
}

bool DefaultInstrument::queryESE(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*ESE?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESE;

    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool DefaultInstrument::queryESR(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*ESR?\n"
    // Response: "+1\n+1\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESR;

    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool DefaultInstrument::execOPC(ViSession &defaultSession, ViSession &instrSession){
    // Command: "*OPC\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_OPC;

    return sendCmdNoRsp(defaultSession, instrSession, command);
}

bool DefaultInstrument::queryOPC(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*OPC?\n"
    // Response: "1\n1\n"
    // Format: 0 or 1

    QByteArray command = QUERY_OPC;

    return sendCmdRsp(defaultSession, instrSession, command, response);
}

bool DefaultInstrument::execCLS(ViSession &defaultSession, ViSession &instrSession){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_CLS;

    return sendCmdNoRsp(defaultSession, instrSession, command);
}

bool DefaultInstrument::execRST(ViSession &defaultSession, ViSession &instrSession){
    // Command: "*RST\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_RST;

    return sendCmdNoRsp(defaultSession, instrSession, command);
}

bool DefaultInstrument::queryTST(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*TST?\n"
    // Response: "1\n1\n"
    // Format: 32-bit signed int

    QByteArray command = QUERY_TST;

    return sendCmdRsp(defaultSession, instrSession, command, response);
}

bool DefaultInstrument::queryOPT(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*OPT?\n"
    // Response: "N7752A,  ,  ,  \nN7752A,  ,  ,  \n"
    // Format: Comma-separated part numbers of installed options. Two spaces if slot is empty.

    QByteArray command = QUERY_OPT;

    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool DefaultInstrument::execWAI(ViSession &defaultSession, ViSession &instrSession){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_WAI;

    return sendCmdNoRsp(defaultSession, instrSession, command);
}

bool DefaultInstrument::queryIDN(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    // Command "*IDN?\n"
    // Response: "Agilent Technologies, N7714A, MY50701231, 1.13.1\nAgilent Technologies, N7714A, MY50701231, 1.13.1\n"
    // Format: Instrument identification

    QByteArray command = QUERY_IDN;

    return sendCmdRsp(defaultSession, instrSession, command, response);

}

bool DefaultInstrument::checkOperationComplete(ViSession &defaultSession, ViSession &instrSession, int timeout = DEFAULT_COMMAND_TIMEOUT_MS){

    // in progress


    int complete = 0;
    QByteArray response;
    ViUInt32 writeCount;

    // start time
    QElapsedTimer timer;
    timer.start();

    //put your while loop here


    ViStatus status = theCommBus.sendCmd(instrSession, theInstrLoc, QUERY_OPC, writeCount);

    ViUInt32 rtnSize;
    status = theCommBus.readCmd(instrSession, theInstrLoc, response, rtnSize);

    complete = response[0];

}

bool DefaultInstrument::sendCmdNoRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command){

    bool success = true;  //assume success

    // open session
    ViStatus sessionStatus = NULL;  //always initialize your variables to a known state

    theCommBus.openInstrSession(defaultSession, theInstrLoc, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;  //get out of the habbit of returning early - create a bool
    }

    ViUInt32 writeCount;
    ViStatus status = theCommBus.sendCmd(instrSession, theInstrLoc, command, writeCount);

        if(status < VI_SUCCESS){
            qDebug() << QString("Query failed: %1").arg(status);
            // close session
            theCommBus.closeSession(instrSession);

            success = false;
        }
        else{
            qDebug() << "Query succeeded: " << command;
        }

    // close session
    theCommBus.closeSession(instrSession);

    return success;
}

bool DefaultInstrument::sendCmdRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command, QByteArray &response){


    // open session
    ViStatus sessionStatus;
    theCommBus.openInstrSession(defaultSession, theInstrLoc, instrSession);


    if(sessionStatus < VI_SUCCESS){
        return false;
    }

    // check if instrument is done processing previous commands

    checkOperationComplete(defaultSession, instrSession);

    ViUInt32 writeCount;
    ViStatus status = theCommBus.sendCmd(instrSession, theInstrLoc, command, writeCount);
        if(status < VI_SUCCESS){
            qDebug() << QString("Query failed: %1").arg(status);
            // close session
            theCommBus.closeSession(instrSession);

            return false;
        }
        else{
            qDebug() << "Query succeeded: " << command;
        }

    ViUInt32 rtnSize;
    status = theCommBus.readCmd(instrSession, theInstrLoc, response, rtnSize);
    if(status < VI_SUCCESS){
        qDebug() << QString("Reading response failed: %1").arg(status);
        // close session
        theCommBus.closeSession(instrSession);

        return false;
    }


    // close session
    theCommBus.closeSession(instrSession);

    return true;

}

