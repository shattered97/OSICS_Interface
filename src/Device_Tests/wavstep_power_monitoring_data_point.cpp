#include "wavstep_power_monitoring_data_point.h"

WavStep_Power_Monitoring_Data_Point::WavStep_Power_Monitoring_Data_Point(QByteArray channelName, QByteArray power,
                                                                         QByteArray time,  QByteArray wavelength,
                                                                         QObject *parent ) : QObject(parent)
{
    this->powerMeterChannelName = channelName;
    this->powerReading = power;
    this->readingTime = time;
    this->wavelength = wavelength;
}

WavStep_Power_Monitoring_Data_Point::WavStep_Power_Monitoring_Data_Point(const WavStep_Power_Monitoring_Data_Point &other){
    this->powerMeterChannelName = other.powerMeterChannelName;
    this->powerReading = other.powerReading;
    this->readingTime = other.readingTime;
    this->wavelength = other.wavelength;
}

QByteArray WavStep_Power_Monitoring_Data_Point::getPowerMeterChannelName(){
    return powerMeterChannelName;
}

QByteArray WavStep_Power_Monitoring_Data_Point::getPowerReading(){
    return powerReading;
}

QByteArray WavStep_Power_Monitoring_Data_Point::getReadingTime(){
    return readingTime;
}

QByteArray WavStep_Power_Monitoring_Data_Point::getWavelength(){
    return wavelength;
}
