#ifndef WAVSTEP_POWER_MONITORING_TEST_WORKER_H
#define WAVSTEP_POWER_MONITORING_TEST_WORKER_H

#include <QObject>
#include <QThread>
#include <EXFO_OSICS_T100.h>
#include <PowerMeter.h>
#include <EXFO_OSICS_SWT.h>
#include <QMutexLocker>
#include <QMutex>


typedef struct TestData{
    EXFO_OSICS_T100 *t100Module;
    EXFO_OSICS_SWT *swtModule;
    int swtChannel;
    PowerMeter* powerMeter;
    double startWav;
    double endWav;
    double dwellInMs;
    double stepSize;
} TestData;

class WavStep_Power_Monitoring_Test_Worker : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_Test_Worker(TestData testData, QMutex *powerMeterLock, QObject *parent = 0);

signals:
    void finished();

public slots:
    void runTest();

private:
    TestData testData;
    QMutex *powerMeterLock;
    void executeTestStep(double currentWavelength);
};

#endif // WAVSTEP_POWER_MONITORING_TEST_WORKER_H
