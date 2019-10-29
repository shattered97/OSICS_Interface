#include "WavStepWithPowerMonitoringTest.h"
#include <QMessageBox>


WavStepWithPowerMonitoringTest::WavStepWithPowerMonitoringTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    qRegisterMetaType<PowerReadings>();
    qRegisterMetaType<QByteArray>();

    QObject::connect(&configWindow, SIGNAL(signalBeginTest(QSettings *)),
                     this, SLOT(slotBeginTest(QSettings *)));
    QObject::connect(&configWindow, SIGNAL(signalGetT100DisplayNames(QList<QByteArray> &)),
                     this, SLOT(slotGetT100DisplayNames(QList<QByteArray> &)));
    QObject::connect(&configWindow, SIGNAL(signalSwitchMapChanged(QMap<int, QByteArray>)),
                     this, SLOT(slotSwitchMapChanged(QMap<int, QByteArray>)));
    QObject::connect(this, SIGNAL(signalUpdateMinMaxWavelength(double, double)),
                     &configWindow, SLOT(slotUpdateMinMaxWavelength(double, double)));
    QObject::connect(&configWindow, SIGNAL(signalGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &)),
                     this, SLOT(slotGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &)));
    QObject::connect(&configWindow, SIGNAL(signalPollForPowerMeterReadings()), this, SLOT(slotPollForPowerMeterReadings()));

    QObject::connect(this, SIGNAL(signalDisplayPowerReadings(QByteArray, QList<QByteArray>)),
                     &configWindow, SLOT(slotDisplayPowerReadings(QByteArray, QList<QByteArray>)));
    QObject::connect(&configWindow, SIGNAL(signalShowGraphWindow()), this, SLOT(slotShowGraphWindow()));

}

WavStepWithPowerMonitoringTest::~WavStepWithPowerMonitoringTest(){

}

void WavStepWithPowerMonitoringTest::slotSendPowerReadings(PowerReadings readingsForPowerMeter){

    PowerMeter *powerMeter = readingsForPowerMeter.powerMeter;
    QList<QByteArray> readings = readingsForPowerMeter.powerReadings;

    // signal to window to display power (send identity and readings list)
    emit signalDisplayPowerReadings(powerMeter->getInstrIdentity(), readings);
}


