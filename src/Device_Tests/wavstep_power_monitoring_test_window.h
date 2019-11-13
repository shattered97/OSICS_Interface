#ifndef WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
#define WAVSTEP_POWER_MONITORING_TEST_WINDOW_H

#include "constants.h"
#include "wavstep_power_monitoring_graph_window.h"
#include "ConversionUtilities.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QSettings>
#include <QDateTime>
#include <QCheckBox>
#include <QFileDialog>

namespace Ui {
class WavStep_Power_Monitoring_Test_Window;
}

class WavStep_Power_Monitoring_Test_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavStep_Power_Monitoring_Test_Window(QWidget *parent = nullptr);
    ~WavStep_Power_Monitoring_Test_Window();

    /**
     * @brief showEvent Override for show() method. Performs setup only if this is the first
     *                  time show() is being called.
     */
    void showEvent(QShowEvent* event);

    /**
     * @brief closeEvent Override to signal to worker threads to finish when test window is closed.
     */
    void closeEvent(QCloseEvent* event);

    /**
     * @brief updateSettings Updates QSettings object with the current test parameters on the GUI.
     */
    void updateSettings();


signals:
    void signalBeginTest(QSettings *settings);
    void signalGetT100DisplayNames(QList<QByteArray> &displayNames);
    void signalGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &powerMeterDisplayPairs);
    void signalSwitchMapChanged(QMap<int, QByteArray> swtChannelToT100Map);
    void signalPollForPowerMeterReadings();
    void signalShowGraphWindow();
    void signalStopAllWorkerThreads();
    void signalTestWindowClosed();

public slots:
    /**
     * @brief slotUpdateMinMaxWavelength Populates the GUI with values for the min and max wavelength
     *                                   of the entire test.
     *
     * @param minWav Min wavelength to display
     * @param maxWav Max wavelength to display
     */
    void slotUpdateMinMaxWavelength(double minWav, double maxWav);
    void slotDisplayPowerReadings(QByteArray powerMeterIdentity, QList<QByteArray> readings);
    void slotTestCompleted();

private slots:

    void on_beginTestPB_clicked();

    /**
     * @brief on_swtChannel1ComboBox_currentIndexChanged Makes call to handle the change
     */
    void on_swtChannel1ComboBox_currentIndexChanged();

    /**
     * @brief on_swtChannel2ComboBox_currentIndexChanged Makes call to handle the change
     */
    void on_swtChannel2ComboBox_currentIndexChanged();

    /**
     * @brief on_swtChannel3ComboBox_currentIndexChanged Makes call to handle the change
     */
    void on_swtChannel3ComboBox_currentIndexChanged();

    /**
     * @brief on_swtChannel4ComboBox_currentIndexChanged Makes call to handle the change
     */
    void on_swtChannel4ComboBox_currentIndexChanged();

    /**
     * @brief on_startWavLineEdit_editingFinished Checks if entered start wavelength is valid. If not, and error msg
     *                                            is displayed and the field is cleared. Calculates new est. runtime.
     */
    void on_startWavLineEdit_editingFinished();

    /**
     * @brief on_endWavLineEdit_editingFinished Checks if entered end wavelength is valid. If not, and error message
     *                                          is displayed and the field is cleared. Calculates new est. runtime.
     */
    void on_endWavLineEdit_editingFinished();

    /**
     * @brief on_dwellLineEdit_editingFinished Checks if entered dwell is valid. If not valid, an error message is
     *                                         displayed and the field is cleared. Calculates new est. runtime.
     */
    void on_dwellLineEdit_editingFinished();

    /**
     * @brief on_stepSizeLineEdit_editingFinished Checks if entered step size is valid. If not valid, an error message
     *                                            is displayed and the field is cleared. Calculates new est. runtime
     */
    void on_stepSizeLineEdit_editingFinished();

    /**
     * @brief on_dwellMinRadioButton_clicked Converts and displays the dwell time in minutes.
     */
    void on_dwellMinRadioButton_clicked();

    /**
     * @brief on_dwellSRadioButton_clicked Displays the dwell time in seconds.
     */
    void on_dwellSRadioButton_clicked();

    /**
     * @brief on_dwellMsecRadioButton_clicked Converts and displays the dwell time in milliseconds.
     */
    void on_dwellMsecRadioButton_clicked();

    /**
     * @brief on_openGraphWindowButton_clicked Emits a signal to the test class to open/display the graph window.
     */
    void on_openGraphWindowButton_clicked();

    /**
     * @brief on_selectCsvLocButton_clicked Opens a QFileDialog so the user can select the output file they want
     *                                      for the .csv file. Displays chosen filename if valid.
     */
    void on_selectCsvLocButton_clicked();

    /**
     * @brief on_graphRefreshRateEdit_editingFinished Activated when a user changes the graph refresh rate. Checks if
     *                                                 entered value is valid. If not valid, an error message is
     *                                                 displayed and the field is cleared.
     */
    void on_graphRefreshRateEdit_editingFinished();

    /**
     * @brief slotDisplayCurrentWavelength Updates the current wavelength field with the passed-in wavelength.
     * @param wavelength Wavelength to display
     */
    void slotDisplayCurrentWavelength(QByteArray wavelength);


    void on_saveConfigBtn_clicked();
    
    void on_loadConfigBtn_clicked();
    
    void on_seriesDataPointsEdit_editingFinished();

private:
    Ui::WavStep_Power_Monitoring_Test_Window *ui;

    QSettings *settings;
    bool t100SelectedForSwitch = false;
    QList<QByteArray> seriesNames;
    QMap<int, QByteArray> swtChannelToT100Map;
    QList<QPair<QByteArray, int>> powerMeterDisplayPairs;
    double dwellTimeInSeconds = 0;
    WavStep_Power_Monitoring_Graph_Window *graphWindow;
    bool isConfigured = false;
    QString settingsFileName;

    /**
     * @brief isInputValueValid Checks if the passed in input value is valid (non-empty and non-numeric). If the
     *                          value is non-numeric, an error message is dispalyed.
     * @param inputValue Value to check
     * @return true if valid
     */
    bool isInputValueValid(QByteArray inputValue);

    /**
     * @brief handleWavelengthErrorCases Handles error cases specific to setting the wavelength values such as checking
     *                                   if the min/max wavelengths have been established and if the value is in range
     * @param lineEdit Wavelength line edit (either start wavelength or end wavelength)
     */
    void handleWavelengthErrorCases(QLineEdit *lineEdit);

    /**
     * @brief calculateTestRuntime Calculates and displays the estimated test runtime if all necessary fields have been
     *                             filled in.
     */
    void calculateTestRuntime();

    /**
     * @brief convertDwellToSeconds Converts the passed in dwell time to the unit indicated by the currently selected
     *                              dwell unit radio button
     * @param dwell Dwell to convert (from the line edit)
     * @return Dwell in seconds
     */
    double convertDwellToSeconds(double dwell);
    void populatePowerMeterListWidget();
    void populateSwitchChannelSelectionDropdowns();
    void populateSwtChannelToT100Map();
    void handleSwitchDropdownAction(QComboBox &dropdown);
    QList<QByteArray> getSeriesNames();
    bool areAllFieldsCompleted();

    void saveSettings();
    void loadSettings();

    void disableFieldsOnTestStart();
    void enableFieldsOnTestFinish();

};

#endif // WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
