#include "N7714A.h"

N7714A::N7714A( QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}


bool N7714A::queryPowerUnit(ViSession &defaultSession, int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_UNIT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, command, response);
}

bool N7714A::execPowerUnit(ViSession &defaultSession, int module, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_UNIT_CMD;

    // outp1:pow:un w
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    command.insert(command.indexOf('\n'), " " + unit);

    qDebug() << command;

    // send command
    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::queryPowerStatus(ViSession &defaultSession, int module, QByteArray &response){

    QByteArray baseCmd = N7714A_POW_STAT_QUERY;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, command, response);

}

bool N7714A::execPowerOnModule(ViSession &defaultSession, int module){

    QByteArray baseCmd = N7714A_POW_ON_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::execPowerOffModule(ViSession &defaultSession, int module){
    QByteArray baseCmd = N7714A_POW_OFF_CMD;
    int paramPosition = baseCmd.indexOf(':');
    QString param = QString("%1").arg(module);

    QByteArray command = QString(baseCmd.insert(paramPosition, param)).toLatin1();

    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::queryPowerLevel(ViSession &defaultSession, int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_POW_LEVEL_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, command, response);
}

bool N7714A::execPowerLevel(ViSession &defaultSession, int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_POW_LEVEL_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, unit)).toLatin1();
    // send command
    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::queryWavelength(ViSession &defaultSession, int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_WAV_QUERY;

    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, command, response);
}

bool N7714A::execWavelength(ViSession &defaultSession, int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_WAV_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::queryFrequency(ViSession &defaultSession, int module, QByteArray &response, QByteArray value){
    QByteArray baseCmd = N7714A_FREQ_QUERY;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    // send command
    return sendCmdRsp(defaultSession, command, response);
}

bool N7714A::execFrequency(ViSession &defaultSession, int module, QByteArray value, QByteArray unit){
    QByteArray baseCmd = N7714A_FREQ_CMD;
    int modulePos = baseCmd.indexOf(':');

    QString moduleString = QString("%1").arg(module);
    QByteArray command = QString(baseCmd.insert(modulePos, moduleString)).toLatin1();

    int valuePos = command.indexOf('\n');
    command = QString(command.insert(valuePos, " " + value)).toLatin1();

    command.insert(command.indexOf('\n'), unit);

    // send command
    return sendCmdNoRsp(defaultSession, command);
}

bool N7714A::testCommand(ViSession &defaultSession, QByteArray cmd, QByteArray &response){
    cmd = cmd + '\n';
    return sendCmdRsp(defaultSession, cmd, response);
}

bool N7714A::queryAutoWavMode(ViSession &defaultSession, int module, QByteArray &response){
    QByteArray baseCmd = "sour:wav:auto?";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool N7714A::turnOnAutoWavMode(ViSession &defaultSession, int module){
    QByteArray baseCmd = "sour:wav:auto on\n";

    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(module));

    return sendCmdNoRsp(defaultSession, baseCmd);
}



