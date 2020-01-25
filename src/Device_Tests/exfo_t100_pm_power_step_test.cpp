#include "exfo_t100_pm_power_step_test.h"
#include <QTime>
#include "ConversionUtilities.h"


EXFO_T100_PM_Power_Step_Test::EXFO_T100_PM_Power_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    QObject::connect(&configWindow, SIGNAL(signalBeginTest(QSettings *)),
                     this, SLOT(slotBeginTest(QSettings *)));
    QObject::connect(&configWindow, SIGNAL(signalGetT100DisplayNames(QList<QByteArray> &)),
                     this, SLOT(slotReturnT100DisplayNames(QList<QByteArray> &)));
    QObject::connect(&configWindow, SIGNAL(signalGetPowerMeterChannels(int &)),
                     this, SLOT(slotReturnPowerMeterChannels(int &)));
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

    QByteArray identityInfo = selectedT100->identificationModuleQuery(t100SlotNum);

    // the serial number is the third item when comma-separated, the module type is the second item
    QByteArray serialNumber = identityInfo.split(',')[2];
    QByteArray moduleType = identityInfo.split(',')[1];
    QByteArray testName = "power_step";
    QByteArray timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss").toLatin1();

    QStringList filenameElements = {serialNumber, moduleType, testName, timestamp};
    QByteArray filename = filenameElements.join('_').toLatin1();
    QByteArray extension = ".csv";
    filename.append(extension);

    return filename;
}

void EXFO_T100_PM_Power_Step_Test::runDeviceTest(){

    // #TODO this method to be executed on another thread
    runTestLoop(outputFilename, startPowerDBM, endPowerDBM, powerStepDBM, wavelengthNM, dwellInSeconds);

    // #TODO add join() call here then emit signal to GUI that the test has finished.
}

void EXFO_T100_PM_Power_Step_Test::runTestLoop(QByteArray filename, double startPow,
                                               double endPow, double powStep, double wavelength, double dwell)
{
    // add .csv header to test data #TODO consider adding to constants file
    testData.append("T100 WAVELENGTH,");
    testData.append("T100 POWER,");
    testData.append("POWER METER READING");
    testData.append("\n");

    // set wavelength (t100)
    QByteArray wavelengthToSet = QByteArray::number(wavelength);
    selectedT100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set wavelength (power meter)
    QByteArray wavUnit = "nm";
    powerMeter->setWavelength(powerMeterSlotNum, wavelengthToSet, wavUnit);

    // set unit
    selectedT100->setModulePowerUnitDBmCmd(t100SlotNum);

    // enable laser
    selectedT100->enableModuleLaserCmd(t100SlotNum);

    // set start power
    QByteArray powerToSet = QByteArray::number(startPow);
    selectedT100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // wait for values to adjust
    QTime timer = QTime::currentTime().addSecs(dwell); // #TODO fix unit conversion
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentPow = startPow;
    while(currentPow <= endPow){

        // set power
        QByteArray powerToSet = QByteArray::number(currentPow);
        selectedT100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

        // wait for power to adjust
        QTime timer = QTime::currentTime().addSecs(dwell);  // #TODO fix unit conversion
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // write wavelength
        QByteArray t100Wavelength = selectedT100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(","));

        // write power
        QByteArray t100Power = selectedT100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(","));

        // write power reading
        QByteArray powerReading = powerMeter->measurePower(powerMeterSlotNum);
        // convert and write out
        double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
        testData.append(QByteArray::number(convertedPower));

        // end data line
        testData.append("\n");

        currentPow += powStep;
        emit signalSendTestProgressToGUI(calculateProgress());
        currentStep++;
    }

    // reset laser power to 0
    powerToSet = QByteArray::number(startPow);
    selectedT100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // shut off laser
    selectedT100->disableModuleLaserCmd(t100SlotNum);

    // #TODO: write test data intermittently

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

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
void EXFO_T100_PM_Power_Step_Test::setPowerMeterSlotNum(int slotNum){
    this->powerMeterSlotNum = slotNum;
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

    powerMeterSlotNum = settings->value(T100_PM_POWER_STEP_TEST_PM_SLOT_NUM).value<int>();
    t100SlotNum = settings->value(T100_PM_POWER_STEP_TEST_T100_SLOT_NUM).value<int>();

    // set selected T100 based on slot number
    for(auto t100Module : availableT100s){
        if(t100Module->getSlotNum() == t100SlotNum){
            selectedT100 = t100Module;
        }
    }
}
