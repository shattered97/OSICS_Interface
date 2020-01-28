#ifndef EXFO_T100_PM_POWER_STEP_TEST_WINDOW_H
#define EXFO_T100_PM_POWER_STEP_TEST_WINDOW_H

#include "constants.h"
#include "ConversionUtilities.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QComboBox>
#include <QVBoxLayout>

namespace Ui {
class EXFO_T100_PM_Power_Step_Test_Window;
}

class EXFO_T100_PM_Power_Step_Test_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit EXFO_T100_PM_Power_Step_Test_Window(QWidget *parent = nullptr);
    ~EXFO_T100_PM_Power_Step_Test_Window();

    /**
     * @brief showEvent Override for show() method. Performs setup only if this is the first
     *                  time show() is being called (populating default values, etc).
     */
    void showEvent(QShowEvent* event);

signals:

    /**
     * @brief signalGetT100DisplayNames Queries the test class for a list of formatted strings formatted
     * for display in the T100 selection drop-down. Format: "<T100 type>, Slot <x>".
     * @param displayNames List of strings representing each T100 module available and their slot numbers.
     */
    void signalGetT100DisplayNames(QList<QByteArray> &displayNames);

    /**
     * @brief signalGetPowerMeterChannels Queries the test class for the number of available power meter
     * channels/slots.
     */
    void signalGetPowerMeterChannels(int &numberOfSlots);

    /**
     * @brief signalBeginTest Triggers the test class to begin executing the test with test parameters
     * specified in the QSettings object.
     * @param settings Test settings specified by the user.
     */
    void signalBeginTest(QSettings *settings);

private slots:

    /**
     * @brief on_t100ComboBox_currentIndexChanged Clears the wavelength text field when a new T100 is selected. This
     * prevents issues where a user has already entered a wavelength, but selects a T100 that does not support
     * that wavelength.
     *
     * @param selectedText Default Qt param - can be used for debug/logging
     */
    void on_t100ComboBox_currentIndexChanged(const QString &selectedText);

    /**
     * @brief on_startPowerEdit_editingFinished Performs any error-checking required when a user enters
     * a start power value. QMessageBoxes will be executed if what was entered is invalid.
     */
    void on_startPowerEdit_editingFinished();

    /**
     * @brief on_startPowerEdit_editingFinished Performs any error-checking required when a user enters
     * an end power value. QMessageBoxes will be executed if what was entered is invalid.
     */
    void on_endPowerEdit_editingFinished();

    /**
     * @brief on_startPowerEdit_editingFinished Performs any error-checking required when a user enters
     * a step size value. QMessageBoxes will be executed if what was entered is invalid.
     */
    void on_powerStepSizeEdit_editingFinished();

    /**
     * @brief on_startPowerEdit_editingFinished Performs any error-checking required when a user enters
     * a dwell value. QMessageBoxes will be executed if what was entered is invalid.
     */
    void on_dwellEdit_editingFinished();

    /**
     * @brief on_startPowerEdit_editingFinished Performs any error-checking required when a user enters
     * a wavelength value. QMessageBoxes will be executed if what was entered is invalid.
     */
    void on_wavelengthEdit_editingFinished();

    /**
     * @brief on_startTestButton_clicked Ensures all test parameter inputs were successfully entered and
     * queries the user to confirm the test selections before triggering the test.
     */
    void on_startTestButton_clicked();

    void on_showTestDescriptionButton_clicked();

    void slotProcessPowerMeterChannelChange(int);

    void slotTestComplete();

    void slotReceiveTestProgress(double progressPercent);

private:
    Ui::EXFO_T100_PM_Power_Step_Test_Window *ui;

    // used for passing test settings to the test class (and to/from a config file)
    QSettings *settings;

    bool isConfigured = false;

    QList<QByteArray> t100DisplayNames;

    QList<QLabel*> t100DisplayLabel;

    QList<QComboBox*> powerMeterDropdowns;

    QList<QString> availablePowerMeterChannels;

    QList<QString> selectedPowerMeterChannels;

    QList<QString> allPowerMeterChannelOptions;

//    /**
//     * @brief populateT100SelectionComboBox Populates the T100 dropdown to contain one element per availalbe T100
//     * formatted in the following manner: "<T100 type>, Slot <x>".
//     */
//    void populateT100SelectionComboBox();

//    /**
//     * @brief populatePowerMeterSlotComboBox Populates the dropdown for power meter slot selection with one element
//     * per the number of the available slots. E.g. If there are 4 slots the elements will be "1", "2", "3", "4".
//     */
//    void populatePowerMeterSlotComboBox();

    /**
     * @brief areAllFieldsCompleted Checks if all required test settings fields in the GUI have been set.  This check
     * is made when the user clicks the start test button.
     * @return True if all required test parameters have been entered, false otherwise.
     */
    bool areAllFieldsCompleted();

    /**
     * @brief enableFieldsOnTestEnd Enables any fields that were disabled when the test started, allowing users to
     * edit them again.
     */
    void enableFieldsOnTestEnd();

    /**
     * @brief disableFieldsOnTestStart Disables (greys-out) any fields that we don't want the user to touch while the
     * test is running.
     */
    void disableFieldsOnTestStart();

    /**
     * @brief updateSettings Populates the QSettings object (communicates the test settings from the GUI to the test
     * class) with the test values selected by the user.
     */
    void updateSettings();

    /**
     * @brief isInputValueNumeric Determines if a text field's value is numeric - specifically, not empty and will
     * successfully convert to a double (contains no letters/other symbols).
     * @param inputValue String value to check
     * @return True if the string value is numeric, false otherwise.
     */
    bool isInputValueNumeric(QByteArray inputValue);

    void populateAvailableT100s();

    void populatePowerMeterSlots();
};

#endif // EXFO_T100_PM_POWER_STEP_TEST_WINDOW_H
