#ifndef BRISTOL_428A_H
#define BRISTOL_428A_H

#include "DefaultInstrument.h"

class Bristol_428A : public DefaultInstrument
{
    Q_OBJECT
public:
    Bristol_428A(QByteArray theIdentity, QByteArray theInstrLoc);

    void setMediumVaccum();
    void setMediumAir();
    QByteArray measureWavelengthSingle();
    QByteArray measurePowerSingle();

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

};




#endif // BRISTOL_428A_H
