#ifndef POWERMETER_H
#define POWERMETER_H

#include "DefaultInstrument.h"
#include <QMainWindow>

class PowerMeter : public DefaultInstrument
{
    Q_OBJECT

public:
    PowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);

//    /**
//     * @brief measurePower Queries the device for the current power and returns the response.
//     * @param defaultSession Default communication session
//     * @param window Window number to read from on device
//     * @param response[out] Response from device
//     * @return true if command successful
//     */
//    virtual bool measurePower(ViSession &defaultSession, int window, QByteArray &response) = 0;

//    /**
//     * @brief setPowerUnitDBM Sends command to device to set power measurement unit to dBm.
//     * @param defaultSession Default communication session
//     * @param window Window number to read from on device
//     * @return true if command successful
//     */
//    virtual bool setPowerUnitDBM(ViSession &defaultSession, int window) = 0;

//    /**
//     * @brief setPowerUnitW Sends command to device to set power measurement unit to W.
//     * @param defaultSession Default communication session
//     * @param window Window number to read from on device
//     * @return true if command successful
//     */
//    virtual bool setPowerUnitW(ViSession &defaultSession, int window) = 0;

//    /**
//     * @brief getPowerUnit Queries the device for the current power unit and returns the response.
//     * @param defaultSession Default communication session
//     * @param window Window number to read from on device
//     * @param response[out] Response from device
//     * @return true if command successful
//     */
//    virtual bool getPowerUnit(ViSession &defaultSession, int window, QByteArray &response) = 0;


    virtual bool measurePower(ViSession &defaultSession, int window, QByteArray &response) = 0;
    virtual bool setPowerUnit(ViSession &defaultSession, int window, QByteArray unit) = 0;
    virtual bool getPowerUnit(ViSession &defaultSession, int window, QByteArray &response) = 0;
    virtual bool getAllPowerUnits(ViSession &defaultSession, QByteArray & response) = 0;
    virtual bool queryWavelength(ViSession &defaultSession, int window, QByteArray &response, QByteArray value="") = 0;
    virtual bool setWavelength(ViSession &defaultSession, int window, QByteArray &value, QByteArray &unit) = 0;
    virtual bool testCommand(ViSession &defaultSession, QByteArray cmd, QByteArray &response) = 0;
    virtual int getNumPowerMeterChannels(ViSession &defaultSession) = 0;
    virtual QList<QByteArray> formatPowerUnits(QByteArray rawUnits, int numChannels) = 0;
    virtual QList<double> parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue) = 0;

private:
    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

};

#endif // POWERMETER_H
