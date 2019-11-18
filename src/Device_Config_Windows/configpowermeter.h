#ifndef CONFIGPOWERMETER_H
#define CONFIGPOWERMETER_H

#include <QMainWindow>
#include <QtMath>
#include <QFileDialog>
#include <QInputDialog>
#include <QSettings>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>

#include "PowerMeter.h"
#include "ConversionUtilities.h"

namespace Ui {
class ConfigPowerMeter;

}

class ConfigPowerMeter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigPowerMeter(QVariant &device, QWidget *parent = nullptr);
    ~ConfigPowerMeter();

    /**
     * @brief showEvent Override of the show() method. Sets up initial objects and signals/slots.  Can't do this
     *                  in the constructor because the signals/slots for this window aren't set up by
     *                  the Orchestrator yet.
     */
    void showEvent(QShowEvent* event);


signals:
    /**
     * @brief signalUpdateConfigSettings Asks device to update the QSettings object with the current device state
     * @param device Device to query for settings
     * @param configSettings Settings object to populate
     */
    void signalUpdateConfigSettings(QVariant device, QSettings *configSettings);

    /**
     * @brief signalApplyConfigSettings Tells the device to apply the settings that exist in the QSettings object
     * @param device Device to apply settings to
     * @param configSettings Settings to apply to device
     */
    void signalApplyConfigSettings(QVariant device, QSettings *configSettings);


public slots:
    /**
     * @brief slotUpdateWindow Clears any GUI text fields, parses new values from QSettings and updates the GUI
     */
    void slotUpdateWindow();


private slots:

    /**
     * @brief slot_radio_button_clicked Sets the channel number variable (slotNum) to match the selected radio button
     *                                  and refreshes the GUI
     */
    void slot_radio_button_clicked();

    /**
     * @brief on_powerUnitComboBox_currentIndexChanged Calls methods to update power unit and displayed power.
     */
    void on_powerUnitComboBox_currentIndexChanged();

    /**
     * @brief on_wavelengthComboBox_currentIndexChanged Calls methods to update wavelength units and display fields.
     */
    void on_wavelengthComboBox_currentIndexChanged();

    /**
     * @brief on_wavelengthEdit_editingFinished Checks if the value entered is valid. If not an error message is
     *                                          displayed. If yes the settings object is updated
     */
    void on_wavelengthEdit_editingFinished();

    /**
     * @brief on_loadSettingsButton_pressed Opens file dialog menu and opens the file selected by the user.
     *                                      Loads the settings that were contained in that file.
     */
    void on_loadSettingsButton_pressed();

    /**
     * @brief on_saveSettingsButton_pressed Opens file dialog menu and creates/selects the file selected by the user.
     *                                      Saves the local QSettings to the selected file.
     */
    void on_saveSettingsButton_pressed();

    /**
     * @brief on_saveChangesButton_clicked Emits signal to apply the changes made on the GUI to the device.
     */
    void on_saveChangesButton_clicked();

    /**
     * @brief on_setNicknameBtn_clicked Opens a QInputDialog for users to enter the desired nickname
     */
    void on_setNicknameBtn_clicked();

    /**
     * @brief on_totalTimeDisplay_editingFinished Checks if the Total Time value is valid. If yes the settings
     *                                            object is updated. If no, an error dialog is opened.
     */
    void on_totalTimeDisplay_editingFinished();

    /**
     * @brief on_periodTimeDisplay_editingFinished Checks if the Period Time value is valid. If yes the settings
     *                                             object is updated. If no, an error dialog is opened.
     */
    void on_periodTimeDisplay_editingFinished();

    /**
     * @brief on_avgTimeDisplay_editingFinished Checks if the Averaging Time value is valid. If yes the settings
     *                                          object is updated. If no, an error dialog is opened.
     */
    void on_avgTimeDisplay_editingFinished();

    /**
     * @brief on_continuousRadioBtn_clicked Changes the QSetting for MinMax mode to Continuous
     */
    void on_continuousRadioBtn_clicked();

    /**
     * @brief on_refreshRadioBtn_clicked Changes the QSetting for MinMax mode to Refresh
     */
    void on_refreshRadioBtn_clicked();

    /**
     * @brief on_dataPointsEdit_editingFinished Checks if the value for Data Points is valid. If yes the settings
     *                                          object is updated.
     */
    void on_dataPointsEdit_editingFinished();

    /**
     * @brief on_timeUnitComboBox_currentIndexChanged Changes the time unit for the page. Values for total, period
     *                                                and averaging time are updated to reflect the unit change.
     * @param unit The unit selected
     */
    void on_timeUnitComboBox_currentIndexChanged(const QString &unit);

