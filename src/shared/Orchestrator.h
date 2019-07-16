#ifndef WORKER_H
#define WORKER_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include <QObject>


class Orchestrator : public QObject
{
    Q_OBJECT

public:
    Orchestrator();
    ~Orchestrator();

public slots:

     void slotLookForDevices();

     void slotCreateN7714ADevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

signals:
     void signalReturnDevicesFound(FoundInstr);

private:
    VisaInterface theCommBus;
    ViSession defaultSession;
    FoundInstr foundResources;

    ViFindList findList;
    ViSession currentSession;
    ViUInt32 numInstruments;
    QByteArray instrAddr;


    DefaultInstrument selectedResource;

};

#endif // WORKER_H
