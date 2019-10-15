#include "wavstep_power_monitoring_file_worker.h"
#include <QDebug>
#include <QFile>

WavStep_Power_Monitoring_File_Worker::WavStep_Power_Monitoring_File_Worker(QByteArray filename, QObject *parent ) : QObject(parent)
{
    this->filename = filename;
    mutex = new QMutex();
}

void WavStep_Power_Monitoring_File_Worker::slotWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> dataPoints){
    mutex->lock();

    qDebug() << "WRITING TO FILE";
    QFile file(filename);
    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);

        for(auto dataPoint : dataPoints){
            QByteArray seriesName = dataPoint.getPowerMeterChannelName();
            QByteArray powerReading = dataPoint.getPowerReading();
            QByteArray readingTime = dataPoint.getReadingTime();
            QByteArray wavelength = dataPoint.getWavelength();

            QByteArray csvLine = seriesName + "," + powerReading + "," + readingTime + "," + wavelength + '\n';
            qDebug() << csvLine;
            stream << csvLine;
        }

        file.flush();
        file.close();
    }

    mutex->unlock();
}


void WavStep_Power_Monitoring_File_Worker::slotWaitForWork(){
    // initialize csv file
    QFile file(filename);
    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);

        stream << "series,power reading (Watt),reading time, wavelength\n";

        file.flush();
        file.close();
    }

    while(waitingForData){
        mutex->lock();
        // wait
        mutex->unlock();
    }
}



