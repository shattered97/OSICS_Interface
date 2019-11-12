#ifndef POWERMETERPOLLINGWORKER_H
#define POWERMETERPOLLINGWORKER_H

#include "PowerMeter.h"

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMetaObject>
#include <QMutex>

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
    /**
     * @brief PowerMeterPollingWorker Queries a power meter for all readings intermittently until this class
     *                                receives a signal to stop.
     * @param powerMeter The power meter to query for readings
     */
    PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent = nullptr);
    ~PowerMeterPollingWorker();


signals:
    /**
     * @brief finished Signal from QThread, emitted when the thread is done executing.
     */
    void finished();

    /**
     * @brief signalSendPowerReadings Emits the data collected from querying the power meter for readings.
     * @param readingsForPowerMeter List of readings (one for each channel) and associated power meter.
     */
    void signalSendPowerReadings(PowerReadings readingsForPowerMeter);
    void signalIsPollingContinued(bool *continuePolling);

public slots:
    /**
     * @brief slotPollPowerMeter The slot executed when starting the thread. Loops continuously, querying the power
     *                           meter each time and signaling out the result.
     */
    void slotPollPowerMeter();

//    /**
//     * @brief slotStopWorkerThreads Changes the flag allowing the loop in slotPollPowerMeter() to false, allowing it
//     *                              to stop executing and emit finished();
//     */
//    void slotStopWorkerThreads();

private:
    PowerMeter *powerMeter;             // pointer to a power meter to query
    bool continuePolling = true;
};

#endif // POWERMETERPOLLINGWORKER_H
