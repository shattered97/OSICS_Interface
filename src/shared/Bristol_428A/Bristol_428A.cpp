#include "Bristol_428A.h"

Bristol_428A::Bristol_428A(QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void Bristol_428A::setMediumVaccum()
{
    QByteArray baseCmd = ":SENS:MED VAC\n";
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Bristol_428A::setMediumAir(){
    QByteArray baseCmd = ":SENS:MED AIR\n";
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Bristol_428A::measureWavelengthSingle(QByteArray &wavelength)
{
    QByteArray baseCmd = ":MEAS:SCAL:WAV?\n";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, wavelength);
}

void Bristol_428A::measurePowerSingle(QByteArray &power)
{
    QByteArray baseCmd = ":MEAS:SCAL:POW?\n";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, power);
}