void WavStepWithPowerMonitoringTest::slotPollForPowerMeterReadings(){

    for(auto powerMeter : powerMeters){
        QThread *workerThread = new QThread;
        PowerMeterPollingWorker *worker = new PowerMeterPollingWorker(powerMeter);
        workers.append(worker);
        worker->moveToThread(workerThread);
        // name threads
        QThread::currentThread()->setObjectName("Main Thread");
        workerThread->setObjectName("PM Polling Thread");

        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!! main thread id: " << QThread::currentThread();

        QObject::connect(worker, SIGNAL(signalSendPowerReadings(PowerReadings)),
                         this, SLOT(slotSendPowerReadings(PowerReadings)));
        QObject::connect(configWindow, SIGNAL(signalStopAllWorkerThreads()), worker, SLOT(slotStopWorkerThreads()));


        connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
        connect(workerThread, SIGNAL(started()), worker, SLOT(slotPollPowerMeter()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

        workerThread->start();
    }

}

bool WavStepWithPowerMonitoringTest::areDevicesValidForTest(){
    // we need to find the EXFO T100, EXFO ATN and a PowerMeter
    bool t100Found = false;
    bool atnFound = false;
    bool swtFound = false;
    bool powerMeterFound = false;

    // iterate through the selected devices
    for(int i = 0; i < selectedDevices->size(); i++){
        // get type name - (typeName() returns the type with '*' at the end)
        QByteArray typeName = selectedDevices->at(i).typeName();
        typeName.chop(1);
        if(typeName == "EXFO_OSICS_MAINFRAME"){
            // create exfo and find out if it has a T100
            // *NOTE* for now we assume that only one T100 is plugged in or we use the first one we see
            QVariant exfoVariant = selectedDevices->at(i);
            EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();

            QMap<int, QVariant> exfoModuleSlotQMap = exfo->getModuleSlotQVariantMap();
            for(auto e: exfoModuleSlotQMap.keys()){
                // get type of module
                QByteArray moduleType = exfoModuleSlotQMap.value(e).typeName();
                moduleType.chop(1);

                if(moduleType == "EXFO_OSICS_T100"){
                    // create t100 modules
                    EXFO_OSICS_T100 *t100 = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_T100*>();
                    QPair<EXFO_OSICS_T100 *, int> t100Pair = {t100, e};
                    t100Modules.append(t100Pair);
                    t100Found = true;
                }
                else if(moduleType == "EXFO_OSICS_ATN"){
                    // create atn if it doesn't already exist
                    if(exfoATN == nullptr){
                        atnSlotNum = e;
                        exfoATN = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_ATN*>();
                        atnFound = true;
                    }
                }
                else if(moduleType == "EXFO_OSICS_SWT"){
                    // create swt if it doesn't already exist
                    if(exfoSWT == nullptr){
                        swtSlotNum = e;
                        exfoSWT = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_SWT*>();
                        swtFound = true;
                    }
                }
            }
        }
        else if(typeName == "PowerMeter"){
            QVariant powerMeterVariant = selectedDevices->at(i);
            PowerMeter *powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeters.append(powerMeter);
            powerMeterFound = true;
        }
    }

    bool success = (t100Found && atnFound && powerMeterFound);
    return success;
}

void WavStepWithPowerMonitoringTest::runDeviceTest()
{

    QThread *workerThread = new QThread;
    WavStep_Power_Monitoring_Test_Worker *worker = new WavStep_Power_Monitoring_Test_Worker(testData);
    worker->moveToThread(workerThread);
    // name threads
    workerThread->setObjectName("Test Worker Thread");

    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!! main thread id: " << QThread::currentThread();

    // create graph window
    double graphRefreshMsec = graphRefreshRate * SEC_TO_MSEC_MULTIPLIER;
    graphWindow = new WavStep_Power_Monitoring_Graph_Window(channelsToGraph, WAVSTEP_GRAPH_MAX_POINTS_PER_SERIES, graphRefreshMsec);

    QObject::connect(worker, SIGNAL(signalAddReadingsToGraph(QList<WavStepPowerMonitoringDataPoint>)),
                     graphWindow, SLOT(slotAddReadingsToGraph(QList<WavStepPowerMonitoringDataPoint>)));
    QObject::connect(configWindow, SIGNAL(signalStopAllWorkerThreads()), worker, SLOT(slotStopWorkerThreads()));
    QObject::connect(worker, SIGNAL(signalDisplayCurrentWavelength(QByteArray)), configWindow, SLOT(slotDisplayCurrentWavelength(QByteArray)));
    QObject::connect(worker, SIGNAL(signalTestCompleted()), configWindow, SLOT(slotTestCompleted()));

    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(workerThread, SIGNAL(started()), worker, SLOT(runTest()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    // start timer

    testStarted = true;

    workerThread->start();

}

void WavStepWithPowerMonitoringTest::slotWrapUpTest(){
    // stop graphing
    testStarted = false;

    // show messagebox when test is complete
    QMessageBox msgBox;
    msgBox.setText("Test complete.");
}



void WavStepWithPowerMonitoringTest::slotGetT100DisplayNames(QList<QByteArray> &displayNames){
    for(auto e : t100Modules){
        QByteArray t100Type = e.first->typeOfModuleQuery(e.second);
        t100Type = t100Type.split(':')[1].trimmed();

        QByteArray t100SlotNum = QByteArray("Slot " + QByteArray::number(e.second));
        displayNames.append(t100Type + "," + t100SlotNum);
    }
}

double WavStepWithPowerMonitoringTest::calculateMinWavelength(){

    if(assignedT100Modules.size() > 0){
        double minWavelength = assignedT100Modules.keys().first()->getT100MinWavelength();
        for(auto e : assignedT100Modules.keys()){
            double compareWavelength = e->getT100MinWavelength();
            if(compareWavelength < minWavelength){
                minWavelength = compareWavelength;
            }
        }

        return minWavelength;
    }
    else{
        return 0;
    }
}

double WavStepWithPowerMonitoringTest::calculateMaxWavelength(){


    if(assignedT100Modules.size() > 0){
        double maxWavelength = assignedT100Modules.keys().first()->getT100MaxWavelength();
        for(auto e : assignedT100Modules.keys()){
            double compareWavelength = e->getT100MaxWavelength();
            if(compareWavelength > maxWavelength){
                maxWavelength = compareWavelength;
            }
        }

        return maxWavelength;
    }
    else{
        return 0;
    }

}

void WavStepWithPowerMonitoringTest::slotSwitchMapChanged(QMap<int, QByteArray> swtChannelToT100Map){
    // populate list of assigned modules
    populateAssignedModules(swtChannelToT100Map);

    // calculate min and max wavelengths
    double minWavelength = calculateMinWavelength();
    double maxWavelength = calculateMaxWavelength();

    emit signalUpdateMinMaxWavelength(minWavelength, maxWavelength);
}

void WavStepWithPowerMonitoringTest::populateAssignedModules(QMap<int, QByteArray> swtChannelToT100Map){
    // parse t100 slot num out of QByteArray
    qDebug() << "populateAssignedModules()";
    assignedT100Modules.clear();

    for(auto switchChannel : swtChannelToT100Map.keys()){

        QByteArray t100Type = swtChannelToT100Map.value(switchChannel).trimmed();
        if(t100Type != "<None>"){
            int t100SlotNum = t100Type.mid(t100Type.size() - 1).toInt();

            EXFO_OSICS_T100 *t100Module = t100Modules.at(t100SlotNum - 1).first;

            assignedT100Modules.insert(t100Module, switchChannel);

        }

    }

}

void WavStepWithPowerMonitoringTest::slotShowGraphWindow(){
    graphWindow->show();
}

void WavStepWithPowerMonitoringTest::slotBeginTest(QSettings *settings){

    this->settings = settings;

    getTestValuesFromSettings();

    QList<TestParamsForT100> testParamsForT100 = createTestParamsForT100();

    testData.swtModule = exfoSWT;
    testData.powerMeters = powerMeters;
    testData.testParamsForT100 = testParamsForT100;
    testData.filename = csvFilename;
    testData.graphRefreshRate = graphRefreshRate;
    testData.dwellInMs = dwellSeconds * 1000;
    testData.stepSize = wavStepSize;

    runDeviceTest();
}


QList<TestParamsForT100> WavStepWithPowerMonitoringTest::createTestParamsForT100(){

    double currentStartWav = startWav;
    double currentStopWav = endWav;

    // add t100 modules to test params
    QList<TestParamsForT100> testParamsForT100;

    while(currentStartWav < currentStopWav){

        bool matchFound = false;
        for(auto t100Module : assignedT100Modules.keys()){

            if(!matchFound){

                double t100MinWav = t100Module->getT100MinWavelength();
                double t100MaxWav = t100Module->getT100MaxWavelength();

                double moduleStartWav = currentStartWav;
                double moduleStopWav = currentStopWav;

                if(currentStartWav >= t100MinWav && currentStartWav <= t100MaxWav){
                    matchFound = true;
                    moduleStartWav = currentStartWav;

                    if(currentStopWav <= t100MaxWav){
                        // we can stop testing at this module because we can reach the end wavelength
                        moduleStopWav = currentStopWav;
                    }
                    else{
                        // the stop wavelength for this module is it's max wavelength
                        moduleStopWav = t100MaxWav;
                    }

                    TestParamsForT100 testParams;
                    testParams.t100Module = t100Module;
                    testParams.swtChannel = assignedT100Modules.value(t100Module);
                    testParams.startWav = moduleStartWav;
                    testParams.endWav = moduleStopWav;
                    testParamsForT100.append(testParams);

                    currentStartWav = moduleStopWav + wavStepSize;
                }
            }
        }
        if(!matchFound){
            // increase search criteria by the step size and try again
            currentStartWav += wavStepSize;
        }
    }

    return testParamsForT100;
}


void WavStepWithPowerMonitoringTest::getTestValuesFromSettings(){
    csvFilename = settings->value(WAV_STEP_TEST_CSV_FILENAME).value<QByteArray>();
    startWav = settings->value(WAV_STEP_TEST_START_WAVELENGTH).value<double>();
    graphRefreshRate = settings->value(WAV_STEP_TEST_POWER_POLL_RATE).value<double>();
    endWav = settings->value(WAV_STEP_TEST_END_WAVELENGTH).value<double>();
    wavStepSize = settings->value(WAV_STEP_TEST_WAV_STEP_SIZE).value<double>();
    dwellSeconds = settings->value(WAV_STEP_TEST_DWELL_SECONDS).value<double>();
    swtChannelToT100Map = settings->value(WAV_STEP_TEST_SWT_CHANNELS_TO_T100).value<QMap<int, QByteArray>>();
    channelsToGraph = settings->value(WAV_STEP_TEST_CHANNELS_TO_GRAPH).value<QList<QByteArray>>();

}



void WavStepWithPowerMonitoringTest::slotGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &powerMeterDisplayPairs){
    powerMeterDisplayPairs.clear();
    for(auto e : powerMeters){
        // create power meter identifier string
        QByteArray powerMeterID = e->getInstrIdentity();

        // for each channel, create pair of <id, channel num> and add to QList
        int numChannels = e->getNumPowerMeterChannels();
        for(int i = 1; i <= numChannels; i++){
            QPair<QByteArray, int> pair = {powerMeterID, i};
            powerMeterDisplayPairs.append(pair);
        }
    }
}
