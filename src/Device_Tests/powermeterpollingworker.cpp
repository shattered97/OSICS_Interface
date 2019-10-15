#include "powermeterpollingworker.h"

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;
}

void PowerMeterPollingWorker::slotPollPowerMeter(){

    while(continuePolling){
       QThread::msleep(WAVSTEP_GUI_POW_POLLING_RATE_MSEC);
       PowerReadings readingsForPowerMeter;
       readingsForPowerMeter.powerReadings = powerMeter->getPowerReadingOnAllChannels();
       readingsForPowerMeter.powerMeter = powerMeter;
       emit signalSendPowerReadings(readingsForPowerMeter);
    }

    emit finished();
}

void PowerMeterPollingWorker::slotStopWorkerThreads(){
    continuePolling = false;

}
