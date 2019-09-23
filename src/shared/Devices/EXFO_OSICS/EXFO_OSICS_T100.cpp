#include "EXFO_OSICS_T100.h"
#include "ConversionUtilities.h"
EXFO_OSICS_T100::EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void EXFO_OSICS_T100::setT100MinMaxWavelengths(QByteArray t100Type){
    // get module type
    if(t100Type.contains("1310")){
        minWavelength = EXFO_OSICS_T100_1310_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1310_MAX_WAV_NM;
    }
    else if(t100Type.contains("1415")){
        minWavelength = EXFO_OSICS_T100_1415_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1415_MAX_WAV_NM;
    }
    else if(t100Type.contains("1520")){
        minWavelength = EXFO_OSICS_T100_1520_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1520_MAX_WAV_NM;
    }
    else if(t100Type.contains("1550")){
        minWavelength = EXFO_OSICS_T100_1550_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1550_MAX_WAV_NM;
    }
    else if(t100Type.contains("1575")){
        minWavelength = EXFO_OSICS_T100_1575_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1575_MAX_WAV_NM;
    }
    else if(t100Type.contains("1620")){
        minWavelength = EXFO_OSICS_T100_1620_MIN_WAV_NM;
        maxWavelength = EXFO_OSICS_T100_1620_MAX_WAV_NM;
    }
}

// ********* Diode-Current Setting Commands **********

// CH#:I?
void EXFO_OSICS_T100::diodeCurrentLevelModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:I?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// CH#:IMAX?
void EXFO_OSICS_T100::diodeMaxCurrentModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:IMAX?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// ********* Calibration Control Commands *********

// CH#:MOD_F=
void EXFO_OSICS_T100::setModFrequencyModuleCmd(int slotNum, QByteArray &frequency){
    QByteArray baseCmd = "CH#:MOD_F=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, frequency);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:MOD_F?
void EXFO_OSICS_T100::modFrequencyModuleQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_F?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// CH#:WAVEREF
void EXFO_OSICS_T100::runWavelengthRefProcedureCmd(int slotNum){
    QByteArray baseCmd = "CH#:WAVEREF\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:LCAL1=
void EXFO_OSICS_T100::setFirstCalibrationWavelengthCmd(int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:LCAL2=
void EXFO_OSICS_T100::setSecondCalibrationWavelengthCmd(int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:LCAL1?
void EXFO_OSICS_T100::firstCalibrationWavelengthQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL1?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// CH#:LCAL2?
void EXFO_OSICS_T100::secondCalibrationWavelengthQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// CH#:PCAL1=
void EXFO_OSICS_T100::setFirstCalibrationPowerCmd(int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#:PCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#PCAL2=
void EXFO_OSICS_T100::setSecondCalibrationPowerCmd(int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#PCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:PCAL1?
void EXFO_OSICS_T100::firstCalibrationPowerQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL1?\n";
    insertSlotNum(baseCmd, slotNum);
    qDebug() << "emitting signal for: " << theInstrLoc;
    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// CH#:PCAL2?
void EXFO_OSICS_T100::secondCalibrationPowerQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

// ********* Module Parameter-Monitoring Commands *********

// CH#:AOUT
void EXFO_OSICS_T100::assignOutBNCPortToSignalCmd(int slotNum, QByteArray &signalType){
    QByteArray baseCmd = "CH#:AOUT\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, signalType);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

// CH#:AOUT?
void EXFO_OSICS_T100::outBNCPortSignalMonitoringQuery(int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:AOUT?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}



void EXFO_OSICS_T100::setSlotNum(int slotNum){
    this->slotNum = slotNum;
}

void EXFO_OSICS_T100::applyConfigSettings(QSettings &configSettings){
    qDebug() << "t100 applyConfigSettings()";

    // apply laser power
    QByteArray power = configSettings.value(EXFO_OSICS_T100_POWER).value<QByteArray>();
    setModuleOutputPowerCmd(slotNum, power);

    // apply laser state
    QByteArray laserState = configSettings.value(EXFO_OSICS_T100_LASER_STATE).value<QByteArray>();
    if(laserState == "DISABLED"){
        disableModuleLaserCmd(slotNum);
    }
    else{
        enableModuleLaserCmd(slotNum);
    }

    // apply laser wavelength (changing wavelength should change frequency)
    QByteArray wavelength = configSettings.value(EXFO_OSICS_T100_WAVELENGTH).value<QByteArray>();
    setRefWavelengthModuleCmd(slotNum, wavelength);

    updateConfig(configSettings);

}

void EXFO_OSICS_T100::updateConfig(QSettings &configSettings){
    qDebug() << "t100 updateConfig() " << theInstrLoc;

    updatePowerSettings(configSettings);
    updateWavelengthSettings(configSettings);
    updateFrequencySettings(configSettings);
}

void EXFO_OSICS_T100::updatePowerSettings(QSettings &configSettings){

    QByteArray power;
    QByteArray laserState;

    outputPowerModuleQuery(slotNum, power);
    laserStateModuleQuery(slotNum, laserState);

    // parse returned value
    power = power.split(':')[1].trimmed();
    if(power != "Disabled"){
        power = power.split('=')[1];
    }

    laserState = laserState.split(':')[1];

    // save to config
    configSettings.setValue(EXFO_OSICS_T100_POWER, QVariant::fromValue(power));
    configSettings.setValue(EXFO_OSICS_T100_LASER_STATE, QVariant::fromValue(laserState));

    configSettings.sync();
}

void EXFO_OSICS_T100::updateWavelengthSettings(QSettings &configSettings){
    QByteArray wavelength;

    refWavelengthModuleQuery(slotNum, wavelength);

    // parse returned strings
    wavelength = wavelength.split('=')[1];

    configSettings.setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelength));
    configSettings.setValue(EXFO_OSICS_T100_MIN_WAVELENGTH, QVariant::fromValue(minWavelength));
    configSettings.setValue(EXFO_OSICS_T100_MAX_WAVELENGTH, QVariant::fromValue(maxWavelength));


    configSettings.sync();
}

void EXFO_OSICS_T100::updateFrequencySettings(QSettings &configSettings){
    QByteArray frequency;

    frequencyModuleQuery(slotNum, frequency);

    // get min/max frequencies by converting min/max wavelengths
    // min frequency from max wavelength and vice versa
    double minwavelengthM = ConversionUtilities::convertWavelengthToMeter(maxWavelength.toDouble(), "nm");
    double maxWavelengthM = ConversionUtilities::convertWavelengthToMeter(minWavelength.toDouble(), "nm");

    double minFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(minwavelengthM);
    double maxFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(maxWavelengthM);

    double minFrequencyGHz = ConversionUtilities::convertFrequencyFromHz(minFrequencyHz, "GHz");
    double maxFrequencyGHz = ConversionUtilities::convertFrequencyFromHz(maxFrequencyHz, "GHz");
    qDebug() << minWavelength << " " << minFrequencyHz << " " << minFrequencyGHz;
    qDebug() << maxWavelength << " " << maxFrequencyHz << " " << maxFrequencyGHz;

    // parse returned strings
    frequency = frequency.split('=')[1];

    configSettings.setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequency));
    configSettings.setValue(EXFO_OSICS_T100_MIN_FREQUENCY, QVariant::fromValue(minFrequencyGHz));
    configSettings.setValue(EXFO_OSICS_T100_MAX_FREQUENCY, QVariant::fromValue(maxFrequencyGHz));

    configSettings.sync();
}