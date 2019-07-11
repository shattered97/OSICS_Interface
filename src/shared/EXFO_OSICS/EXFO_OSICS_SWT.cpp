#include "EXFO_OSICS_SWT.h"

EXFO_OSICS_SWT::EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{

}


// CH#:MODE
bool EXFO_OSICS_SWT::setAPCModuleOperatingMode(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &mode){
    QByteArray baseCmd = "CH#:MODE\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, mode);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:MODE?
bool EXFO_OSICS_SWT::getAPCModuleOperatinGMode(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:MODE?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:ACFG
bool EXFO_OSICS_SWT::autoDetectT100Modules(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:ACFG\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:CLOSE=
bool EXFO_OSICS_SWT::selectChannelForSignalAPC(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &channelNum){
    QByteArray baseCmd = "CH#:CLOSE=\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdNoSpace(baseCmd, channelNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:CLOSE?
bool EXFO_OSICS_SWT::getChannelForSignalAPC(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:CLOSE?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:SHUT
bool EXFO_OSICS_SWT::shutSingleShutter(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:SHUT\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:OPEN
bool EXFO_OSICS_SWT::openSingleShutter(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:OPEN\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:SHUT?
bool EXFO_OSICS_SWT::getSingleShutterState(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:SHUT?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:SHUTMODE
bool EXFO_OSICS_SWT::openCloseShutters(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &shutterAB, QByteArray &shutter12){
    QByteArray baseCmd = "CH#:SHUTMODE\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, shutterAB);
    appendParamToCmdWithSpace(baseCmd, shutter12);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:SHUTMODE?
bool EXFO_OSICS_SWT::getMultipleShutterState(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:SHUTMODE?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:BAR
bool EXFO_OSICS_SWT::setSwitchModeBar(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:BAR\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:CROSS
bool EXFO_OSICS_SWT::setSwitchModeCross(ViSession &defaultSession, ViSession &instrSession, int slotNum){
    QByteArray baseCmd = "CH#:CROSS\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:BAR?
bool EXFO_OSICS_SWT::getSwitchMode(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:BAR?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}

// CH#:CH
bool EXFO_OSICS_SWT::selectSignalChannel(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &channel){
    QByteArray baseCmd = "CH#:CH\n";
    insertSlotNum(baseCmd, slotNum);
    appendParamToCmdWithSpace(baseCmd, channel);

    return sendCmdNoRsp(defaultSession, instrSession, baseCmd);
}

// CH#:CH?
bool EXFO_OSICS_SWT::getSignalChannel(ViSession &defaultSession, ViSession &instrSession, int slotNum, QByteArray &response){
    QByteArray baseCmd = "CH#:CH?\n";
    insertSlotNum(baseCmd, slotNum);

    return sendCmdRsp(defaultSession, instrSession, baseCmd, response);
}
