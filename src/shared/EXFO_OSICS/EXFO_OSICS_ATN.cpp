#include "EXFO_OSICS_ATN.h"

EXFO_OSICS_ATN::EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
}

void EXFO_OSICS_ATN::setModuleAttenuationCmd(int slotNum, QByteArray &attenuation){
    // Command: "CH#:ATN\n"
    // Params: 0 < slotnum <= 8
    // Response: None
     QByteArray baseCmd = "CH#:ATN\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, attenuation);

     emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_ATN::moduleAttenuationQuery(int slotNum, QByteArray &response){
    // Command: "CH#:ATN?\n";
    // Params: 0 < slotnum <= 8
    // Response: CH#:ATN=xx.xx

    QByteArray baseCmd = "CH#:ATN?\n";

     insertSlotNum(baseCmd, slotNum);

     emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void EXFO_OSICS_ATN::moduleAttenuationMinMaxQuery(int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:ATN_MIN_MAX?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:ATN_MIN_MAX=+<minimum value>+<maximum value>

    QByteArray baseCmd = "CH#:ATN_MIN_MAX?\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void EXFO_OSICS_ATN::moduleWavelengthNMQuery(int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:LREF?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:L(1|2)=<wavelength value>

    QByteArray baseCmd = "CH#:LREF?\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void EXFO_OSICS_ATN::moduleAttenuationOffsetCmd(int slotNum, QByteArray wavelengthNum, QByteArray offsetVal){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    //         -10 dB <= offsetVal <= +10 dB (offset in dB, format: xx.xx)
    // Response: None

    QByteArray baseCmd = "CH#:OFFSET\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);
    appendParamToCmdWithSpace(baseCmd, offsetVal);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void EXFO_OSICS_ATN::moduleAttenuationOffsetQuery(int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:OFFSET(1:2)=+xx.xx

    QByteArray baseCmd = "CH#:OFFSET\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}
