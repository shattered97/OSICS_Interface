#include "EXFO_OSICS_SWT.h"
#include "ConversionUtilities.h"

EXFO_OSICS_SWT::EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
    setNickname(theIdentity);
}

void EXFO_OSICS_SWT::setAPCModuleOperatingMode(int slotNum, QByteArray mode){
    // Command: "CH#:MODE\n"
    // Params: 0 < slotnum <= 8
    //         mode = SWT (module set to Switch mode) OR mode = ECL (module set to Full-band mode)
    // Response: None

    QByteArray baseCmd = "CH#:MODE\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, mode);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray EXFO_OSICS_SWT::getAPCModuleOperatingMode(int slotNum){
    // Command: "CH#:MODE?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:MODE=SWT (module is in Switch mode) OR CH#:MODE=ECL (module is in Full-band mode)

    QByteArray baseCmd = "CH#:MODE?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void  EXFO_OSICS_SWT::autoDetectT100Modules(int slotNum){
    // Command: "CH#:ACFG\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:ACFG\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::selectChannelForSignalAPC(int slotNum, QByteArray channelNum){
    // Command: "CH#:CLOSE=\n"
    // Params: 0 < slotnum <= 8
    //         1 <= channelNum <= 4 (channel number to activate)
    // Response: None

    QByteArray baseCmd = "CH#:CLOSE=\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdNoSpace(baseCmd, channelNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray  EXFO_OSICS_SWT::getChannelForSignalAPC(int slotNum){
    // Command: "CH#:CLOSE?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:CLOSE=<channel number>

    QByteArray baseCmd = "CH#:CLOSE?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void  EXFO_OSICS_SWT::shutSingleShutter(int slotNum){
    // Command: "CH#:SHUT\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:SHUT\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::openSingleShutter(int slotNum){
    // Command: "CH#:OPEN\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:OPEN\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray  EXFO_OSICS_SWT::getSingleShutterState(int slotNum){
    // Command: "CH#:SHUT?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:SHUT=TRUE OR CH#:SHUT=FALSE

    QByteArray baseCmd = "CH#:SHUT?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void  EXFO_OSICS_SWT::openCloseShutters(int slotNum, QByteArray shutterAB, QByteArray shutter12){
    // Command: "CH#:SHUTMODE\n"
    // Params: 0 < slotnum <= 8
    //         shutterAB = 0 (closes the A-B shutter) OR shutterAB = 1 (opens the A-B shutter)
    //         shutter12 = 0 (closes the 1-2 shutter) OR shutter12 = 1 (opens the 1-2 shutter)
    // Response: None

    QByteArray baseCmd = "CH#:SHUTMODE\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, shutterAB);
    baseCmd = appendParamToCmdWithSpace(baseCmd, shutter12);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray  EXFO_OSICS_SWT::getMultipleShutterState(int slotNum){
    // Command: "CH#:SHUTMODE?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:SHUTMODE 0|1 0|1

    QByteArray baseCmd = "CH#:SHUTMODE?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void  EXFO_OSICS_SWT::setSwitchModeBar(int slotNum){
    // Command: "CH#:BAR\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:BAR\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::setSwitchModeCross(int slotNum){
    // Command: "CH#:CROSS\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:CROSS\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray  EXFO_OSICS_SWT::getSwitchMode(int slotNum){
    // Command: "CH#:BAR?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:BAR=TRUE (switch is set to Bar) OR CH#:BAR=FALSE (switch is set to Cross)

    QByteArray baseCmd = "CH#:BAR?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void  EXFO_OSICS_SWT::selectSignalChannel(int slotNum, QByteArray channel){
    // Command: "CH#:CH\n"
    // Params: 0 < slotnum <= 8
    //         1 <= channel <= 2 OR 1 <= channel <= 4 (depends on model)
    // Response: None

    QByteArray baseCmd = "CH#:CH\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, channel);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray  EXFO_OSICS_SWT::getSignalChannel(int slotNum){
    // Command: "CH#:CH?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:CH=<channel number>

    QByteArray baseCmd = "CH#:CH?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}



void EXFO_OSICS_SWT::setSlotNum(int slotNum){
    this->slotNum = slotNum;
}

int EXFO_OSICS_SWT::getSlotNum(){
    return slotNum;
}

void EXFO_OSICS_SWT::updateConfig(QSettings *configSettings){

    configSettings->setValue(DEVICE_NICKNAME, QVariant::fromValue(getNickname()));
    // get operating mode and store it

    QByteArray opMode = getAPCModuleOperatingMode(slotNum);


    if(opMode.contains("SWT")){

        QByteArray activeChannel =  getChannelForSignalAPC(slotNum);
        activeChannel = activeChannel = activeChannel.split('=')[1].trimmed();

        // change opMode to full-band mode to be able to get power/wavelength/frequency values
        QByteArray fullBand = "ECL";
        setAPCModuleOperatingMode(slotNum, fullBand);

        // auto-detect T100 modules
        if(!autoDetectComplete){
            autoDetectT100Modules(slotNum);
            autoDetectComplete = true;
        }

        updatePowerSettings(*configSettings);
        updateWavelengthSettings(*configSettings);
        updateFrequencySettings(*configSettings);

        // return operating mode to original state
        setAPCModuleOperatingMode(slotNum, "SWT");
        selectChannelForSignalAPC(slotNum, activeChannel);

        updateActiveChannelSettings(*configSettings);
        updateOperatingModeSettings(*configSettings);
    }
    else{

        // auto-detect T100 modules
        if(!autoDetectComplete){
            autoDetectT100Modules(slotNum);
            autoDetectComplete = true;
        }

        updatePowerSettings(*configSettings);
        updateWavelengthSettings(*configSettings);
        updateFrequencySettings(*configSettings);
        updateActiveChannelSettings(*configSettings);
        updateOperatingModeSettings(*configSettings);
    }

}

void EXFO_OSICS_SWT::applyConfigSettings(QSettings *configSettings){

    // apply nickname
    QByteArray nicknameToSet = configSettings->value(DEVICE_NICKNAME).value<QByteArray>();
    setNickname(nicknameToSet);

    // apply operating mode from settings
    QByteArray operatingMode = configSettings->value(EXFO_OSICS_SWT_OPMODE).value<QByteArray>();
    setAPCModuleOperatingMode(slotNum, operatingMode);

    if(operatingMode == "SWT"){

        // apply active channel from settings
        QByteArray activeChannel = configSettings->value(EXFO_OSICS_SWT_ACTIVE_CHANNEL).value<QByteArray>();
        selectChannelForSignalAPC(slotNum, activeChannel);

    }
    else{
        // apply output power state from settings
        QByteArray outputStatus = configSettings->value(EXFO_OSICS_SWT_OUTPUT_STATUS).value<QByteArray>();
        if(outputStatus == "ENABLED"){
            enableModuleLaserCmd(slotNum);
        }
        else{
            disableModuleLaserCmd(slotNum);
        }

        // apply power from settings
        // make sure power unit is set to dbm
        setModulePowerUnitDBmCmd(slotNum);
        QByteArray power = configSettings->value(EXFO_OSICS_SWT_POWER_SETTING).value<QByteArray>();
        setModuleOutputPowerCmd(slotNum, power);

        // apply wavelength from settings
        QByteArray wavelength = configSettings->value(EXFO_OSICS_SWT_WAVELENGTH_SETTING).value<QByteArray>();
        setWavelengthForModuleCmd(slotNum, wavelength);

    }

    // update values
    updateConfig(configSettings);
}


void EXFO_OSICS_SWT::updateOperatingModeSettings(QSettings &configSettings)
{

    QByteArray operatingMode = getAPCModuleOperatingMode(slotNum);

    // parse returned value
    operatingMode = operatingMode.split('=')[1].trimmed();

    configSettings.setValue(EXFO_OSICS_SWT_OPMODE, QVariant::fromValue(operatingMode));
}

void EXFO_OSICS_SWT::updateActiveChannelSettings(QSettings &configSettings)
{

    QByteArray activeChannel = getChannelForSignalAPC(slotNum);

    // parse returned value
    activeChannel = activeChannel.split('=')[1].trimmed();

    configSettings.setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void EXFO_OSICS_SWT::updatePowerSettings(QSettings &configSettings)
{

    QByteArray outputStatus = laserStateModuleQuery(slotNum);
    outputStatus = outputStatus.split(':')[1].trimmed();
    configSettings.setValue(EXFO_OSICS_SWT_OUTPUT_STATUS, QVariant::fromValue(outputStatus.trimmed().toUpper()));

    QByteArray power = outputPowerModuleQuery(slotNum);

    if(power.contains("Disabled")){
        power = "DISABLED";
    }
    else{
        // parse returned value
        power = power.split('=')[1].trimmed();
    }

    configSettings.setValue(EXFO_OSICS_SWT_POWER_SETTING, QVariant::fromValue(power.trimmed()));

}

void EXFO_OSICS_SWT::updateWavelengthSettings(QSettings &configSettings)
{

    QByteArray wavelength = refWavelengthModuleQuery(slotNum);

    // if there is no laser input, you can't read the wavelength
    if(wavelength != "")
        wavelength = wavelength.split('=')[1].trimmed();

    configSettings.setValue(EXFO_OSICS_SWT_WAVELENGTH_SETTING, QVariant::fromValue(wavelength));

    if(!minMaxWavelengthsFound){

        QByteArray minWavelength = getMinWavelengthForSWT();
        QByteArray maxWavelength = getMaxWavelengthForSWT();

        configSettings.setValue(EXFO_OSICS_SWT_MIN_WAV_SETTING, QVariant::fromValue(minWavelength));
        configSettings.setValue(EXFO_OSICS_SWT_MAX_WAV_SETTING, QVariant::fromValue(maxWavelength));

        minMaxWavelengthsFound = true;
    }
}

void EXFO_OSICS_SWT::updateFrequencySettings(QSettings &configSettings)
{
    QByteArray frequency = frequencyModuleQuery(slotNum);

    // if there is no laser input, you can't read the frequency
    if(frequency != "")
        frequency = frequency.split('=')[1].trimmed();

    configSettings.setValue(EXFO_OSICS_SWT_FREQUENCY_SETTING, QVariant::fromValue(frequency));
}

QByteArray EXFO_OSICS_SWT::getMinWavelengthForSWT(){
    // query each module for type
    double minWavelength = INT_MAX;

    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QByteArray t100MinWav = QByteArray::number(INT_MAX);
        QByteArray presentModule = moduleTypeAtSlotQuery(i + 1);
        if(presentModule.trimmed() != "-1"){
            QByteArray type = typeOfModuleQuery(i + 1).split(':')[1];

            if(type == EXFO_OSICS_T100_1310_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1310_MIN_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1415_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1415_MIN_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1520_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1520_MIN_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1550_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1550_MIN_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1575_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1575_MIN_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1620_TYPE_NAME){
                t100MinWav = EXFO_OSICS_T100_1620_MIN_WAV_NM;
            }

            if(t100MinWav.toDouble() < minWavelength){
                minWavelength = t100MinWav.toDouble();
            }
        }
    }

    return QByteArray::number(minWavelength);
}

QByteArray EXFO_OSICS_SWT::getMaxWavelengthForSWT(){
    // query each module for type
    double maxWavelength = 0;
    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QByteArray t100MaxWav = QByteArray::number(0);
        QByteArray presentModule = moduleTypeAtSlotQuery(i + 1);
        if(presentModule.trimmed() != "-1"){
            QByteArray type = typeOfModuleQuery(i + 1).split(':')[1];
            if(type == EXFO_OSICS_T100_1310_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1310_MAX_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1415_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1415_MAX_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1520_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1520_MAX_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1550_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1550_MAX_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1575_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1575_MAX_WAV_NM;
            }
            else if(type == EXFO_OSICS_T100_1620_TYPE_NAME){
                t100MaxWav = EXFO_OSICS_T100_1620_MAX_WAV_NM;
            }

            if(t100MaxWav.toDouble() > maxWavelength){
                maxWavelength = t100MaxWav.toDouble();
            }
        }
    }

    return QByteArray::number(maxWavelength);
}

