#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "KeysightPowerMeter.h"

#include <QObject>

Q_DECLARE_METATYPE(N7714A*)
Q_DECLARE_METATYPE(KeysightPowerMeter*)
Q_DECLARE_METATYPE(DefaultInstrument*)
Q_DECLARE_METATYPE(PowerMeter*)

class Orchestrator : public QObject
{
    Q_OBJECT

public:
    Orchestrator();
    ~Orchestrator();

    ViSession * getDefaultSession();
    QVariant getDeviceAtIndex(int index);

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
    void slotCreateN7714ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void slotCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void slotSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
    void slotSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);

signals:

    /**
     * @brief signalReturnDevicesFound Signals the list of instruments found to reciever.
     */
    void signalReturnDevicesFound(FoundInstr);

private:
    VisaInterface theCommBus;               // common methods for talking to VISA devices
    ViSession defaultSession;               // default session for device communication
    FoundInstr foundResources;              // map of VISA resources found

    QList<QVariant> selectedDevices;

    bool checkOperationComplete(ViSession instrSession, QByteArray instrAddress, int timeout = DEFAULT_COMMAND_TIMEOUT_MS);

};

#endif // ORCHESTRATOR_H
