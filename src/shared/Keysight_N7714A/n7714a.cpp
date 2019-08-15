#include "N7714A.h"

N7714A::N7714A( QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}


void N7714A::queryPowerUnit(int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_UNIT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execPowerUnit(int module, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_UNIT_CMD;

    // outp1:pow:un w
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    command.insert(command.indexOf('\n'), " " + unit);

    qDebug() << command;

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryPowerStatus(int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_STAT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);

}

void N7714A::execPowerOnModule(int module){

    QByteArray baseCmd = N7714A_POW_ON_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::execPowerOffModule(int module){
    QByteArray baseCmd = N7714A_POW_OFF_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryPowerLevel(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_POW_LEVEL_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execPowerLevel(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_LEVEL_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, unit)).toLatin1();
    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryWavelength(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_WAV_QUERY;

    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execWavelength(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_WAV_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::queryFrequency(int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_FREQ_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    emit signalSendCmdRsp(theInstrLoc, command, response);
}

void N7714A::execFrequency(int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_FREQ_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    emit signalSendCmdNoRsp(theInstrLoc, command);
}

void N7714A::testCommand(QByteArray cmd, QByteArray &response){
    cmd = cmd + '\n';
    emit signalSendCmdRsp(theInstrLoc, cmd, response);
}

void N7714A::queryAutoWavMode(int module, QByteArray &response){
    QByteArray baseCmd = "sour:wav:auto?";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void N7714A::turnOnAutoWavMode(int module){
    QByteArray baseCmd = "sour:wav:auto on\n";

    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}



