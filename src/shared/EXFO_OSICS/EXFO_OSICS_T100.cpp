#include "EXFO_OSICS_T100.h"

EXFO_OSICS_T100::EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{

}

// ********* Diode-Current Setting Commands **********

// CH#:I?
bool EXFO_OSICS_T100::diodeCurrentLevelModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:I?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// CH#:IMAX?
bool EXFO_OSICS_T100::diodeMaxCurrentModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:IMAX?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// ********* Calibration Control Commands *********

// CH#:MOD_F=
bool EXFO_OSICS_T100::setModFrequencyModuleCmd(ViSession &defaultSession, int slotNum, QByteArray &frequency){
    QByteArray baseCmd = "CH#:MOD_F=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, frequency);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:MOD_F?
bool EXFO_OSICS_T100::modFrequencyModuleQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MOD_F?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// CH#:WAVEREF
bool EXFO_OSICS_T100::runWavelengthRefProcedureCmd(ViSession &defaultSession, int slotNum){
    QByteArray baseCmd = "CH#:WAVEREF\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:LCAL1=
bool EXFO_OSICS_T100::setFirstCalibrationWavelengthCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:LCAL2=
bool EXFO_OSICS_T100::setSecondCalibrationWavelengthCmd(ViSession &defaultSession, int slotNum, QByteArray &wavelength){
    QByteArray baseCmd = "CH#:LCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, wavelength);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:LCAL1?
bool EXFO_OSICS_T100::firstCalibrationWavelengthQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL1?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// CH#:LCAL2?
bool EXFO_OSICS_T100::secondCalibrationWavelengthQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:LCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// CH#:PCAL1=
bool EXFO_OSICS_T100::setFirstCalibrationPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#:PCAL1=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#PCAL2=
bool EXFO_OSICS_T100::setSecondCalibrationPowerCmd(ViSession &defaultSession, int slotNum, QByteArray &power){
    QByteArray baseCmd = "CH#PCAL2=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, power);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:PCAL1?
bool EXFO_OSICS_T100::firstCalibrationPowerQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL1?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// CH#:PCAL2?
bool EXFO_OSICS_T100::secondCalibrationPowerQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:PCAL2?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

// ********* Module Parameter-Monitoring Commands *********

// CH#:AOUT
bool EXFO_OSICS_T100::assignOutBNCPortToSignalCmd(ViSession &defaultSession, int slotNum, QByteArray &signalType){
    QByteArray baseCmd = "CH#:AOUT\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, signalType);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

// CH#:AOUT?
bool EXFO_OSICS_T100::outBNCPortSignalMonitoringQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:AOUT?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}
