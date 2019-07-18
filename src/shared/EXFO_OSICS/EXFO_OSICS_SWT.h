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
    /**
     * @brief shutSingleShutter Shuts the shutter of a SWT 1x1 module
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool shutSingleShutter(ViSession &defaultSession, int slotNum);

    // CH#:OPEN
    /**
     * @brief openSingleShutter Opens the shutter of a SWT 1x1 module
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool openSingleShutter(ViSession &defaultSession, int slotNum);

    // CH#:SHUT?
    /**
     * @brief getSingleShutterState Returns the state of the SWT 1x1 shutter
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (shutter is shut) | FALSE (shutter is open)
     * @return true if command was successful
     */
    bool getSingleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:SHUTMODE
    /**
     * @brief openCloseShutters Opens or closes A-B and/or 1-2 shutters on the SWT 2x(1x1)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param shutterAB Output mode of the A-B shutter - 0 (closes shutter) | 1 (opens shutter)
     * @param shutter12 Output mode of the 1-2 shutter - 0 (closes shutter) | 1 (opens shutter)
     * @return true if command was successful
     */
    bool openCloseShutters(ViSession &defaultSession, int slotNum, QByteArray &shutterAB, QByteArray &shutter12);

    // CH#:SHUTMODE?
    /**
     * @brief getMultipleShutterState Returns the output power mode of the A-B and 1-2 shutters on SWT 2x(1x1)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Output format: "CH#:SHUTMODE 0|1 0|1"
     * @return true if command was successful
     */
    bool getMultipleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:BAR
    /**
     * @brief setSwitchModeBar Sets the switch output mode to Bar (A linked to 1, B liked to 2)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setSwitchModeBar(ViSession &defaultSession, int slotNum);

    // CH#:CROSS
    /**
     * @brief setSwitchModeCross Sets the switch output mode to Cross (A linked to 2, B linked to 1)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setSwitchModeCross(ViSession &defaultSession, int slotNum);

    // CH#:BAR?
    /**
     * @brief getSwitchMode Returns the output mode (Cross/Bar) of the switch
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (switch set to Bar) | FALSE (switch set to cross)
     * @return true if command was successful
     */
    bool getSwitchMode(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:CH
    /**
     * @brief selectSignalChannel Selects the channel through which the signal is directed (SWT 1x2 and SWT 1x4)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param channel Channel number (1-2 or 1-4 depending on module)
     * @return true if command was successful
     */
    bool selectSignalChannel(ViSession &defaultSession, int slotNum, QByteArray &channel);

    // CH#:CH?
    /**
     * @brief getSignalChannel Returns the active channel through which the signal is directed (SWT 1x2, SWT 1x4)
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response
     * @return true if command was successful
     */
    bool getSignalChannel(ViSession &defaultSession, int slotNum, QByteArray &response);


private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;
};

#endif // EXFO_OSICS_SWT_H
