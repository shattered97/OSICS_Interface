#ifndef N7714A_H
#define N7714A_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"

class N7714A : public DefaultInstrument
{
public:
    N7714A();
    N7714A(QByteArray theIdentity, QByteArray theInstrLoc);

    bool queryPowerUnit(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray &response);

    bool queryPowerStatus(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray &response);

    bool execPowerOnModule(ViSession &defaultSession, ViSession &instrSession, int module);

    bool execPowerOffModule(ViSession &defaultSession, ViSession &instrSession, int module);

    bool queryPowerLevel(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray &response, QByteArray value="");

    bool execPowerLevel(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray value="");

private:

};

#endif // N7714A_H


