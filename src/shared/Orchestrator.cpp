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
    else if(type == "ANDO,AQ6331"){
        Ando_AQ6331 *device = new Ando_AQ6331(instrumentIdentity, instrumentAddress);
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

void Orchestrator::slotGetEXFOModuleQVariants(QList<ModuleConfigPair> &modules, QList<QByteArray> modTypes, QVariant &device){
    // #TODO Factory class?

    qDebug() << "slotGetEXFOModuleQVariants";
    DefaultInstrument *deviceFromVariant = device.value<DefaultInstrument*>();
    QByteArray chassisAddress = deviceFromVariant->getInstrLocation();
    QByteArray chassisIdentity = deviceFromVariant->getInstrIdentity();

    QVariant moduleVariant;
    for(int i = 0; i < modTypes.size(); i++){
        if(modTypes[i].contains("T100")){
            qDebug() << "t100 module";
            EXFO_OSICS_T100 *module = new EXFO_OSICS_T100(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
        }
        else if(modTypes[i].contains("ATN")){
            qDebug() << "atn module";
            EXFO_OSICS_ATN *module = new EXFO_OSICS_ATN(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
        }
        else if(modTypes[i].contains("SWT")){
            qDebug() << "swt module";
            EXFO_OSICS_SWT *module = new EXFO_OSICS_SWT(chassisIdentity, chassisAddress);
            moduleVariant.setValue(module);
        }
        else{
            // #TODO slot is either empty or module is not supported (error msg)
        }


        // create window
        QMainWindow *configWindow = WindowFactory::makeWindow(modTypes[i], moduleVariant);
        DefaultInstrument *module = moduleVariant.value<DefaultInstrument*>();

        QObject::connect(module, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                         this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
        QObject::connect(module, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                         this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

        module->setConfigWindow(configWindow);

        ModuleConfigPair modConfigPair;
        modConfigPair.first = moduleVariant;
        modConfigPair.second = configWindow;
        modules.append(modConfigPair);
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
        qDebug() << "device not recognized in slotApplyConfigSettings()";
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

QByteArray testPMPowerReading(KeysightPowerMeter *powerMeter, int slotNum){
    QByteArray power;
    powerMeter->measurePower(1, power);
    double powerDouble = power.split('\n')[0].toDouble();
    powerDouble = ConversionUtilities::convertWattToDBm(powerDouble);
    return QByteArray::number(powerDouble);
}

QByteArray testPMWavelengthReading(KeysightPowerMeter *powerMeter, int slotNum){
    QByteArray pmWavelength;
    powerMeter->queryWavelength(1, pmWavelength);
    double pmWavDouble = pmWavelength.split('\n')[0].toDouble();
    pmWavDouble = ConversionUtilities::convertWavelengthFromMeter(pmWavDouble, "nm");
    return QByteArray::number(pmWavDouble);
}

void testSetPMWavelength(KeysightPowerMeter *powerMeter, int slotNum, QByteArray wavelength, QByteArray unit){
    qDebug() << "setting wavelength on power meter to: " << wavelength;
    QByteArray wavUnit = "nm";
    powerMeter->setWavelength(1, wavelength, unit);
}

QByteArray testT100GetWavelength(EXFO_OSICS_T100 *t100, int slotNum){
    QByteArray wavelength;
    t100->refWavelengthModuleQuery(1, wavelength);
    double wavDouble = wavelength.split('=')[1].toDouble();
    return QByteArray::number(wavDouble);
}

void testSetT100Wavelength(EXFO_OSICS_T100 *t100, int slotNum, QByteArray wavelength){
    qDebug() << "setting wavelength on t100 to: " << wavelength;
    t100->setRefWavelengthModuleCmd(slotNum, wavelength);
}

void testSetT100Power(EXFO_OSICS_T100 *t100, int slotNum, QByteArray power){
    qDebug() << "setting power on t100 to: " << power;
    t100->setModuleOutputPowerCmd(1, power);
}

QByteArray testT100OutputPower(EXFO_OSICS_T100 *t100, int slotNum){
    QByteArray power;
    t100->outputPowerModuleQuery(1, power);
    double powerDouble = power.split('=')[1].toDouble();
    return QByteArray::number(powerDouble);
}

void Orchestrator::testOSACommands(){

    QByteArray filename;
    double startWav;
    double endWav;
    double wavStep = 0;
    QByteArray span;
    int slotNum = 0;


// ************************************************************** test csv output

    filename = "t100_1415_OSAWavStep_1360_1470_20.csv";
    startWav = 1360;
    endWav = 1470;
    wavStep = 20;
    span = "5";
    slotNum = 2;

// ************************************************************** step through wavelengths, fine granularity

//    filename = "t100_1310_OSAWavStep_1260_1360_005.csv";
//    startWav = 1260;
//    endWav = 1360;
//    wavStep = 0.05;
//    span = "3";
//    slotNum = 1;

//    filename = "t100_1415_OSAWavStep_1360_1470_005.csv";
//    startWav = 1360;
//    endWav = 1470;
//    wavStep = 0.05;
//    span = "3";
//    slotNum = 2;

//    filename = "t100_1520_OSAWavStep_1465_1575_005.csv";
//    startWav = 1465;
//    endWav = 1575;
//    wavStep = 0.05;
//    span = "3";
//    slotNum = 3;

//    filename = "t100_1620_OSAWavStep_1560_1680_005.csv";
//    startWav = 1560;
//    endWav = 1680;
//    wavStep = 0.05;
//    span = "3";
//    slotNum = 4;


    runOSATest(filename, startWav, endWav, wavStep, span, slotNum);

}

void Orchestrator::runOSATest(QByteArray filename, double startWav, double endWav, double wavStep, QByteArray span, int slotNum){
    // ************ Test Setting Values and Sweeping ***********
    QVariant andoVariant = selectedDevices[0];
    Ando_AQ6331 *ando = andoVariant.value<Ando_AQ6331*>();

    QVariant exfoVariant = selectedDevices[1];

    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();
    EXFO_OSICS_T100 *t100 = new EXFO_OSICS_T100(exfo->getInstrIdentity(), exfo->getInstrLocation());

    QObject::connect(t100, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(t100, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));


    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 Wavelength,";
    stream << "OSA Wavelength,";
    stream << "OSA Power Level" << endl;


    t100->setModulePowerUnitDBmCmd(slotNum);
    t100->enableModuleLaserCmd(slotNum);
    QByteArray startWavString = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(slotNum, startWavString);

    // wait for wav adjustment
    QTime timer = QTime::currentTime().addSecs(2);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentWavelength = startWav;
    while(currentWavelength <= endWav){

        // set current wavelength on exfo
        QByteArray currentWavString = QByteArray::number(currentWavelength);
        t100->setRefWavelengthModuleCmd(slotNum, currentWavString);
        stream << currentWavString << ",";

        // wait for wav adjustment
        QTime timer = QTime::currentTime().addSecs(2);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // set OSA values
        ando->setCenterWavelength(currentWavString);
        ando->setSpan(span);
        ando->runSingleSweep();

        // wait for sweep
        QTime sweepTimer = QTime::currentTime().addSecs(2);
        while(QTime::currentTime() < sweepTimer){
            // do nothing
        }

        QByteArray peakWav;
        QByteArray peakPower;
        ando->getPeakDataFromTrace(peakWav, peakPower);
        stream << peakWav << ",";
        stream << peakPower << endl;

        currentWavelength += wavStep;
    }

    qDebug() << "COMPLETE **********************************************";

}
void Orchestrator::characterizeT100Power(){
    qDebug() << selectedDevices.size();
    QVariant powerMeterVariant = selectedDevices[0];
    QVariant exfoVariant = selectedDevices[1];

    KeysightPowerMeter *n7745a = powerMeterVariant.value<KeysightPowerMeter*>();
    QObject::connect(n7745a, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(n7745a, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();
    EXFO_OSICS_T100 *t100 = new EXFO_OSICS_T100(exfo->getInstrIdentity(), exfo->getInstrLocation());

    QObject::connect(t100, SIGNAL(signalSendCmdRsp(QByteArray, QByteArray&, QByteArray&)),
                     this, SLOT(slotSendCmdRsp(QByteArray, QByteArray &, QByteArray &)));
    QObject::connect(t100, SIGNAL(signalSendCmdNoRsp(QByteArray, QByteArray&)),
                     this, SLOT(slotSendCmdNoRsp(QByteArray, QByteArray &)));

    // init output file
    QString filename = "t100_1310_power_wav_cycle.csv";
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 Wavelength,Desired T100 Output Power,T100 Output Power,Power Meter Wavelength,Power Meter Reading" << endl;

    double startPower = -6.9;
    double endPower = 5;
    double powerStep = 0.5;

    double startWavelength = 1260;
    double endWavelength = 1280;
    double wavelengthStep = 10;

    int waitTimeSeconds = 0;

    //enable laser
    t100->enableModuleLaserCmd(1);

    // get wavelength from exfo t100
    QByteArray wavelength = testT100GetWavelength(t100, 1);
    qDebug() << wavelength;

    // get wavelength from power meter
    qDebug() << testPMWavelengthReading(n7745a, 1);

    // set wavelength on power meter
    testSetPMWavelength(n7745a, 1, wavelength, "nm");

    // check if wavelength was accepted
    qDebug() << testPMWavelengthReading(n7745a, 1);

    // test power reading
    qDebug() << testPMPowerReading(n7745a, 1);

    double currentWavelength = startWavelength;


    while(currentWavelength < endWavelength){
        qDebug() << "-------------------------------------------------------------------";
        // set current wavelength on exfo t100 (slot 1)
        testSetT100Wavelength(t100, 1, QByteArray::number(currentWavelength));

        // wait
        QTime timer = QTime::currentTime().addSecs(waitTimeSeconds);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        double currentPower = startPower;

        while(currentPower < endPower){

            // write out current wavelengths
            stream << testT100GetWavelength(t100, 1) << ",";

            stream << QByteArray::number(currentPower) << ",";

            // set current power on exfo t100 (slot 1);
            testSetT100Power(t100, 1, QByteArray::number(currentPower));

            // wait
            QTime timer = QTime::currentTime().addSecs(waitTimeSeconds);
            while(QTime::currentTime() < timer){
                // do nothing
            }

            stream << testT100OutputPower(t100, 1) << ",";

            // set power meter wavelength
            testSetPMWavelength(n7745a, 1, QByteArray::number(currentWavelength), "nm");

            // check set wavelength;
            stream << testPMWavelengthReading(n7745a, 1) << ",";

            // read power on power meter
            stream << testPMPowerReading(n7745a, 1) << "," << endl;

            // increment power by powerStep
            currentPower += powerStep;
        }


        // increment wavelength by wavelengthStep
        currentWavelength += wavelengthStep;
    }

    t100->disableModuleLaserCmd(1);

    qDebug("*************************** COMPLETE *****************************");


}

