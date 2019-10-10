#include "wavstep_power_monitoring_test_worker.h"

WavStep_Power_Monitoring_Test_Worker::WavStep_Power_Monitoring_Test_Worker(TestData testData, QObject *parent) : QObject(parent)
{
    this->testData = testData;

}

void WavStep_Power_Monitoring_Test_Worker::runTest(){

    for(auto testParams : testData.testParamsForT100){
        executeTestOnT100Module(testParams);
    }

    emit finished();

}

void WavStep_Power_Monitoring_Test_Worker::executeTestOnT100Module(TestParamsForT100 testParams){

    int t100SlotNum = testParams.t100Module->getSlotNum();

    // set initial wavelength on t100
    QByteArray wavelengthToSet = QByteArray::number(testParams.startWav);
    testParams.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // enable laser output for this t100 module
    testParams.t100Module->enableModuleLaserCmd(t100SlotNum);

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

    // wait for amount specified by dwell time
    qDebug() << "waiting for : " << testData.dwellInMs << " ms";
    QThread::msleep(testData.dwellInMs);


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
