#include "powermeterpollingworker.h"
#include <QTimer>
#include <QMetaObject>

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;

}

void PowerMeterPollingWorker::slotPollPowerMeter(){
    qDebug() << "slotPollPowerMeter()";

//    QByteArray unit = powerMeter->getPowerUnit(1);
//    qDebug() << "power unit: " << unit;


//    QList<QByteArray> readings = powerMeter->getPowerReadingOnAllChannels();
//    qDebug() << " ***************** " << readings;


    while(continuePolling){
       QThread::msleep(1000);
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
