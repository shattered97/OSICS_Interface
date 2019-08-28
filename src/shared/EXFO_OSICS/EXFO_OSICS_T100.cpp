#include "EXFO_OSICS_T100.h"

EXFO_OSICS_T100::EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
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
    qDebug() << "emitting signal";
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
    qDebug() << "t100 updateConfig()";

    // test some commands
    QByteArray minPower;
    QByteArray maxPower;
    firstCalibrationPowerQuery(1, minPower);
    qDebug() << minPower;
    secondCalibrationPowerQuery(1, maxPower);
    qDebug() << maxPower;


}

void EXFO_OSICS_T100::updatePowerSettings(QSettings &configSettings){
    // query device for power values

    QByteArray power;
    QByteArray minPower;
    QByteArray maxPower;
    QByteArray laserState;

    outputPowerModuleQuery(1, power);
    qDebug() << power;
    firstCalibrationPowerQuery(1, minPower);
    qDebug() << minPower;
    secondCalibrationPowerQuery(1, maxPower);
    qDebug() << maxPower;
    laserStateModuleQuery(1, laserState);
    qDebug() << laserState;

//    // save to config
//    configSettings.setValue(N7714A_POWER_SETTINGS, QVariant::fromValue(powerSettings));
//    qDebug() << configSettings.value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
//    configSettings.setValue(N7714A_MIN_POWER, QVariant::fromValue(minPowerSettings));
//    qDebug() << configSettings.value(N7714A_MIN_POWER).value<QList<QByteArray>>();
//    configSettings.setValue(N7714A_MAX_POWER, QVariant::fromValue(maxPowerSettings));
//    qDebug() << configSettings.value(N7714A_MAX_POWER).value<QList<QByteArray>>();
//    configSettings.setValue(N7714A_LASER_STATE, QVariant::fromValue(laserStates));
//    qDebug() << configSettings.value(N7714A_LASER_STATE).value<QList<QByteArray>>();
//    configSettings.sync();
}

void EXFO_OSICS_T100::updateWavelengthSettings(QSettings &configSettings){

}

void EXFO_OSICS_T100::updateFrequencySettings(QSettings &configSettings){

}
