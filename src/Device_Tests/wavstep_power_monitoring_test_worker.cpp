#include "wavstep_power_monitoring_test_worker.h"

WavStep_Power_Monitoring_Test_Worker::WavStep_Power_Monitoring_Test_Worker(TestData testData, QObject *parent) : QObject(parent)
{
    this->testData = testData;

}

void WavStep_Power_Monitoring_Test_Worker::runTest(){
    
    // setup file output worker
    QThread *fileWorkerThread = new QThread;
    fileWriteWorker = new WavStep_Power_Monitoring_File_Worker(testData.filename);
    fileWriteWorker->moveToThread(fileWorkerThread);

    connect(fileWriteWorker, SIGNAL(finished()), fileWorkerThread, SLOT(quit()));
    connect(fileWorkerThread, SIGNAL(started()), fileWriteWorker, SLOT(slotWaitForWork()));
    connect(fileWriteWorker, SIGNAL(finished()), fileWriteWorker, SLOT(deleteLater()));
    connect(fileWorkerThread, SIGNAL(finished()), fileWorkerThread, SLOT(deleteLater()));

    // setup modules
    initializeT100Modules();

    // start timer
    timer.start();
    
    for(auto testParams : testData.testParamsForT100){
        executeTestOnT100Module(testParams);
    }

    // #TODO disable output on all lasers


    emit finished();

}


void WavStep_Power_Monitoring_Test_Worker::initializeT100Modules(){

    // for each module, set initial wavelength
    for(auto testParam : testData.testParamsForT100){
        int t100SlotNum = testParam.t100Module->getSlotNum();
        QByteArray wavelengthToSet = QByteArray::number(testParam.startWav);
        testParam.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);
    }

}

void WavStep_Power_Monitoring_Test_Worker::executeTestOnT100Module(TestParamsForT100 testParams){

    int t100SlotNum = testParams.t100Module->getSlotNum();

    // starting wavelengths already set, enable laser output for this t100 module
    testParams.t100Module->enableModuleLaserCmd(t100SlotNum);

    // open switch channel that the t100 is connected to
    int swtSlotNum = testData.swtModule->getSlotNum();
    QByteArray channelNum = QByteArray::number(testParams.swtChannel);
    testData.swtModule->selectChannelForSignalAPC(swtSlotNum, channelNum);

    // step through wavelengths
    double currentWavelength = testParams.startWav;
    while(currentWavelength <= testParams.endWav){
        executeTestStep(currentWavelength, testParams);
        currentWavelength += testData.stepSize;
    }

}

void WavStep_Power_Monitoring_Test_Worker::executeTestStep(double currentWavelength, TestParamsForT100 testParams){

    QByteArray wavelengthToSet = QByteArray::number(currentWavelength);
    int t100SlotNum = testParams.t100Module->getSlotNum();

    // set wavelength on t100
    testParams.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set wavelength on power meters
    setWavelengthOnPowerMeters(wavelengthToSet);

    // begin collecting power meter readings
    QElapsedTimer dwellTimer;
    dwellTimer.start();
    while(dwellTimer.elapsed() <= testData.dwellInMs){

        QList<WavStep_Power_Monitoring_Data_Point> dataPoints;

        // get power meter readings for each channel
        for(auto powerMeter : testData.powerMeters){
            int numChannels = powerMeter->getNumPowerMeterChannels();

            QList<QByteArray> readings = powerMeter->getPowerReadingOnAllChannels();
            QByteArray timeOfReading = QByteArray::number(timer.elapsed() / SEC_TO_MSEC_MULTIPLIER);

            // we expect one reading (and data point) per channel
            for(int i = 1; i <= numChannels; i++){

                QByteArray channel = QByteArray(" Channel ").append(QByteArray::number(i));
                QByteArray powerMeterName = powerMeter->getInstrIdentity().replace(",", "");
                powerMeterName = powerMeterName + channel;

                // create data points for graph/.csv
                QByteArray reading = readings[i - 1];

                WavStep_Power_Monitoring_Data_Point testDataPoint(powerMeterName, reading,
                                                                  timeOfReading, wavelengthToSet);

                dataPoints.append(testDataPoint);

                // append datapoint to buffer and write out to file if needed
                if(usingFirstBuffer){
                    firstBuffer.append(testDataPoint);
                    if(firstBuffer.size() >= maxBufferSize){
                        usingFirstBuffer = false;
                        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                                  Q_ARG(QList<WavStep_Power_Monitoring_Data_Point>, firstBuffer));
                    }
                }
                else{
                    secondBuffer.append(testDataPoint);

                    if(secondBuffer.size() >= maxBufferSize){
                        usingFirstBuffer = true;
                        QMetaObject::invokeMethod(fileWriteWorker, "slotWriteBufferToFile", Qt::AutoConnection,
                                                  Q_ARG(QList<WavStep_Power_Monitoring_Data_Point>, secondBuffer));
                    }
                }
            }
        }
        emit signalAddReadingsToGraph(dataPoints);
    }



    qDebug() << "returning from test step";

}

void WavStep_Power_Monitoring_Test_Worker::setWavelengthOnPowerMeters(QByteArray wavelength){
    for(auto powerMeter : testData.powerMeters){
        int numChannels = powerMeter->getNumPowerMeterChannels();
        qDebug() << "num chanels: " << numChannels;
        for(int i = 1; i <= numChannels; i++){
            QByteArray channelNum = QByteArray::number(i);
            QByteArray unit = "nm";
            powerMeter->setWavelength(i, wavelength, unit);
            qDebug() << "set wavelength on power meter channel";
        }
    }
}
