#ifndef POWERMETER_H
#define POWERMETER_H

#include <QString>
#include <QObject>
#include "DefaultInstrument.h"

class PowerMeter : QObject, protected DefaultInstrument
{
    Q_OBJECT
public:
    PowerMeter();
    virtual ~PowerMeter() = 0;

    virtual bool measurePower(ViSession &defaultSession, ViSession &instrSession, int window, QByteArray response) = 0;

    virtual bool setPowerUnitDBM(ViSession &defaultSession, ViSession &instrSession, int window) = 0;

    virtual bool setPowerUnitW(ViSession &defaultSession, ViSession &instrSession, int window) = 0;

};

#endif // POWERMETER_H