private:
    Ui::ConfigPowerMeter *ui;

    QVariant device;                         // the device to be configured (a power meter)
    QByteArray deviceAddress;                // address of device
    QByteArray deviceIdentity;               // identity of device
    QByteArray deviceNickname;               // nickname of device

    QList<QRadioButton*> buttons;            // list of radio buttons - one for each channel on the power meter
    int slotNum = 1;                         // slot number of the currently selected channel in the GUI
    int numSlots;                            // number of slots (channels) the power meter has
    bool windowConfigured = false;           // flag to determine if the gui needs to be updated when show() is called

    QList<bool> wavelengthFieldColored;      // one flag/channel to indicate if the wavlngth field should be colored
    QList<bool> totalTimeTextColored;        // one flag/channel to set the color status of the total time field
    QList<bool> periodTimeTextColored;       // one flag/channel to set the color status for the period time field
    QList<bool> avgTimeTextColored;          // one flag/channel to set the color status of the average time field
    QList<bool> minMaxDataPointsColored;     // one flag/channel to set the color status of the data points field
    QList<bool> minMaxRefreshModeColored;    // one flag/channel to set the color status of the refresh mode button
    QList<bool> minMaxContinuousModeColored; // one flag/channel to set the color status of the continuous mode button

    QString settingsFileName;                // filename to store/retrieve QSettings contents
    QSettings *settings;                     // QSettings object to hold config settings

    QList<QByteArray> powerReadings;         // list of power readings from device to be displayed
    QList<QByteArray> wavelengthSettings;    // list of wavelength settings from device to be displayed
    QList<QByteArray> minWavelengths;        // list of min wavelength values to be displayed
    QList<QByteArray> maxWavelengths;        // list of max wavelength values to be displayed
    QList<QByteArray> totalTimeInSeconds;    // list of total time values to be displayed
    QList<QByteArray> periodTimeInSeconds;   // list of period time values to be displayed
    QList<QByteArray> avgTimeInSeconds;      // list of averaging time values to be displayed
    QList<QByteArray> minMaxMode;            // list of mode values (Continuous or Refresh) to be displayed
    QList<QByteArray> minMaxDataPoints;      // list of num data points (for min/max mode) to be displayed


    // ================================== GUI Element Population Methods ==================================

    /**
     * @brief populateIdentityAndLoc Populates the device identity and the device address in the GUI.
     */
    void populateIdentityAndLoc();

    /**
     * @brief populatePower Populates the displayed power value from the list of current power readings. Converts
     *                      to dBm if needed.
     */
    void populatePower();

    /**
     * @brief populateWavelengthUnit Populates all displayed unit tags with the wavelength unit in the dropdown.
     */
    void populateWavelengthUnit();

    /**
     * @brief populateWavelength Calls method to convert and display the wavelength setting for the selected channel
     */
    void populateWavelength();

    /**
     * @brief populateMinWavelength Calls method to convert and display the min wavelength for the selected channel
     */
    void populateMinWavelength();

    /**
     * @brief populateMaxWavelength Calls method to convert and display the max wavelength for the selected channel
     */
    void populateMaxWavelength();

    /**
     * @brief populateAllValues Calls all methods needed to refresh displayed GUI values
     */
    void populateAllValues();

    /**
     * @brief populateTotalTime Converts and displays the value for Total Time
     */
    void populateTotalTime();

    /**
     * @brief populatePeriodTime Converts and displays the value for Period Time
     */
    void populatePeriodTime();

    /**
     * @brief populateAvgTime Converts and displays the value for Averaging Time
     */
    void populateAvgTime();

    /**
     * @brief populateMinMaxMode Selects the radio button that corresponds with the MinMax Mode value
     */
    void populateMinMaxMode();

    /**
     * @brief populateMinMaxDataPoints Displays the value for number of Data Points
     */
    void populateMinMaxDataPoints();

    /**
     * @brief initChannelRadioButtons Adds a radio button to the GUI for every channel that exists on the power meter
     */
    void initChannelRadioButtons();

    /**
     * @brief convertAndDisplayWavelength Helper method to convert a wavelength value to the unit selected by the
     *                                    dropdown menu and display it
     * @param wavelength Wavelength to convert
     * @param displayField Field to display result
     */
    void convertAndDisplayWavelength(QList<QByteArray> wavelength, QLineEdit* displayField);

    /**
     * @brief resetDisplayFieldColoredStatus Resets the list of color status flags and clears the GUI of coloring
     */
    void resetDisplayFieldColoredStatus();

    /**
     * @brief colorDisplayFieldText Calls the colorText method on all necessary GUI fields
     */
    void colorDisplayFieldText();

    /**
     * @brief colorText Colors the text of the passed in QLineEdit based on the colored flag
     * @param textField Text field to color
     * @param colored Flag indicating whether the field will be colored blue or the default color
     */
    void colorText(QLineEdit *textField, bool colored);


    // ================================ Config Settings Helper Methods ====================================

    /**
     * @brief saveSettings Takes the state of the current QSettings object and applies it to a QSettings object created
     *                     from the config filename. Syncs when finished to apply changes.
     */
    void saveSettings();

    /**
     * @brief loadSettings Takes the QSettings from the selected config file and applies them to our internal QSettings
     *                     object. Signals to apply the new settings to the device.
     */
    void loadSettings();

    /**
     * @brief getValuesFromConfig Parses config values from QSettings object into individual data fields.
     */
    void getValuesFromConfig();

};

#endif // CONFIGPOWERMETER_H
