#ifndef KEYSIGHTPOWERMETER_H
#define KEYSIGHTPOWERMETER_H

#include "PowerMeter.h"

class KeysightPowerMeter : public PowerMeter
{
    Q_OBJECT

public:
    KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);
    ~KeysightPowerMeter();

    void measurePower(int window, QByteArray &response);
    void setPowerUnit(int window, QByteArray unit);
    void getPowerUnit(int window, QByteArray &response);
    void getAllPowerUnits(QByteArray & response);
    void queryWavelength(int window, QByteArray &response, QByteArray value="");
    void setWavelength(int window, QByteArray &value, QByteArray &unit);
    void testCommand(QByteArray cmd, QByteArray &response);
    int getNumPowerMeterChannels();
    QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels);
    QList<QByteArray> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue);
    void getPowerReadingOnAllChannels(QList<QByteArray> &readings);
    void updateConfig(QSettings &configSettings);
    void getAllPowerReadings(QByteArray &response);

    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void applyConfigSettings(QSettings &configSettings);
signals:
//    void signalSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
//    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
    int numSlots;                           // the number of slots/channels of the power meter
};

#endif // KEYSIGHTPOWERMETER_H
