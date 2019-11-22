#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "KeysightPowerMeter.h"
#include "EXFO_OSICS/EXFO_OSICS_MAINFRAME.h"
#include "EXFO_OSICS/EXFO_OSICS_ATN.h"
#include "EXFO_OSICS/EXFO_OSICS_SWT.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "Ando_AQ6331.h"
#include <QObject>
#include <QMetaType>
#include <QMutex>
#include <QThread>
#include "PowerMeterFactory.h"
#include "WindowFactory.h"
#include "ConversionUtilities.h"

#include "DeviceTest.h"
#include "DeviceTestFactory.h"

Q_DECLARE_METATYPE(N7714A*)
Q_DECLARE_METATYPE(KeysightPowerMeter*)
Q_DECLARE_METATYPE(DefaultInstrument*)
Q_DECLARE_METATYPE(PowerMeter*)
Q_DECLARE_METATYPE(EXFO_OSICS_MAINFRAME*)
Q_DECLARE_METATYPE(Ando_AQ6331*)
Q_DECLARE_METATYPE(Bristol_428A*)
Q_DECLARE_METATYPE(QByteArray*)
Q_DECLARE_METATYPE(QVariant)
Q_DECLARE_METATYPE(QVariant*)
Q_DECLARE_METATYPE(FoundInstr)
Q_DECLARE_METATYPE(QList<double>)
Q_DECLARE_METATYPE(double)
Q_DECLARE_METATYPE(double *)


namespace deviceType
{
    // #TODO
    // create enum and enum conversion helper functions string->enum enum->string
}

class Orchestrator : public QObject
{
    Q_OBJECT

public:
    Orchestrator(WindowFactory *windowFactory, DeviceTestFactory *deviceTestFactory, QObject *parent = nullptr);
    ~Orchestrator();

    QVariant getDeviceAtIndex(int index);

public slots:
    void slotStartOrchestrator();
    /**
     * @brief slotLookForDevices - Queries for all connected VISA devices. Signals back to the sender a list of found resources.
     */
    void slotLookForDevices();
    void slotCreateDevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);
    void slotGetEXFOModuleQVariants(QMap <int, QVariant> &modules, QVariant &device);
    void slotBeginTest(QString testTypeName);
    void slotClearSelectedDevices();
    void slotGetEXFOModuleConfigPairs(QVariant device, QMap<int, ModuleConfigPair> *moduleConfigPairs);
signals:
    void signalReturnDevicesFound(FoundInstr);
    void signalSettingsUpdated();
    void signalSetupEXFOModules();
    void signalSetupPowerMeter();
    void signalSendDecisionErrorMsg(QString errorMsg);
    void signalSendSimpleErrorMsg(QString errorMsg);
    void signalDeviceCreated();
    /**
     * @brief finished Signal from QThread, emitted when the thread is done executing.
     */
    void finished();
    void signalShowConfigWindow();

private:
    VisaInterface theCommBus;               // common methods for talking to VISA devices
    ViSession defaultSession;               // default session for device communication
    FoundInstr foundResources;              // map of VISA resources found
    QList<QVariant> selectedDevices;        // devices selected by the user
    QMutex *communicationLock;
    WindowFactory *windowFactory;
    DeviceTestFactory *deviceTestFactory;
    bool checkOperationComplete(ViSession instrSession, QByteArray instrAddress, int timeout = DEFAULT_COMMAND_TIMEOUT_MS);

private slots:
    void slotSendCmdRsp(QByteArray instrAddress, QByteArray command, QByteArray *response);
    void slotSendCmdNoRsp(QByteArray instrAddress, QByteArray command);
    void slotUpdateConfigSettings(QVariant device, QSettings *configSettings);
    void slotApplyConfigSettings(QVariant device, QSettings *configSettings);
};

#endif // ORCHESTRATOR_H
