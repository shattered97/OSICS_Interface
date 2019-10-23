#include "exfo_t100_pm_power_step_test.h"
#include <QTime>
#include "ConversionUtilities.h"


EXFO_T100_PM_Power_Step_Test::EXFO_T100_PM_Power_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{

}


bool EXFO_T100_PM_Power_Step_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100 and a PowerMeter.
    bool t100Found = false;
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
            qDebug() << exfoModuleSlotQMap;
            for(auto e: exfoModuleSlotQMap.keys()){
                // get type of module
                QByteArray moduleType = exfoModuleSlotQMap.value(e).typeName();
                moduleType.chop(1);

                if(moduleType == "EXFO_OSICS_T100"){
                    // create T100 if it doesn't already exist (in the case where there are multiple T100s installed)
                    if(t100 == nullptr){
                        t100SlotNum = e;
                        t100 = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_T100*>();
                        t100Found = true;
                    }
                }
            }
        }
        else if(typeName == "PowerMeter"){
            QVariant powerMeterVariant = selectedDevices->at(i);
            powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeterFound = true;
        }
    }

    bool success = (t100Found && powerMeterFound);
    return success;
}

QByteArray EXFO_T100_PM_Power_Step_Test::constructOutputFilename(){
    qDebug() << "in constructOutputFilename()";
    // construct filename
    QByteArray identityInfo = t100->identificationModuleQuery(t100SlotNum);
    qDebug() << identityInfo;
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
    qDebug() << "runDeviceTest() in powerMeterStepTestT100";
    // construct filename
    QByteArray filename = constructOutputFilename();
    qDebug() << "constructed filename";
    runTestLoop(filename, startPower, endPower, powerStep, wavelength);
    qDebug() << "finished running test loop";
}

void EXFO_T100_PM_Power_Step_Test::runTestLoop(QByteArray filename, double startPow,
                                               double endPow, double powStep, double wavelength){
    // add .csv header to test data
    testData.append("T100 WAVELENGTH,");
    testData.append("T100 POWER,");
    testData.append("POWER METER READING");
    testData.append("\n");

    // set wavelength (t100)
    QByteArray wavelengthToSet = QByteArray::number(wavelength);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set wavelength (power meter)
    QByteArray wavUnit = "nm";
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << powerMeterSlotNum;
    powerMeter->setWavelength(powerMeterSlotNum, wavelengthToSet, wavUnit);

    // set unit
    t100->setModulePowerUnitDBmCmd(t100SlotNum);

    // enable laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // set start power
    QByteArray powerToSet = QByteArray::number(startPow);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // wait for values to adjust
    QTime timer = QTime::currentTime().addSecs(2);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentPow = startPow;
    while(currentPow <= endPow){

        // set power
        QByteArray powerToSet = QByteArray::number(currentPow);
        t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

        // wait for power to adjust
        QTime timer = QTime::currentTime().addSecs(2);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // write wavelength
        QByteArray t100Wavelength = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(","));

        // write power
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(","));

        // write power reading
        QByteArray powerReading = powerMeter->measurePower(powerMeterSlotNum);
        // convert and write out
        double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
        testData.append(QByteArray::number(convertedPower));

        // end data line
        testData.append("\n");

        currentPow += powStep;
    }

    // shut off laser
    t100->disableModuleLaserCmd(t100SlotNum);


    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

}

void EXFO_T100_PM_Power_Step_Test::writeTestDataToFile(QByteArray filename){
    if(testData.size() > 0){

        // init output file
        QFile file(filename);
        file.open(QIODevice::ReadWrite);
        QTextStream stream(&file);

        for( auto e : testData ){
            stream << e;
        }

        file.close();
    }
}

void EXFO_T100_PM_Power_Step_Test::setStartPower(double startPower){
    this->startPower = startPower;
}
void EXFO_T100_PM_Power_Step_Test::setEndPower(double endPower){
    this->endPower = endPower;
}
void EXFO_T100_PM_Power_Step_Test::setPowerStep(double powerStep){
    this->powerStep = powerStep;
}
void EXFO_T100_PM_Power_Step_Test::setWavelength(double wavelength){
    this->wavelength = wavelength;
}
void EXFO_T100_PM_Power_Step_Test::setPowerMeterSlotNum(int slotNum){
    this->powerMeterSlotNum = slotNum;
}
