#include "WavStepWithPowerMonitoringTest.h"

WavStepWithPowerMonitoringTest::WavStepWithPowerMonitoringTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    QObject::connect(&configWindow, SIGNAL(signalBeginTest(QSettings *)), this, SLOT(slotBeginTest(QSettings *)));
    QObject::connect(&configWindow, SIGNAL(signalGetT100DisplayNames(QList<QByteArray> &)),
                     this, SLOT(slotGetT100DisplayNames(QList<QByteArray> &)));
    QObject::connect(&configWindow, SIGNAL(signalSwitchMapChanged(QMap<int, QByteArray>)),
                     this, SLOT(slotSwitchMapChanged(QMap<int, QByteArray>)));
    QObject::connect(this, SIGNAL(signalUpdateMinMaxWavelength(double, double)),
                     &configWindow, SLOT(slotUpdateMinMaxWavelength(double, double)));
    QObject::connect(&configWindow, SIGNAL(signalGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &)),
                     this, SLOT(slotGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &)));
    QObject::connect(&configWindow, SIGNAL(signalPollForPowerMeterReadings()), this, SLOT(slotPollForPowerMeterReadings()));
}

void WavStepWithPowerMonitoringTest::slotPollForPowerMeterReadings(){
    // # TODO one worker for each power meter
    qDebug() << "slotPollForPowerMeterReadings()";

    for(auto e : powerMeters){
        QThread *workerThread = new QThread;
        PowerMeterPollingWorker *worker = new PowerMeterPollingWorker(e);
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

    qDebug() << t100Found << " " << atnFound << " " << powerMeterFound;
    bool success = (t100Found && atnFound && powerMeterFound);
    return success;
}

void WavStepWithPowerMonitoringTest::runDeviceTest(){

    qDebug() << t100Modules;
    qDebug() << powerMeters;
    double min = calculateMinWavelength();
    double max = calculateMaxWavelength();
    qDebug() << min << " " << max;


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
    qDebug() << swtChannelToT100Map;

    // populate list of assigned modules
    populateAssignedModules(swtChannelToT100Map);

    // calculate min and max wavelengths
    double minWavelength = calculateMinWavelength();
    double maxWavelength = calculateMaxWavelength();

    emit signalUpdateMinMaxWavelength(minWavelength, maxWavelength);
}

void WavStepWithPowerMonitoringTest::populateAssignedModules(QMap<int, QByteArray> swtChannelToT100Map){
    // parse t100 slot num out of QByteArray
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
    qDebug() << "assigned modules: " << assignedT100Modules;
}

void WavStepWithPowerMonitoringTest::slotBeginTest(QSettings *settings){
    runDeviceTest();
}


//void WavStepWithPowerMonitoringTest::slotGetTestValues(QSettings settings){
//    // populate test value fields from settings
////    this->settings = &settings;

////    csvFilename = settings.value(WAV_STEP_TEST_CSV_FILENAME).value<QByteArray>();
////    graphFilename = settings.value(WAV_STEP_TEST_GRAPH_FILENAME).value<QByteArray>();
////    startWav = settings.value(WAV_STEP_TEST_START_WAVELENGTH).value<double>();
////    endWav = settings.value(WAV_STEP_TEST_END_WAVELENGTH).value<double>();
////    wavStepSize = settings.value(WAV_STEP_TEST_WAV_STEP_SIZE).value<double>();
////    dwellSeconds = settings.value(WAV_STEP_TEST_DWELL_SECONDS).value<double>();
////    estimatedTime = settings.value(WAV_STEP_TEST_ESTIMATED_TIME).value<double>();
//}


void WavStepWithPowerMonitoringTest::slotGetPowerMeterDisplayPairs(QList<QPair<QByteArray, int>> &powerMeterDisplayPairs){
    powerMeterDisplayPairs.clear();
    for(auto e : powerMeters){
        // create power meter identifier string
        QByteArray powerMeterID = e->getInstrIdentity();

        // for each channel, create pair of <id, channel num> and add to QList
        int numChannels = e->getNumPowerMeterChannels();
        for(int i = 1; i <= numChannels; i++){
            qDebug() << i << " " << powerMeterID;
            QPair<QByteArray, int> pair = {powerMeterID, i};
            powerMeterDisplayPairs.append(pair);
        }
    }
}
