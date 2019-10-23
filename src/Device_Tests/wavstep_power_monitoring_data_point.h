#ifndef WAVSTEP_POWER_MONITORING_DATA_POINT_H
#define WAVSTEP_POWER_MONITORING_DATA_POINT_H

#include <QObject>

class WavStep_Power_Monitoring_Data_Point : public QObject
{
    Q_OBJECT
public:
    WavStep_Power_Monitoring_Data_Point(QByteArray channelName, QByteArray power, QByteArray time,
                                        QByteArray wavelength, QObject *parent = nullptr);

    WavStep_Power_Monitoring_Data_Point(const WavStep_Power_Monitoring_Data_Point &other);

    /**
     * @brief getPowerMeterChannelName Return the display name of the power meter channel.
     * @return Power meter channel name
     */
    QByteArray getPowerMeterChannelName();

    /**
     * @brief getPowerReading Return the reading taken from the power meter channel
     * @return Power meter reading
     */
    QByteArray getPowerReading();

    /**
     * @brief getReadingTime Return the time that the reading was taken from start of test
     * @return Time of power meter reading
     */
    QByteArray getReadingTime();

    /**
     * @brief getWavelength Return the wavelength set on devices at the time
     * @return
     */
    QByteArray getWavelength();


private:
    QByteArray powerMeterChannelName;   /* Display name of a single power meter channel */
    QByteArray powerReading;            /* A reading (Watt) taken from the power meter at this channel */
    QByteArray readingTime;             /* Time in the test process that the reading was taken */
    QByteArray wavelength;              /* Wavelength set at the time the power reading was taken */

};

#endif // WAVSTEP_POWER_MONITORING_DATA_POINT_H
