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
    QByteArray instrIdentity;
    QByteArray instrLoc;
};

#endif // KEYSIGHTPOWERMETER_H
