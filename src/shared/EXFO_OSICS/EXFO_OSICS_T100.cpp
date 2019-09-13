#include "EXFO_OSICS_T100.h"

EXFO_OSICS_T100::EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
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


void EXFO_OSICS_T100::applyConfigSettings(QSettings &configSettings){
    qDebug() << "t100 applyConfigSettings()";
}

void EXFO_OSICS_T100::updateConfig(QSettings &configSettings){
    qDebug() << "t100 updateConfig() " << theInstrLoc;

    updatePowerSettings(configSettings);
    updateWavelengthSettings(configSettings);
    updateFrequencySettings(configSettings);
}

void EXFO_OSICS_T100::updatePowerSettings(QSettings &configSettings){

    QByteArray power;
    QByteArray minPower;
    QByteArray maxPower;
    QByteArray laserState;

    outputPowerModuleQuery(slotNum, power);
    firstCalibrationPowerQuery(slotNum, minPower);
    secondCalibrationPowerQuery(slotNum, maxPower);
    laserStateModuleQuery(slotNum, laserState);

    // parse returned value
    power = power.split(':')[1].trimmed();
    if(power != "Disabled"){
        power = power.split('=')[1];
    }

    minPower = minPower.split('=')[1];
    maxPower = maxPower.split('=')[1];
    laserState = laserState.split(':')[1];

    // save to config
    configSettings.setValue(EXFO_OSICS_T100_POWER, QVariant::fromValue(power));
    configSettings.setValue(EXFO_OSICS_T100_MIN_POWER, QVariant::fromValue(minPower));
    configSettings.setValue(EXFO_OSICS_T100_MAX_POWER, QVariant::fromValue(maxPower));
    configSettings.setValue(EXFO_OSICS_T100_LASER_STATE, QVariant::fromValue(laserState));

    qDebug() << "*******************************************************************";
    qDebug() << configSettings.value(EXFO_OSICS_T100_POWER).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MIN_POWER).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MAX_POWER).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_LASER_STATE).value<QByteArray>();
    qDebug() << "*******************************************************************";
    configSettings.sync();
}

void EXFO_OSICS_T100::updateWavelengthSettings(QSettings &configSettings){
    QByteArray wavelength;
    QByteArray minWavelength;
    QByteArray maxWavelength;

    refWavelengthModuleQuery(slotNum, wavelength);
    firstCalibrationWavelengthQuery(slotNum, minWavelength);
    secondCalibrationWavelengthQuery(slotNum, maxWavelength);

    // parse returned strings
    wavelength = wavelength.split('=')[1];
    minWavelength = minWavelength.split('=')[1];
    maxWavelength = maxWavelength.split('=')[1];

    configSettings.setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelength));
    configSettings.setValue(EXFO_OSICS_T100_MIN_WAVELENGTH, QVariant::fromValue(minWavelength));
    configSettings.setValue(EXFO_OSICS_T100_MAX_WAVELENGTH, QVariant::fromValue(minWavelength));

    qDebug() << "*******************************************************************";
    qDebug() << configSettings.value(EXFO_OSICS_T100_WAVELENGTH).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MIN_WAVELENGTH).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MAX_WAVELENGTH).value<QByteArray>();
    qDebug() << "*******************************************************************";
    configSettings.sync();
}

void EXFO_OSICS_T100::updateFrequencySettings(QSettings &configSettings){
    QByteArray frequency;
    QByteArray minFrequency;
    QByteArray maxFrequency;

    frequencyModuleQuery(slotNum, frequency);
    // #TODO how to handle min/max values with no queries?
    minFrequency = "0";
    maxFrequency = "0";

    // parse returned strings
    frequency = frequency.split('=')[1];

    configSettings.setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequency));
    configSettings.setValue(EXFO_OSICS_T100_MIN_FREQUENCY, QVariant::fromValue(minFrequency));
    configSettings.setValue(EXFO_OSICS_T100_MAX_FREQUENCY, QVariant::fromValue(maxFrequency));

    qDebug() << "*******************************************************************";
    qDebug() << configSettings.value(EXFO_OSICS_T100_FREQUENCY).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MIN_FREQUENCY).value<QByteArray>();
    qDebug() << configSettings.value(EXFO_OSICS_T100_MAX_FREQUENCY).value<QByteArray>();
    qDebug() << "*******************************************************************";
    configSettings.sync();
}
