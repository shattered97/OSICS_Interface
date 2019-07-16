#ifndef KEYSIGHTPOWERMETER_H
#define KEYSIGHTPOWERMETER_H

#include "PowerMeter.h"
#include <QObject>
#include "DefaultInstrument.h"

class KeysightPowerMeter : virtual PowerMeter
{
public:
    KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc);
    ~KeysightPowerMeter();

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
};

#endif // KEYSIGHTPOWERMETER_H
