#include "exfo_t100_pm_power_step_test.h"
#include <QTime>
#include "ConversionUtilities.h"


EXFO_T100_PM_Power_Step_Test::EXFO_T100_PM_Power_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    qRegisterMetaType<QMap<int, int>>();
    qRegisterMetaTypeStreamOperators<QMap<int, int>>();

    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    QObject::connect(&configWindow, SIGNAL(signalBeginTest(QSettings *)),
                     this, SLOT(slotBeginTest(QSettings *)));
    QObject::connect(&configWindow, SIGNAL(signalGetT100DisplayNames(QList<QByteArray> &)),
                     this, SLOT(slotReturnT100DisplayNames(QList<QByteArray> &)));
    QObject::connect(&configWindow, SIGNAL(signalGetPowerMeterChannels(int &)),
                     this, SLOT(slotReturnPowerMeterChannels(int &)));
    QObject::connect(this, SIGNAL(signalSendTestProgressToGUI(double)),
                     &configWindow, SLOT(slotReceiveTestProgress(double)));
    QObject::connect(this, SIGNAL(signalTestComplete()),
                     &configWindow, SLOT(slotTestComplete()));
    QObject::connect(this, SIGNAL(signalGUIProcessEvents()),
                     &configWindow, SLOT(slotGUIProcessEvents()));
}

bool EXFO_T100_PM_Power_Step_Test::areDevicesValidForTest(){
    // checks for correct device AND initializes them for the test at the same time

    // we need to find the EXFO T100 and a PowerMeter.
    bool t100Found = false;
    bool powerMeterFound = false;

    // iterate through the selected devices
    for(int i = 0; i < selectedDevices.size(); i++){
        // get type name - (typeName() returns the type with '*' at the end)
        QByteArray typeName = selectedDevices.at(i).typeName();
        typeName.chop(1);
        if(typeName == "EXFO_OSICS_MAINFRAME"){
            // create exfo and find out if it has at least one T100
            QVariant exfoVariant = selectedDevices.at(i);
            EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();

            QMap<int, QVariant> exfoModuleSlotQMap = exfo->getModuleSlotQVariantMap();

            for(auto e: exfoModuleSlotQMap.keys()){
                // get type of module
                QByteArray moduleType = exfoModuleSlotQMap.value(e).typeName();
                moduleType.chop(1);

                if(moduleType == "EXFO_OSICS_T100"){
                    // add all T100's found to the list of available modules
                    availableT100s.append(exfoModuleSlotQMap.value(e).value<EXFO_OSICS_T100*>());

                    t100Found = true;
                }
            }
        }
        else if(typeName == "PowerMeter"){
            QVariant powerMeterVariant = selectedDevices.at(i);
            powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeterFound = true;
        }
    }

    bool success = (t100Found && powerMeterFound);
    return success;
}

QByteArray EXFO_T100_PM_Power_Step_Test::constructOutputFilename(){

    // #TODO: needs to be updated to append the wavelength number (e.g. 1520, 1310) to beginning of filename

    QStringList filenameElements;
    for(auto t100SlotNum : t100SlotNumToPMSlotNumMap.keys())
    {
        // create an identifier for each exfo we are testing
        QByteArray identityInfo = availableT100s.first()->identificationModuleQuery(t100SlotNum);

        // the serial number is the third item when comma-separated, the module type is the second item
        QByteArray serialNumber = identityInfo.split(',')[2];
        QByteArray moduleType = identityInfo.split(',')[1];

        filenameElements.append(serialNumber);
        filenameElements.append(moduleType);
    }

    QByteArray testName = "power_step";
    QByteArray timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss").toLatin1();

    filenameElements.append(testName);
    filenameElements.append(timestamp);
    QByteArray filename = filenameElements.join('_').toLatin1();
    QByteArray extension = ".csv";
    filename.append(extension);

    return filename;
}

