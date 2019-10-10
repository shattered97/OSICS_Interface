#ifndef WAVSTEP_POWER_MONITORING_TEST_WORKER_H
#define WAVSTEP_POWER_MONITORING_TEST_WORKER_H

#include <QObject>
#include <QThread>
#include <EXFO_OSICS_T100.h>
#include <PowerMeter.h>
#include <EXFO_OSICS_SWT.h>


typedef struct TestParamsForT100{
    EXFO_OSICS_T100 *t100Module;
    int swtChannel;
    double startWav;
    double endWav;
} TestParamsForT100;

typedef struct TestData{
    EXFO_OSICS_SWT *swtModule;
    QList<PowerMeter*> powerMeters;
    QList<TestParamsForT100> testParamsForT100;
    double dwellInMs;
    double stepSize;
} TestData;



class WavStep_Power_Monitoring_Test_Worker : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_Test_Worker(TestData testData, QObject *parent = 0);

signals:
    void finished();

public slots:
    void runTest();

private:
    TestData testData;
    void executeTestOnT100Module(TestParamsForT100 testParams);
    void executeTestStep(double currentWavelength, TestParamsForT100 testParams);
    void setWavelengthOnPowerMeters(QByteArray wavelength);
};

#endif // WAVSTEP_POWER_MONITORING_TEST_WORKER_H