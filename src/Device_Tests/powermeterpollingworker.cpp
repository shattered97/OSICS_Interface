#include "powermeterpollingworker.h"

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;
    lock = new QMutex();
}

PowerMeterPollingWorker::~PowerMeterPollingWorker(){
    delete lock;
}

void PowerMeterPollingWorker::slotPollPowerMeter(){

    // loop until signal is received to stop (upon test window closing)
    while(continuePolling && powerMeter){
       lock->lock();

       // pause thread for time = refresh rate
       QThread::msleep(WAVSTEP_GUI_POW_POLLING_RATE_MSEC);

       // get power reading from power meter
       PowerReadings readingsForPowerMeter;
       readingsForPowerMeter.powerReadings = powerMeter->getPowerReadingOnAllChannels();
       readingsForPowerMeter.powerMeter = powerMeter;

       // signal out power readings
       emit signalSendPowerReadings(readingsForPowerMeter);

       lock->unlock();
    }

    emit finished();
}

void PowerMeterPollingWorker::slotStopWorkerThreads()
{
    // grab lock between loops to stop polling
    lock->lock();
    continuePolling = false;
    lock->unlock();
}
