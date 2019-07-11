#include "EXFO_OSICS_T100.h"

EXFO_OSICS_T100::EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{

}

// ********* Diode-Current Setting Commands **********

// CH#:I?
bool EXFO_OSICS_T100::diodeCurrentLevelModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:I?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:IMAX?
bool EXFO_OSICS_T100::diodeMaxCurrentModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:IMAX?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ********* Calibration Control Commands *********

// CH#:MOD_F=
bool EXFO_OSICS_T100::setModFrequencyModuleCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &frequency){
    QByteArray baseCmd = "CH#:MOD_F=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, frequency);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MOD_F?
bool EXFO_OSICS_T100::modFrequencyModuleQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_F?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:WAVEREF
bool EXFO_OSICS_T100::runWavelengthRefProcedureCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:WAVEREF\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:LCAL1=
bool EXFO_OSICS_T100::setFirstCalibrationWavelengthCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:LCAL2=
bool EXFO_OSICS_T100::setSecondCalibrationWavelengthCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:LCAL1?
bool EXFO_OSICS_T100::firstCalibrationWavelengthQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelength, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL1?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:LCAL2?
bool EXFO_OSICS_T100::secondCalibrationWavelengthQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &wavelength, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:PCAL1=
bool EXFO_OSICS_T100::setFirstCalibrationPowerCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#:PCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#PCAL2=
bool EXFO_OSICS_T100::setSecondCalibrationPowerCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#PCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:PCAL1?
bool EXFO_OSICS_T100::firstCalibrationPowerQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL1?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:PCAL2?
bool EXFO_OSICS_T100::secondCalibrationPowerQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &power, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// ********* Module Parameter-Monitoring Commands *********

// CH#:AOUT
bool EXFO_OSICS_T100::assignOutBNCPortToSignalCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &signalType){
    QByteArray baseCmd = "CH#:AOUT\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, signalType);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:AOUT?
bool EXFO_OSICS_T100::outBNCPortSignalMonitoringQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:AOUT?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}
