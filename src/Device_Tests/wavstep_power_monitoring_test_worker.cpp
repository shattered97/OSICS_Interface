#include "wavstep_power_monitoring_test_worker.h"
#include "ConversionUtilities.h"
WavStep_Power_Monitoring_Test_Worker::WavStep_Power_Monitoring_Test_Worker(TestData testData, QObject *parent) : QObject(parent)
{
    this->testData = testData;
}

WavStep_Power_Monitoring_Test_Worker::~WavStep_Power_Monitoring_Test_Worker()
{
}

void WavStep_Power_Monitoring_Test_Worker::runTest()
{

    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!! test worker thread id: " << QThread::currentThread();

    // setup file output worker
    setupFileWriteWorker();

    // setup modules
    initializeT100Modules();

    int swtSlotNum = testData.swtModule->getSlotNum();

    // make sure switch is in full band mode
    testData.swtModule->setAPCModuleOperatingMode(swtSlotNum, "ECL");
//    QMetaObject::invokeMethod(testData.swtModule, "setAPCModuleOperatingMode",
//                              Qt::BlockingQueuedConnection, Q_ARG(int, swtSlotNum),
//                              Q_ARG(QByteArray, "ECL"));

    // enable laser output for switch (turns on all lasers)
    testData.swtModule->enableModuleLaserCmd(swtSlotNum);

    // start timer
    timer.start();

    // execute test steps
    for(auto testParams : testData.testParamsForT100){
        executeTestOnT100Module(testParams);
    }

    // #TEST read power to see if test waits at end before emitting signal to close
    for(auto powerMeter : testData.powerMeters){
        QList<QByteArray> readings = powerMeter->getPowerReadingOnAllChannels();
    }

    // send last buffer to be written
    if(usingFirstBuffer){
        qDebug() << "writing first buffer";
        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                  Q_ARG(QList<WavStepPowerMonitoringDataPoint>, firstBuffer));
    }
    else{
        qDebug() << "writing second buffer";
        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                  Q_ARG(QList<WavStepPowerMonitoringDataPoint>, secondBuffer));
    }

    // tell the file worker thread it can finish
    emit signalStopFileWorkerThread();

    // wait for file worker to finish
    fileWorkerThread->quit();
    fileWorkerThread->wait();

    // emit signal that test is complete
    emit signalTestCompleted();

    // close this worker
    emit finished();
}

void WavStep_Power_Monitoring_Test_Worker::setupFileWriteWorker()
{
    // initialize thread object
    fileWorkerThread = new QThread;
    fileWriteWorker = new WavStep_Power_Monitoring_File_Worker(testData.filename);
    fileWriteWorker->moveToThread(fileWorkerThread);
    // name threads
    fileWorkerThread->setObjectName("File output worker Thread");

    connect(fileWriteWorker, SIGNAL(finished()), fileWorkerThread, SLOT(quit()));
    connect(fileWorkerThread, SIGNAL(started()), fileWriteWorker, SLOT(startFileOutputWorker()));
    connect(fileWriteWorker, SIGNAL(finished()), fileWriteWorker, SLOT(deleteLater()));
    connect(fileWorkerThread, SIGNAL(finished()), fileWorkerThread, SLOT(deleteLater()));

    connect(this, SIGNAL(signalWriteBufferToFile(QList<WavStepPowerMonitoringDataPoint>)),
            fileWriteWorker, SLOT(slotWriteBufferToFile(QList<WavStepPowerMonitoringDataPoint>)));
    connect(this, SIGNAL(signalStopFileWorkerThread()), fileWriteWorker, SLOT(slotStopThread()));
    // run thread
    fileWorkerThread->start();
}

void WavStep_Power_Monitoring_Test_Worker::initializeT100Modules()
{
//    // for each module set initial wavelength (so modules are primed when switched over to)
//    for(auto testParam : testData.testParamsForT100){
//        int t100SlotNum = testParam.t100Module->getSlotNum();
//        QByteArray wavelengthToSet = QByteArray::number(testParam.startWav);
//        testParam.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);
//    }
}

void WavStep_Power_Monitoring_Test_Worker::executeTestOnT100Module(TestParamsForT100 testParams)
{
    int t100SlotNum = testParams.t100Module->getSlotNum();
    int swtSlotNum = testData.swtModule->getSlotNum();

//    // enable laser output for this t100 module (starting wavelengths are already set)
//    testParams.t100Module->enableModuleLaserCmd(t100SlotNum);

//    // make sure switch is in full band mode
//    testData.swtModule->setAPCModuleOperatingMode(swtSlotNum, "ECL");

//    // set optical emission wavelength
//    testData.swtModule->setRefWavelengthModuleCmd(swtSlotNum, QByteArray::number(testParams.startWav));

//    // open switch channel that the t100 is connected to
//    QByteArray channelNum = QByteArray::number(testParams.swtChannel);

//    testData.swtModule->selectChannelForSignalAPC(swtSlotNum, channelNum);

    // step through wavelengths
    double currentWavelength = testParams.startWav;
    while(currentWavelength <= testParams.endWav){
        // emit signal to display current wavelength on gui
        emit signalDisplayCurrentWavelength(QByteArray::number(currentWavelength));
        executeTestStep(currentWavelength, testParams);
        currentWavelength += testData.stepSize;
    }
}

