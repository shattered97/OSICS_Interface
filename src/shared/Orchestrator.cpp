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

    // make config window
//    ConfigN7714AWindow *configWindow = new ConfigN7714AWindow(*this, device);
//    device->setConfigWindow(configWindow);

    QVariant deviceVariant;
    deviceVariant.setValue(device);
    selectedDevices.append(deviceVariant);

    qDebug() << "-------------------------------------------------------------";
    qDebug() << "Test Query in Orchestrator slot slotCreateN7714ADevice";
    QByteArray response;
    N7714A *test = selectedDevices.at(selectedDevices.size()-1).value<N7714A*>();
    test->queryIDN(defaultSession, response);
    qDebug() << "Response: " << response;
    qDebug() << "-------------------------------------------------------------";
}

void Orchestrator::slotCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity){

    PowerMeter *device = PowerMeterFactory::makePowerMeter(type, instrumentIdentity, instrumentAddress, *this);

    // connect device to communication slots
    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)), this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)), this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    QMainWindow * configWindow = WindowFactory::makeWindow(type, *this, device);
    device->setConfigWindow(configWindow);

    QVariant deviceVariant;
    deviceVariant.setValue(device);
    selectedDevices.append(deviceVariant);

    qDebug() << "-------------------------------------------------------------";
    qDebug() << "Test Query in Orchestrator slot slotCreateN7745ADevice";
    QByteArray response;
    PowerMeter *test = selectedDevices.at(selectedDevices.size()-1).value<PowerMeter*>();
    test->queryIDN(defaultSession, response);
    qDebug() << "Response: " << response;
    qDebug() << "-------------------------------------------------------------";
}

ViSession * Orchestrator::getDefaultSession(){
    return &defaultSession;
}

QVariant Orchestrator::getDeviceAtIndex(int index){
    return selectedDevices.at(index);
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
