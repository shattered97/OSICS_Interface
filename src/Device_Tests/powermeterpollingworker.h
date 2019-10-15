#ifndef POWERMETERPOLLINGWORKER_H
#define POWERMETERPOLLINGWORKER_H

#include "PowerMeter.h"

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMetaObject>

typedef struct PowerReadings{
    PowerMeter* powerMeter;             /* pointer to a selected power meter */
    QList<QByteArray> powerReadings;    /* power readings (raw, in Watt) gathered from query to power meter */
} PowerReadings;

/**
 * @brief The PowerMeterPollingWorker class intermittently queries a power meter for readings
 * on all it's channels. It will return the response of each query via signal. Polling continues
 * until the thread receives a signal to stop.
 */
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
