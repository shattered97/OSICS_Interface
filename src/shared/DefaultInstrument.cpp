#include "DefaultInstrument.h"

DefaultInstrument::DefaultInstrument() :
    theIdentity(""),
    theInstrLoc("")
{
    theCommBus = VisaInterface();
}

DefaultInstrument::DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc){
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

QByteArray DefaultInstrument::getInstrIdentity()
{
    return theIdentity;
}


QByteArray DefaultInstrument::getInstrLocation()
{
    return theInstrLoc;
}

bool DefaultInstrument::querySTB(ViSession &defaultSession, QByteArray &response){
    // Command "*STB?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_STB;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::execESE(ViSession &defaultSession, ViByte registerVal){
    // Command: "*ESE [registerVal]\n"
    // Params: 0 <= registerVal <= 255
    // Example: "*ESE 1\n"

    QByteArray baseCmd = EXEC_ESE;
    int paramPosition = baseCmd.indexOf('\n');
    QString param = QString(" %1").arg(registerVal);
    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    return sendCmdNoRsp(defaultSession, command);
}

bool DefaultInstrument::queryESE(ViSession &defaultSession, QByteArray &response){
    // Command "*ESE?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESE;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::queryESR(ViSession &defaultSession, QByteArray &response){
    // Command "*ESR?\n"
    // Response: "+1\n+1\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESR;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::execOPC(ViSession &defaultSession){
    // Command: "*OPC\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_OPC;

    return sendCmdNoRsp(defaultSession, command);
}

bool DefaultInstrument::queryOPC(ViSession &defaultSession, QByteArray &response){
    // Command "*OPC?\n"
    // Response: "1\n1\n"
    // Format: 0 or 1

    QByteArray command = QUERY_OPC;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::execCLS(ViSession &defaultSession){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_CLS;

    return sendCmdNoRsp(defaultSession, command);
}

bool DefaultInstrument::execRST(ViSession &defaultSession){
    // Command: "*RST\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_RST;

    return sendCmdNoRsp(defaultSession, command);
}

bool DefaultInstrument::queryTST(ViSession &defaultSession, QByteArray &response){
    // Command "*TST?\n"
    // Response: "1\n1\n"
    // Format: 32-bit signed int

    QByteArray command = QUERY_TST;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::queryOPT(ViSession &defaultSession, QByteArray &response){
    // Command "*OPT?\n"
    // Response: "N7752A,  ,  ,  \nN7752A,  ,  ,  \n"
    // Format: Comma-separated part numbers of installed options. Two spaces if slot is empty.

    QByteArray command = QUERY_OPT;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::execWAI(ViSession &defaultSession){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_WAI;

    return sendCmdNoRsp(defaultSession, command);
}

bool DefaultInstrument::queryIDN(ViSession &defaultSession, QByteArray &response){
    // Command "*IDN?\n"
    // Response: "Agilent Technologies, N7714A, MY50701231, 1.13.1\nAgilent Technologies, N7714A, MY50701231, 1.13.1\n"
    // Format: Instrument identification

    QByteArray command = QUERY_IDN;

    return sendCmdRsp(defaultSession, command, response);
}

bool DefaultInstrument::checkOperationComplete(ViSession &instrSession, int timeout = DEFAULT_COMMAND_TIMEOUT_MS){

    // start time
    QElapsedTimer timer;
    timer.start();

    int complete = 0;

    while(timer.elapsed() < timeout && complete == 0){
        complete = 0;

        ViUInt32 writeCount;
        theCommBus.sendCmd(instrSession, theInstrLoc, QUERY_OPC, writeCount);

        QByteArray response;
        ViUInt32 rtnSize;
        theCommBus.readCmd(instrSession, theInstrLoc, response, rtnSize);

        complete = response[0];
    }
    return complete;
}

bool DefaultInstrument::sendCmdNoRsp(ViSession &defaultSession, QByteArray &command){

    qDebug() << "Sent command: " << command;
    bool success = true;

    ViSession instrSession;

    // open session
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, theInstrLoc, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;
    }
    else{
        checkOperationComplete(instrSession);

        ViUInt32 writeCount;
        ViStatus status = theCommBus.sendCmd(instrSession, theInstrLoc, command, writeCount);

        if(status < VI_SUCCESS){
            success = false;
        }
        else{
            qDebug() << "Query succeeded: " << command;
        }

        // close session
        theCommBus.closeSession(instrSession);

    }

   return success;

}

bool DefaultInstrument::sendCmdRsp(ViSession &defaultSession, QByteArray &command, QByteArray &response){

    qDebug() << "Command sent: " << command;
    bool success = true;

    ViSession instrSession;

    // open session
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, theInstrLoc, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;
        qDebug() << "Opening session failed.  status: " << sessionStatus;
    }
    else{

        // check if instrument is done processing previous commands
        checkOperationComplete(instrSession);

        ViUInt32 writeCount;
        ViStatus status = theCommBus.sendCmd(instrSession, theInstrLoc, command, writeCount);
            if(status < VI_SUCCESS){
                qDebug() << QString("Query failed: %1").arg(status);
                status = false;
            }
            else{
                qDebug() << "Query succeeded: " << command;

                ViUInt32 rtnSize;
                status = theCommBus.readCmd(instrSession, theInstrLoc, response, rtnSize);

                if(status < VI_SUCCESS){
                    qDebug() << QString("Reading response failed: %1").arg(status);
                    success = false;
                }
            }

        // close session
        theCommBus.closeSession(instrSession);

    }

    return success;

}

