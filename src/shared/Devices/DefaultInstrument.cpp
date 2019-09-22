#include "DefaultInstrument.h"


DefaultInstrument::DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc, QObject *parent) : QObject(parent)
{
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

void DefaultInstrument::querySTB(QByteArray &response){
    // Command "*STB?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_STB;

    emit signalSendCmdRsp(theInstrLoc, command, response);
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

void DefaultInstrument::queryESE(QByteArray &response){
    // Command "*ESE?\n"
    // Response: "+4\n+4\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESE;

    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void DefaultInstrument::queryESR(QByteArray &response){
    // Command "*ESR?\n"
    // Response: "+1\n+1\n"
    // Format: 16-bit signed int

    QByteArray command = QUERY_ESR;

    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void DefaultInstrument::execOPC(){
    // Command: "*OPC\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_OPC;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void DefaultInstrument::queryOPC(QByteArray &response){
    // Command "*OPC?\n"
    // Response: "1\n1\n"
    // Format: 0 or 1

    QByteArray command = QUERY_OPC;

    emit signalSendCmdRsp(theInstrLoc, command, response);
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

void DefaultInstrument::queryTST(QByteArray &response){
    // Command "*TST?\n"
    // Response: "1\n1\n"
    // Format: 32-bit signed int

    QByteArray command = QUERY_TST;

    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void DefaultInstrument::queryOPT(QByteArray &response){
    // Command "*OPT?\n"
    // Response: "N7752A,  ,  ,  \nN7752A,  ,  ,  \n"
    // Format: Comma-separated part numbers of installed options. Two spaces if slot is empty.

    QByteArray command = QUERY_OPT;

    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void DefaultInstrument::execWAI(){
    // Command: "*CLS\n"
    // Params: None
    // Response: None

    QByteArray command = EXEC_WAI;

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void DefaultInstrument::queryIDN(QByteArray &response){
    // Command "*IDN?\n"
    // Response: "Agilent Technologies, N7714A, MY50701231, 1.13.1\nAgilent Technologies, N7714A, MY50701231, 1.13.1\n"
    // Format: Instrument identification

    QByteArray command = QUERY_IDN;

    emit signalSendCmdRsp(theInstrLoc, command, response);
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

