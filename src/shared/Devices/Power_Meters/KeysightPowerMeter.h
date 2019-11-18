#ifndef KEYSIGHTPOWERMETER_H
#define KEYSIGHTPOWERMETER_H

#include "PowerMeter.h"

class KeysightPowerMeter : public PowerMeter
{
    Q_OBJECT

public:
    KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);
    ~KeysightPowerMeter();

    QByteArray measurePower(int window);
    void setPowerUnit(int window, QByteArray unit);
    QByteArray getPowerUnit(int window);
    QByteArray getAllPowerUnits();
    QByteArray queryWavelength(int window, QByteArray value="");
    void setWavelength(int window, QByteArray value, QByteArray unit);
    QByteArray testCommand(QByteArray cmd);
    int getNumPowerMeterChannels();
    QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels);
    QList<QByteArray> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue);
    QList<QByteArray> getPowerReadingOnAllChannels();
    void updateConfig(QSettings *configSettings);
    QByteArray getAllPowerReadings();
    QByteArray getStabilityValues(int channel);
    void setStabilityValues(int channel, double totalTime, double avgTime, double periodTime);
    void setMinMaxModeValues(int channel, QByteArray mode, int dataPoints);
    QByteArray getMinMaxModeValues(int channel);
    
    void updateMinMaxSettings(QSettings &configSettings);
    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void updateStabilitySettings(QSettings &configSettings);
    void applyConfigSettings(QSettings *configSettings);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
    int numChannels;                        // the number of slots/channels of the power meter
    QByteArray response = "";               // holds a communication response from the instrument (power meter)
};

#endif // KEYSIGHTPOWERMETER_H
