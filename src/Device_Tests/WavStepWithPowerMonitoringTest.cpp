#include "WavStepWithPowerMonitoringTest.h"


WavStepWithPowerMonitoringTest::WavStepWithPowerMonitoringTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

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

void WavStepWithPowerMonitoringTest::slotSendPowerReadingCommand(PowerMeter *powerMeter){
    QList<QByteArray> readings;
    powerMeter->getPowerReadingOnAllChannels(readings);

    // signal to window to display power (send identity and readings list)
    emit signalDisplayPowerReadings(powerMeter->getInstrIdentity(), readings);

    if(testStarted){
        qDebug() << "in test started loop";
        for(int i = 0; i < readings.size(); i++){
            // create series name
            QByteArray seriesName = powerMeter->getInstrIdentity() + " Channel " + QByteArray::number(i+1);
            double timeInMs = timer.elapsed();
            double timeInSec = timeInMs / 1000;
            QPair<QByteArray, QByteArray> dataPoint = {QByteArray::number(timeInSec), readings[i]};
            qDebug() << dataPoint;
            qDebug() << allData.keys().size();
            allData.value(seriesName)->append(dataPoint);

        }
        readingCount += 1;
        if(readingCount == maxCountBeforeWrite){
            // clear count and write data to graph
            readingCount = 0;
            emit signalGraphPowerMeterReadings(allData);
        }
    }
}