void EXFO_T100_PM_Power_Step_Test::runDeviceTest()
{
//    workerThread = new QThread;
//    worker = new EXFO_T100_PM_Power_Step_Test_Worker(startPowerDBM, endPowerDBM, powerStepDBM,
//                                                     dwellInSeconds, wavelengthNM);

//    worker->moveToThread(workerThread);
//    workerThread->setObjectName("Test Worker Thread");

//    // basic thread connections
//    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
//    connect(workerThread, SIGNAL(started()), worker, SLOT(runTest()));
//    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
//    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));



//    workerThread->start();

    // #TODO this method to be executed on another thread

    // we can safely set the "selected t100" device to any T100, since the Mainframe is the actual reciever
    // and the actual T100s are differentiated by slot number
    selectedT100 = availableT100s.first();


    runTestLoop(outputFilename, startPowerDBM, endPowerDBM, powerStepDBM, wavelengthNM, dwellInSeconds,
                t100SlotNumToPMSlotNumMap);
}

void EXFO_T100_PM_Power_Step_Test::runTestLoop(QByteArray filename, double startPow,
                                               double endPow, double powStep, double wavelength,
                                               double dwell, QMap<int, int> t100SlotNumToPMSlotNumMap)
{
    // create csv header based on selected modules
    for(auto t100SlotNum : t100SlotNumToPMSlotNumMap.keys()){
        QString t100WavelengthInfo = "T100 Slot " + QString::number(t100SlotNum) + " WAVELENGTH,";
        qDebug() << t100WavelengthInfo;
        QString powerMeterPowerInfo = "PM Slot " +
                QString::number(t100SlotNumToPMSlotNumMap.value(t100SlotNum)) + " POWER,";

        testData.append(t100WavelengthInfo);
        testData.append(powerMeterPowerInfo);
        testData.append("POWER METER READING,");
    }
    testData.append("\n");

    qDebug() << testData;

    // set wavelengths on T100 and PM for each module
    for(auto currentT100SlotNum : t100SlotNumToPMSlotNumMap.keys()){

        // set wavelength (t100)
        QByteArray wavelengthToSet = QByteArray::number(wavelength);
        selectedT100->setRefWavelengthModuleCmd(currentT100SlotNum, wavelengthToSet);

        // set wavelength (power meter)
        int currentPowerMeterSlotNum = t100SlotNumToPMSlotNumMap.value(currentT100SlotNum);
        QByteArray wavUnit = "nm";
        powerMeter->setWavelength(currentPowerMeterSlotNum, wavelengthToSet, wavUnit);

        // don't need to set PM units anymore since we will be doing a bulk read
    }

    // enable lasers and set power
    for(auto currentT100SlotNum : t100SlotNumToPMSlotNumMap.keys()){

        // enable laser
        selectedT100->enableModuleLaserCmd(currentT100SlotNum);

        // set start power
        QByteArray powerToSet = QByteArray::number(startPow);
        selectedT100->setModuleOutputPowerCmd(currentT100SlotNum, powerToSet);
        int currentPowerMeterSlotNum = t100SlotNumToPMSlotNumMap.value(currentT100SlotNum);
    }

    // wait for values to adjust
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();
    // elapsed timer is in milliseconds, convert to seconds
    while((elapsedTimer.elapsed() / 1000) <= dwell){
        // signal to window to processEvents
        emit signalGUIProcessEvents();
    }

    double currentPow = startPow;
    while(currentPow <= endPow){

        for(auto currentT100SlotNum : t100SlotNumToPMSlotNumMap.keys()){
            // set output power
            QByteArray powerToSet = QByteArray::number(currentPow);
            selectedT100->setModuleOutputPowerCmd(currentT100SlotNum, powerToSet);
        }

        // wait for power to adjust
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();
        // elapsed timer is in milliseconds, convert to seconds
        while((elapsedTimer.elapsed() / 1000) <= dwell){
            // signal to window to processEvents
            emit signalGUIProcessEvents();
        }

        // get readings here in bulk so we don't have to repeat for each module
        QList<QByteArray> bulkPowerReadings = powerMeter->getPowerReadingOnAllChannels();
        qDebug() << "power readings: " << bulkPowerReadings;
        for(auto currentT100SlotNum : t100SlotNumToPMSlotNumMap.keys()){
            // write wavelength
            QByteArray t100Wavelength = selectedT100->refWavelengthModuleQuery(currentT100SlotNum);
            testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(","));

            // write power
            QByteArray t100Power = selectedT100->outputPowerModuleQuery(currentT100SlotNum);
            testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(","));

            // power meter readings are now bulk readings- get value from bulk list
            int currentPowerMeterSlotNum = t100SlotNumToPMSlotNumMap.value(currentT100SlotNum);
            double powerReadingInDBM = bulkPowerReadings[currentPowerMeterSlotNum - 1].trimmed().toDouble();

            // write power reading
            testData.append(QByteArray::number(powerReadingInDBM));
            testData.append(",");
        }

        // end data line
        testData.append("\n");

        currentPow += powStep;
        emit signalSendTestProgressToGUI(calculateProgress());
        currentStep++;
    }

    // reset laser power to 0 and turn off laser
    QByteArray powerToSet = QByteArray::number(startPow);

    for(auto currentT100SlotNum : t100SlotNumToPMSlotNumMap.keys()){

        selectedT100->setModuleOutputPowerCmd(currentT100SlotNum, powerToSet);

        selectedT100->disableModuleLaserCmd(currentT100SlotNum);
    }

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";
    emit signalTestComplete();
}

