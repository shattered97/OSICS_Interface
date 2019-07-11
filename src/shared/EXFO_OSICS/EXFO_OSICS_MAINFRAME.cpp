#include "EXFO_OSICS_MAINFRAME.h"

EXFO_OSICS_MAINFRAME::EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc)
{
    this->setInstrIdentity(theIdentity);
    this->setInstrLocation(theInstrLoc);
}

bool EXFO_OSICS_MAINFRAME::disableMainframeLaserCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "DISABLE\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::enableMainframeLaserCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "ENABLE\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::laserStateMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "ENABLE?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);

}

bool EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitGHzCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "GHZ\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitNMCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "NM\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::spectralUnitMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "NM?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::setMainframePowerUnitDBmCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "DBM\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::setMainframePowerUnitMWCmd(ViSession &defaultSession, ViSession &instrSession){
    QByteArray baseCmd = "MW\n";

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::powerUnitMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "MW?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::setMainframeOutputPowerCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &power){
    QByteArray baseCmd = "P=\n";
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::outputPowerMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "P?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::setMainframeModSrcTypeCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &modSrc){
    QByteArray baseCmd = "MOD_SRC\n";
    appendParamToCmdWithSpace(baseCmd, modSrc);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::modSrcTypeMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "MOD_SRC?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::setMainframeFrequencyQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &frequency){
    QByteArray baseCmd = "MOD_F=\n";
    appendParamToCmdNoSpace(baseCmd, frequency);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::frequencyMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "MOD_F?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::saveManframeConfigCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &configMemory){
    QByteArray baseCmd = "SAVE\n";
    appendParamToCmdWithSpace(baseCmd, configMemory);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::recallMainframeConfigCmd(ViSession &defaultSession, ViSession &instrSession, QByteArray &configMemory){
    QByteArray baseCmd = "RECALL\n";
    appendParamToCmdWithSpace(baseCmd, configMemory);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}


bool EXFO_OSICS_MAINFRAME::remoteInterlockMainframeQuery(ViSession &defaultSession, ViSession &instrSession, QByteArray &response){
    QByteArray baseCmd = "INTERLOCK?\n";

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


bool EXFO_OSICS_MAINFRAME::moduleTypeAtSlotQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "PRESENT?\n";
    QByteArray param;
    param.setNum(slotNum);
    appendParamToCmdWithSpace(baseCmd, param);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


// ********** Shared Module Commands ***********


bool EXFO_OSICS_MAINFRAME::setModuleSpectralUnitGHzCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:GHZ\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

bool EXFO_OSICS_MAINFRAME::setModuleSpectralUnitNMCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:NM\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

bool EXFO_OSICS_MAINFRAME::spectralUnitModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:NM?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Wavelength Setting *********

bool EXFO_OSICS_MAINFRAME::setRefWavelengthModuleCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelengthNum){
    QByteArray baseCmd = "CH#:L=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

bool EXFO_OSICS_MAINFRAME::refWavelengthModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelengthNum, QByteArray &response){
    QByteArray baseCmd = "CH#:L?\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Module System-Version Info ********

bool EXFO_OSICS_MAINFRAME::softwareVersionModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:FIRM?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

bool EXFO_OSICS_MAINFRAME::identificationModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:*IDN?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

bool EXFO_OSICS_MAINFRAME::typeOfModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:TYPE?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


// ******** Optical-Output Control ********

// CH#:DISABLE
bool EXFO_OSICS_MAINFRAME::disableModuleLaserCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:DISABLE\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:ENABLE
bool EXFO_OSICS_MAINFRAME::enableModuleLaserCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:ENABLE\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:ENABLE?
bool EXFO_OSICS_MAINFRAME::laserStateModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:ENABLE?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Unit Selection *********


// CH#:DBM
bool EXFO_OSICS_MAINFRAME::setModulePowerUnitDBmCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:DBM\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MW
bool EXFO_OSICS_MAINFRAME::setModulePowerUnitMWCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:MW\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MW?
bool EXFO_OSICS_MAINFRAME::powerUnitModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MW?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Output Power Setting *******

// CH#:P=
bool EXFO_OSICS_MAINFRAME::setModuleOutputPowerCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#:P=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:P?
bool EXFO_OSICS_MAINFRAME::outputPowerModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:P?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:LIMIT?
bool EXFO_OSICS_MAINFRAME::outputPowerReachedQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LIMIT?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Optical Emission Wavelength/Frequency Setting *********


// CH#:F=
bool EXFO_OSICS_MAINFRAME::setFrequencyModuleCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &frequency){
    QByteArray baseCmd = "CH#:F=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, frequency);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:F?
bool EXFO_OSICS_MAINFRAME::frequencyModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:F?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:CTRL
bool EXFO_OSICS_MAINFRAME::enableCoherenceControlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:CTRL\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:CTRL?
bool EXFO_OSICS_MAINFRAME::coherenceControlEnabledQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:CTRL?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:APF
bool EXFO_OSICS_MAINFRAME::enableAutoPeakFindControlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:APF\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:APF?
bool EXFO_OSICS_MAINFRAME::autoPeakFindControlQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:APF?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ******** Modulation Control *********

// CH#:MOD_CTRL
bool EXFO_OSICS_MAINFRAME::setModuleModulationCtrlCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:MOD_CTRL\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MOD_CTRL?
bool EXFO_OSICS_MAINFRAME::moduleModulationCtrlQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_CTRL?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:MOD_SRC
bool EXFO_OSICS_MAINFRAME::setModuleModulationSrcCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:MOD_SRC\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MOD_SRC?
bool EXFO_OSICS_MAINFRAME::moduleModulationSrcQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_SRC?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}


// ************ Helper Functions ************

void EXFO_OSICS_MAINFRAME::appendParamToCmdWithSpace(QByteArray &command, QByteArray param){
    param.prepend(" ");
    command.insert(command.indexOf('\n'), param);
}

void EXFO_OSICS_MAINFRAME::appendParamToCmdNoSpace(QByteArray &command, QByteArray param){
    command.insert(command.indexOf('\n'), param);
}

void EXFO_OSICS_MAINFRAME::insertSlotNum(QByteArray &command, int slotNum){
    QByteArray convertedSlotNum;
    convertedSlotNum.setNum(slotNum);
    command.insert(command.indexOf('#'), convertedSlotNum);
}
