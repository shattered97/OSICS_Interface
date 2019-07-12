#include "Worker.h"
#include <QObject>

Worker::Worker()
{
    theCommBus.createDefaultRM(defaultSession);
}

Worker::~Worker()
{
     theCommBus.closeDefaultSession(defaultSession);
}

void Worker::slotLookForDevices(QByteArray deviceType)
{
    // ask hardware for devices
    theCommBus.displayResources(defaultSession, instrAddr, currentSession, &numInstruments, &findList, foundResources);

    QList<QByteArray> convertedResourceInfo = resourcesQmapToQList(foundResources, deviceType);

    // signal list to sender
    QObject *sender = QObject::sender();
    QObject::connect(this, SIGNAL(signalReturnDevicesFound(QList<QByteArray>)), sender, SLOT(slotReceiveDevices(QList<QByteArray>)));

    emit signalReturnDevicesFound(convertedResourceInfo);
}

QList<QByteArray> Worker::resourcesQmapToQList(FoundInstr foundResources, QByteArray deviceType)
{
    QList<QByteArray> convertedResourceInfo;

    for(auto e: foundResources){
        QByteArray deviceString = e.first + " " + e.second;

        if(deviceString.contains(deviceType)){                               // not a sustainable method for matching instruments
            convertedResourceInfo.append(e.first + " " + e.second.split('\n')[0]);
        }
    }

    return convertedResourceInfo;
}

void Worker::slotCreateN7714ADevice(QByteArray instrumentAddress, QByteArray instrumentIdentity)
{
    qDebug() << "creating device object";

    selectedResource = N7714A(instrumentAddress, instrumentIdentity);
}
