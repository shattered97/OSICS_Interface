#ifndef POWERMETERPOLLINGWORKER_H
#define POWERMETERPOLLINGWORKER_H

#include <QObject>
#include <QThread>
#include "PowerMeter.h"

typedef struct PowerReadings{
    PowerMeter* powerMeter;
    QList<QByteArray> powerReadings;
} PowerReadings;



class PowerMeterPollingWorker : public QObject
{
    Q_OBJECT
public:
    PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent = 0);

signals:
    void finished();
    void signalSendPowerReadings(PowerReadings readingsForPowerMeter);

public slots:
    void slotPollPowerMeter();
    void slotStopWorkerThreads();

private:
    PowerMeter *powerMeter;
    bool continuePolling = true;
};

#endif // POWERMETERPOLLINGWORKER_H
