#ifndef EXFO_OSICS_SWT_H
#define EXFO_OSICS_SWT_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_SWT :  EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc);

    // CH#:MODE
    bool setAPCModuleOperatingMode(ViSession &defaultSession, int slotNum, QByteArray &mode);

    // CH#:MODE?
    bool getAPCModuleOperatinGMode(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:ACFG
    bool autoDetectT100Modules(ViSession &defaultSession, int slotNum);

    // CH#:CLOSE=
    bool selectChannelForSignalAPC(ViSession &defaultSession, int slotNum, QByteArray &channelNum);

    // CH#:CLOSE?
    bool getChannelForSignalAPC(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:SHUT
    bool shutSingleShutter(ViSession &defaultSession, int slotNum);

    // CH#:OPEN
    bool openSingleShutter(ViSession &defaultSession, int slotNum);

    // CH#:SHUT?
    bool getSingleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:SHUTMODE
    bool openCloseShutters(ViSession &defaultSession, int slotNum, QByteArray &shutterAB, QByteArray &shutter12);

    // CH#:SHUTMODE?
    bool getMultipleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:BAR
    bool setSwitchModeBar(ViSession &defaultSession, int slotNum);

    // CH#:CROSS
    bool setSwitchModeCross(ViSession &defaultSession, int slotNum);

    // CH#:BAR?
    bool getSwitchMode(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:CH
    bool selectSignalChannel(ViSession &defaultSession, int slotNum, QByteArray &channel);

    // CH#:CH?
    bool getSignalChannel(ViSession &defaultSession, int slotNum, QByteArray &response);


private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
};

#endif // EXFO_OSICS_SWT_H