void EXFO_T100_PM_Power_Step_Test::writeTestDataToFile(QByteArray filename){
    if(testData.size() > 0){
        qDebug() << filename;
        // init output file
        QFile file(filename);
        file.open(QIODevice::ReadWrite);
        QTextStream stream(&file);

        for( auto e : testData ){
            stream << e;
            qDebug() << testData;
        }

        file.close();
    }
}

void EXFO_T100_PM_Power_Step_Test::calculateNumberOfSteps(){
    double powerRange = endPowerDBM - startPowerDBM;
    numberOfSteps = (int) powerRange / powerStepDBM;
}

double EXFO_T100_PM_Power_Step_Test::calculateProgress(){
    double progress = 100 * currentStep / numberOfSteps;
    return progress;
}

void EXFO_T100_PM_Power_Step_Test::setStartPower(double startPower){
    this->startPowerDBM = startPower;
}
void EXFO_T100_PM_Power_Step_Test::setEndPower(double endPower){
    this->endPowerDBM = endPower;
}
void EXFO_T100_PM_Power_Step_Test::setPowerStep(double powerStep){
    this->powerStepDBM = powerStep;
}
void EXFO_T100_PM_Power_Step_Test::setWavelength(double wavelength){
    this->wavelengthNM = wavelength;
}

void EXFO_T100_PM_Power_Step_Test::slotReturnT100DisplayNames(QList<QByteArray> &displayNames)
{
    for(auto t100Module : availableT100s)
    {
        int t100SlotNum = t100Module->getSlotNum();

        QByteArray t100Type = t100Module->typeOfModuleQuery(t100SlotNum);
        t100Type = t100Type.split(':')[1].trimmed();

        QByteArray formattedSlotNum = QByteArray::number(t100SlotNum);
        formattedSlotNum = QByteArray("Slot " + formattedSlotNum);

        displayNames.append(t100Type + "," + formattedSlotNum);
    }
}

void EXFO_T100_PM_Power_Step_Test::slotReturnPowerMeterChannels(int &numberOfSlots)
{
    numberOfSlots = powerMeter->getNumPowerMeterChannels();
}

void EXFO_T100_PM_Power_Step_Test::slotBeginTest(QSettings *settings)
{
    // get settings
    this->settings = settings;
    getTestValuesFromSettings();

    // construct filename
    outputFilename = constructOutputFilename();

    calculateNumberOfSteps();

    runDeviceTest();
}

void EXFO_T100_PM_Power_Step_Test::getTestValuesFromSettings()
{
    startPowerDBM = settings->value(T100_PM_POWER_STEP_TEST_START_POWER).value<double>();
    endPowerDBM = settings->value(T100_PM_POWER_STEP_TEST_END_POWER).value<double>();
    powerStepDBM = settings->value(T100_PM_POWER_STEP_TEST_POWER_STEP).value<double>();
    dwellInSeconds = settings->value(T100_PM_POWER_STEP_TEST_DWELL).value<double>();
    wavelengthNM = settings->value(T100_PM_POWER_STEP_TEST_WAVELENGTH).value<double>();
    t100SlotNumToPMSlotNumMap = settings->value(T100_SLOT_NUM_TO_PM_SLOT_NUM_MAP).value<QMap<int, int>>();

    for(auto t100SlotNum : t100SlotNumToPMSlotNumMap.keys()){
        qDebug() << "T100: " << t100SlotNum << " ----- PM: " << t100SlotNumToPMSlotNumMap.value(t100SlotNum);
    }

}
