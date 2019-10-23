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
    EXFO_OSICS_T100 *t100Module;                    /* An EXFO T100 module to step output wavelengths */
    int swtChannel;                                 /* The channel (1-4) on the SWT module to make active */
    double startWav;                                /* Start wavelength for the T100 module */
    double endWav;                                  /* End wavelength for the T100 module */
} TestParamsForT100;

typedef struct TestData{
    EXFO_OSICS_SWT *swtModule;                      /* The SWT 1x4 module installed in the EXFO Chassis */
    QList<PowerMeter*> powerMeters;                 /* List of power meters selected for this test */
    QList<TestParamsForT100> testParamsForT100;     /* List of parameters for each T100 module */
    QByteArray filename;                            /* Output filename of .csv */
    double graphRefreshRate;                        /* Refresh rate of live graphing utility */
    double dwellInMs;                               /* Amount of time to wait before stepping up wavelength */
    double stepSize;                                /* Amount (nm) to step up wavelength */
} TestData;


class WavStep_Power_Monitoring_Test_Worker : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_Test_Worker(TestData testData, QObject *parent = nullptr);
    ~WavStep_Power_Monitoring_Test_Worker();


signals:
    /**
     * @brief finished Signal from QThread, emitted when the thread is done executing.
     */
    void finished();

    /**
     * @brief signalWriteBufferToFile Signals to the file writing worker to output the list of data points
     *                                to the .csv file.
     * @param dataPoints List of data points to write to file.
     */
    void signalWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);

    /**
     * @brief signalAddReadingsToGraph Signals to the graphing window to plot the list of data points.
     * @param dataPoints List of data points to plot on graph.
     */
    void signalAddReadingsToGraph(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);

    /**
     * @brief signalStopWorkerThread Signals to the file worker that it can return.
     */
    void signalStopWorkerThread();


public slots:
    /**
     * @brief runTest Slot executed when this thread is started. Facilitates the wavelength step test.
     */
    void runTest();

    /**
     * @brief slotStopWorkerThreads Ensures all data is written from buffers before signaling to
     *                              the file worker to return;
     */
    void slotStopWorkerThreads();

private:
    TestData testData;                                          /* All parameters needed to execute the step test */
    QElapsedTimer timer;                                        /* Timer to measure when readings were taken */

    QList<WavStep_Power_Monitoring_Data_Point> firstBuffer;     /* One of two buffers for storing .csv data */
    QList<WavStep_Power_Monitoring_Data_Point> secondBuffer;    /* Two of two buffers for storing .csv data */
    bool usingFirstBuffer = true;                               /* Flag to determine which buffer to use */
    int maxBufferSize = WAVSTEP_OUTPUT_CSV_BUFFER_SIZE;         /* Max size of one buffer before switching to other */

    WavStep_Power_Monitoring_File_Worker *fileWriteWorker;      /* Object for facilitating .csv writing */
    QThread *fileWorkerThread;                                  /* Thread to carry out .csv writing */

    /**
     * @brief initializeT100Modules Iterates through T100 modules and sets the start wavelength on each.
     */
    void initializeT100Modules();

    /**
     * @brief executeTestOnT100Module Executes the wavelength step test on each T100 module based on its
     *                                test parameters.
     * @param testParams Information about the T100's start/end wavelength, SWT channel, etc.
     */
    void executeTestOnT100Module(TestParamsForT100 testParams);

    /**
     * @brief executeTestStep Carries out a wavelength step and power meter reading. Sets wavelength on T100 and
     *                        power meters, collects readings and stores/signals out the result.
     * @param currentWavelength The current wavelength to set in the test loop.
     * @param testParams Information about the T100's start/end wavelength, SWT channel, etc.
     */
    void executeTestStep(double currentWavelength, TestParamsForT100 testParams);

    /**
     * @brief setWavelengthOnPowerMeters
     * @param wavelength
     */
    void setWavelengthOnPowerMeters(QByteArray wavelength);

    /**
     * @brief setupFileWriteWorker Initializes and starts the thread for writing data to the .csv file
     */
    void setupFileWriteWorker();

    /**
     * @brief addDataToFileBuffer Appends a data point to the active buffer
     * @param testDataPoint Data point to add to buffer for file output
     */
    void addDataToFileBuffer(WavStep_Power_Monitoring_Data_Point testDataPoint);
};

#endif // WAVSTEP_POWER_MONITORING_TEST_WORKER_H
