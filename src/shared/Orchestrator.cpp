#include "Orchestrator.h"

Orchestrator::Orchestrator()
{
    theCommBus.createDefaultRM(defaultSession);
}

Orchestrator::~Orchestrator()
{
    theCommBus.closeDefaultSession(defaultSession);
}

void Orchestrator::slotLookForDevices()
{
    // ask hardware for devices
    theCommBus.displayResources(defaultSession, foundResources);

    // signal list back to sender
    QObject *sender = QObject::sender();
    QObject::connect(this, SIGNAL(signalReturnDevicesFound(FoundInstr)), sender, SLOT(slotReceiveDevices(FoundInstr)));

    emit signalReturnDevicesFound(foundResources);
}

void Orchestrator::slotCreateN7714ADevice(QByteArray instrumentAddress, QByteArray instrumentIdentity)
{
    selectedResource = DefaultInstrument(instrumentIdentity, instrumentAddress);

    qDebug() << "-------------------------------------------------------------";
    qDebug() << "Test Query in Orchestrator slot slotCreateN7714ADevice";
    QByteArray response;
    selectedResource.queryIDN(defaultSession, response);
    qDebug() << "Response: " << response;

}


