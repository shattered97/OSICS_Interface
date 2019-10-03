#include "Orchestrator.h"
#include "PowerMeterFactory.h"
#include "WindowFactory.h"
#include "ConversionUtilities.h"

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
    qDebug() << "slotCreateDevice()";
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
        qDebug() << "exfo in slotCreateDevice()";

        EXFO_OSICS_MAINFRAME *device = new EXFO_OSICS_MAINFRAME(instrumentIdentity, instrumentAddress);

        // connecting signals for sending commands here so we can query for installed modules
        QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                         this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)));
        QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                         this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

        QObject::connect(this, SIGNAL(signalSetupEXFOModules()), device, SLOT(slotSetupEXFOModules()));
        emit signalSetupEXFOModules();

        deviceVariant.setValue(device);

    }
    else if(type == "ANDO,AQ6331"){
        Ando_AQ6331 *device = new Ando_AQ6331(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else if(type == Bristol_428A_DEVICE){
        Bristol_428A *device = new Bristol_428A(instrumentIdentity, instrumentAddress);
        deviceVariant.setValue(device);
    }
    else{
        // #TODO error/exit
    }

    selectedDevices.append(deviceVariant);

    QMainWindow *configWindow = WindowFactory::makeWindow(type, deviceVariant);
    DefaultInstrument *device = deviceVariant.value<DefaultInstrument*>();
    device->setConfigWindow(configWindow);

    QObject::connect(device, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)));
    QObject::connect(device, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

    QObject::connect(configWindow, SIGNAL(signalUpdateConfigSettings(QVariant &, QSettings &)),
                     this, SLOT(slotUpdateConfigSettings(QVariant &, QSettings &)));
    QObject::connect(configWindow, SIGNAL(signalApplyConfigSettings(QVariant &, QSettings &)),
                     this, SLOT(slotApplyConfigSettings(QVariant &, QSettings &)));
}

QVariant Orchestrator::getDeviceAtIndex(int index){
    return selectedDevices.at(index);
}

void Orchestrator::slotGetEXFOModuleQVariants(QMap<int, QVariant> &modules, QVariant &device){
    // #TODO Factory class?

    qDebug() << "slotGetEXFOModuleQVariants()";
    EXFO_OSICS_MAINFRAME *exfo = device.value<EXFO_OSICS_MAINFRAME*>();
    QByteArray chassisAddress = exfo->getInstrLocation();
    QByteArray chassisIdentity = exfo->getInstrIdentity();
    QList<QByteArray> modTypes = exfo->getModuleTypeNames();
    QVariant moduleVariant;


    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        int slotNum = i + 1;
        if(modTypes[i].contains("T100")){
            qDebug() << "t100 module";
            EXFO_OSICS_T100 *module = new EXFO_OSICS_T100(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            module->setT100MinMaxWavelengths(modTypes[i]);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)));
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow = WindowFactory::makeWindow(modTypes[i], moduleVariant);
            module->setConfigWindow(configWindow);
        }
        else if(modTypes[i].contains("ATN")){
            qDebug() << "atn module";
            EXFO_OSICS_ATN *module = new EXFO_OSICS_ATN(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)));
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow = WindowFactory::makeWindow(modTypes[i], moduleVariant);
            module->setConfigWindow(configWindow);
        }
        else if(modTypes[i].contains("SWT")){
            qDebug() << "swt module";
            EXFO_OSICS_SWT *module = new EXFO_OSICS_SWT(chassisIdentity, chassisAddress);
            module->setSlotNum(slotNum);
            moduleVariant.setValue(module);
            modules.insert(slotNum, moduleVariant);

            QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray, QByteArray *)),
                             this, SLOT(slotSendCmdRsp(QByteArray, QByteArray, QByteArray *)));
            QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray)),
                             this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray)));

            // create window
            QMainWindow *configWindow = WindowFactory::makeWindow(modTypes[i], moduleVariant);
            module->setConfigWindow(configWindow);
        }
        else{
            // #TODO slot is either empty or module is not supported (error msg)
        }


        DefaultInstrument *module = moduleVariant.value<DefaultInstrument*>();

    }

}

void Orchestrator::slotGetEXFOModuleConfigPairs(QVariant &device, QMap<int, ModuleConfigPair> &moduleConfigPairs){
    // get exfo from qvariant
    qDebug() << "slotGetEXFOModuleConfigPairs()";
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

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_ATN"){
        qDebug() << "updating atn";
        EXFO_OSICS_ATN* device = deviceVariant.value<EXFO_OSICS_ATN*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else if(typeName == "EXFO_OSICS_SWT"){
        qDebug() << "updating swt";
        EXFO_OSICS_SWT* device = deviceVariant.value<EXFO_OSICS_SWT*>();
        device->updateConfig(configSettings);

        QObject::connect(this, SIGNAL(signalSettingsUpdated()), device->getConfigWindow(), SLOT(slotUpdateWindow()));
        emit signalSettingsUpdated();
    }
    else{
        // #TODO error/exit
    }

}

void Orchestrator::slotApplyConfigSettings(QVariant &deviceVariant, QSettings &configSettings){
    QString typeName = QString(deviceVariant.typeName());
    typeName.chop(1);
    qDebug() << "slotApplyConfigSettings()";
    qDebug() << "***********************************************" << typeName;
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

void Orchestrator::slotSendCmdNoRsp(QByteArray instrAddress, QByteArray command){

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

void Orchestrator::slotSendCmdRsp(QByteArray instrAddress, QByteArray command, QByteArray *response){

    qDebug() << "Command sent: " << command;
    bool success = true;

    ViSession instrSession;

    // open session
    ViStatus sessionStatus = theCommBus.openInstrSession(defaultSession, instrAddress, instrSession);
    qDebug() << "opened session to instrument";
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

                status = theCommBus.readCmd(instrSession, instrAddress, *response, rtnSize);

                if(status < VI_SUCCESS){
                    qDebug() << QString("Reading response failed: %1").arg(status);
                    success = false;
                }
                else{
                    qDebug() << "Response: " << *response;
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


void Orchestrator::slotBeginTest(QString testTypeName){
    // #TODO probably do enum for test types

    qDebug() << "in slotBeginTest()";
    DeviceTest *test = DeviceTestFactory::makeDeviceTest(testTypeName, selectedDevices);

    if(!test){
        // signal to mainWindow to show error message
        QByteArray invalidTestMsg = "Test not yet supported.";
        emit signalCreateErrorDialog(invalidTestMsg);
    }
    else{
        if(!test->areDevicesValidForTest()){
            qDebug() << "not running test";
            // don't run test and send error msg to mainwindow
            QByteArray invalidDevicesMsg = "Combination of selected devices are not valid for the selected test.";
            emit signalCreateErrorDialog(invalidDevicesMsg);
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
