#ifndef EXFO_OSICS_SWT_H
#define EXFO_OSICS_SWT_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_SWT :  public EXFO_OSICS_MAINFRAME
{
    Q_OBJECT
public:
    EXFO_OSICS_SWT(QByteArray theIdentity, QByteArray theInstrLoc);

    // ****************************** SWT-APC Commands ***********************************

    /**
     * @brief setAPCModuleOperatingMode Selects the SWT-APC operating mode (SWT/ECL)
     *         Base command: CH#:MODE
     * @param slotNum Target slot number
     * @param mode Operating mode - SWT (Switch mode) | ECL (Full-band mode)
     * @return true if command was successful
     */
    void setAPCModuleOperatingMode(int slotNum, QByteArray &mode);

    /**
     * @brief getAPCModuleOperatinGMode Returns the operating mode of the SWT-APC module
     *         Base command: CH#:MODE?
     * @param slotNum Target slot number
     * @param response Response from instrument - SWT (Switch mode) | ECL (Full-band mode)
     * @return true if command was successful
     */
    void getAPCModuleOperatingMode(int slotNum, QByteArray &response);

    /**
     * @brief autoDetectT100Modules Automatically detects connected T100 modules (only available in Full-band mode)
     *         Base command: CH#:ACFG
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void autoDetectT100Modules(int slotNum);

    /**
     * @brief selectChannelForSignalAPC Selects the channel through which the signal will be directed
     *         Base command: CH#:CLOSE=
     * @param slotNum Target slot number
     * @param channelNum Channel number to activate in the range 1-4
     * @return true if command was successful
     */
    void selectChannelForSignalAPC(int slotNum, QByteArray &channelNum);

    /**
     * @brief getChannelForSignalAPC Returns the active channel through which the signal is directed
     *         Base command: CH#:CLOSE?
     * @param slotNum Target slot number
     * @param response Active channel number 1-4
     * @return true if command was successful
     */
    void getChannelForSignalAPC(int slotNum, QByteArray &response);


    // ********************************** SWT Commands *************************************

    /**
     * @brief shutSingleShutter Shuts the shutter of a SWT 1x1 module
     *         Base command: CH#:SHUT
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void shutSingleShutter(int slotNum);

    /**
     * @brief openSingleShutter Opens the shutter of a SWT 1x1 module
     *         Base command: CH#:OPEN
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void openSingleShutter(int slotNum);

    /**
     * @brief getSingleShutterState Returns the state of the SWT 1x1 shutter
     *         Base command: CH#:SHUT?
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (shutter is shut) | FALSE (shutter is open)
     * @return true if command was successful
     */
    void getSingleShutterState(int slotNum, QByteArray &response);

    /**
     * @brief openCloseShutters Opens or closes A-B and/or 1-2 shutters on the SWT 2x(1x1)
     *         Base command: CH#:SHUTMODE
     * @param slotNum Target slot number
     * @param shutterAB Output mode of the A-B shutter - 0 (closes shutter) | 1 (opens shutter)
     * @param shutter12 Output mode of the 1-2 shutter - 0 (closes shutter) | 1 (opens shutter)
     * @return true if command was successful
     */
    void openCloseShutters(int slotNum, QByteArray &shutterAB, QByteArray &shutter12);

    /**
     * @brief getMultipleShutterState Returns the output power mode of the A-B and 1-2 shutters on SWT 2x(1x1)
     *         Base command: CH#:SHUTMODE?
     * @param slotNum Target slot number
     * @param response Response from instrument - Output format: "CH#:SHUTMODE 0|1 0|1"
     * @return true if command was successful
     */
    void getMultipleShutterState(int slotNum, QByteArray &response);

    /**
     * @brief setSwitchModeBar Sets the switch output mode to Bar (A linked to 1, B liked to 2)
     *         Base command: CH#:BAR
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setSwitchModeBar(int slotNum);

    /**
     * @brief setSwitchModeCross Sets the switch output mode to Cross (A linked to 2, B linked to 1)
     *         Base command: CH#:CROSS
     * @param slotNum Target slot number
     * @return true if command was successful
     */
    void setSwitchModeCross(int slotNum);

    /**
     * @brief getSwitchMode Returns the output mode (Cross/Bar) of the switch
     *         Base command: CH#:BAR?
     * @param slotNum Target slot number
     * @param response Response from instrument - TRUE (switch set to Bar) | FALSE (switch set to cross)
     * @return true if command was successful
     */
    void getSwitchMode(int slotNum, QByteArray &response);

    /**
     * @brief selectSignalChannel Selects the channel through which the signal is directed (SWT 1x2 and SWT 1x4)
     *         Base command: CH#:CH
     * @param slotNum Target slot number
     * @param channel Channel number (1-2 or 1-4 depending on module)
     * @return true if command was successful
     */
    void selectSignalChannel(int slotNum, QByteArray &channel);

    /**
     * @brief getSignalChannel Returns the active channel through which the signal is directed (SWT 1x2, SWT 1x4)
     *        Base command: CH#:CH?
     * @param slotNum Target slot number
     * @param response Response from instrument - channel number (1-4)
     * @return true if command was successful
     */
    void getSignalChannel(int slotNum, QByteArray &response);

// *********** Functions for Applying/Updating Config Settings **********

    void applyConfigSettings(QSettings &configSettings);
    void updateConfig(QSettings &configSettings);
    void setSlotNum(int slotNum);
    int getSlotNum();
private:

    // identity of instrument (manufacturer, model num, etc.)
    QByteArray theIdentity;

    // the physical address of the instrument
    QByteArray theInstrLoc;

    int slotNum = 1;

    void updateOperatingModeSettings(QSettings &configSettings);
    void updateActiveChannelSettings(QSettings &configSettings);
    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void updateFrequencySettings(QSettings &configSettings);

};

#endif // EXFO_OSICS_SWT_H
