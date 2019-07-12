#ifndef WORKER_H
#define WORKER_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include <QObject>


class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

public slots:

     void slotLookForDevices(QByteArray deviceType);

     void slotCreateN7714ADevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

signals:
     void signalReturnDevicesFound(QList<QByteArray>);

private:
    VisaInterface theCommBus;
    ViFindList findList;
    ViSession defaultSession;
    ViSession currentSession;
    ViUInt32 numInstruments;
    QByteArray instrAddr;
    FoundInstr foundResources;
    InstrData selectedResourceInfo;
    DefaultInstrument selectedResource;

    QList<QByteArray> resourcesQmapToQList(FoundInstr foundResources, QByteArray deviceType);

};

#endif // WORKER_H
