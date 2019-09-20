#ifndef EXFO_OSICS_T100_H
#define EXFO_OSICS_T100_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_T100 : public EXFO_OSICS_MAINFRAME
{
    Q_OBJECT
public:
    EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc);

    // ********************************* Diode-Current Setting Commands *********************************

    /**
     * @brief diodeCurrentLevelModuleQuery Returns the present current level in mA
     *        Base command: CH#:I?
     * @param slotNum Target slot number
     * @param response Response from instrument - current level | Disabled (optical output is disabled)
     * @return true if command was successful
     */
    void diodeCurrentLevelModuleQuery(int slotNum, QByteArray &response);

    /**
     * @brief diodeMaxCurrentModuleQuery Returns the diode maximum current in mA
     *        Base command: CH#:IMAX?
     * @param slotNum Target slot number
     * @param response Response from instrument - diode maximum current in mA
     * @return true if command was successful
     */
    void diodeMaxCurrentModuleQuery(int slotNum, QByteArray &response);


    // ********************************* Modulation Control Commands *********************************

    /**
     * @brief setModFrequencyModuleCmd Sets the frequency of the T100 module INTERNAL modulation source
     *        Base command: CH#:MOD_F
     * @param slotNum Target slot number
     * @param frequency Frequency of the modulation signal in Hz (153 to 1000000 Hz)
     * @return true if command was successful
     */
    void setModFrequencyModuleCmd(int slotNum, QByteArray &frequency);

    /**
     * @brief modFrequencyModuleQuery Returns the frequency selected for the internal modulation generator in Hz
     *        Base command: MOD_F?
     * @param slotNum Target slot number
     * @param response Response from instrument - selected frequency in Hz
     * @return true if command was successful
     */
    void modFrequencyModuleQuery(int slotNum, QByteArray &response);


    // ********************************* Calibration Control Commands ********************************

    /**
     * @brief runWavelengthRefProcedureCmd Runs the internal wavelength referencing procedure
     *        Base command: CH#:WAVEREF
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void runWavelengthRefProcedureCmd(int slotNum);

    /**
     * @brief setFirstCalibrationWavelengthCmd Sets the first wavelength value of the wavelength calibration method
     *        Base command: CH#:LCAL1=
     * @param slotNum Target slot number
     * @param wavelength First wavelength in nm
     * @return true if command was successful
     */
    void setFirstCalibrationWavelengthCmd(int slotNum, QByteArray &wavelength);

    /**
     * @brief setSecondCalibrationWavelengthCmd Sets the second wavelength value of the wavelength calibration
     *        Base command: CH#:LCAL2=
     * @param slotNum Target slot number
     * @param wavelength Second wavelength in nm
     * @return true if command was successful
     */
    void setSecondCalibrationWavelengthCmd(int slotNum, QByteArray &wavelength);

    /**
     * @brief firstCalibrationWavelengthQuery Returns the first calibration wavelength
     *        Base command: CH#:LCAL1?
     * @param slotNum Target slot number
     * @param response Response from instrument - First calibration wavelength in nm
     * @return true if command was successful
     */
    void firstCalibrationWavelengthQuery(int slotNum,  QByteArray &response);

    /**
     * @brief secondCalibrationWavelengthQuery Returns the second calibration wavelength
     *        Base command: CH#:LCAL2?
     * @param slotNum Target slot number
     * @param response Response from instrument - Second calibration wavelength in nm
     * @return true if command was successful
     */
    void secondCalibrationWavelengthQuery(int slotNum, QByteArray &response);

    /**
     * @brief setFirstCalibrationPowerCmd Sets the first power value of the calibration method
     *        Base command: CH#:PCAL1=
     * @param slotNum Target slot number
     * @param power Output power in mW
     * @return true if command was successful
     */
    void setFirstCalibrationPowerCmd(int slotNum, QByteArray &power);

    /**
     * @brief setSecondCalibrationPowerCmd Sets the second power value of the calibration method
     *        Base command: CH#:PCAL2=
     * @param slotNum Target slot number
     * @param power Output power in mW
     * @return true if command was successful
     */
    void setSecondCalibrationPowerCmd(int slotNum, QByteArray &power);

    /**
     * @brief firstCalibrationPowerQuery Returns the first power value used for the power calibration
     *        Base command: CH#:PCAL1?
     * @param slotNum Target slot number
     * @param response Response from instrument - Output power value in mW
     * @return true if command was successful
     */
    void firstCalibrationPowerQuery(int slotNum, QByteArray &response);

    /**
     * @brief secondCalibrationPowerQuery Returns the second power value used for the power calibration
     *        Base command: CH#:PCAL2?
     * @param slotNum Target slot number
     * @param response Response from instrument - Output power value in mW
     * @return true if command was successful
     */
    void secondCalibrationPowerQuery(int slotNum, QByteArray &response);


    // ********************************** Module Parameter-Monitoring Commands *********************************

    /**
     * @brief assignOutBNCPortToSignalCmd Assigns the OUT 1 BNC port to monitor the selected signal
     *        Base command: CH#:AOUT
     * @param slotNum Target slot number
     * @param signalType Type of signal - I (monitor diode's current signal) | P (monitor optical-power signal)
     * @return true if command was successful
     */
    void assignOutBNCPortToSignalCmd(int slotNum, QByteArray &signalType);

    /**
     * @brief outBNCPortSignalMonitoringQuery Returns the parameter monitored by the OUT 1 BNC port
     *        Base command: CH#:AOUT?
     * @param slotNum Target slot number
     * @param response Response from instrument - I (T100 laser-diode) | P (optical output power)
     * @return true if command was successful
     */
    void outBNCPortSignalMonitoringQuery(int slotNum, QByteArray &response);


// *********** Functions for Applying/Updating Config Settings **********

    void applyConfigSettings(QSettings &configSettings);
    void updateConfig(QSettings &configSettings);

    void setSlotNum(int slotNum);
    void setT100MinMaxWavelengths(QByteArray t100Type);

private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

    int slotNum = 1;

    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void updateFrequencySettings(QSettings &configSettings);


    QByteArray minWavelength;
    QByteArray maxWavelength;
};

#endif // EXFO_OSICS_T100_H
