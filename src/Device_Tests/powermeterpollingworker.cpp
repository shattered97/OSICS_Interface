#include "powermeterpollingworker.h"

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;
}

void PowerMeterPollingWorker::slotPollPowerMeter(){
    qDebug() << "slotPollPowerMeter()";

    // query power meter for power reading over all channels
//    QList<QByteArray> readings;
//    powerMeter->getPowerReadingOnAllChannels(readings);
//    qDebug() << "printing readings...";
//    qDebug() << readings;

    for(;;){
       emit signalSendPowerReadingCommand(powerMeter);
    }

    emit finished();
}

