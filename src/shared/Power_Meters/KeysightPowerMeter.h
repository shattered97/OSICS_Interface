#ifndef KEYSIGHTPOWERMETER_H
#define KEYSIGHTPOWERMETER_H

#include "PowerMeter.h"

class KeysightPowerMeter : public PowerMeter
{
    Q_OBJECT

public:
    KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);
    ~KeysightPowerMeter();

    bool measurePower(ViSession &defaultSession, int window, QByteArray &response);
    bool setPowerUnit(ViSession &defaultSession, int window, QByteArray unit);
    bool getPowerUnit(ViSession &defaultSession, int window, QByteArray &response);
    bool getAllPowerUnits(ViSession &defaultSession, QByteArray & response);
    bool queryWavelength(ViSession &defaultSession, int window, QByteArray &response, QByteArray value="");
    bool setWavelength(ViSession &defaultSession, int window, QByteArray &value, QByteArray &unit);
    bool testCommand(ViSession &defaultSession, QByteArray cmd, QByteArray &response);
    int getNumPowerMeterChannels(ViSession &defaultSession);
    QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels);
    QList<double> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue);

signals:
    void signalSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
};

#endif // KEYSIGHTPOWERMETER_H
