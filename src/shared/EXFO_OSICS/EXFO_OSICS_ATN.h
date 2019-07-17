#ifndef EXFO_OSICS_ATN_H
#define EXFO_OSICS_ATN_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_ATN : EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc);

    /**
     * @brief setModuleAttenuationCmd Sets the total attenuation in dB.
     *        Base command: CH#:ATN
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param attenuation Total attenuation value to set
     * @return true if command was successful
     */
    bool setModuleAttenuationCmd(ViSession &defaultSession, int slotNum, QByteArray &attenuation);

    /**
     * @brief moduleAttenuationQuery Returns the value of the attenuation in dB.
     *        Base command: CH#:ATN?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from the instrument - attenuation value in dB
     * @return true if command was successful
     */
    bool moduleAttenuationQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief moduleAttenuationMinMaxQuery Returns the min and max attenuation in dB for the given wavelength number.
     *        Base command: CH#:ATN_MIN_MAX?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelengthNum Wavelength number - either 1 or 2 for first/second factory calibration value
     * @param response Response from the instrument - min and max attenuation
     * @return true if command was successful
     */
    bool moduleAttenuationMinMaxQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response);

    /**
     * @brief moduleWavelengthNMQuery Returns the wavelength in nm for the given wavelength number
     *        Base command: CH#:LREF?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelengthNum Wavelength number - either 1 or 2 for first/second factory calibration value
     * @param response Response from the instrument - wavelength value in nm for specified wavelength number
     * @return true if command was successful
     */
    bool moduleWavelengthNMQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response);

    /**
     * @brief moduleAttenuationOffsetCmd Sets the attenuation offset for the given wavelength number.
     *        Base command: CH#:OFFSET
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelengthNum Wavelength number - either 1 or 2 for first/second factory calibration value
     * @param offsetVal Offset value in dB to set
     * @return true if command was successful
     */
    bool moduleAttenuationOffsetCmd(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray offsetVal);

    /**
     * @brief moduleAttenuationOffsetQuery Returns the offset value in dB for the given wavelength number
     *        Base command: CH#:OFFSET?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelengthNum Wavelength number - either 1 or 2 for first/second factory calibration value
     * @param response Response from the instrument - the offset value in dB
     * @return true if command was successful
     */
    bool moduleAttenuationOffsetQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response);

private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;
};

#endif // EXFO_OSICS_ATN_H
