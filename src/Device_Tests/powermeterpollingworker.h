#ifndef POWERMETERPOLLINGWORKER_H
#define POWERMETERPOLLINGWORKER_H

#include <QObject>
#include <QThread>
#include "PowerMeter.h"

class PowerMeterPollingWorker : public QObject
{
    Q_OBJECT
public:
    PowerMeterPollingWorker(PowerMeter *powerMeter, QObject *parent = 0);

signals:
    void finished();

public slots:
    void slotPollPowerMeter();

private:
    PowerMeter *powerMeter;
};

#endif // POWERMETERPOLLINGWORKER_H
