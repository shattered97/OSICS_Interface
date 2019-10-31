#include "PowerMeter.h"

PowerMeter::PowerMeter(QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void PowerMeter::setNumChannelsVar(int numChannels){
    this->numChannels = numChannels;
}

int PowerMeter::getNumChannelsVar(){
    return numChannels;
}

void PowerMeter::slotSetupPowerMeter(){
    setNumChannelsVar(getNumPowerMeterChannels());
}
