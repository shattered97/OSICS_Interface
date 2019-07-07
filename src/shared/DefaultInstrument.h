#ifndef DEFAULTINSTRUMENT_H
#define DEFAULTINSTRUMENT_H

#include "VisaInterface.h"

#include <QThread>
#include <QString>

class DefaultInstrument
{
public:
    DefaultInstrument();



    bool sendCmdNoRsp();
    bool sendCmdRsp();








private:
    QString theIdentity;
    QString theInstrLoc;
    VisaInterface theCommBus;
};

#endif // DEFAULTINSTRUMENT_H
