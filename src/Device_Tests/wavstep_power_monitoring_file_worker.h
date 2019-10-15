#ifndef WAVSTEP_POWER_MONITORING_FILE_WORKER_H
#define WAVSTEP_POWER_MONITORING_FILE_WORKER_H

#include <QObject>
#include "wavstep_power_monitoring_data_point.h"
#include <QMutex>

class WavStep_Power_Monitoring_File_Worker : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_File_Worker(QByteArray filename, QObject *parent = 0);

signals:
    void finished();
public slots:

    void slotWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);
    void slotWaitForWork();

private:
    QMutex *mutex;
    bool waitingForData = true;
    QByteArray filename;
};

#endif // WAVSTEP_POWER_MONITORING_FILE_WORKER_H
