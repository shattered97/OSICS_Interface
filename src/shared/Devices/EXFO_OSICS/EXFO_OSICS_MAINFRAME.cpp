#include "EXFO_OSICS_MAINFRAME.h"

EXFO_OSICS_MAINFRAME::EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;

}

void EXFO_OSICS_MAINFRAME::slotSetupEXFOModules(){
    qDebug() << "slotSetupEXFOModules()";

    setupModuleTypesList();

    QVariant exfoVariant = QVariant::fromValue(this);
    QObject::connect(this, SIGNAL(signalGetEXFOModuleQVariants(QMap<int, QVariant> &, QVariant &)),
                     QObject::sender(), SLOT(slotGetEXFOModuleQVariants(QMap<int, QVariant> &, QVariant &)));
    emit signalGetEXFOModuleQVariants(modules, exfoVariant);

}

void EXFO_OSICS_MAINFRAME::disableMainframeLaserCmd(){
    QByteArray baseCmd = "DISABLE\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::enableMainframeLaserCmd(){
    QByteArray baseCmd = "ENABLE\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::laserStateMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "ENABLE?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);

}

void EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitGHzCmd(){
    QByteArray baseCmd = "GHZ\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitNMCmd(){
    QByteArray baseCmd = "NM\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::spectralUnitMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "NM?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::setMainframePowerUnitDBmCmd(){
    QByteArray baseCmd = "DBM\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::setMainframePowerUnitMWCmd(){
    QByteArray baseCmd = "MW\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::powerUnitMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "MW?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::setMainframeOutputPowerCmd(QByteArray &power){
    QByteArray baseCmd = "P=\n";
    appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::outputPowerMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "P?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::setMainframeModSrcTypeCmd(QByteArray &modSrc){
    QByteArray baseCmd = "MOD_SRC\n";
    appendParamToCmdWithSpace(baseCmd, modSrc);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::modSrcTypeMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "MOD_SRC?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::setMainframeFrequencyQuery(QByteArray &frequency){
    QByteArray baseCmd = "MOD_F=\n";
    appendParamToCmdNoSpace(baseCmd, frequency);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::frequencyMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "MOD_F?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::saveManframeConfigCmd(QByteArray &configMemory){
    QByteArray baseCmd = "SAVE\n";
    appendParamToCmdWithSpace(baseCmd, configMemory);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::recallMainframeConfigCmd(QByteArray &configMemory){
    QByteArray baseCmd = "RECALL\n";
    appendParamToCmdWithSpace(baseCmd, configMemory);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::remoteInterlockMainframeQuery(QByteArray &response){
    QByteArray baseCmd = "INTERLOCK?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


void EXFO_OSICS_MAINFRAME::moduleTypeAtSlotQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "PRESENT?\n";
    QByteArray param;
    param.setNum(slotNum);
    appendParamToCmdWithSpace(baseCmd, param);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


// ********** Shared Module Commands ***********


void EXFO_OSICS_MAINFRAME::setModuleSpectralUnitGHzCmd(int slotNum){
    QByteArray baseCmd = "CH#:GHZ\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_MAINFRAME::setModuleSpectralUnitNMCmd(int slotNum){
    QByteArray baseCmd = "CH#:NM\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_MAINFRAME::spectralUnitModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:NM?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Wavelength Setting *********

void EXFO_OSICS_MAINFRAME::setRefWavelengthModuleCmd(int slotNum, QByteArray &wavelengthNum){
    QByteArray baseCmd = "CH#:L\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_MAINFRAME::refWavelengthModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:L?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Module System-Version Info ********

void EXFO_OSICS_MAINFRAME::softwareVersionModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:FIRM?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

void EXFO_OSICS_MAINFRAME::identificationModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:*IDN?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

void EXFO_OSICS_MAINFRAME::typeOfModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:TYPE?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}


// ******** Optical-Output Control ********

// CH#:DISABLE
void EXFO_OSICS_MAINFRAME::disableModuleLaserCmd(int slotNum){
    QByteArray baseCmd = "CH#:DISABLE\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:ENABLE
void EXFO_OSICS_MAINFRAME::enableModuleLaserCmd(int slotNum){
    QByteArray baseCmd = "CH#:ENABLE\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:ENABLE?
void EXFO_OSICS_MAINFRAME::laserStateModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:ENABLE?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Unit Selection *********


// CH#:DBM
void EXFO_OSICS_MAINFRAME::setModulePowerUnitDBmCmd(int slotNum){
    QByteArray baseCmd = "CH#:DBM\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MW
void EXFO_OSICS_MAINFRAME::setModulePowerUnitMWCmd(int slotNum){
    QByteArray baseCmd = "CH#:MW\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MW?
void EXFO_OSICS_MAINFRAME::powerUnitModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MW?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Output Power Setting *******

// CH#:P=
void EXFO_OSICS_MAINFRAME::setModuleOutputPowerCmd(int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#:P=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:P?
void EXFO_OSICS_MAINFRAME::outputPowerModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:P?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// CH#:LIMIT?
void EXFO_OSICS_MAINFRAME::outputPowerReachedQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LIMIT?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Optical Emission Wavelength/Frequency Setting *********


// CH#:F=
void EXFO_OSICS_MAINFRAME::setFrequencyModuleCmd(int slotNum, QByteArray &frequency){
    QByteArray baseCmd = "CH#:F=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, frequency);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:F?
void EXFO_OSICS_MAINFRAME::frequencyModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:F?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// CH#:CTRL
void EXFO_OSICS_MAINFRAME::enableCoherenceControlCmd(int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:CTRL\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:CTRL?
void EXFO_OSICS_MAINFRAME::coherenceControlEnabledQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:CTRL?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// CH#:APF
void EXFO_OSICS_MAINFRAME::enableAutoPeakFindControlCmd(int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:APF\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:APF?
void EXFO_OSICS_MAINFRAME::autoPeakFindControlQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:APF?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// ******** Modulation Control *********

// CH#:MOD_CTRL
void EXFO_OSICS_MAINFRAME::setModuleModulationCtrlCmd(int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:MOD_CTRL\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MOD_CTRL?
void EXFO_OSICS_MAINFRAME::moduleModulationCtrlQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_CTRL?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
}

// CH#:MOD_SRC
void EXFO_OSICS_MAINFRAME::setModuleModulationSrcCmd(int slotNum, QByteArray &setting){
    QByteArray baseCmd = "CH#:MOD_SRC\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MOD_SRC?
void EXFO_OSICS_MAINFRAME::moduleModulationSrcQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_SRC?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);
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
    int index = command.indexOf('#');
    command.remove(index, 1);
    command.insert(index, QByteArray::number(slotNum));
}



// *********** Functions for Applying/Updating Config Settings **********

void EXFO_OSICS_MAINFRAME::applyConfigSettings(QSettings &configSettings){
    // # TODO mainframe won't have many config settings (if any) so apply
    // settings to modules
    qDebug() << "applyConfigSettings() in EXFO_OSICS_MAINFRAME";
}

void EXFO_OSICS_MAINFRAME::updateConfig(QSettings &configSettings){
    qDebug() << "updateConfigSettings()";

    configSettings.setValue(DEVICE_LOCATION, QVariant::fromValue(theInstrLoc));
    configSettings.setValue(DEVICE_IDENTITY, QVariant::fromValue(theIdentity));

    updateInstalledModules(configSettings);
}

void EXFO_OSICS_MAINFRAME::updateInstalledModules(QSettings &configSettings){
    configSettings.setValue(EXFO_OSICS_MODULE_NAMES, QVariant::fromValue(moduleNames));
    qDebug() << configSettings.value(EXFO_OSICS_MODULE_NAMES).value<QList<QByteArray>>();
}

void EXFO_OSICS_MAINFRAME::setupModuleTypesList(){

    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QByteArray present;
        moduleTypeAtSlotQuery(i + 1, present);
        if(present.toInt() == -1){
            moduleNames.append("EMPTY");
        }
        else{
            QByteArray moduleType;
            typeOfModuleQuery(i + 1, moduleType);
            moduleNames.append(moduleType.split(':')[1]);
        }
    }
}

QMap<int, QVariant> EXFO_OSICS_MAINFRAME::getModuleSlotQVariantMap(){
    return modules;
}

QVariant EXFO_OSICS_MAINFRAME::getModuleAtSlot(int slotNum){
    return modules.value(slotNum);
}

QMainWindow* EXFO_OSICS_MAINFRAME::getWindowForModuleAtSlot(int slotNum){
    QVariant module = modules.value(slotNum);
    QMainWindow *configWindow = module.value<DefaultInstrument*>()->getConfigWindow();
    return configWindow;
}

QList<QByteArray> EXFO_OSICS_MAINFRAME::getModuleTypeNames(){
    return moduleNames;
}

