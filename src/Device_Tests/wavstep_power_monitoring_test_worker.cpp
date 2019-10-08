#include "wavstep_power_monitoring_test_worker.h"

WavStep_Power_Monitoring_Test_Worker::WavStep_Power_Monitoring_Test_Worker(TestData testData, QMutex *powerMeterLock, QObject *parent) : QObject(parent)
{
    this->testData = testData;
    this->powerMeterLock = powerMeterLock;
}

void WavStep_Power_Monitoring_Test_Worker::runTest(){
    qDebug() << "@@@@@@@@@@@@@@@@@@@ in test worker runTest() method";
//    powerMeterLock->lock();

//    int channels = testData.powerMeter->getNumPowerMeterChannels();
//    qDebug() <<  "num channels (in worker)?? "<< channels;

//    powerMeterLock->unlock();


    // open switch channel
    int swtSlotNum = testData.swtModule->getSlotNum();


    QByteArray switchChannelToOpen = QByteArray::number(testData.swtChannel);
    testData.swtModule->selectChannelForSignalAPC(swtSlotNum, switchChannelToOpen);
    qDebug() << "opened switch channel";

    // try to use rsp command with another resource
    QByteArray channel;
    testData.swtModule->getChannelForSignalAPC(swtSlotNum, channel);



//    double currentWavelength = testData.startWav;
//    while(currentWavelength <= testData.endWav){
//        executeTestStep(currentWavelength);
//        currentWavelength += testData.stepSize;
//    }
}

void WavStep_Power_Monitoring_Test_Worker::executeTestStep(double currentWavelength){

    // set wavelength on t100
    QByteArray wavelengthToSet = QByteArray::number(currentWavelength);
    int t100SlotNum = testData.t100Module->getSlotNum();
    testData.t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);
    qDebug() << "set wavelength on t100";


//    for(auto powerMeter : testData.powerMeter){
//        int numChannels = powerMeter->getNumPowerMeterChannels();
//        qDebug() << "num chanels: " << numChannels;
//        for(int i = 1; i <= numChannels; i++){
//            QByteArray channelNum = QByteArray::number(i);
//            QByteArray unit = "nm";
//            powerMeter->setWavelength(i, wavelengthToSet, unit);
//            qDebug() << "set wavelength on power meter channel";
//        }
//    }


    // wait for amount specified by dwell time
    QElapsedTimer dwellTimer;
    dwellTimer.start();
    while(dwellTimer.elapsed() < testData.dwellInMs){
       // wait
    }

    qDebug() << "returning from test step";

}
