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

    // DBM
    bool setMainframePowerUnitDBmCmd(ViSession &defaultSession);

    // MW
    bool setMainframePowerUnitMWCmd(ViSession &defaultSession);

    // MW?
    bool powerUnitMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // P=
    bool setMainframeOutputPowerCmd(ViSession &defaultSession, QByteArray &power);

    // P?
    bool outputPowerMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // MOD_SRC
    bool setMainframeModSrcTypeCmd(ViSession &defaultSession, QByteArray &modSrc);

    // MOD_SRC?
    bool modSrcTypeMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // MOD_F=
    bool setMainframeFrequencyQuery(ViSession &defaultSession, QByteArray &frequency);

    // MOD_F?
    bool frequencyMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // SAVE
    bool saveManframeConfigCmd(ViSession &defaultSession, QByteArray &configMemory);

    // RECALL
    bool recallMainframeConfigCmd(ViSession &defaultSession, QByteArray &configMemory);

    // INTERLOCK?
    bool remoteInterlockMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // PRESENT?
    bool moduleTypeAtSlotQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************* Shared Module Commands - Optical-Output Control *********************************

    // CH#:DISABLE
    bool disableModuleLaserCmd(ViSession &defaultSession, int slotNum);

    // CH#:ENABLE
    bool enableModuleLaserCmd(ViSession &defaultSession, int slotNum);

    // CH#:ENABLE?
    bool laserStateModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // **************************** Shared Module Commands - Unit Selection ***********************************

    // CH#:GHZ
    bool setModuleSpectralUnitGHzCmd(ViSession &defaultSession, int slotNum);

    // CH#:NM
    bool setModuleSpectralUnitNMCmd(ViSession &defaultSession, int slotNum);

    // CH#:NM?
    bool spectralUnitModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:DBM
    bool setModulePowerUnitDBmCmd(ViSession &defaultSession, int slotNum);

    // CH#:MW
    bool setModulePowerUnitMWCmd(ViSession &defaultSession, int slotNum);

    // CH#:MW?
    bool powerUnitModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************************* Shared Module Commands - Output Power Setting ************************************

    // CH#:P=
    bool setModuleOutputPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power);

    // CH#:P?
    bool outputPowerModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:LIMIT?
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
     * @return
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
