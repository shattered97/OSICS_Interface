#include "EXFO_OSICS_ATN.h"

EXFO_OSICS_ATN::EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
}

bool EXFO_OSICS_ATN::setModuleAttenuationCmd(ViSession &defaultSession, int slotNum, QByteArray &attenuation){
    // Command: "CH#:ATN\n"
    // Params: 0 < slotnum <= 8
    // Response: None

     QByteArray baseCmd = "CH#:ATN\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, attenuation);

     return EXFO_OSICS_MAINFRAME::sendCmdNoRsp(defaultSession, baseCmd);
}

bool EXFO_OSICS_ATN::moduleAttenuationQuery(ViSession &defaultSession, int slotNum, QByteArray &response){
    // Command: "CH#:ATN?\n";
    // Params: 0 < slotnum <= 8
    // Response: CH#:ATN=xx.xx

    QByteArray baseCmd = "CH#:ATN?\n";

     insertSlotNum(baseCmd, slotNum);

     return sendCmdRsp(defaultSession, baseCmd, response);
}

bool EXFO_OSICS_ATN::moduleAttenuationMinMaxQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:ATN_MIN_MAX?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:ATN_MIN_MAX=+<minimum value>+<maximum value>

    QByteArray baseCmd = "CH#:ATN_MIN_MAX?\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool EXFO_OSICS_ATN::moduleWavelengthNMQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:LREF?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:L(1|2)=<wavelength value>

    QByteArray baseCmd = "CH#:LREF?\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool EXFO_OSICS_ATN::moduleAttenuationOffsetCmd(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray offsetVal){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    //         -10 dB <= offsetVal <= +10 dB (offset in dB, format: xx.xx)
    // Response: None

    QByteArray baseCmd = "CH#:OFFSET\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, wavelengthNum);
    appendParamToCmdWithSpace(baseCmd, offsetVal);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

bool EXFO_OSICS_ATN::moduleAttenuationOffsetQuery(ViSession &defaultSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:OFFSET(1:2)=+xx.xx

    QByteArray baseCmd = "CH#:OFFSET\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     return sendCmdRsp(defaultSession, baseCmd, response);
}
