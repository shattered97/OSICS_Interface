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

void Orchestrator::slotCreateN7714ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity)
{
    N7714A *device = new N7714A(instrumentIdentity, instrumentAddress);

    // connect device to communication slots
    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)), this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)), this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    QVariant deviceVariant;
    deviceVariant.setValue(device);
    selectedDevices.append(deviceVariant);

    QMainWindow * configWindow = WindowFactory::makeWindow(type, deviceVariant);
    device->setConfigWindow(configWindow);


}

void Orchestrator::slotCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity){

    PowerMeter *device = PowerMeterFactory::makePowerMeter(type, instrumentIdentity, instrumentAddress);

    // connect device to communication slots
    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    QVariant deviceVariant;
    deviceVariant.setValue(device);
    selectedDevices.append(deviceVariant);

    QMainWindow * configWindow = WindowFactory::makeWindow(type, deviceVariant);
    device->setConfigWindow(configWindow);

    QObject::connect(configWindow, SIGNAL(signalUpdateConfigSettings(QVariant &, QSettings &)),
                     this, SLOT(slotUpdateConfigSettings(QVariant &, QSettings &)));
    QObject::connect(this, SIGNAL(signalSettingsUpdated()), configWindow, SLOT(slotUpdateWindow()));
}

QVariant Orchestrator::getDeviceAtIndex(int index){
    return selectedDevices.at(index);
}

void Orchestrator::slotUpdateConfigSettings(QVariant &deviceVariant, QSettings &configSettings){
    // because QVariant types are <type*> compare result of typeName()[:-1] with enum strings
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);
    qDebug() << typeName;

    if(typeName == "PowerMeter"){
        qDebug() << "QVariant interpreted as PowerMeter";
        PowerMeter* device = deviceVariant.value<PowerMeter*>();
        device->updateConfig(configSettings);

        // config settings updated, signal to sender
        emit signalSettingsUpdated();
    }
    else if(typeName == "N7714A"){
        qDebug() << "QVariant interpreted as N7714A";
    }
    // continue if/else chain when new devices are added to the system
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
