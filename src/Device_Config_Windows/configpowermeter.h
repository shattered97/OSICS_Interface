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
     * @brief showEvent Override of the show() method. Sets up QSettings object and signals to update it
     */
    void showEvent(QShowEvent* event);


signals:
    /**
     * @brief signalUpdateConfigSettings Asks device to update the QSettings object with the current device state
     * @param device Device to query for settings
     * @param configSettings Settings object to populate
     */
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);

    /**
     * @brief signalApplyConfigSettings Tells the device to apply the settings that exist in the QSettings object
     * @param device Device to apply settings to
     * @param configSettings Settings to apply to device
     */
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);


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


    void on_setNicknameBtn_clicked();

private:
    Ui::ConfigPowerMeter *ui;

    QVariant device;                        // the device to be configured (a power meter)
    QList<QRadioButton*> buttons;           // list of radio buttons - one for each channel on the powe meter
    bool windowConfigured = false;          // flag to determine if the gui needs to be updated when show() is called
    QList<bool> displayTextColored;         // one flag per channel to set if a value needs to be updated on device
    int slotNum = 1;                        // slot number of the currently selected channel in the GUI

    QString settingsFileName;               // filename to store/retrieve QSettings contents
    QSettings *settings;                    // QSettings object to hold config settings

    int numSlots;                           // number of slots (channels) the power meter has
    QList<QByteArray> powerReadings;        // list of power readings from device to be displayed
    QList<QByteArray> wavelengthSettings;   // list of wavelength settings from device to be displayed
    QList<QByteArray> minWavelengths;       // list of min wavelength values to be displayed
    QList<QByteArray> maxWavelengths;       // list of max wavelength values to be displayed
    QByteArray deviceAddress;               // address of device
    QByteArray deviceIdentity;              // identity of device
    QByteArray deviceNickname;              // nickname of device
    bool identityColored = false;
    // =================================== GUI Element Population Methods ==================================

    /**
     * @brief populateIdentityAndLoc Populates the device identity and the device address in the GUI.
     */
    void populateIdentityAndLoc();

    /**
     * @brief populatePowerUnit Populates the displayed power unit with what was selected from the dropdown.
     */
    void populatePowerUnit();

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
