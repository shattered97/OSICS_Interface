#ifndef EXFO_OSICS_T100_H
#define EXFO_OSICS_T100_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_T100 : EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc);

    // ********************************* Diode-Current Setting Commands *********************************

    /**
     * @brief diodeCurrentLevelModuleQuery Returns the present current level in mA
     *        Base command: CH#:I?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - current level | Disabled (optical output is disabled)
     * @return true if command was successful
     */
    bool diodeCurrentLevelModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief diodeMaxCurrentModuleQuery Returns the diode maximum current in mA
     *        Base command: CH#:IMAX?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - diode maximum current in mA
     * @return true if command was successful
     */
    bool diodeMaxCurrentModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ********************************* Modulation Control Commands *********************************

    /**
     * @brief setModFrequencyModuleCmd Sets the frequency of the T100 module INTERNAL modulation source
     *        Base command: CH#:MOD_F
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param frequency Frequency of the modulation signal in Hz (153 to 1000000 Hz)
     * @return true if command was successful
     */
    bool setModFrequencyModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &frequency);

    /**
     * @brief modFrequencyModuleQuery Returns the frequency selected for the internal modulation generator in Hz
     *        Base command: MOD_F?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - selected frequency in Hz
     * @return true if command was successful
     */
    bool modFrequencyModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ********************************* Calibration Control Commands ********************************

    /**
     * @brief runWavelengthRefProcedureCmd Runs the internal wavelength referencing procedure
     *        Base command: CH#:WAVEREF
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool runWavelengthRefProcedureCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief setFirstCalibrationWavelengthCmd Sets the first wavelength value of the wavelength calibration method
     *        Base command: CH#:LCAL1=
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param wavelength First wavelength in nm
     * @return true if command was successful
     */
    bool setFirstCalibrationWavelengthCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelength);

    /**
     * @brief setSecondCalibrationWavelengthCmd Sets the second wavelength value of the wavelength calibration
     *        Base command: CH#:LCAL2=
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param wavelength Second wavelength in nm
     * @return true if command was successful
     */
    bool setSecondCalibrationWavelengthCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelength);

    /**
     * @brief firstCalibrationWavelengthQuery Returns the first calibration wavelength
     *        Base command: CH#:LCAL1?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - First calibration wavelength in nm
     * @return true if command was successful
     */
    bool firstCalibrationWavelengthQuery(ViSession &defaultSession, int slotNum,  QByteArray &response);

    /**
     * @brief secondCalibrationWavelengthQuery Returns the second calibration wavelength
     *        Base command: CH#:LCAL2?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - Second calibration wavelength in nm
     * @return true if command was successful
     */
    bool secondCalibrationWavelengthQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setFirstCalibrationPowerCmd Sets the first power value of the calibration method
     *        Base command: CH#:PCAL1=
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param power Output power in mW
     * @return true if command was successful
     */
    bool setFirstCalibrationPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power);

    /**
     * @brief setSecondCalibrationPowerCmd Sets the second power value of the calibration method
     *        Base command: CH#:PCAL2=
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param power Output power in mW
     * @return true if command was successful
     */
    bool setSecondCalibrationPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power);

    /**
     * @brief firstCalibrationPowerQuery Returns the first power value used for the power calibration
     *        Base command: CH#:PCAL1?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - Output power value in mW
     * @return true if command was successful
     */
    bool firstCalibrationPowerQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief secondCalibrationPowerQuery Returns the second power value used for the power calibration
     *        Base command: CH#:PCAL2?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - Output power value in mW
     * @return true if command was successful
     */
    bool secondCalibrationPowerQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ********************************** Module Parameter-Monitoring Commands *********************************

    /**
     * @brief assignOutBNCPortToSignalCmd Assigns the OUT 1 BNC port to monitor the selected signal
     *        Base command: CH#:AOUT
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param signalType Type of signal - I (monitor diode's current signal) | P (monitor optical-power signal)
     * @return true if command was successful
     */
    bool assignOutBNCPortToSignalCmd(ViSession &defaultSession, int slotNum, QByteArray &signalType);

    /**
     * @brief outBNCPortSignalMonitoringQuery Returns the parameter monitored by the OUT 1 BNC port
     *        Base command: CH#:AOUT?
     * @param defaultSession Default instrument session
     * @param slotNum Target slot number
     * @param response Response from instrument - I (T100 laser-diode) | P (optical output power)
     * @return true if command was successful
     */
    bool outBNCPortSignalMonitoringQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

};

#endif // EXFO_OSICS_T100_H
