#include "Orchestrator.h"
#include "PowerMeterFactory.h"
#include "WindowFactory.h"

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
    // clear qmap of resources
    foundResources.clear();

    // ask hardware for devices
    theCommBus.displayResources(defaultSession, foundResources);

    // signal list back to sender
    QObject *sender = QObject::sender();
    QObject::connect(this, SIGNAL(signalReturnDevicesFound(FoundInstr)), sender, SLOT(slotReceiveDevices(FoundInstr)));

    emit signalReturnDevicesFound(foundResources);

    // disconnect signal so we don't get duplicate returns
    QObject::disconnect(this, SIGNAL(signalReturnDevicesFound(FoundInstr)), 0, 0);
}

void Orchestrator::slotCreateDevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity)
{
    QVariant deviceVariant;
    // #TODO finish enum for type strings

    if(type == "N7714A"){
        N7714A *device = new N7714A(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else if(type == "N7745A") {
        PowerMeter *device = PowerMeterFactory::makePowerMeter(type, instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);

    }
    else if(type == "EXFO,OSICS"){
        EXFO_OSICS_MAINFRAME *device = new EXFO_OSICS_MAINFRAME(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else{
        // #TODO error/exit
    }

    selectedDevices.append(deviceVariant);

    QMainWindow *configWindow = WindowFactory::makeWindow(type, deviceVariant);
    DefaultInstrument *device = deviceVariant.value<DefaultInstrument*>();
    device->setConfigWindow(configWindow);

    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    QObject::connect(configWindow, SIGNAL(signalUpdateConfigSettings(QVariant &, QSettings &)),
                     this, SLOT(slotUpdateConfigSettings(QVariant &, QSettings &)));
    QObject::connect(configWindow, SIGNAL(signalApplyConfigSettings(QVariant &, QSettings &)),
                     this, SLOT(slotApplyConfigSettings(QVariant &, QSettings &)));
}

QVariant Orchestrator::getDeviceAtIndex(int index){
    return selectedDevices.at(index);
}

void Orchestrator::slotGetEXFOModuleQVariants(QList<QVariant> &modules, QList<QByteArray> modTypes, QVariant &device){
    // #TODO Factory?

    qDebug() << "slotGetEXFOModuleQVariants";
    DefaultInstrument *deviceFromVariant = device.value<DefaultInstrument*>();
    QByteArray chassisAddress = deviceFromVariant->getInstrIdentity();
    QByteArray chassisIdentity = deviceFromVariant->getInstrLocation();

    QVariant moduleVariant;
    for(int i = 0; i < modTypes.size(); i++){
        if(modTypes[i].contains("T100")){
            qDebug() << "t100";
            EXFO_OSICS_T100 *module = new EXFO_OSICS_T100(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
            modules.append(moduleVariant);
        }
        else if(modTypes[i].contains("ATN")){
            qDebug() << "atn";
            EXFO_OSICS_ATN *module = new EXFO_OSICS_ATN(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
            modules.append(moduleVariant);
        }
        else if(modTypes[i].contains("SWT")){
            qDebug() << "swt";
            EXFO_OSICS_SWT *module = new EXFO_OSICS_SWT(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
            modules.append(moduleVariant);
        }
        else{
            // #TODO slot is either empty or module is not supported (error msg)
        }
    }
}

void Orchestrator::slotUpdateConfigSettings(QVariant &deviceVariant, QSettings &configSettings){
    // because QVariant types are <type*> compare result of typeName()[:-1] with enum strings
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);

     qDebug() << "slotupdateconfigsettings()";

    if(typeName == "PowerMeter"){
        qDebug() << "QVariant interpreted as PowerMeter";
        PowerMeter* device = deviceVariant.value<PowerMeter*>();
        device->updateConfig(configSettings);

        // config settings updated, signal to sender
        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "N7714A"){
        qDebug() << "QVariant interpreted as N7714A";
        N7714A* device = deviceVariant.value<N7714A*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_MAINFRAME"){
        qDebug() << "updatig exfo config";
        EXFO_OSICS_MAINFRAME* device = deviceVariant.value<EXFO_OSICS_MAINFRAME*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_T100"){


        qDebug() << "updating t100";
        EXFO_OSICS_T100* device = deviceVariant.value<EXFO_OSICS_T100*>();
        device->updateConfig(configSettings);

        QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                         this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
        QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                         this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_ATN"){
        qDebug() << "updating atn";

    }
    else if(typeName == "EXFO_OSICS_SWT"){
        qDebug() << "updating swt";
    }
    else{
        // #TODO error/exit
    }


}

void Orchestrator::slotApplyConfigSettings(QVariant &deviceVariant, QSettings &configSettings){
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);

    if(typeName == "PowerMeter"){
        qDebug() << "QVariant interpreted as PowerMeter";
        PowerMeter* device = deviceVariant.value<PowerMeter*>();
        device->applyConfigSettings(configSettings);

        // config settings updated, signal to sender
        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "N7714A"){
        qDebug() << "QVariant interpreted as N7714A";
        N7714A* device = deviceVariant.value<N7714A*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_MAINFRAME"){
        qDebug() << "QVariant interpreted as EXFO_OSICS_MAINFRAME";
        EXFO_OSICS_MAINFRAME* device = deviceVariant.value<EXFO_OSICS_MAINFRAME*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else{
        // #TODO error/exit
    }
}

void Orchestrator::slotSendCmdNoRsp(QByteArray instrAddress, QByteArray &command){
    qDebug() << "Sent command: " << command;
    bool success = true;

    ViSession instrSession;

    // open session
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, instrAddress, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;
    }
    else{
        checkOperationComplete(instrSession, instrAddress);

        ViUInt32 writeCount;
        ViStatus status = theCommBus.sendCmd(instrSession, instrAddress, command, writeCount);

        if(status < VI_SUCCESS){
            success = false;
        }
        else{
            qDebug() << "Query succeeded: " << command;
        }

        // close session
        theCommBus.closeSession(instrSession);

    }

    // #TODO SIGNAL QMESSAGEBOX IF UNSUCCESSFUL
}

void Orchestrator::slotSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response){
    qDebug() << "Command sent: " << command;
    bool success = true;

    ViSession instrSession;

    // open session
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, instrAddress, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;
        qDebug() << "Opening session failed.  status: " << sessionStatus;
    }
    else{

        // check if instrument is done processing previous commands
        checkOperationComplete(instrSession, instrAddress);

        ViUInt32 writeCount;
        ViStatus status = theCommBus.sendCmd(instrSession, instrAddress, command, writeCount);
            if(status < VI_SUCCESS){
                qDebug() << QString("Query failed: %1").arg(status);
                status = false;
            }
            else{
                ViUInt32 rtnSize;
                status = theCommBus.readCmd(instrSession, instrAddress, response, rtnSize);

                if(status < VI_SUCCESS){
                    qDebug() << QString("Reading response failed: %1").arg(status);
                    success = false;
                }
                else{
                    qDebug() << "Response: " << response;
                }
            }

        // close session
        theCommBus.closeSession(instrSession);

    }

    // #TODO SIGNAL QMESSAGEBOX IF UNSUCCESSFUL
}

bool Orchestrator::checkOperationComplete(ViSession instrSession, QByteArray instrAddress, int timeout){

    // start time
    QElapsedTimer timer;
    timer.start();

    int complete = 0;

    while(timer.elapsed() < timeout && complete == 0){
        complete = 0;

        ViUInt32 writeCount;
        theCommBus.sendCmd(instrSession, instrAddress, QUERY_OPC, writeCount);

        QByteArray response;
        ViUInt32 rtnSize;
        theCommBus.readCmd(instrSession, instrAddress, response, rtnSize);

        complete = response[0];
    }
    return complete;
}
