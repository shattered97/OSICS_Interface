#ifndef TESTSETUPWINDOW_H
#define TESTSETUPWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "Orchestrator.h"
#include "N7714A.h"
#include "KeysightPowerMeter.h"

namespace Ui {
class TestSetupWindow;
}

class TestSetupWindow : public QMainWindow
{
    Q_OBJECT

public:
    TestSetupWindow(Orchestrator &orchestrator, QByteArray laserInfo, QByteArray powerMeterInfo, QWidget *parent = nullptr);
    ~TestSetupWindow();

private slots:

    void on_testCommandEdit_returnPressed();

    void on_startWavLineEdit_returnPressed();

    void on_endWavLineEdit_returnPressed();

    void on_dwellLineEdit_returnPressed();

    void on_stepSizeLineEdit_returnPressed();

    void on_beginTestPB_clicked();

private:
    Ui::TestSetupWindow *ui;

    Orchestrator *orchestrator;
    ViSession *defaultSession;

    N7714A *laserSource;
    KeysightPowerMeter *powerMeter;

    double minWavelength;
    double maxWavelength;
    int dwell = 0;
    double stepSize = 0;

    double startWavelength = 0;
    double endWavelength = 0;

    void getMinMaxWavelength();
    void addPowerMeterChannels();
    double convertSciToDouble(QByteArray sci);
    double convertMeterToNanoMeter(double meter);
    void setTime(double calculatedTime);
};

#endif // TESTSETUPWINDOW_H
