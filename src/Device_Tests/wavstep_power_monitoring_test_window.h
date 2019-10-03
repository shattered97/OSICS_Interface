#ifndef WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
#define WAVSTEP_POWER_MONITORING_TEST_WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QSettings>
#include <QDateTime>
#include "constants.h"
#include "wavstep_power_monitoring_graph_window.h"


namespace Ui {
class WavStep_Power_Monitoring_Test_Window;
}

class WavStep_Power_Monitoring_Test_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavStep_Power_Monitoring_Test_Window(QWidget *parent = nullptr);
    ~WavStep_Power_Monitoring_Test_Window();
    void showEvent(QShowEvent* event);
    void updateSettings();
signals:
    void signalBeginTest(QSettings *settings);
    void signalGetT100DisplayNames(QList<QByteArray> &displayNames);
    void signalGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &powerMeterDisplayPairs);
    void signalSwitchMapChanged(QMap<int, QByteArray> swtChannelToT100Map);
    void signalPollForPowerMeterReadings();
    void signalShowGraphWindow();

public slots:
    void slotUpdateMinMaxWavelength(double minWav, double maxWav);
    void slotDisplayPowerReadings(QByteArray powerMeterIdentity, QList<QByteArray> readings);

private slots:

    void on_beginTestPB_clicked();

    void on_swtChannel1ComboBox_currentIndexChanged(const QString &arg1);

    void on_swtChannel2ComboBox_currentIndexChanged(const QString &arg1);

    void on_swtChannel3ComboBox_currentIndexChanged(const QString &arg1);

    void on_swtChannel4ComboBox_currentIndexChanged(const QString &arg1);

    void on_startWavLineEdit_editingFinished();

    void on_endWavLineEdit_editingFinished();

    void on_dwellLineEdit_editingFinished();

    void on_stepSizeLineEdit_editingFinished();

    void on_dwellMinRadioButton_clicked();

    void on_dwellSRadioButton_clicked();

    void on_dwellMsecRadioButton_clicked();

    void on_openGraphWindowButton_clicked();

private:
    Ui::WavStep_Power_Monitoring_Test_Window *ui;

    QSettings *settings;
    void populateSwitchChannelSelectionDropdowns();
    void populateSwtChannelToT100Map();

    bool t100SelectedForSwitch = false;
    void handleSwitchDropdownAction(QComboBox *dropdown);
    QMap<int, QByteArray> swtChannelToT100Map;
    QList<QPair<QByteArray, int>> powerMeterDisplayPairs;
    double dwellTimeInSeconds = 0;

    WavStep_Power_Monitoring_Graph_Window *graphWindow;

    bool isInputValueValid(QByteArray inputValue);
    void handleWavelengthErrorCases(QLineEdit *lineEdit);

    void calculateTestRuntime();
    double convertDwellToSeconds(double dwell);
    void populatePowerMeterListWidget();
    QList<QByteArray> seriesNames;
    QList<QByteArray> getSeriesNames();

};

#endif // WAVSTEP_POWER_MONITORING_TEST_WINDOW_H
