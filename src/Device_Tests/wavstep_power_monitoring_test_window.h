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

public slots:
    /**
     * @brief slotUpdateMinMaxWavelength Populates the GUI with values for the min and max wavelength
     *                                   of the entire test.
     *
     * @param minWav
     * @param maxWav
     */
    void slotUpdateMinMaxWavelength(double minWav, double maxWav);
    void slotDisplayPowerReadings(QByteArray powerMeterIdentity, QList<QByteArray> readings);

private slots:

    void on_beginTestPB_clicked();

    void on_swtChannel1ComboBox_currentIndexChanged();

    void on_swtChannel2ComboBox_currentIndexChanged();

    void on_swtChannel3ComboBox_currentIndexChanged();

    void on_swtChannel4ComboBox_currentIndexChanged();

    void on_startWavLineEdit_editingFinished();

    void on_endWavLineEdit_editingFinished();

    void on_dwellLineEdit_editingFinished();

    void on_stepSizeLineEdit_editingFinished();

    void on_dwellMinRadioButton_clicked();

    void on_dwellSRadioButton_clicked();

    void on_dwellMsecRadioButton_clicked();

    void on_openGraphWindowButton_clicked();

    void on_selectCsvLocButton_clicked();

    void on_pmReadingRefreshRateEdit_editingFinished();

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

    bool isInputValueValid(QByteArray inputValue);
    void handleWavelengthErrorCases(QLineEdit *lineEdit);
    void calculateTestRuntime();
    double convertDwellToSeconds(double dwell);
    void populatePowerMeterListWidget();
    void populateSwitchChannelSelectionDropdowns();
    void populateSwtChannelToT100Map();
    void handleSwitchDropdownAction(QComboBox &dropdown);
    QList<QByteArray> getSeriesNames();
    bool areAllFieldsCompleted();

};

#endif // WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
