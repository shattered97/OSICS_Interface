#ifndef EXFO_OSICS_MAINFRAME_H
#define EXFO_OSICS_MAINFRAME_H

#include "DefaultInstrument.h"

class EXFO_OSICS_MAINFRAME : protected DefaultInstrument
{
public:
    EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc);

    // ******************************* Mainframe Commands Only  *******************************

    /**
     * @brief disableMainframeLaserCmd Disables the laser output on all OSICS modules
     *        Base command: DISABLE
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool disableMainframeLaserCmd(ViSession &defaultSession);

    /**
     * @brief enableMainframeLaserCmd Enables the laser output on all OSICS modules
     *        Base command: ENABLE
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool enableMainframeLaserCmd(ViSession &defaultSession);

    /**
     * @brief laserStateMainframeQuery Returns the current state of the OSICS laser output master control
     *        Base command: ENABLE?
     * @param defaultSession Default communication session
     * @param response Response from instrument - ENABLED | DISABLED
     * @return true if command was successful
     */
    bool laserStateMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief setMainframeSpectralUnitGHzCmd Sets the frequency in GHz as the spectral unit on OSICS system
     *        Base command: GHZ
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool setMainframeSpectralUnitGHzCmd(ViSession &defaultSession);

    /**
     * @brief setMainframeSpectralUnitNMCmd Sets the wavelength in nm as the spectral unit on OSICS system
     *        Base command: NM
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool setMainframeSpectralUnitNMCmd(ViSession &defaultSession);

    /**
     * @brief spectralUnitMainframeQuery Returns the current spectral unit used on the OSICS system
     *        Base command: NM?
     * @param defaultSession Default communication session
     * @param response Response from instrument - 0 (spectral unit is nm) | 1 (spectral unit is GHz)
     * @return true if command was successful
     */
    bool spectralUnitMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief setMainframePowerUnitDBmCmd Sets dBm as the power unit on all modules
     *        Base command: DBM
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool setMainframePowerUnitDBmCmd(ViSession &defaultSession);

    /**
     * @brief setMainframePowerUnitMWCmd Sets mW as the power unit on all modules
     *        Base command: MW
     * @param defaultSession Default communication session
     * @return true if command was successful
     */
    bool setMainframePowerUnitMWCmd(ViSession &defaultSession);

    /**
     * @brief powerUnitMainframeQuery Returns the current power unit used on the OSICS system
     *        Base command: MW?
     * @param defaultSession Default communication session
     * @param response Response from instrument - 0 (power is in dBm) | 1 (power is in mW)
     * @return true if command was successful
     */
    bool powerUnitMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief setMainframeOutputPowerCmd Sets the optical output power of all modules to the same value
     *        Base command: P=
     * @param defaultSession Default communication session
     * @param power Output power to set (in mW or dBm depending on set unit)
     * @return true if command was successful
     */
    bool setMainframeOutputPowerCmd(ViSession &defaultSession, QByteArray &power);

    /**
     * @brief outputPowerMainframeQuery Returns the optical output power value set for the modules
     *        Base command: P?
     * @param defaultSession Default communication session
     * @param response Response from instrument - Value set by the P= command (not the power of installed modules)
     * @return true if command was successful
     */
    bool outputPowerMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief setMainframeModSrcTypeCmd Sets the type of modulation source of the OSICS mainframe
     *        Base command: MOD_SRC
     * @param defaultSession Default communication session
     * @param modSrc Type of modulation source - INT (internal) | EXT (external)
     * @return true if command was successful
     */
    bool setMainframeModSrcTypeCmd(ViSession &defaultSession, QByteArray &modSrc);

    /**
     * @brief modSrcTypeMainframeQuery Returns the type of digital (TTL) modulation source on the system
     *        Base command: MOD_SRC?
     * @param defaultSession Default communication session
     * @param response Response from instrument - INT (internal) | EXT (external)
     * @return true if command was successful
     */
    bool modSrcTypeMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief setMainframeFrequencyQuery Sets the frequency of the OSICS internal TTL modulation source
     *        Base command: MOD_F=
     * @param defaultSession Default communication session
     * @param frequency Frequency in Hz in the range 123 Hz to 1000000 Hz (1MHz)
     * @return true if command was successful
     */
    bool setMainframeFrequencyQuery(ViSession &defaultSession, QByteArray &frequency);

    /**
     * @brief frequencyMainframeQuery Returns the frequency of the OSICS internal digital modulation source in Hz
     *        Base command: MOD_F?
     * @param defaultSession Default communication session
     * @param response Response from instrument - frequency in Hz of internal digital modulation source
     * @return true if command was successful
     */
    bool frequencyMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief saveManframeConfigCmd Saves the current OSICS Mainframe and module config settings to selected memory
     *        Base command: SAVE
     * @param defaultSession Default communication session
     * @param configMemory Memory location to store - STARTUP | A | B | C | D
     * @return true if command was successful
     */
    bool saveManframeConfigCmd(ViSession &defaultSession, QByteArray &configMemory);

    /**
     * @brief recallMainframeConfigCmd Loads the selected configuration type
     *        Base command: RECALL
     * @param defaultSession Default communication session
     * @param configMemory Memory location to select - DEFAULT | STARTUP | A | B | C | D
     * @return true if command was successful
     */
    bool recallMainframeConfigCmd(ViSession &defaultSession, QByteArray &configMemory);

    /**
     * @brief remoteInterlockMainframeQuery Returns the current state of the remote interlock mode
     *        Base command: INTERLOCK?
     * @param defaultSession Default communication session
     * @param response Response from instrument - 0 (interlock off) | 1 (interlock on)
     * @return true if command was successful
     */
    bool remoteInterlockMainframeQuery(ViSession &defaultSession, QByteArray &response);

    /**
     * @brief moduleTypeAtSlotQuery Returns the type of OSICS module installed in channel-slot number #
     *        Base command: PRESENT?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - type of OSICS module
     *        -1 (empty) | 1 (T100) | 2 (DFB/SLD) | 7 (SWT) | 8 (ATN/BKR) | 10 (TLS)
     * @return true if command was successful
     */
    bool moduleTypeAtSlotQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************* Shared Module Commands - Optical-Output Control *********************************

    /**
     * @brief disableModuleLaserCmd Disables the laser output of the module
     *        Base command: DISABLE
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool disableModuleLaserCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief enableModuleLaserCmd Enables the laser output of the module
     *        Base command: ENABLE
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool enableModuleLaserCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief laserStateModuleQuery Returns the state of the laser output control
     *        Base command: ENABLE?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - ENABLED | DISABLED
     * @return true if command was successful
     */
    bool laserStateModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // **************************** Shared Module Commands - Unit Selection ***********************************

    /**
     * @brief setModuleSpectralUnitGHzCmd Sets GHz as the spectral unit of the module
     *        Base command: CH#:GHZ
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setModuleSpectralUnitGHzCmd(ViSession &defaultSession, int slotNum);

    // CH#:NM
    /**
     * @brief setModuleSpectralUnitNMCmd Sets nm as the spectral unit of the module
     *        Base command: CH#:NM
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setModuleSpectralUnitNMCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief spectralUnitModuleQuery Returns the set spectral unit of the module
     *        Base command: CH#:NM?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (unit is GHz) | 1 (unit is nm)
     * @return true if command was successful
     */
    bool spectralUnitModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setModulePowerUnitDBmCmd Sets dBm as the power unit of the module
     *        Base command: CH#:DBM
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setModulePowerUnitDBmCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief setModulePowerUnitMWCmd Sets mW as the power unit of the module
     *        Base command: CH#:MW
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setModulePowerUnitMWCmd(ViSession &defaultSession, int slotNum);

    /**
     * @brief powerUnitModuleQuery Returns the set power unit of the module
     *        Base command: CH#:MW?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (unit is dBm) | 1 (unit is mW)
     * @return true if command was successful
     */
    bool powerUnitModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************************* Shared Module Commands - Output Power Setting ************************************

    /**
     * @brief setModuleOutputPowerCmd Sets the optical output power of the module depending on selected power unit
     *        Base command: CH#:P=
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param power Optical output power in dBm or mW
     * @return true if command was successful
     */
    bool setModuleOutputPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power);

    /**
     * @brief outputPowerModuleQuery Returns the current value of the output power according to selected unit
     *        Base command: CH#:P?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Output power in mW or dBm | Disabled (optical output is disabled)
     * @return true if command was successful
     */
    bool outputPowerModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief outputPowerReachedQuery Retuns the state of the output power
     *        Base command: CH#:LIMIT?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (power is reached) | 1 (power not reached)
     * @return true if command was successful
     */
    bool outputPowerReachedQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // *******************  Shared Module Commands - Optical Emission Wavelength/Frequency Setting **************************

    /**
     * @brief setEmissionWavelengthModuleCmd Sets the emission wavelength of the module in nm
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelength Wavelength in nm to set
     * @return true if command was successful
     */
    bool setEmissionWavelengthModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &wavelength);

    /**
     * @brief emissionWavelengthModuleCmd Returns the emission wavelenth of the module in nm
     *        Base command: CH#:L?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - emission wavelength in nm
     * @return true if command was successful
     */
    bool emissionWavelengthModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setRefWavelengthModuleCmd Sets the reference wavelength to one of two factory calibrations
     *        Base command: CH#:L
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param wavelengthNum Either 1 (first wavelength value) or 2 (second wavelength value)
     * @return true if command was successful
     */
    bool setRefWavelengthModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelengthNum);

    /**
     * @brief refWavelengthModuleQuery Returns the number of the wavelength used (1 or 2)
     *        Base command: CH#:L?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Either 1 | 2
     * @return true if command was successful
     */
    bool refWavelengthModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setFrequencyModuleCmd Sets the emission frequency of the module in GHz
     *        Base command: CH#:F=
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param frequency Frequency to set on module
     * @return true if command was successful
     */
    bool setFrequencyModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &frequency);

    /**
     * @brief frequencyModuleQuery Returns the emission frequency of the module in GHz
     *        Base command: CH#:F?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - the emission frequency in GHz
     * @return true if command was successful
     */
    bool frequencyModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief enableCoherenceControlCmd Enables/disables the Coherence Control function
     *        Base command: CH#:CTRL
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param setting OFF (disable function) | ON (enable function)
     * @return true if command was successful
     */
    bool enableCoherenceControlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    /**
     * @brief coherenceControlEnabledQuery Returns the state of the Coherence Control function (0 or 1)
     *        Base command: CH#:CTRL?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (coherence control off) | 1 (coherence control on)
     * @return true if command was successful
     */
    bool coherenceControlEnabledQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief enableAutoPeakFindControlCmd Enables/disables the Auto-peak Find function
     *        Base command: CH#:APF
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param setting OFF (disable function | ON (enable function)
     * @return true if command was successful
     */
    bool enableAutoPeakFindControlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    /**
     * @brief autoPeakFindControlQuery Returns the state of the Auto-peak Find function (0 or 1)
     *        Base command: CH#:APF?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - 0 (function is off) | 1 (function is on)
     * @return true if command was successful
     */
    bool autoPeakFindControlQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ****************************** Shared Module Commands - Modulation Control *******************************

    /**
     * @brief setModuleModulationCtrlCmd Sets the digital modulation of the module optical signal
     *        Base command: CH#:MOD_CTRL
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param setting OFF (digital modulation is off) | ON (digital modulation on) | ON_INV (reversed digital modulation)
     * @return true if command was successful
     */
    bool setModuleModulationCtrlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    /**
     * @brief moduleModulationCtrlQuery Returns the selected modulation activation state
     *        Base command: CH#:MOD_CTRL?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Either OFF | ON | ON_INV
     * @return true if command was successful
     */
    bool moduleModulationCtrlQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setModuleModulationSrcCmd Sets the type of modulation source of the module
     *        Base command: CH#:MOD_SRC
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param setting Either MAIN to set to mainframe or INT to set to internal
     * @return true if command was successful
     */
    bool setModuleModulationSrcCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    /**
     * @brief moduleModulationSrcQuery Returns the selected modulation source
     *        Base command: CH#:MOD_SRC?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Either INT | MAIN
     * @return true if command was successful
     */
    bool moduleModulationSrcQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************ Shared Module Commands - Module System-Version Info ****************************

    /**
     * @brief softwareVersionModuleQuery Returns the software version of the module
     *        Base command: CH#:FIRM?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - the software version of the module
     * @return true if command was successful
     */
    bool softwareVersionModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief identificationModuleQuery Returns info about the module (company name, module, serial num, software version)
     *        Base command: CH:*IDN?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - company name, module, serian num, software version)
     * @return true if command was successful
     */
    bool identificationModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief typeOfModuleQuery Returns info about the module's type, version and options.
     *        Base command: CH#:TYPE?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - module type, version, options
     * @return true if command was successful
     */
    bool typeOfModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


protected:

    // ********************************** Helper Methods *************************************

    /**
     * @brief appendParamToCmdWithSpace Appends a parameter to the the end of a command with an additional space character.
     * @param command Command to modify
     * @param param Param to append to command
     */
    void appendParamToCmdWithSpace(QByteArray &command, QByteArray param);

    /**
     * @brief appendParamToCmdNoSpace Appends a parameter to the end of a command with no space characters.
     * @param command Command to modify
     * @param param Param to append to command
     */
    void appendParamToCmdNoSpace(QByteArray &command, QByteArray param);

    /**
     * @brief insertSlotNum Inserts the slot number of a device to a base command.
     * @param command Command to modify
     * @param slotNum Slot number to insert into command
     */
    void insertSlotNum(QByteArray &command, int slotNum);

private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;
};

#endif // EXFO_OSICS_MAINFRAME_H
