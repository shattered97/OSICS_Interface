#ifndef EXFO_OSICS_MAINFRAME_H
#define EXFO_OSICS_MAINFRAME_H

#include "DefaultInstrument.h"

class EXFO_OSICS_MAINFRAME : protected DefaultInstrument
{
public:
    EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc);

    // ******************************* Mainframe Commands Only  *******************************

    // DISABLE
    bool disableMainframeLaserCmd(ViSession &defaultSession);

    // ENABLE
    bool enableMainframeLaserCmd(ViSession &defaultSession);

    // ENABLE?
    bool laserStateMainframeQuery(ViSession &defaultSession, QByteArray &response);

    // GHZ
    bool setMainframeSpectralUnitGHzCmd(ViSession &defaultSession);

    // NM
    bool setMainframeSpectralUnitNMCmd(ViSession &defaultSession);

    // NM?
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

    // CH#:L=
    bool setRefWavelengthModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelengthNum);

    // CH#:L?
    bool refWavelengthModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &wavelengthNum, QByteArray &response);

    // CH#:F=
    bool setFrequencyModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &frequency);

    // CH#:F?
    bool frequencyModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:CTRL
    bool enableCoherenceControlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    // CH#:CTRL?
    bool coherenceControlEnabledQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:APF
    bool enableAutoPeakFindControlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    // CH#:APF?
    bool autoPeakFindControlQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ****************************** Shared Module Commands - Modulation Control *******************************

    // CH#:MOD_CTRL
    bool setModuleModulationCtrlCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    // CH#:MOD_CTRL?
    bool moduleModulationCtrlQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:MOD_SRC
    bool setModuleModulationSrcCmd(ViSession &defaultSession, int slotNum, QByteArray &setting);

    // CH#:MOD_SRC?
    bool moduleModulationSrcQuery(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ************************ Shared Module Commands - Module System-Version Info ****************************

    // CH#:FIRM?
    bool softwareVersionModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:*IDN?
    bool identificationModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:TYPE?
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
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

};

#endif // EXFO_OSICS_MAINFRAME_H
