#include "powermeterpollingworker.h"
#include <QTimer>

PowerMeterPollingWorker::PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent ) : QObject(parent)
{
    this->powerMeter = powerMeter;
}

void PowerMeterPollingWorker::slotPollPowerMeter(){
    qDebug() << "slotPollPowerMeter()";

    for(;;){
       QThread::msleep(1000);
       emit signalSendPowerReadingCommand(powerMeter);
    }

    emit finished();
}

