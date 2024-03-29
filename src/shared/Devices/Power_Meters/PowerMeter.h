#ifndef POWERMETER_H
#define POWERMETER_H

#include "DefaultInstrument.h"
#include <QMainWindow>

class PowerMeter : public DefaultInstrument
{
    Q_OBJECT

public:
    PowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);

    virtual QByteArray measurePower(int window) = 0;
    virtual void setPowerUnit(int window, QByteArray unit) = 0;
    virtual QByteArray getPowerUnit(int window) = 0;
    virtual QByteArray getAllPowerUnits() = 0;
    virtual QByteArray queryWavelength(int window, QByteArray value="") = 0;
    virtual void setWavelength(int window, QByteArray value, QByteArray unit) = 0;
    virtual QByteArray testCommand(QByteArray cmd) = 0;
    virtual int getNumPowerMeterChannels() = 0;
    virtual QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels) = 0;
    virtual QList<QByteArray> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue) = 0;
    virtual QList<QByteArray> getPowerReadingOnAllChannels() = 0;
    virtual QByteArray getStabilityValues(int channel) = 0;
    virtual void setStabilityValues(int channel, double totalTime, double avgTime, double periodTime) = 0;
    virtual QByteArray getMinMaxModeValues(int channel) = 0;
    virtual void setMinMaxModeValues(int channel, QByteArray mode, int dataPoints) = 0;
    virtual void updateConfig(QSettings *) = 0;
    virtual void applyConfigSettings(QSettings *) = 0;
    void setNumChannelsVar(int numChannels);
    int getNumChannelsVar();

public slots:
    void slotSetupPowerMeter();

private:
    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

    // number of channels on the power meter
    int numChannels;
};

#endif // POWERMETER_H
