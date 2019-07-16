#include "KeysightPowerMeter.h"

KeysightPowerMeter::KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc)
{
    this->instrIdentity = theIdentity;
    this->instrLoc = theInstrLoc;
}

KeysightPowerMeter::~KeysightPowerMeter()
{
}

bool PowerMeter::measurePower(ViSession &defaultSession, ViSession &instrSession, int window, QByteArray response){

    QByteArray baseCmd = "READ:POW?";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

bool PowerMeter::setPowerUnitDBM(ViSession &defaultSession, ViSession &instrSession, int window){

    QByteArray baseCmd = "UNIT:POW DBM\n";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

bool PowerMeter::setPowerUnitW(ViSession &defaultSession, ViSession &instrSession, int window){

    QByteArray baseCmd = "UNIT:POW W\n";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

