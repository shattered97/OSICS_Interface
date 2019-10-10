#ifndef EXFO_OSICS_MAINFRAME_H
#define EXFO_OSICS_MAINFRAME_H

#include "DefaultInstrument.h"

class EXFO_OSICS_MAINFRAME : public DefaultInstrument
{
    Q_OBJECT
public:
    EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc);

    // ******************************* Mainframe Commands Only  *******************************

    /**
     * @brief disableMainframeLaserCmd Disables the laser output on all OSICS modules
     *        Base command: DISABLE
     * @return true if command was successful
     */
    void disableMainframeLaserCmd();

    /**
     * @brief enableMainframeLaserCmd Enables the laser output on all OSICS modules
     *        Base command: ENABLE
     * @return true if command was successful
     */
    void enableMainframeLaserCmd();

    /**
     * @brief laserStateMainframeQuery Returns the current state of the OSICS laser output master control
     *        Base command: ENABLE?
     * @param response Response from instrument - ENABLED | DISABLED
     * @return true if command was successful
     */
    QByteArray laserStateMainframeQuery();

    /**
     * @brief setMainframeSpectralUnitGHzCmd Sets the frequency in GHz as the spectral unit on OSICS system
     *        Base command: GHZ
     * @return true if command was successful
     */
    void setMainframeSpectralUnitGHzCmd();

    /**
     * @brief setMainframeSpectralUnitNMCmd Sets the wavelength in nm as the spectral unit on OSICS system
     *        Base command: NM
     * @return true if command was successful
     */
    void setMainframeSpectralUnitNMCmd();

    /**
     * @brief spectralUnitMainframeQuery Returns the current spectral unit used on the OSICS system
     *        Base command: NM?
     * @param response Response from instrument - 0 (spectral unit is nm) | 1 (spectral unit is GHz)
     * @return true if command was successful
     */
    QByteArray spectralUnitMainframeQuery();

    /**
     * @brief setMainframePowerUnitDBmCmd Sets dBm as the power unit on all modules
     *        Base command: DBM
     * @return true if command was successful
     */
    void setMainframePowerUnitDBmCmd();

    /**
     * @brief setMainframePowerUnitMWCmd Sets mW as the power unit on all modules
     *        Base command: MW
     * @return true if command was successful
     */
    void setMainframePowerUnitMWCmd();

    /**
     * @brief powerUnitMainframeQuery Returns the current power unit used on the OSICS system
     *        Base command: MW?
     * @param response Response from instrument - 0 (power is in dBm) | 1 (power is in mW)
     * @return true if command was successful
     */
    QByteArray powerUnitMainframeQuery();

    /**
     * @brief setMainframeOutputPowerCmd Sets the optical output power of all modules to the same value
     *        Base command: P=
     * @param power Output power to set (in mW or dBm depending on set unit)
     * @return true if command was successful
     */
    void setMainframeOutputPowerCmd(QByteArray power);

    /**
     * @brief outputPowerMainframeQuery Returns the optical output power value set for the modules
     *        Base command: P?
     * @param response Response from instrument - Value set by the P= command (not the power of installed modules)
     * @return true if command was successful
     */
    QByteArray outputPowerMainframeQuery();

    /**
     * @brief setMainframeModSrcTypeCmd Sets the type of modulation source of the OSICS mainframe
     *        Base command: MOD_SRC
     * @param modSrc Type of modulation source - INT (internal) | EXT (external)
     * @return true if command was successful
     */
    void setMainframeModSrcTypeCmd(QByteArray modSrc);

    /**
     * @brief modSrcTypeMainframeQuery Returns the type of digital (TTL) modulation source on the system
     *        Base command: MOD_SRC?
     * @param response Response from instrument - INT (internal) | EXT (external)
     * @return true if command was successful
     */
    QByteArray modSrcTypeMainframeQuery();

    /**
     * @brief setMainframeFrequencyQuery Sets the frequency of the OSICS internal TTL modulation source
     *        Base command: MOD_F=
     * @param frequency Frequency in Hz in the range 123 Hz to 1000000 Hz (1MHz)
     * @return true if command was successful
     */
    void setMainframeFrequencyQuery(QByteArray frequency);

    /**
     * @brief frequencyMainframeQuery Returns the frequency of the OSICS internal digital modulation source in Hz
     *        Base command: MOD_F?
     * @param response Response from instrument - frequency in Hz of internal digital modulation source
     * @return true if command was successful
     */
    QByteArray frequencyMainframeQuery();

    /**
     * @brief saveManframeConfigCmd Saves the current OSICS Mainframe and module config settings to selected memory
     *        Base command: SAVE
     * @param configMemory Memory location to store - STARTUP | A | B | C | D
     * @return true if command was successful
     */
    void saveManframeConfigCmd(QByteArray configMemory);

    /**
     * @brief recallMainframeConfigCmd Loads the selected configuration type
     *        Base command: RECALL
     * @param configMemory Memory location to select - DEFAULT | STARTUP | A | B | C | D
     * @return true if command was successful
     */
    void recallMainframeConfigCmd(QByteArray configMemory);

    /**
     * @brief remoteInterlockMainframeQuery Returns the current state of the remote interlock mode
     *        Base command: INTERLOCK?
     * @param response Response from instrument - 0 (interlock off) | 1 (interlock on)
     * @return true if command was successful
     */
    QByteArray remoteInterlockMainframeQuery();

    /**
     * @brief moduleTypeAtSlotQuery Returns the type of OSICS module installed in channel-slot number #
     *        Base command: PRESENT?
     * @param slotNum Target slot number
     * @param response Response from instrument - type of OSICS module
     *        -1 (empty) | 1 (T100) | 2 (DFB/SLD) | 7 (SWT) | 8 (ATN/BKR) | 10 (TLS)
     * @return true if command was successful
     */
    QByteArray moduleTypeAtSlotQuery(int slotNum);


    // ************************* Shared Module Commands - Optical-Output Control *********************************

    /**
     * @brief disableModuleLaserCmd Disables the laser output of the module
     *        Base command: DISABLE
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void disableModuleLaserCmd(int slotNum);

    /**
     * @brief enableModuleLaserCmd Enables the laser output of the module
     *        Base command: ENABLE
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void enableModuleLaserCmd(int slotNum);

    /**
     * @brief laserStateModuleQuery Returns the state of the laser output control
     *        Base command: ENABLE?
     * @param slotNum Target slot number
     * @param response Response from instrument - ENABLED | DISABLED
     * @return true if command was successful
     */
    QByteArray laserStateModuleQuery(int slotNum);


    // **************************** Shared Module Commands - Unit Selection ***********************************

    /**
     * @brief setModuleSpectralUnitGHzCmd Sets GHz as the spectral unit of the module
     *        Base command: CH#:GHZ
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setModuleSpectralUnitGHzCmd(int slotNum);

    // CH#:NM
    /**
     * @brief setModuleSpectralUnitNMCmd Sets nm as the spectral unit of the module
     *        Base command: CH#:NM
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setModuleSpectralUnitNMCmd(int slotNum);

    /**
     * @brief spectralUnitModuleQuery Returns the set spectral unit of the module
     *        Base command: CH#:NM?
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (unit is GHz) | 1 (unit is nm)
     * @return true if command was successful
     */
    QByteArray spectralUnitModuleQuery(int slotNum);

    /**
     * @brief setModulePowerUnitDBmCmd Sets dBm as the power unit of the module
     *        Base command: CH#:DBM
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setModulePowerUnitDBmCmd(int slotNum);

    /**
     * @brief setModulePowerUnitMWCmd Sets mW as the power unit of the module
     *        Base command: CH#:MW
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setModulePowerUnitMWCmd(int slotNum);

    /**
     * @brief powerUnitModuleQuery Returns the set power unit of the module
     *        Base command: CH#:MW?
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (unit is dBm) | 1 (unit is mW)
     * @return true if command was successful
     */
    QByteArray powerUnitModuleQuery(int slotNum);


    // ************************************* Shared Module Commands - Output Power Setting ************************************

    // CH#:P=
    /**
     * @brief setModuleOutputPowerCmd
     *        Base command: CH#:P=
     * @param slotNum
     * @param power
     * @return 
     */
    void setModuleOutputPowerCmd(int slotNum, QByteArray power);

    // CH#:P?
    /**
     * @brief outputPowerModuleQuery
     *        Base command: CH#:P?
     * @param slotNum
     * @param response
     * @return 
     */
    QByteArray outputPowerModuleQuery(int slotNum);

    // CH#:LIMIT?
    /**
     * @brief outputPowerReachedQuery Retuns the state of the output power
     *        Base command: CH#:LIMIT?
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (power is reached) | 1 (power not reached)
     * @return true if command was successful
     */
    QByteArray outputPowerReachedQuery(int slotNum);


    // *******************  Shared Module Commands - Optical Emission Wavelength/Frequency Setting **************************

    /**
     * @brief setEmissionWavelengthModuleCmd Sets the emission wavelength of the module in nm
     * @param slotNum Target slot number
     * @param wavelength Wavelength in nm to set
     * @return true if command was successful
     */
    void setEmissionWavelengthModuleQuery(int slotNum, QByteArray wavelength);

    /**
     * @brief emissionWavelengthModuleCmd Returns the emission wavelenth of the module in nm
     *        Base command: CH#:L?
     * @param slotNum Target slot number
     * @param response Response from instrument - emission wavelength in nm
     * @return true if command was successful
     */
    QByteArray emissionWavelengthModuleCmd(int slotNum);

    /**
     * @brief setRefWavelengthModuleCmd Sets the reference wavelength to one of two factory calibrations
     *        Base command: CH#:L
     * @param slotNum Target slot number
     * @param wavelengthNum Either 1 (first wavelength value) or 2 (second wavelength value)
     * @return true if command was successful
     */
    void setRefWavelengthModuleCmd(int slotNum, QByteArray wavelengthNum);

    /**
     * @brief refWavelengthModuleQuery Returns the number of the wavelength used (1 or 2)
     *        Base command: CH#:L?
     * @param slotNum Target slot number
     * @param response Response from instrument - Either 1 | 2
     * @return true if command was successful
     */
    QByteArray refWavelengthModuleQuery(int slotNum);

    /**
     * @brief setFrequencyModuleCmd Sets the emission frequency of the module in GHz
     *        Base command: CH#:F=
     * @param slotNum Target slot number
     * @param frequency Frequency to set on module
     * @return true if command was successful
     */
    void setFrequencyModuleCmd(int slotNum, QByteArray frequency);

    /**
     * @brief frequencyModuleQuery Returns the emission frequency of the module in GHz
     *        Base command: CH#:F?
     * @param slotNum Target slot number
     * @param response Response from instrument - the emission frequency in GHz
     * @return true if command was successful
     */
    QByteArray frequencyModuleQuery(int slotNum);

    /**
     * @brief enableCoherenceControlCmd Enables/disables the Coherence Control function
     *        Base command: CH#:CTRL
     * @param slotNum Target slot number
     * @param setting OFF (disable function) | ON (enable function)
     * @return true if command was successful
     */
    void enableCoherenceControlCmd(int slotNum, QByteArray setting);

    /**
     * @brief coherenceControlEnabledQuery Returns the state of the Coherence Control function (0 or 1)
     *        Base command: CH#:CTRL?
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (coherence control off) | 1 (coherence control on)
     * @return true if command was successful
     */
    QByteArray coherenceControlEnabledQuery(int slotNum);

    /**
     * @brief enableAutoPeakFindControlCmd Enables/disables the Auto-peak Find function
     *        Base command: CH#:APF
     * @param slotNum Target slot number
     * @param setting OFF (disable function | ON (enable function)
     * @return true if command was successful
     */
    void enableAutoPeakFindControlCmd(int slotNum, QByteArray setting);

    /**
     * @brief autoPeakFindControlQuery Returns the state of the Auto-peak Find function (0 or 1)
     *        Base command: CH#:APF?
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (function is off) | 1 (function is on)
     * @return true if command was successful
     */
    QByteArray autoPeakFindControlQuery(int slotNum);


    // ****************************** Shared Module Commands - Modulation Control *******************************

    /**
     * @brief setModuleModulationCtrlCmd Sets the digital modulation of the module optical signal
     *        Base command: CH#:MOD_CTRL
     * @param slotNum Target slot number
     * @param setting OFF (digital modulation is off) | ON (digital modulation on) | ON_INV (reversed digital modulation)
     * @return true if command was successful
     */
    void setModuleModulationCtrlCmd(int slotNum, QByteArray setting);

    /**
     * @brief moduleModulationCtrlQuery Returns the selected modulation activation state
     *        Base command: CH#:MOD_CTRL?
     * @param slotNum Target slot number
     * @param response Response from instrument - Either OFF | ON | ON_INV
     * @return true if command was successful
     */
    QByteArray moduleModulationCtrlQuery(int slotNum);

    /**
     * @brief setModuleModulationSrcCmd Sets the type of modulation source of the module
     *        Base command: CH#:MOD_SRC
     * @param slotNum Target slot number
     * @param setting Either MAIN to set to mainframe or INT to set to internal
     * @return true if command was successful
     */
    void setModuleModulationSrcCmd(int slotNum, QByteArray setting);

    /**
     * @brief moduleModulationSrcQuery Returns the selected modulation source
     *        Base command: CH#:MOD_SRC?
     * @param slotNum Target slot number
     * @param response Response from instrument - Either INT | MAIN
     * @return
     */
    QByteArray moduleModulationSrcQuery(int slotNum);


    // ************************ Shared Module Commands - Module System-Version Info ****************************

    /**
     * @brief softwareVersionModuleQuery Returns the software version of the module
     *        Base command: CH#:FIRM?
     * @param slotNum Target slot number
     * @param response Response from instrument - the software version of the module
     * @return true if command was successful
     */
    QByteArray softwareVersionModuleQuery(int slotNum);

    /**
     * @brief identificationModuleQuery Returns info about the module (company name, module, serial num, software version)
     *        Base command: CH:*IDN?
     * @param slotNum Target slot number
     * @param response Response from instrument - company name, module, serian num, software version)
     * @return true if command was successful
     */
    QByteArray identificationModuleQuery(int slotNum);

    /**
     * @brief typeOfModuleQuery Returns info about the module's type, version and options.
     *        Base command: CH#:TYPE?
     * @param slotNum Target slot number
     * @param response Response from instrument - module type, version, options
     * @return true if command was successful
     */
    QByteArray typeOfModuleQuery(int slotNum);


    // *********** Functions for Applying/Updating Config Settings **********

    void applyConfigSettings(QSettings &configSettings);
    void updateConfig(QSettings &configSettings);
    void updateInstalledModules(QSettings &configSettings);
    QVariant getModuleAtSlot(int slotNum);
    QMainWindow* getWindowForModuleAtSlot(int slotNum);
    QList<QByteArray> getModuleTypeNames();
    QMap<int, QVariant> getModuleSlotQVariantMap();

public slots:
    void slotSetupEXFOModules();

signals:
    void signalGetEXFOModuleQVariants(QMap<int, QVariant> &modules, QVariant &device);

protected:

    // ********************************** Helper Methods *************************************

    /**
     * @brief appendParamToCmdWithSpace Appends a parameter to the the end of a command with an additional space character.
     * @param command Command to modify
     * @param param Param to append to command
     */
    QByteArray appendParamToCmdWithSpace(QByteArray command, QByteArray param);

    /**
     * @brief appendParamToCmdNoSpace Appends a parameter to the end of a command with no space characters.
     * @param command Command to modify
     * @param param Param to append to command
     */
    QByteArray appendParamToCmdNoSpace(QByteArray command, QByteArray param);

    /**
     * @brief insertSlotNum Inserts the slot number of a device to a base command.
     * @param command Command to modify
     * @param slotNum Slot number to insert into command
     */
    QByteArray insertSlotNum(QByteArray command, int slotNum);


private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

    // map of slot numbers to modules installed in chassis
    QMap<int, QVariant> modules;

    // list of module names
    QList<QByteArray> moduleNames;

    void setupModuleTypesList();

};

#endif // EXFO_OSICS_MAINFRAME_H
