#ifndef POWERMETER_H
#define POWERMETER_H

#include <QString>
#include <QObject>
#include "DefaultInstrument.h"

class PowerMeter : QObject, protected DefaultInstrument
{
    Q_OBJECT
public:
    PowerMeter();
    virtual ~PowerMeter() = 0;

    /**
     * @brief measurePower Queries the device for the current power and returns the response.
     * @param defaultSession Default communication session
     * @param instrSession Session to instrument
     * @param window Window number to read from on device
     * @param response[out] Response from device
     * @return true if command successful
     */
    virtual bool measurePower(ViSession &defaultSession, int window, QByteArray response) = 0;

    /**
     * @brief setPowerUnitDBM Sends command to device to set power measurement unit to dBm.
     * @param defaultSession Default communication session
     * @param instrSession Session to instrument
     * @param window Window number to read from on device
     * @return true if command successful
     */
    virtual bool setPowerUnitDBM(ViSession &defaultSession, int window) = 0;

    /**
     * @brief setPowerUnitW Sends command to device to set power measurement unit to W.
     * @param defaultSession Default communication session
     * @param instrSession Session to instrument
     * @param window Window number to read from on device
     * @return true if command successful
     */
    virtual bool setPowerUnitW(ViSession &defaultSession, int window) = 0;

};

#endif // POWERMETER_H
