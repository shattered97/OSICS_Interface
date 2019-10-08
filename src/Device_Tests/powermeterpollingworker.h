#ifndef POWERMETERPOLLINGWORKER_H
#define POWERMETERPOLLINGWORKER_H

#include <QObject>
#include <QThread>
#include "PowerMeter.h"
#include <QMutex>

class PowerMeterPollingWorker : public QObject
{
    Q_OBJECT
public:
    PowerMeterPollingWorker(PowerMeter *powerMeter, QMutex *powerMeterLock, QObject *parent = 0);

signals:
    void finished();
    void signalSendPowerReadingCommand(PowerMeter *powerMeter);

public slots:
    void slotPollPowerMeter();
    void slotStopWorkerThreads();

private:
    PowerMeter *powerMeter;
    QMutex *powerMeterLock;

};

#endif // POWERMETERPOLLINGWORKER_H
