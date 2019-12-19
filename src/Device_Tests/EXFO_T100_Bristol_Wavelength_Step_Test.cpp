#include "EXFO_T100_Bristol_Wavelength_Step_Test.h"
#include <QTime>
EXFO_T100_Bristol_Wavelength_Step_Test::EXFO_T100_Bristol_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_Bristol_Wavelength_Step_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100, SWT Bristol Wavemeter, and a PowerMeter.
    bool t100Found = false;
    bool bristolFound = false;
    bool powerMeterFound = false;

    // iterate through the selected devices
    for(int i = 0; i < selectedDevices.size(); i++){
        // get type name - (typeName() returns the type with '*' at the end)
        QByteArray typeName = selectedDevices.at(i).typeName();
        typeName.chop(1);
        if(typeName == "EXFO_OSICS_MAINFRAME"){
            // create exfo and find out if it has a T100
            // *NOTE* for now we assume that only one T100 is plugged in or we use the first one we see
            QVariant exfoVariant = selectedDevices.at(i);
            EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();

            QMap<int, QVariant> exfoModuleSlotQMap = exfo->getModuleSlotQVariantMap();
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
        else if(typeName == "Bristol_428A"){
            QVariant bristolVariant = selectedDevices.at(i);
            bristol = bristolVariant.value<Bristol_428A*>();
            bristolFound = true;
        }
        else if(typeName == "PowerMeter"){
            // *NOTE* for now we only use the first slot on a power meter.
            powerMeterSlotNum = 1;
            QVariant powerMeterVariant = selectedDevices.at(i);
            powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeterFound = true;
        }
    }

    bool success = (t100Found && bristolFound);
    return success;

}

void EXFO_T100_Bristol_Wavelength_Step_Test::writeTestDataToFile(QByteArray filename){
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

QByteArray EXFO_T100_Bristol_Wavelength_Step_Test::constructOutputFilename(){

    //construct filename
    QByteArray identityInfo = t100->identificationModuleQuery(t100SlotNum);

    // the serial number is the third item when comma-separated, the module type is the second item
    QByteArray serialNumber = identityInfo.split(',')[2];
    QByteArray moduleType = identityInfo.split(',')[1];
    QByteArray testName = "Bristol_Wavemeter_wavelength_step";
    QByteArray timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss").toLatin1();

    QStringList filenameElements = {serialNumber, moduleType, testName, timestamp};
    QByteArray filename = filenameElements.join('_').toLatin1();
    QByteArray extension = ".csv";
    filename.append(extension);

    return filename;

}

void EXFO_T100_Bristol_Wavelength_Step_Test::runDeviceTest(){
    qDebug() << "executing t100/bristol test";

    QByteArray filename = constructOutputFilename();


    // get min and max wavelength based on module
    startWav = t100->getT100MinWavelength();
    endWav = t100->getT100MaxWavelength();
    qDebug() << startWav << " " << endWav;

    calculateNumberOfSteps();


//    if(powerMeter != nullptr){
//        runTestLoopWithPowerMeter(filename, startWav, endWav, wavStep);
//    }
//    else{
        runTestLoopBristolOnly(filename, startWav, endWav, wavStep);
//    }
}

void EXFO_T100_Bristol_Wavelength_Step_Test::runTestLoopWithPowerMeter(QByteArray filename, double startWav, double endWav, double wavStep){

    // add .csv header
    testData.append("T100 WAVELENGTH,");
    testData.append("T100 POWER,");
    testData.append("BRISTOL WAVELENGTH,");
    testData.append("BRISTOL POWER,");
    testData.append("POWER METER POWER\n");

    //set starting wavelength
    QByteArray wavelengthToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // enable laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // set power values
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = ("0");
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // wait for values to adjust
    QTime timer = QTime::currentTime().addSecs(5);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentWav = startWav;
    while(currentWav <= endWav){
        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // set wavelength on power meter
        QByteArray wavUnit = "nm";
        powerMeter->setWavelength(powerMeterSlotNum, wavelengthToSet, wavUnit);

       // wait for wavelength to adjust
        QTime timer = QTime::currentTime().addSecs(5);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // get wavelength reported by t100
        QByteArray t100Wavelength = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(','));

        // get output power of t100
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));

        // get wavelength reported by wavemeter
        QByteArray bristolWavelength = bristol->measureWavelengthSingle();
        testData.append(bristolWavelength.trimmed().append(','));

        // get power reported by wavemeter
        QByteArray bristolPower = bristol->measurePowerSingle();
        testData.append(bristolPower.trimmed().append(','));

        // get power reported by powerMeter
        QByteArray powerMeterReading = powerMeter->measurePower(powerMeterSlotNum);
        testData.append(powerMeterReading.trimmed() + "\n");

        currentWav += wavStep;
    }

    // enable laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

}


void EXFO_T100_Bristol_Wavelength_Step_Test::runTestLoopBristolOnly(QByteArray filename, double startWav, double endWav, double wavStep)
{
    // add .csv header
    testData.append("T100 WAVELENGTH,");
    testData.append("T100 POWER,");
    testData.append("BRISTOL WAVELENGTH,");
    testData.append("BRISTOL POWER\n");

    //set starting wavelength (t100)
    QByteArray wavelengthToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // enable laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // set power values
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = ("0");
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // wait for values to adjust
    QTime timer = QTime::currentTime().addSecs(5);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentWav = startWav;
    while(currentWav <= endWav){

        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // wait for wavelength to adjust
        QTime timer = QTime::currentTime().addSecs(5);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // get wavelength reported by t100
        QByteArray t100Wavelength = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(','));

        // get output power of t100
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));

        // get wavelength reported by wavemeter
        QByteArray bristolWavelength = bristol->measureWavelengthSingle();
        testData.append(bristolWavelength.trimmed().append(','));

        // get power reported by wavemeter
        QByteArray bristolPower = bristol->measurePowerSingle();
        testData.append(bristolPower.trimmed().append('\n'));

        currentWav += wavStep;
        emit signalSendTestProgressToGUI(calculateProgress());
        currentStep++;
    }

    // disable laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

}

void EXFO_T100_Bristol_Wavelength_Step_Test::calculateNumberOfSteps(){
    double wavelengthRange = endWav - startWav;
    numberOfSteps = (int) wavelengthRange / wavStep;
    qDebug() << "NUMBER OF STEPS CALCULATED: " << numberOfSteps;
}

double EXFO_T100_Bristol_Wavelength_Step_Test::calculateProgress(){
    double progress = 100 * currentStep / numberOfSteps;
    qDebug() << "PROGRESS CALCULATED (" << currentStep << "/" << numberOfSteps << "): " << progress;
    return progress;
}


void EXFO_T100_Bristol_Wavelength_Step_Test::setStartWavelength(double startWav){
    this->startWav = startWav;
}

void EXFO_T100_Bristol_Wavelength_Step_Test::setEndWavelength(double endWav){
    this->endWav = endWav;
}

void EXFO_T100_Bristol_Wavelength_Step_Test::setWavelengthStep(double wavStep){
    this->wavStep = wavStep;
}

void EXFO_T100_Bristol_Wavelength_Step_Test::setPowerMeterSlotNum(int slotNum){
    this->powerMeterSlotNum = slotNum;
}
