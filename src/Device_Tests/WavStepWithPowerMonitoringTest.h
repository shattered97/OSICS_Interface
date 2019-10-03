#ifndef WAVSTEPWITHPOWERMONITORINGTEST_H
#define WAVSTEPWITHPOWERMONITORINGTEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS_T100.h"
#include "EXFO_OSICS_SWT.h"
#include "EXFO_OSICS_ATN.h"
#include "PowerMeter.h"
#include "powermeterpollingworker.h"

class WavStepWithPowerMonitoringTest : public DeviceTest
{
    Q_OBJECT
public:
    WavStepWithPowerMonitoringTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();

signals:
   void signalUpdateMinMaxWavelength(double minWav, double maxWav);
   void signalDisplayPowerReadings(QByteArray powerMeterIdentity, QList<QByteArray> readings);

public slots:
    void slotBeginTest(QSettings *settings);
    void slotGetT100DisplayNames(QList<QByteArray> &displayNames);
    void slotSwitchMapChanged(QMap<int, QByteArray> swtChannelToT100Map);
    void slotGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &powerMeterDisplayPairs);
    void slotPollForPowerMeterReadings();
    void slotSendPowerReadingCommand(PowerMeter *powerMeter);

private:


    // list of t100 modules (must have at least one)
    QList<QPair<EXFO_OSICS_T100 *, int>> t100Modules;

    // assigned modules and corresponding switch channel
    QList<QPair<EXFO_OSICS_T100 *, int>> assignedT100Modules;

    // list of powermeters (can be 1-n)
    QList<PowerMeter *> powerMeters;

    // switch
    EXFO_OSICS_SWT *exfoSWT = nullptr;
    int swtSlotNum = 1;

    // attenuator
    EXFO_OSICS_ATN *exfoATN = nullptr;
    int atnSlotNum = 1;

    QSettings *settings;

    // test values
    QByteArray csvFilename = "";
    QByteArray graphFilename = "";
    double startWav = 0.0;
    double endWav = 0.0;
    double wavStepSize = 0.0;
    double dwellSeconds = 0.0;
    double estimatedTime = 0.0;

    double calculateMinWavelength();
    double calculateMaxWavelength();

    void populateAssignedModules(QMap<int, QByteArray> swtChannelToT100Map);



};

#endif // WAVSTEPWITHPOWERMONITORINGTEST_H
