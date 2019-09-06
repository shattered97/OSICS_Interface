#include "EXFO_OSICS_SWT.h"

EXFO_OSICS_SWT::EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void EXFO_OSICS_SWT::setAPCModuleOperatingMode(int slotNum, QByteArray &mode){
    // Command: "CH#:MODE\n"
    // Params: 0 < slotnum <= 8
    //         mode = SWT (module set to Switch mode) OR mode = ECL (module set to Full-band mode)
    // Response: None

    QByteArray baseCmd = "CH#:MODE\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, mode);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getAPCModuleOperatingMode(int slotNum, QByteArray &response){
    // Command: "CH#:MODE?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:MODE=SWT (module is in Switch mode) OR CH#:MODE=ECL (module is in Full-band mode)

    QByteArray baseCmd = "CH#:MODE?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void  EXFO_OSICS_SWT::autoDetectT100Modules(int slotNum){
    // Command: "CH#:ACFG\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:ACFG\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::selectChannelForSignalAPC(int slotNum, QByteArray &channelNum){
    // Command: "CH#:CLOSE=\n"
    // Params: 0 < slotnum <= 8
    //         1 <= channelNum <= 4 (channel number to activate)
    // Response: None

    QByteArray baseCmd = "CH#:CLOSE=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, channelNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getChannelForSignalAPC(int slotNum, QByteArray &response){
    // Command: "CH#:CLOSE\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:CLOSE=<channel number>

    QByteArray baseCmd = "CH#:CLOSE?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void  EXFO_OSICS_SWT::shutSingleShutter(int slotNum){
    // Command: "CH#:SHUT\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:SHUT\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::openSingleShutter(int slotNum){
    // Command: "CH#:OPEN\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:OPEN\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getSingleShutterState(int slotNum, QByteArray &response){
    // Command: "CH#:SHUT?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:SHUT=TRUE OR CH#:SHUT=FALSE

    QByteArray baseCmd = "CH#:SHUT?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void  EXFO_OSICS_SWT::openCloseShutters(int slotNum, QByteArray &shutterAB, QByteArray &shutter12){
    // Command: "CH#:SHUTMODE\n"
    // Params: 0 < slotnum <= 8
    //         shutterAB = 0 (closes the A-B shutter) OR shutterAB = 1 (opens the A-B shutter)
    //         shutter12 = 0 (closes the 1-2 shutter) OR shutter12 = 1 (opens the 1-2 shutter)
    // Response: None

    QByteArray baseCmd = "CH#:SHUTMODE\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, shutterAB);
    appendParamToCmdWithSpace(baseCmd, shutter12);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getMultipleShutterState(int slotNum, QByteArray &response){
    // Command: "CH#:SHUTMODE?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:SHUTMODE 0|1 0|1

    QByteArray baseCmd = "CH#:SHUTMODE?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void  EXFO_OSICS_SWT::setSwitchModeBar(int slotNum){
    // Command: "CH#:BAR\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:BAR\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::setSwitchModeCross(int slotNum){
    // Command: "CH#:CROSS\n"
    // Params: 0 < slotnum <= 8
    // Response: None

    QByteArray baseCmd = "CH#:CROSS\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getSwitchMode(int slotNum, QByteArray &response){
    // Command: "CH#:BAR?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:BAR=TRUE (switch is set to Bar) OR CH#:BAR=FALSE (switch is set to Cross)

    QByteArray baseCmd = "CH#:BAR?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void  EXFO_OSICS_SWT::selectSignalChannel(int slotNum, QByteArray &channel){
    // Command: "CH#:CH\n"
    // Params: 0 < slotnum <= 8
    //         1 <= channel <= 2 OR 1 <= channel <= 4 (depends on model)
    // Response: None

    QByteArray baseCmd = "CH#:CH\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, channel);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void  EXFO_OSICS_SWT::getSignalChannel(int slotNum, QByteArray &response){
    // Command: "CH#:CH?\n"
    // Params: 0 < slotnum <= 8
    // Response: CH#:CH=<channel number>

    QByteArray baseCmd = "CH#:CH?\n";
    insertSlotNum(baseCmd, slotNum);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}
