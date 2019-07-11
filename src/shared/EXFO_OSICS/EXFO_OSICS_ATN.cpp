#include "EXFO_OSICS_ATN.h"

EXFO_OSICS_ATN::EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{

}

// CH#:ATN
bool EXFO_OSICS_ATN::setModuleAttenuationCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &attenuation){
     QByteArray baseCmd = "CH#:ATN\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, attenuation);

     return EXFO_OSICS_MAINFRAME::sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:ATN?
bool EXFO_OSICS_ATN::moduleAttenuationQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
     QByteArray baseCmd = "CH#:ATN?\n";
     insertSlotNum(baseCmd, slotNum);

     return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:ATN_MIN_MAX?
bool EXFO_OSICS_ATN::moduleAttenuationMinMaxQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
     QByteArray baseCmd = "CH#:ATN_MIN_MAX?\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:LREF?
bool EXFO_OSICS_ATN::moduleWavelengthNMQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
     QByteArray baseCmd = "CH#:LREF?\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:OFFSET
bool EXFO_OSICS_ATN::moduleAttenuationOffsetCmd(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray wavelengthNum, QByteArray offsetVal){
     QByteArray baseCmd = "CH#:OFFSET\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);
     appendParamToCmdWithSpace(baseCmd, offsetVal);

     return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:OFFSET?
bool EXFO_OSICS_ATN::moduleAttenuationOffsetQuery(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray wavelengthNum, QByteArray &response){
     QByteArray baseCmd = "CH#:OFFSET\n";
     insertSlotNum(baseCmd, slotNum);
     appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}
