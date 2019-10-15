#ifndef WAVSTEP_POWER_MONITORING_DATA_POINT_H
#define WAVSTEP_POWER_MONITORING_DATA_POINT_H

#include <QObject>

class WavStep_Power_Monitoring_Data_Point : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_Data_Point(QByteArray channelName, QByteArray power, QByteArray time,
                                        QByteArray wavelength, QObject *parent = 0);

    WavStep_Power_Monitoring_Data_Point(const WavStep_Power_Monitoring_Data_Point &other);
    QByteArray getPowerMeterChannelName();
    QByteArray getPowerReading();
    QByteArray getReadingTime();
    QByteArray getWavelength();


private:
    QByteArray powerMeterChannelName;
    QByteArray powerReading;
    QByteArray readingTime;
    QByteArray wavelength;

};

#endif // WAVSTEP_POWER_MONITORING_DATA_POINT_H
