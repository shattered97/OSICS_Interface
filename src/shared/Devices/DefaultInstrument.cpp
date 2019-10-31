#include "DefaultInstrument.h"


DefaultInstrument::DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc, QObject *parent) : QObject(parent)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;

    // default nickname to identity/location combo
    this->nickname = theIdentity;
    qRegisterMetaType<QByteArray>();
}

QByteArray DefaultInstrument::getInstrIdentity()
{
    return theIdentity;
}


QByteArray DefaultInstrument::getInstrLocation()
{
    return theInstrLoc;
}

QByteArray DefaultInstrument::getNickname(){
    return nickname;
}

void DefaultInstrument::setNickname(QByteArray nickname){
    this->nickname = nickname;
}

QByteArray DefaultInstrument::querySTB(){
    // Command "*STB?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_STB;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

void DefaultInstrument::execESE(char registerVal){
    // Command: "*ESE [registerVal]\n"
    // Params: 0 <= registerVal <= 255
    // Example: "*ESE 1\n"

    QByteArray baseCmd = EXEC_ESE;
    int paramPosition = baseCmd.indexOf('\n');
    QString param = QString(" %1").arg(registerVal);
    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

QByteArray DefaultInstrument::queryESE(){
    // Command "*ESE?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESE;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

QByteArray DefaultInstrument::queryESR(){
    // Command "*ESR?\n"
    // Response: "+1\n+1\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESR;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

void DefaultInstrument::execOPC(){
    // Command: "*OPC\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_OPC;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

QByteArray DefaultInstrument::queryOPC(){
    // Command "*OPC?\n"
    // Response: "1\n1\n"
    // Format: 0 or 1

    QByteArray command = QUERY_OPC;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

void DefaultInstrument::execCLS(){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_CLS;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void DefaultInstrument::execRST(){
    // Command: "*RST\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_RST;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

QByteArray DefaultInstrument::queryTST(){
    // Command "*TST?\n"
    // Response: "1\n1\n"
    // Format: 32-bit signed int

    QByteArray command = QUERY_TST;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

QByteArray DefaultInstrument::queryOPT(){
    // Command "*OPT?\n"
    // Response: "N7752A,  ,  ,  \nN7752A,  ,  ,  \n"
    // Format: Comma-separated part numbers of installed options. Two spaces if slot is empty.

    QByteArray command = QUERY_OPT;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

void DefaultInstrument::execWAI(){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_WAI;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

QByteArray DefaultInstrument::queryIDN(){
    // Command "*IDN?\n"
    // Response: "Agilent Technologies, N7714A, MY50701231, 1.13.1\nAgilent Technologies, N7714A, MY50701231, 1.13.1\n"
    // Format: Instrument identification

    QByteArray command = QUERY_IDN;
    QByteArray response = "";

    sendCommandAndWaitForResponse(theInstrLoc, command, &response);

    return response;
}

QMainWindow * DefaultInstrument::getConfigWindow(){
    return configWindow;
}

void DefaultInstrument::setConfigWindow(QMainWindow *configWindow){
    this->configWindow = configWindow;
}

void DefaultInstrument::updateConfig(QSettings &){
    qDebug() << "default updateConfig()";
}

void DefaultInstrument::sendCommandAndWaitForResponse(QByteArray theInstrLoc, QByteArray command, QByteArray *response){
    if(response){
        emit signalSendCmdRsp(theInstrLoc, command, response);
        while(*response == ""){
            // wait
        }
    }
}

