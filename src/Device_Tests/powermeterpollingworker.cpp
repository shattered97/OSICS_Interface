#include "powermeterpollingworker.h"
#include <QTimer>

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QMutex *powerMeterLock, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;
    this->powerMeterLock = powerMeterLock;
}

void PowerMeterPollingWorker::slotPollPowerMeter(){
    qDebug() << "slotPollPowerMeter()";


    QList<QByteArray> readings;
    qDebug() << "************ " << readings.isEmpty();
    qDebug() << &readings;
    powerMeter->getPowerReadingOnAllChannels(readings);

//    for(;;){
//       QThread::msleep(30000);
//       powerMeterLock->lock();
//       emit signalSendPowerReadingCommand(powerMeter);
//       powerMeterLock->unlock();
//    }


}

void PowerMeterPollingWorker::slotStopWorkerThreads(){
     emit finished();
}
