#ifndef N7714A_H
#define N7714A_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"

class N7714A : public DefaultInstrument
{
public:
    N7714A();
    N7714A(QByteArray theIdentity, QByteArray theInstrLoc);

    bool execPowerUnit(ViSession &defaultSession, ViSession &instrSession, int module, int unit);
    bool queryPowerUnit(ViSession &defaultSession, ViSession &instrSession, int module, QByteArray &response);
    bool execPowerOnModule(ViSession &defaultSession, ViSession &instrSession, int module);
    bool execPowerOffModule(ViSession &defaultSession, ViSession &instrSession, int module);
private:

};

#endif // N7714A_H


