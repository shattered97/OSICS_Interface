#ifndef POWERMETER_H
#define POWERMETER_H

#include "DefaultInstrument.h"
#include <QMainWindow>

class PowerMeter : public DefaultInstrument
{
    Q_OBJECT

public:
    PowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);

    virtual void measurePower(int window, QByteArray &response) = 0;
    virtual void setPowerUnit(int window, QByteArray unit) = 0;
    virtual void getPowerUnit(int window, QByteArray &response) = 0;
    virtual void getAllPowerUnits(QByteArray & response) = 0;
    virtual void queryWavelength(int window, QByteArray &response, QByteArray value="") = 0;
    virtual void setWavelength(int window, QByteArray &value, QByteArray &unit) = 0;
    virtual void testCommand(QByteArray cmd, QByteArray &response) = 0;
    virtual int getNumPowerMeterChannels() = 0;
    virtual QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels) = 0;
    virtual QList<double> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue) = 0;

    virtual void updateConfig(QSettings &) = 0;


private:
    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

};

#endif // POWERMETER_H