void WavStep_Power_Monitoring_Test_Worker::executeTestStep(double currentWavelength, TestParamsForT100 testParams)
{

    QByteArray wavelengthToSet = QByteArray::number(currentWavelength);
    int t100SlotNum = testParams.t100Module->getSlotNum();
    int swtSlotNum = testData.swtModule->getSlotNum();

    // set wavelength on t100
    testParams.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set optical emission wavelength
    testData.swtModule->setRefWavelengthModuleCmd(swtSlotNum, wavelengthToSet);

    // set wavelength on power meters
    setWavelengthOnPowerMeters(wavelengthToSet);

    // wait until wavelength is adjusted
    QByteArray setRefWav = testData.swtModule->refWavelengthModuleQuery(swtSlotNum);
    while(setRefWav.toDouble() > currentWavelength){
        setRefWav = testData.swtModule->refWavelengthModuleQuery(swtSlotNum);
    }

    // begin collecting power meter readings
    QElapsedTimer dwellTimer;
    dwellTimer.start();
    while(dwellTimer.elapsed() <= testData.dwellInMs){

        QList<WavStepPowerMonitoringDataPoint> dataPoints;

        // get power meter readings for each channel
        for(auto powerMeter : testData.powerMeters){
            int numChannels = powerMeter->getNumChannelsVar();

            QList<QByteArray> readings = powerMeter->getPowerReadingOnAllChannels();
            QByteArray timeOfReading = QByteArray::number(timer.elapsed() / SEC_TO_MSEC_MULTIPLIER);

            // we expect one reading (and data point) per channel
            for(int i = 1; i <= numChannels; i++){

                // construct name (power meter + channel num)
                QByteArray channel = QByteArray(" Channel ").append(QByteArray::number(i));
                QByteArray powerMeterName = powerMeter->getNickname().replace(",", "");
                powerMeterName = powerMeterName + channel;
                QByteArray reading = readings[i - 1];


                // ##### testing only
                if(i == 3){
                    double todBm = ConversionUtilities::convertWattToDBm(reading.toDouble());
                    qDebug() << "                                                            " <<  todBm << " " << timeOfReading << " " << wavelengthToSet;
                }
                // create data points for graph/.csv
                WavStepPowerMonitoringDataPoint testDataPoint = {powerMeterName, reading,
                                                                 timeOfReading, wavelengthToSet};

                // add data point to list for graphing and to buffer for writing to .csv
                dataPoints.append(testDataPoint);
                addDataToFileBuffer(testDataPoint);
            }
        }

        // send readings to be graphed
        emit signalAddReadingsToGraph(dataPoints);

    }

    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! dwell time elapsed : " << dwellTimer.elapsed();
}

void WavStep_Power_Monitoring_Test_Worker::addDataToFileBuffer(WavStepPowerMonitoringDataPoint testDataPoint)
{
    // append datapoint to active buffer and write out to file if needed
    if(usingFirstBuffer){
        firstBuffer.append(testDataPoint);

        if(firstBuffer.size() >= maxBufferSize){
            usingFirstBuffer = false;
            // write buffer to file
            QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                      Q_ARG(QList<WavStepPowerMonitoringDataPoint>, firstBuffer));
            // clear buffer
            firstBuffer.clear();
        }
    }
    else{
        secondBuffer.append(testDataPoint);

        if(secondBuffer.size() >= maxBufferSize){
            usingFirstBuffer = true;
            // write buffer to file
            QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                      Q_ARG(QList<WavStepPowerMonitoringDataPoint>, secondBuffer));
            // clear buffer
            secondBuffer.clear();
        }
    }
}

void WavStep_Power_Monitoring_Test_Worker::setWavelengthOnPowerMeters(QByteArray wavelength)
{
    // iterate through power meters and set wavelength on each channel
    for(auto powerMeter : testData.powerMeters){
        int numChannels = powerMeter->getNumChannelsVar();

        for(int i = 1; i <= numChannels; i++){
            QByteArray channelNum = QByteArray::number(i);
            QByteArray unit = "nm";
            powerMeter->setWavelength(i, wavelength, unit);
        }
    }
}

void WavStep_Power_Monitoring_Test_Worker::slotStopWorkerThreads(){
    // if there is data in either buffer, write to file
    if(firstBuffer.size() > 0){
        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                  Q_ARG(QList<WavStepPowerMonitoringDataPoint>, firstBuffer));
    }
    if(secondBuffer.size() > 0){
        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                  Q_ARG(QList<WavStepPowerMonitoringDataPoint>, secondBuffer));
    }

    emit finished();
}
