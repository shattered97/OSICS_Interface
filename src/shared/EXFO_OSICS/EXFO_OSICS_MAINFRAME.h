#ifndef EXFO_OSICS_MAINFRAME_H
#define EXFO_OSICS_MAINFRAME_H

#include "DefaultInstrument.h"

class EXFO_OSICS_MAINFRAME : protected DefaultInstrument
{
public:
    EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc);

    // ******************************* Mainframe Commands Only  *******************************

    // DISABLE
    bool disableMainframeLaserCmd(ViSession &defaultSession, ViSession &instrSession);

    // ENABLE
    bool enableMainframeLaserCmd(ViSession &defaultSession, ViSession &instrSession);

    // ENABLE?
    bool laserStateMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // GHZ
    bool setMainframeSpectralUnitGHzCmd(ViSession &defaultSession, ViSession &instrSession);

    // NM
    bool setMainframeSpectralUnitNMCmd(ViSession &defaultSession, ViSession &instrSession);

    // NM?
    bool spectralUnitMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // DBM
    bool setMainframePowerUnitDBmCmd(ViSession &defaultSession, ViSession &instrSession);

    // MW
    bool setMainframePowerUnitMWCmd(ViSession &defaultSession, ViSession &instrSession);

    // MW?
    bool powerUnitMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // P=
    bool setMainframeOutputPowerCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &power);

    // P?
    bool outputPowerMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // MOD_SRC
    bool setMainframeModSrcTypeCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &modSrc);

    // MOD_SRC?
    bool modSrcTypeMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // MOD_F=
    bool setMainframeFrequencyQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &frequency);

    // MOD_F?
    bool frequencyMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // SAVE
    bool saveManframeConfigCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &configMemory);

    // RECALL
    bool recallMainframeConfigCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &configMemory);

    // INTERLOCK?
    bool remoteInterlockMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    // PRESENT?
    bool moduleTypeAtSlotQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // ************************* Shared Module Commands - Optical-Output Control *********************************

    // CH#:DISABLE
    bool disableModuleLaserCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:ENABLE
    bool enableModuleLaserCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:ENABLE?
    bool laserStateModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // **************************** Shared Module Commands - Unit Selection ***********************************

    // CH#:GHZ
    bool setModuleSpectralUnitGHzCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:NM
    bool setModuleSpectralUnitNMCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:NM?
    bool spectralUnitModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:DBM
    bool setModulePowerUnitDBmCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:MW
    bool setModulePowerUnitMWCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum);

    // CH#:MW?
    bool powerUnitModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // ************************************* Shared Module Commands - Output Power Setting ************************************

    // CH#:P=
    bool setModuleOutputPowerCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power);

    // CH#:P?
    bool outputPowerModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:LIMIT?
    bool outputPowerReachedQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // *******************  Shared Module Commands - Optical Emission Wavelength/Frequency Setting **************************

    // CH#:L=
    bool setRefWavelengthModuleCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelengthNum);

    // CH#:L?
    bool refWavelengthModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelengthNum, QByteArray &response);

    // CH#:F=
    bool setFrequencyModuleCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &frequency);

    // CH#:F?
    bool frequencyModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:CTRL
    bool enableCoherenceControlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting);

    // CH#:CTRL?
    bool coherenceControlEnabledQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:APF
    bool enableAutoPeakFindControlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting);

    // CH#:APF?
    bool autoPeakFindControlQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // ****************************** Shared Module Commands - Modulation Control *******************************

    // CH#:MOD_CTRL
    bool setModuleModulationCtrlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting);

    // CH#:MOD_CTRL?
    bool moduleModulationCtrlQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:MOD_SRC
    bool setModuleModulationSrcCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting);

    // CH#:MOD_SRC?
    bool moduleModulationSrcQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


    // ************************ Shared Module Commands - Module System-Version Info ****************************

    // CH#:FIRM?
    bool softwareVersionModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:*IDN?
    bool identificationModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);

    // CH#:TYPE?
    bool typeOfModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response);


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
