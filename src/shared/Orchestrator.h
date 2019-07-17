#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

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

    /**
     * @brief slotLookForDevices - Queries for all connected VISA devices. Signals back to the sender a list of found resources.
     */
    void slotLookForDevices();

    /**
     * @brief slotCreateN7714ADevice Creates a N7714A device object.
     * @param instrumentAddress Physical address of instrument
     * @param instrumentIdentity Identity of instrument (manufacturer, model num, etc.)
     */
    void slotCreateN7714ADevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

signals:

    /**
     * @brief signalReturnDevicesFound Signals the list of instruments found to reciever.
     */
    void signalReturnDevicesFound(FoundInstr);

private:
    VisaInterface theCommBus;               // common methods for talking to VISA devices
    ViSession defaultSession;               // default session for device communication
    FoundInstr foundResources;              // map of VISA resources found

    DefaultInstrument selectedResource;

};

#endif // ORCHESTRATOR_H