void WavStepWithPowerMonitoringTest::slotPollForPowerMeterReadings(){
    // # TODO one worker for each power meter
    qDebug() << "slotPollForPowerMeterReadings()";


    for(auto e : powerMeters){
        QThread *workerThread = new QThread;
        PowerMeterPollingWorker *worker = new PowerMeterPollingWorker(e);
        workers.append(worker);

        QObject::connect(worker, SIGNAL(signalSendPowerReadingCommand(PowerMeter *)),
                         this, SLOT(slotSendPowerReadingCommand(PowerMeter *)));

        worker->moveToThread(workerThread);

        connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
        connect(workerThread, SIGNAL(started()), worker, SLOT(slotPollPowerMeter()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

        qDebug() << "starting worker";
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

void WavStepWithPowerMonitoringTest::runDeviceTest(){
    
    // perform setup operations
    setupTestOperations();
    
    
    // start timer
    timer.start();
    testStarted = true;

}

void WavStepWithPowerMonitoringTest::setupTestOperations(){
    
}

void WavStepWithPowerMonitoringTest::slotGetT100DisplayNames(QList<QByteArray> &displayNames){
    for(auto e : t100Modules){
        QByteArray t100Type = "";
        e.first->typeOfModuleQuery(e.second, t100Type);
        t100Type = t100Type.split(':')[1].trimmed();

        QByteArray t100SlotNum = QByteArray("Slot " + QByteArray::number(e.second));
        displayNames.append(t100Type + "," + t100SlotNum);
    }
}

double WavStepWithPowerMonitoringTest::calculateMinWavelength(){

    if(assignedT100Modules.size() > 0){
        double minWavelength = assignedT100Modules.first().first->getT100MinWavelength();
        for(auto e : assignedT100Modules){
            double compareWavelength = e.first->getT100MinWavelength();
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
        double maxWavelength = assignedT100Modules.first().first->getT100MaxWavelength();
        for(auto e : assignedT100Modules){
            double compareWavelength = e.first->getT100MaxWavelength();
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
    this->swtChannelToT100Map = swtChannelToT100Map;

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
    for(auto e : swtChannelToT100Map.keys()){

        QByteArray t100Type = swtChannelToT100Map.value(e).trimmed();
        if(t100Type != "<None>"){
            int t100SlotNum = t100Type.mid(t100Type.size() - 1).toInt();
            int switchChannel = e;
            QPair<EXFO_OSICS_T100*, int> pair = {t100Modules.at(t100SlotNum - 1).first, switchChannel};
            assignedT100Modules.append(pair);

        }

    }

}

void WavStepWithPowerMonitoringTest::slotShowGraphWindow(){
    graphWindow->show();
}

void WavStepWithPowerMonitoringTest::slotBeginTest(QSettings *settings){

    this->settings = settings;
    getTestValuesFromSettings();

    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    qDebug() << assignedT100Modules.size();
    queueT100sForTest();
    prepareOutputDataMap();

    // create graph window
    graphWindow = new WavStep_Power_Monitoring_Graph_Window(channelsToGraph);
    QObject::connect(this, SIGNAL(signalGraphPowerMeterReadings(WavStepPowerTestData)),
                     graphWindow, SLOT(slotGraphPowerMeterReadings(WavStepPowerTestData)));
    runDeviceTest();
}

void WavStepWithPowerMonitoringTest::executeTestStep(EXFO_OSICS_T100 *t100Module, QByteArray wavelengthToSet, double dwellTimeInMs){

    // set wavelength on t100
    int t100SlotNum = t100Module->getSlotNum();
    t100Module->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // we will need to know which t100 we are operating on at th time


    // set wavelength on power meter(s)
    for(auto powerMeter : powerMeters){
        int numChannels = powerMeter->getNumPowerMeterChannels();
        for(int i = 1; i <= numChannels; i++){
            QByteArray channelNum = QByteArray::number(i);
            QByteArray unit = "nm";
            powerMeter->setWavelength(i, wavelengthToSet, unit);
        }
    }

    // wait for amount specified by dwell time
    QElapsedTimer dwellTimer;
    dwellTimer.start();
    if(dwellTimer.elapsed() < dwellTimeInMs){
       // wait
    }

}

void WavStepWithPowerMonitoringTest::queueT100sForTest(){

    qDebug() << "===========================================================================";
    QList<QPair<EXFO_OSICS_T100*, QPair<double, double>>> t100TestQueue;

    double currentStartWav = startWav;
    double currentStopWav = endWav;
    qDebug() << "current start wav: " << currentStartWav;
    qDebug() << "current end wav: " << currentStopWav;

    while(currentStartWav < currentStopWav){
        qDebug() << currentStartWav;
        bool matchFound = false;
        qDebug() << "///////////////////////////////////////////////";
        for(auto e : assignedT100Modules){
            if(!matchFound){
                qDebug() << "********************";
                qDebug() << "slotnum of module: " << e.first->getSlotNum();
                double t100MinWav = e.first->getT100MinWavelength();
                double t100MaxWav = e.first->getT100MaxWavelength();

                qDebug() << "min/max wav: " << t100MinWav << " " << t100MaxWav;
                double moduleStartWav = currentStartWav;
                double moduleStopWav = currentStopWav;

                qDebug() << "is " << currentStartWav <<  " >= " << t100MinWav << " and <= " << t100MaxWav;

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

                    QPair<EXFO_OSICS_T100*, QPair<double, double>> queuePair = {e.first, {moduleStartWav, moduleStartWav}};
                    t100TestQueue.append(queuePair);
                    qDebug() << "Test Pair added: < " << e.first->getSlotNum() << " , < " << QByteArray::number(moduleStartWav) << " , " << QByteArray::number(moduleStopWav) << " >";

                    currentStartWav = moduleStopWav + 0.01;
                    qDebug() << "new current startWav = " << currentStartWav;
                }
            }
            else{
                qDebug() << "skipping laser at slotNum : " << e.first->getSlotNum() << " because we already found a match";
            }

        }
        if(!matchFound){

            qDebug() << "increasing search criteria by " << wavStepSize;
            // increase search criteria by the step size and try again
            currentStartWav += wavStepSize;
        }
        qDebug() << "currentStartWav < currentStopWav?" << currentStartWav << " " << currentStopWav;
    }

    qDebug() << "=======================================================================";
}


void WavStepWithPowerMonitoringTest::getTestValuesFromSettings(){

    csvFilename = settings->value(WAV_STEP_TEST_CSV_FILENAME).value<QByteArray>();
    graphFilename = settings->value(WAV_STEP_TEST_GRAPH_FILENAME).value<QByteArray>();
    startWav = settings->value(WAV_STEP_TEST_START_WAVELENGTH).value<double>();
    endWav = settings->value(WAV_STEP_TEST_END_WAVELENGTH).value<double>();
    wavStepSize = settings->value(WAV_STEP_TEST_WAV_STEP_SIZE).value<double>();
    dwellSeconds = settings->value(WAV_STEP_TEST_DWELL_SECONDS).value<double>();
    swtChannelToT100Map = settings->value(WAV_STEP_TEST_SWT_CHANNELS_TO_T100).value<QMap<int, QByteArray>>();
    channelsToGraph = settings->value(WAV_STEP_TEST_CHANNELS_TO_GRAPH).value<QList<QByteArray>>();
    qDebug() << "channels to graph: " << channelsToGraph;

}

void WavStepWithPowerMonitoringTest::prepareOutputDataMap(){

    // get series name for each power meter channel
    for(auto e : powerMeters){
        QByteArray powerMeterID = e->getInstrIdentity();
        int numChannels = e->getNumPowerMeterChannels();
        for(int i = 1; i <= numChannels; i++){
            powerMeterChannelNames.append(powerMeterID + " Channel " + QByteArray::number(i));
        }
    }

    for(auto e : powerMeterChannelNames){
        QList<QPair<QByteArray, QByteArray>> *placeholderList = new QList<QPair<QByteArray, QByteArray>>();
        allData.insert(e, placeholderList);
    }
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
