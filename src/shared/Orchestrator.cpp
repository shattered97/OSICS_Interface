#include "Orchestrator.h"


Orchestrator::Orchestrator(WindowFactory *windowFactory, QObject *parent) : QObject(parent)
{
    this->windowFactory = windowFactory;
    qRegisterMetaType<FoundInstr>();
    qRegisterMetaType<QVariant>();
    qRegisterMetaType<QVariant*>();
}

Orchestrator::~Orchestrator()
{
    theCommBus.closeDefaultSession(defaultSession);
}

void Orchestrator::slotStartOrchestrator(){

    theCommBus.createDefaultRM(defaultSession);
    communicationLock = new QMutex();
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

        // connecting signals for sending commands here so we can query for number of modules
        QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                         this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
        QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                         this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)), Qt::AutoConnection);
        QObject::connect(this, SIGNAL(signalSetupPowerMeter()), device, SLOT(slotSetupPowerMeter()));
        emit signalSetupPowerMeter();
    }
    else if(type == "EXFO,OSICS"){

        EXFO_OSICS_MAINFRAME *device = new EXFO_OSICS_MAINFRAME(instrumentIdentity, instrumentAddress);

        // connecting signals for sending commands here so we can query for installed modules
        QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                         this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
        QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                         this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)), Qt::AutoConnection);

        QObject::connect(this, SIGNAL(signalSetupEXFOModules()), device, SLOT(slotSetupEXFOModules()));
        emit signalSetupEXFOModules();

        deviceVariant.setValue(device);

    }
    else if(type == "ANDO,AQ6331"){
        Ando_AQ6331 *device = new Ando_AQ6331(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else if(type == BRISTOL_428A_DEVICE){
        Bristol_428A *device = new Bristol_428A(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else{
        // #TODO error/exit
    }

    selectedDevices.append(deviceVariant);


    QMainWindow *configWindow;
    QMetaObject::invokeMethod(windowFactory, "makeWindow", Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QMainWindow *, configWindow),
                              Q_ARG(QString, type),
                              Q_ARG(QVariant *, &deviceVariant));
    qDebug() << "@@@@@@@@@@@@@@@@@ " << QThread::currentThread();

    DefaultInstrument *device = deviceVariant.value<DefaultInstrument*>();
    device->setConfigWindow(configWindow);


    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)), Qt::AutoConnection);

    QObject::connect(configWindow, SIGNAL(signalUpdateConfigSettings(QVariant, QSettings *)),
                     this, SLOT(slotUpdateConfigSettings(QVariant, QSettings *)));
    QObject::connect(configWindow, SIGNAL(signalApplyConfigSettings(QVariant, QSettings *)),
                     this, SLOT(slotApplyConfigSettings(QVariant, QSettings *)));
}

QVariant Orchestrator::getDeviceAtIndex(int index){
    return selectedDevices.at(index);
}

void Orchestrator::slotGetEXFOModuleQVariants(QMap<int, QVariant> &modules, QVariant &device){

    EXFO_OSICS_MAINFRAME *exfo = device.value<EXFO_OSICS_MAINFRAME*>();
    QByteArray chassisAddress = exfo->getInstrLocation();
    QByteArray chassisIdentity = exfo->getInstrIdentity();
    QList<QByteArray> modTypes = exfo->getModuleTypeNames();
    QVariant moduleVariant;


    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        int slotNum = i + 1;
        if(modTypes[i].contains("T100")){
            EXFO_OSICS_T100 *module = new EXFO_OSICS_T100(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            module->setT100MinMaxWavelengths(modTypes[i]);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow;
            QMetaObject::invokeMethod(windowFactory, "makeWindow", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(QMainWindow *, configWindow),
                                      Q_ARG(QString, modTypes[i]),
                                      Q_ARG(QVariant *, &moduleVariant));

            module->setConfigWindow(configWindow);
        }
        else if(modTypes[i].contains("ATN")){
            EXFO_OSICS_ATN *module = new EXFO_OSICS_ATN(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow;
            QMetaObject::invokeMethod(windowFactory, "makeWindow", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(QMainWindow *, configWindow),
                                      Q_ARG(QString, modTypes[i]),
                                      Q_ARG(QVariant *, &moduleVariant));

            module->setConfigWindow(configWindow);
        }
        else if(modTypes[i].contains("SWT")){
            EXFO_OSICS_SWT *module = new EXFO_OSICS_SWT(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)), Qt::AutoConnection);
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow;
            QMetaObject::invokeMethod(windowFactory, "makeWindow", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(QMainWindow *, configWindow),
                                      Q_ARG(QString, modTypes[i]),
                                      Q_ARG(QVariant *, &moduleVariant));
            module->setConfigWindow(configWindow);
        }
        else{
            // #TODO slot is either empty or module is not supported (error msg)
        }


    }

}

void Orchestrator::slotGetEXFOModuleConfigPairs(QVariant &device, QMap<int, ModuleConfigPair> &moduleConfigPairs){
    // get exfo from qvariant

    EXFO_OSICS_MAINFRAME *exfo = device.value<EXFO_OSICS_MAINFRAME*>();
    QMap<int, QVariant> moduleVariantMap = exfo->getModuleSlotQVariantMap();

    QList<ModuleConfigPair> configPairs;
    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        int slotNum = i + 1;
        if(moduleVariantMap.count(slotNum)){
            QVariant moduleVariant = exfo->getModuleAtSlot(slotNum);
            QMainWindow *moduleWindow = exfo->getWindowForModuleAtSlot(slotNum);
            ModuleConfigPair modPair(moduleVariant, moduleWindow);
            moduleConfigPairs.insert(slotNum, modPair);
        }
    }
}

