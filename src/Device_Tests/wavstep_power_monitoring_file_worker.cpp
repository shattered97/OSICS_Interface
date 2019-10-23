#include "wavstep_power_monitoring_file_worker.h"
#include <QDebug>
#include <QFile>
#include "constants.h"

WavStep_Power_Monitoring_File_Worker::WavStep_Power_Monitoring_File_Worker(QByteArray filename, QObject *parent ) : QObject(parent)
{
    this->filename = filename;
    mutex = new QMutex();
}

void WavStep_Power_Monitoring_File_Worker::slotWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints){
    mutex->lock();

    QFile file(filename);
    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);

        for(auto dataPoint : dataPoints){
            // construct and print csv line from data point
            QString seriesName = dataPoint.getPowerMeterChannelName();
            QString powerReading = dataPoint.getPowerReading();
            QString readingTime = dataPoint.getReadingTime();
            QString wavelength = dataPoint.getWavelength();
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
    if(file.open(QIODevice::Append)){
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



