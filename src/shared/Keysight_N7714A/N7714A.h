#ifndef N7714A_H
#define N7714A_H

#include "DefaultInstrument.h"

class N7714A : public DefaultInstrument
{
    Q_OBJECT

public:
    N7714A(QByteArray theIdentity, QByteArray theInstrLoc);

    bool queryPowerUnit(ViSession &defaultSession, int module, QByteArray &response);

    bool execPowerUnit(ViSession &defaultSession, int module, QByteArray unit="");

    bool queryPowerStatus(ViSession &defaultSession, int module, QByteArray &response);

    bool execPowerOnModule(ViSession &defaultSession, int module);

    bool execPowerOffModule(ViSession &defaultSession, int module);

    bool queryPowerLevel(ViSession &defaultSession, int module, QByteArray &response, QByteArray value="");

    bool execPowerLevel(ViSession &defaultSession, int module, QByteArray value, QByteArray unit="");

    bool queryWavelength(ViSession &defaultSession, int module, QByteArray &response, QByteArray value="");

    bool execWavelength(ViSession &defaultSession, int module, QByteArray value, QByteArray unit="");

    bool queryFrequency(ViSession &defaultSession, int module, QByteArray &response, QByteArray value="");

    bool execFrequency(ViSession &defaultSession, int module, QByteArray value, QByteArray unit="");

    bool testCommand(ViSession &defaultSession, QByteArray cmd, QByteArray &response);

    bool queryAutoWavMode(ViSession &defaultSession, int module, QByteArray &response);

    bool turnOnAutoWavMode(ViSession &defaultSession, int module);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
};

#endif // N7714A_H


