#include "wavstep_power_monitoring_file_worker.h"
#include <QDebug>
#include <QFile>
#include "constants.h"

WavStep_Power_Monitoring_File_Worker::WavStep_Power_Monitoring_File_Worker(QByteArray filename, QObject *parent ) : QObject(parent)
{
    this->filename = filename;
    mutex = new QMutex();
}

WavStep_Power_Monitoring_File_Worker::WavStep_Power_Monitoring_File_Worker(QObject *parent ) : QObject(parent){

}

void WavStep_Power_Monitoring_File_Worker::setFilename(QByteArray filename){
    this->filename = filename;
}
void WavStep_Power_Monitoring_File_Worker::slotWriteBufferToFile(QList<WavStepPowerMonitoringDataPoint> dataPoints){
    mutex->lock();

    QFile file(filename);
    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);

        for(int i = 0; i < dataPoints.size(); i++){
            // construct and print csv line from data point
            QString seriesName = dataPoints[i].powerMeterChannelName;
            QString powerReading = dataPoints[i].powerReading;
            QString readingTime = dataPoints[i].readingTime;
            QString wavelength = dataPoints[i].wavelength;
            QString csvLine = WAVSTEP_CSV_LINE.arg(seriesName).arg(powerReading).arg(readingTime).arg(wavelength);
            stream << csvLine;
        }

        file.flush();
        file.close();
    }

    mutex->unlock();
}

void WavStep_Power_Monitoring_File_Worker::startFileOutputWorker(){
    // initialize csv file
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);

        stream << WAVSTEP_CSV_FILE_HEADING;

        file.flush();
        file.close();
    }
}

void WavStep_Power_Monitoring_File_Worker::slotStopThread(){
    // aquire lock and emit signal to close thread

    mutex->lock();
    emit finished();
    mutex->unlock();
}



