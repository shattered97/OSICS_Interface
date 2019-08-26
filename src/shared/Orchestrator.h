#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "KeysightPowerMeter.h"
#include "EXFO_OSICS/EXFO_OSICS_MAINFRAME.h"

#include <QObject>

Q_DECLARE_METATYPE(N7714A*)
Q_DECLARE_METATYPE(KeysightPowerMeter*)
Q_DECLARE_METATYPE(DefaultInstrument*)
Q_DECLARE_METATYPE(PowerMeter*)
//Q_DECLARE_METATYPE(EXFO_OSICS_MAINFRAME*)


namespace deviceType
{
    // #TODO
    // create enum and enum conversion helper functions string->enum enum->string
}

class Orchestrator : public QObject
{
    Q_OBJECT

public:
    Orchestrator();
    ~Orchestrator();

    QVariant getDeviceAtIndex(int index);

public slots:

    /**
     * @brief slotLookForDevices - Queries for all connected VISA devices. Signals back to the sender a list of found resources.
     */
    void slotLookForDevices();
//    void slotCreateN7714ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);
//    void slotCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);
    void slotCreateDevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

signals:
    void signalReturnDevicesFound(FoundInstr);
    void signalSettingsUpdated();

private:
    VisaInterface theCommBus;               // common methods for talking to VISA devices
    ViSession defaultSession;               // default session for device communication
    FoundInstr foundResources;              // map of VISA resources found
    QList<QVariant> selectedDevices;        // devices selected by the user

    bool checkOperationComplete(ViSession instrSession, QByteArray instrAddress, int timeout = DEFAULT_COMMAND_TIMEOUT_MS);

private slots:
    void slotSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
    void slotSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);
    void slotUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void slotApplyConfigSettings(QVariant &device, QSettings &configSettings);
};

#endif // ORCHESTRATOR_H
