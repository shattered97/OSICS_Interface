#ifndef EXFO_OSICS_SWT_H
#define EXFO_OSICS_SWT_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_SWT :  EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc);

    // ****************************** SWT-APC Commands ***********************************

    /**
     * @brief setAPCModuleOperatingMode Selects the SWT-APC operating mode (SWT/ECL)
     *         Base command: CH#:MODE
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param mode Operating mode - SWT (Switch mode) | ECL (Full-band mode)
     * @return true if command was successful
     */
    bool setAPCModuleOperatingMode(ViSession &defaultSession, int slotNum, QByteArray &mode);

    /**
     * @brief getAPCModuleOperatinGMode Returns the operating mode of the SWT-APC module
     *         Base command: CH#:MODE?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - SWT (Switch mode) | ECL (Full-band mode)
     * @return true if command was successful
     */
    bool getAPCModuleOperatinGMode(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief autoDetectT100Modules Automatically detects connected T100 modules (only available in Full-band mode)
     *         Base command: CH#:ACFG
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool autoDetectT100Modules(ViSession &defaultSession, int slotNum);

    /**
     * @brief selectChannelForSignalAPC Selects the channel through which the signal will be directed
     *         Base command: CH#:CLOSE=
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param channelNum Channel number to activate in the range 1-4
     * @return true if command was successful
     */
    bool selectChannelForSignalAPC(ViSession &defaultSession, int slotNum, QByteArray &channelNum);

    /**
     * @brief getChannelForSignalAPC Returns the active channel through which the signal is directed
     *         Base command: CH#:CLOSE?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Active channel number 1-4
     * @return true if command was successful
     */
    bool getChannelForSignalAPC(ViSession &defaultSession, int slotNum, QByteArray &response);


    // ********************************** SWT Commands *************************************

    /**
     * @brief shutSingleShutter Shuts the shutter of a SWT 1x1 module
     *         Base command: CH#:SHUT
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool shutSingleShutter(ViSession &defaultSession, int slotNum);

    /**
     * @brief openSingleShutter Opens the shutter of a SWT 1x1 module
     *         Base command: CH#:OPEN
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool openSingleShutter(ViSession &defaultSession, int slotNum);

    /**
     * @brief getSingleShutterState Returns the state of the SWT 1x1 shutter
     *         Base command: CH#:SHUT?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (shutter is shut) | FALSE (shutter is open)
     * @return true if command was successful
     */
    bool getSingleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief openCloseShutters Opens or closes A-B and/or 1-2 shutters on the SWT 2x(1x1)
     *         Base command: CH#:SHUTMODE
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param shutterAB Output mode of the A-B shutter - 0 (closes shutter) | 1 (opens shutter)
     * @param shutter12 Output mode of the 1-2 shutter - 0 (closes shutter) | 1 (opens shutter)
     * @return true if command was successful
     */
    bool openCloseShutters(ViSession &defaultSession, int slotNum, QByteArray &shutterAB, QByteArray &shutter12);

    /**
     * @brief getMultipleShutterState Returns the output power mode of the A-B and 1-2 shutters on SWT 2x(1x1)
     *         Base command: CH#:SHUTMODE?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - Output format: "CH#:SHUTMODE 0|1 0|1"
     * @return true if command was successful
     */
    bool getMultipleShutterState(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief setSwitchModeBar Sets the switch output mode to Bar (A linked to 1, B liked to 2)
     *         Base command: CH#:BAR
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setSwitchModeBar(ViSession &defaultSession, int slotNum);

    /**
     * @brief setSwitchModeCross Sets the switch output mode to Cross (A linked to 2, B linked to 1)
     *         Base command: CH#:CROSS
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    bool setSwitchModeCross(ViSession &defaultSession, int slotNum);

    /**
     * @brief getSwitchMode Returns the output mode (Cross/Bar) of the switch
     *         Base command: CH#:BAR?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (switch set to Bar) | FALSE (switch set to cross)
     * @return true if command was successful
     */
    bool getSwitchMode(ViSession &defaultSession, int slotNum, QByteArray &response);

    /**
     * @brief selectSignalChannel Selects the channel through which the signal is directed (SWT 1x2 and SWT 1x4)
     *         Base command: CH#:CH
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param channel Channel number (1-2 or 1-4 depending on module)
     * @return true if command was successful
     */
    bool selectSignalChannel(ViSession &defaultSession, int slotNum, QByteArray &channel);

    /**
     * @brief getSignalChannel Returns the active channel through which the signal is directed (SWT 1x2, SWT 1x4)
     *        Base command: CH#:CH?
     * @param defaultSession Default communication session
     * @param slotNum Target slot number
     * @param response Response from instrument - channel number (1-4)
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
