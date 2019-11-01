#include "EXFO_OSICS_MAINFRAME.h"

EXFO_OSICS_MAINFRAME::EXFO_OSICS_MAINFRAME(QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
    setNickname(theIdentity);

}

void EXFO_OSICS_MAINFRAME::slotSetupEXFOModules(){

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


QByteArray EXFO_OSICS_MAINFRAME::laserStateMainframeQuery(){
    QByteArray baseCmd = "ENABLE?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitGHzCmd(){
    QByteArray baseCmd = "GHZ\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::setMainframeSpectralUnitNMCmd(){
    QByteArray baseCmd = "NM\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::spectralUnitMainframeQuery(){
    QByteArray baseCmd = "NM?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


void EXFO_OSICS_MAINFRAME::setMainframePowerUnitDBmCmd(){
    QByteArray baseCmd = "DBM\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::setMainframePowerUnitMWCmd(){
    QByteArray baseCmd = "MW\n";

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::powerUnitMainframeQuery(){
    QByteArray baseCmd = "MW?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


void EXFO_OSICS_MAINFRAME::setMainframeOutputPowerCmd(QByteArray power){
    QByteArray baseCmd = "P=\n";
    baseCmd = appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::outputPowerMainframeQuery(){
    QByteArray baseCmd = "P?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


void EXFO_OSICS_MAINFRAME::setMainframeModSrcTypeCmd(QByteArray modSrc){
    QByteArray baseCmd = "MOD_SRC\n";
    baseCmd = appendParamToCmdWithSpace(baseCmd, modSrc);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::modSrcTypeMainframeQuery(){
    QByteArray baseCmd = "MOD_SRC?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


void EXFO_OSICS_MAINFRAME::setMainframeFrequencyQuery(QByteArray frequency){
    QByteArray baseCmd = "MOD_F=\n";
    baseCmd = appendParamToCmdNoSpace(baseCmd, frequency);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::frequencyMainframeQuery(){
    QByteArray baseCmd = "MOD_F?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


void EXFO_OSICS_MAINFRAME::saveManframeConfigCmd(QByteArray configMemory){
    QByteArray baseCmd = "SAVE\n";
    baseCmd = appendParamToCmdWithSpace(baseCmd, configMemory);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


void EXFO_OSICS_MAINFRAME::recallMainframeConfigCmd(QByteArray configMemory){
    QByteArray baseCmd = "RECALL\n";
    baseCmd = appendParamToCmdWithSpace(baseCmd, configMemory);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray EXFO_OSICS_MAINFRAME::remoteInterlockMainframeQuery(){
    QByteArray baseCmd = "INTERLOCK?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


QByteArray EXFO_OSICS_MAINFRAME::moduleTypeAtSlotQuery(int slotNum){
    QByteArray baseCmd = "PRESENT?\n";
    QByteArray param = QByteArray::number(slotNum);

    baseCmd = appendParamToCmdWithSpace(baseCmd, param);

    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    // parse response
    return response;
}


// ********** Shared Module Commands ***********


void EXFO_OSICS_MAINFRAME::setModuleSpectralUnitGHzCmd(int slotNum){
    QByteArray baseCmd = "CH#:GHZ\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_MAINFRAME::setModuleSpectralUnitNMCmd(int slotNum){
    QByteArray baseCmd = "CH#:NM\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray EXFO_OSICS_MAINFRAME::spectralUnitModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:NM?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Wavelength Setting *********

void EXFO_OSICS_MAINFRAME::setRefWavelengthModuleCmd(int slotNum, QByteArray wavelengthNum){
    QByteArray baseCmd = "CH#:L\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_MAINFRAME::setWavelengthForModuleCmd(int slotNum, QByteArray wavelength){
    QByteArray baseCmd = "CH#:L=\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    int paramIndex = baseCmd.indexOf('\n');
    baseCmd = baseCmd.insert(paramIndex, wavelength);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray EXFO_OSICS_MAINFRAME::refWavelengthModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:L?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Module System-Version Info ********

QByteArray EXFO_OSICS_MAINFRAME::softwareVersionModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:FIRM?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray EXFO_OSICS_MAINFRAME::identificationModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:*IDN?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray EXFO_OSICS_MAINFRAME::typeOfModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:TYPE?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


// ******** Optical-Output Control ********

// CH#:DISABLE
void EXFO_OSICS_MAINFRAME::disableModuleLaserCmd(int slotNum){
    QByteArray baseCmd = "CH#:DISABLE\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:ENABLE
void EXFO_OSICS_MAINFRAME::enableModuleLaserCmd(int slotNum){
    QByteArray baseCmd = "CH#:ENABLE\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:ENABLE?
QByteArray EXFO_OSICS_MAINFRAME::laserStateModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:ENABLE?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Unit Selection *********


// CH#:DBM
void EXFO_OSICS_MAINFRAME::setModulePowerUnitDBmCmd(int slotNum){
    QByteArray baseCmd = "CH#:DBM\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MW
void EXFO_OSICS_MAINFRAME::setModulePowerUnitMWCmd(int slotNum){
    QByteArray baseCmd = "CH#:MW\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MW?
QByteArray EXFO_OSICS_MAINFRAME::powerUnitModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:MW?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Output Power Setting *******

// CH#:P=
void EXFO_OSICS_MAINFRAME::setModuleOutputPowerCmd(int slotNum, QByteArray power){
    QByteArray baseCmd = "CH#:P=\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:P?
QByteArray EXFO_OSICS_MAINFRAME::outputPowerModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:P?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// CH#:LIMIT?
QByteArray EXFO_OSICS_MAINFRAME::outputPowerReachedQuery(int slotNum){
    QByteArray baseCmd = "CH#:LIMIT?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Optical Emission Wavelength/Frequency Setting *********


// CH#:F=
void EXFO_OSICS_MAINFRAME::setFrequencyModuleCmd(int slotNum, QByteArray frequency){
    QByteArray baseCmd = "CH#:F=\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdNoSpace(baseCmd, frequency);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:F?
QByteArray EXFO_OSICS_MAINFRAME::frequencyModuleQuery(int slotNum){
    QByteArray baseCmd = "CH#:F?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// CH#:CTRL
void EXFO_OSICS_MAINFRAME::enableCoherenceControlCmd(int slotNum, QByteArray setting){
    QByteArray baseCmd = "CH#:CTRL\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:CTRL?
QByteArray EXFO_OSICS_MAINFRAME::coherenceControlEnabledQuery(int slotNum){
    QByteArray baseCmd = "CH#:CTRL?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// CH#:APF
void EXFO_OSICS_MAINFRAME::enableAutoPeakFindControlCmd(int slotNum, QByteArray setting){
    QByteArray baseCmd = "CH#:APF\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:APF?
QByteArray EXFO_OSICS_MAINFRAME::autoPeakFindControlQuery(int slotNum){
    QByteArray baseCmd = "CH#:APF?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// ******** Modulation Control *********

// CH#:MOD_CTRL
void EXFO_OSICS_MAINFRAME::setModuleModulationCtrlCmd(int slotNum, QByteArray setting){
    QByteArray baseCmd = "CH#:MOD_CTRL\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MOD_CTRL?
QByteArray EXFO_OSICS_MAINFRAME::moduleModulationCtrlQuery(int slotNum){
    QByteArray baseCmd = "CH#:MOD_CTRL?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

// CH#:MOD_SRC
void EXFO_OSICS_MAINFRAME::setModuleModulationSrcCmd(int slotNum, QByteArray setting){
    QByteArray baseCmd = "CH#:MOD_SRC\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, setting);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MOD_SRC?
QByteArray EXFO_OSICS_MAINFRAME::moduleModulationSrcQuery(int slotNum){
    QByteArray baseCmd = "CH#:MOD_SRC?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}


// ************ Helper Functions ************

QByteArray EXFO_OSICS_MAINFRAME::appendParamToCmdWithSpace(QByteArray command, QByteArray param){
    param.prepend(" ");
    return command.insert(command.indexOf('\n'), param);
}

QByteArray EXFO_OSICS_MAINFRAME::appendParamToCmdNoSpace(QByteArray command, QByteArray param){
    return command.insert(command.indexOf('\n'), param);
}

QByteArray EXFO_OSICS_MAINFRAME::insertSlotNum(QByteArray command, int slotNum){
    int index = command.indexOf('#');
    command.remove(index, 1);
    return command.insert(index, QByteArray::number(slotNum));
}



// *********** Functions for Applying/Updating Config Settings **********

void EXFO_OSICS_MAINFRAME::applyConfigSettings(QSettings &configSettings){
    // # TODO mainframe won't have many config settings (if any) so apply
    // settings to modules

    // apply nickname
    QByteArray nicknameToSet = configSettings.value(DEVICE_NICKNAME).value<QByteArray>();
    setNickname(nicknameToSet);

}

void EXFO_OSICS_MAINFRAME::updateConfig(QSettings &configSettings){

    configSettings.setValue(DEVICE_ADDRESS, QVariant::fromValue(theInstrLoc));
    configSettings.setValue(DEVICE_IDENTITY, QVariant::fromValue(theIdentity));
    configSettings.setValue(DEVICE_NICKNAME, QVariant::fromValue(getNickname()));

    updateInstalledModules(configSettings);
}

void EXFO_OSICS_MAINFRAME::updateInstalledModules(QSettings &configSettings){
    configSettings.setValue(EXFO_OSICS_MODULE_NAMES, QVariant::fromValue(moduleNames));
}

void EXFO_OSICS_MAINFRAME::setupModuleTypesList(){

    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QByteArray present = moduleTypeAtSlotQuery(i + 1);

        if(present.toInt() == -1){
            moduleNames.append("EMPTY");
        }
        else{
            QByteArray moduleType = typeOfModuleQuery(i + 1);
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

