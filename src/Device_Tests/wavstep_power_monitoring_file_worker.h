#ifndef WAVSTEP_POWER_MONITORING_FILE_WORKER_H
#define WAVSTEP_POWER_MONITORING_FILE_WORKER_H

#include <QObject>
#include "wavstep_power_monitoring_data_point.h"
#include <QMutex>

class WavStep_Power_Monitoring_File_Worker : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_File_Worker(QByteArray filename, QObject *parent = nullptr);


signals:
    /**
     * @brief finished Signal from QThread, emitted when the thread is done executing.
     */
    void finished();


public slots:

    /**
     * @brief slotWriteBufferToFile Appends the list of test data to the .csv file.
     * @param dataPoints List of data points to write to .csv file.
     */
    void slotWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints);

    /**
     * @brief slotWaitForWork Slot executed when worker is started. Adds header to .csv.
     */
    void startFileOutputWorker();

    /**
     * @brief slotStopThread Emits signal to close the thread.
     */
    void slotStopThread();

private:
    QMutex *mutex;          /* Lock to prevent double-access to file  */
    QByteArray filename;    /* Output .csv filename */
};

#endif // WAVSTEP_POWER_MONITORING_FILE_WORKER_H
