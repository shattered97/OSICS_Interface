#ifndef WAVSTEP_POWER_MONITORING_TEST_WORKER_H
#define WAVSTEP_POWER_MONITORING_TEST_WORKER_H

#include <QObject>
#include <QThread>
#include <EXFO_OSICS_T100.h>
#include <PowerMeter.h>
#include <EXFO_OSICS_SWT.h>
#include "wavstep_power_monitoring_data_point.h"
#include "wavstep_power_monitoring_file_worker.h"


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
    QByteArray filename;
    double powerPollRate;
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
    void signalWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);
    void signalAddReadingsToGraph(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);
public slots:
    void runTest();

private:
    TestData testData;
    QElapsedTimer timer;
    void executeTestOnT100Module(TestParamsForT100 testParams);
    void executeTestStep(double currentWavelength, TestParamsForT100 testParams);
    void setWavelengthOnPowerMeters(QByteArray wavelength);
    void initializeT100Modules();
    QList<WavStep_Power_Monitoring_Data_Point> firstBuffer;
    QList<WavStep_Power_Monitoring_Data_Point> secondBuffer;
    bool usingFirstBuffer = true;
    int maxBufferSize = 100;
    WavStep_Power_Monitoring_File_Worker *fileWriteWorker;
};

#endif // WAVSTEP_POWER_MONITORING_TEST_WORKER_H
