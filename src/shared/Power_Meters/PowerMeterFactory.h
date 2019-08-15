#ifndef POWERMETERFACTORY_H
#define POWERMETERFACTORY_H

#include <QObject>
#include "PowerMeter.h"
#include "KeysightPowerMeter.h"
#include "configpowermeter.h"

class PowerMeterFactory : public QObject
{
    Q_OBJECT
public:
    explicit PowerMeterFactory(QObject *parent = nullptr);

    static PowerMeter *makePowerMeter(QString powerMeterType, QByteArray instrAddress, QByteArray instrIdentity, Orchestrator &orchestrator);
signals:

public slots:
};

#endif // POWERMETERFACTORY_H
