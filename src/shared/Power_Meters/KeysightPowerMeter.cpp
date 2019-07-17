#include "KeysightPowerMeter.h"

KeysightPowerMeter::KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

KeysightPowerMeter::~KeysightPowerMeter()
{
}

bool PowerMeter::measurePower(ViSession &defaultSession, int window, QByteArray response){

    QByteArray baseCmd = "READ:POW?";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool PowerMeter::setPowerUnitDBM(ViSession &defaultSession, int window){

    QByteArray baseCmd = "UNIT:POW DBM\n";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdNoRsp(defaultSession, baseCmd);
}

bool PowerMeter::setPowerUnitW(ViSession &defaultSession, int window){

    QByteArray baseCmd = "UNIT:POW W\n";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdNoRsp(defaultSession, baseCmd);
}