void Orchestrator::slotUpdateConfigSettings(QVariant deviceVariant, QSettings *configSettings){
    // because QVariant types are <type*> compare result of typeName()[:-1] with enum strings
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);

    if(typeName == "PowerMeter"){

        PowerMeter* device = deviceVariant.value<PowerMeter*>();
        device->updateConfig(configSettings);

        // config settings updated, signal to sender
        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "N7714A"){

        N7714A* device = deviceVariant.value<N7714A*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_MAINFRAME"){

        EXFO_OSICS_MAINFRAME* device = deviceVariant.value<EXFO_OSICS_MAINFRAME*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_T100"){

        EXFO_OSICS_T100* device = deviceVariant.value<EXFO_OSICS_T100*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_ATN"){

        EXFO_OSICS_ATN* device = deviceVariant.value<EXFO_OSICS_ATN*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_SWT"){

        EXFO_OSICS_SWT* device = deviceVariant.value<EXFO_OSICS_SWT*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else{
        // #TODO error/exit
    }

}

void Orchestrator::slotApplyConfigSettings(QVariant deviceVariant, QSettings *configSettings){
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);

    if(typeName == "PowerMeter"){

        PowerMeter* device = deviceVariant.value<PowerMeter*>();
        device->applyConfigSettings(configSettings);

        // config settings updated, signal to sender
        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "N7714A"){
        N7714A* device = deviceVariant.value<N7714A*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_MAINFRAME"){

        EXFO_OSICS_MAINFRAME* device = deviceVariant.value<EXFO_OSICS_MAINFRAME*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_ATN"){
        EXFO_OSICS_ATN* device = deviceVariant.value<EXFO_OSICS_ATN*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_SWT"){
        EXFO_OSICS_SWT* device = deviceVariant.value<EXFO_OSICS_SWT*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_T100"){
        EXFO_OSICS_T100* device = deviceVariant.value<EXFO_OSICS_T100*>();
        device->applyConfigSettings(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else{
        qDebug() << "device not recognized in slotApplyConfigSettings()";
        // #TODO error/exit
    }
}


void Orchestrator::slotClearSelectedDevices(){
    // #TODO should close any config windows that may be open
    selectedDevices.clear();
}


void Orchestrator::slotBeginTest(QString testTypeName){
    // #TODO probably do enum for test types

    DeviceTest *test = DeviceTestFactory::makeDeviceTest(testTypeName, selectedDevices);

    if(!test){
        // signal to mainWindow to show error message
        QString invalidTestMsg = "Test not yet supported.";
        emit signalSendSimpleErrorMsg(invalidTestMsg);
    }
    else{
        if(!test->areDevicesValidForTest()){

            // don't run test and send error msg to mainwindow
            QString invalidDevicesMsg = "Combination of selected devices are not valid for the selected test.";
            emit signalSendSimpleErrorMsg(invalidDevicesMsg);
        }
        else{
            if(test->isWindowConfigureable()){
                // show window (if the test has one)
                test->configWindow->show();
            }
            else{
                // else run test w/o window
                test->runDeviceTest();
            }
        }
    }
}

// ========================================= COMMUNICATION FUNCTIONS ==============================================

void Orchestrator::slotSendCmdNoRsp(QByteArray instrAddress, QByteArray command)
{
    communicationLock->lock();

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

        ViStatus status = theCommBus.sendCmd(instrSession, instrAddress, command);

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
    communicationLock->unlock();
}

void Orchestrator::slotSendCmdRsp(QByteArray instrAddress, QByteArray command, QByteArray *response)
{
    communicationLock->lock();

    bool success = true;

    // open a communication session to the instrument
    ViSession instrSession;
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, instrAddress, instrSession);

    if(sessionStatus < VI_SUCCESS){
        success = false;
        qDebug() << "Opening session failed.  status: " << sessionStatus;

        // send message to mainWindow that we can't open a session on the instrument
        QString message = QString(ERR_OPEN_SESSION_FAILED).arg(QString(instrAddress));
        emit signalSendDecisionErrorMsg(message);
        *response = ERR_NO_COMM_RESPONSE;
    }
    else{

        // check if instrument is done processing previous commands
        checkOperationComplete(instrSession, instrAddress);

        qDebug() << "operation complete.";
        ViStatus status = theCommBus.sendCmd(instrSession, instrAddress, command);
            if(status < VI_SUCCESS){
                qDebug() << QString("Query failed: %1").arg(status);
                success = false;
                QString message = QString(ERR_SENDING_CMD_FAILED).arg(QString(instrAddress));
                emit signalSendDecisionErrorMsg(message);
                *response = ERR_NO_COMM_RESPONSE;
            }
            else{
                qDebug() << "Command sent: " << command;
                status = theCommBus.readCmd(instrSession, instrAddress, *response);

                if(status < VI_SUCCESS){
                    qDebug() << QString("Reading response failed: %1").arg(status);
                    success = false;

                    QString message = QString(ERR_READING_RSP_FAILED).arg(QString(instrAddress));
                    emit signalSendDecisionErrorMsg(message);
                    *response = ERR_NO_COMM_RESPONSE;
                }
                else{

                }
            }

        // close session
        theCommBus.closeSession(instrSession);

    }
    communicationLock->unlock();
}

bool Orchestrator::checkOperationComplete(ViSession instrSession, QByteArray instrAddress, int timeout)
{
    // start timer
    QElapsedTimer timer;
    timer.start();

    int complete = 0;

    // retry sending the command and reading response until the timeout is reached
    while(timer.elapsed() < timeout && complete == 0){
        complete = 0;

        theCommBus.sendCmd(instrSession, instrAddress, QUERY_OPC);

        QByteArray response = "";
        theCommBus.readCmd(instrSession, instrAddress, response);

        complete = response[0];
    }
    return complete;
}



