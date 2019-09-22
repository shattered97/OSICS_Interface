#ifndef POWERMETERFACTORY_H
#define POWERMETERFACTORY_H

#include <QObject>
#include "PowerMeter.h"
#include "KeysightPowerMeter.h"

class PowerMeterFactory : public QObject
{
    Q_OBJECT
public:
    explicit PowerMeterFactory(QObject *parent = nullptr);

    static PowerMeter *makePowerMeter(QString powerMeterType, QByteArray instrAddress, QByteArray instrIdentity);
signals:

public slots:
};

#endif // POWERMETERFACTORY_H
