#include "EXFO_T100_SWT_PM_WM_Test.h"
#include "ConversionUtilities.h"

EXFO_T100_SWT_PM_WM_Test::EXFO_T100_SWT_PM_WM_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_SWT_PM_WM_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100, SWT Bristol Wavemeter, and a PowerMeter.
    bool t100Found = false;
    bool swtFound = false;
    bool bristolFound = false;
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
                    // create T100 if it doesn't already exist (in the case where there are multiple T100s installed)
                    if(t100 == nullptr){
                        t100SlotNum = e;
                        t100 = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_T100*>();
                        t100Found = true;
                    }
                }
                else if(moduleType == "EXFO_OSICS_SWT"){
                    // create swt if it doesn't already exist
                    if(swt == nullptr){
                        swtSlotNum = e;
                        swt = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_SWT*>();
                        swtFound = true;
                    }
                }
            }
        }
        else if(typeName == "Bristol_428A"){
            QVariant bristolVariant = selectedDevices->at(i);
            bristol = bristolVariant.value<Bristol_428A*>();
            bristolFound = true;
        }
        else if(typeName == "PowerMeter"){
            // *NOTE* for now we only use the first slot on a power meter.
            powerMeterSlotNum = 1;
            QVariant powerMeterVariant = selectedDevices->at(i);
            powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeterFound = true;
        }
    }

    bool success = (t100Found && swtFound && powerMeterFound);
    return success;
}

QByteArray EXFO_T100_SWT_PM_WM_Test::constructOutputFilename(){
    // get active channel number
    QByteArray activeChannelNum = swt->getChannelForSignalAPC(swtSlotNum);
    activeChannelNum = activeChannelNum.split('=')[1].trimmed();

    // construct filename
    QByteArray identityInfo = swt->identificationModuleQuery(swtSlotNum);

    // the serial number is the third item when comma-separated, the module type is the second item
    QByteArray serialNumber = identityInfo.split(',')[2];
    QByteArray moduleType = identityInfo.split(',')[1];
    QByteArray testName = "wavelength_step";
    QByteArray timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss").toLatin1();


    QStringList filenameElements = {serialNumber, moduleType, activeChannelNum, testName, timestamp};
    QByteArray filename = filenameElements.join('_').toLatin1();
    QByteArray extension = ".csv";
    filename.append(extension);

    return filename;
}

void EXFO_T100_SWT_PM_WM_Test::runDeviceTest(){

    // init switch
    QByteArray fullBandMode = "ECL";
    swt->setAPCModuleOperatingMode(swtSlotNum, fullBandMode);
    swt->autoDetectT100Modules(swtSlotNum);

    // set active channel
    QByteArray channel = QByteArray::number(activeChannel);
    swt->selectChannelForSignalAPC(swtSlotNum, channel);

    QByteArray filename = constructOutputFilename();
    qDebug() << filename;

    runTestLoopPowerMeterOnly(filename, activeChannel, startWav, endWav, wavStep, power);



}

void EXFO_T100_SWT_PM_WM_Test::runTestLoopPowerMeterOnly(QByteArray filename, int activeChannel, double startWav, double endWav, double wavStep, double power){

    // add .csv header to test data
    testData.append("SWITCH CHANNEL,");
    testData.append("T100 POWER,");
    testData.append("T100 WAVELENGTH,");
    testData.append("POWER METER POWER\n");


    // get active switch channel
    QByteArray channel = swt->getChannelForSignalAPC(swtSlotNum);


    // enable laser and switch output
    t100->enableModuleLaserCmd(t100SlotNum);
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    swt->enableModuleLaserCmd(swtSlotNum);
    swt->setModulePowerUnitDBmCmd(swtSlotNum);

    // set laser power
    QByteArray powerToSet = QByteArray::number(power);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);
    // set swich output power
    swt->setModuleOutputPowerCmd(swtSlotNum, powerToSet);

    // int starting wavelength
    QByteArray startWavToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, startWavToSet);
    QByteArray wavUnit = "nm";
    powerMeter->setWavelength(powerMeterSlotNum, startWavToSet, wavUnit);

    // wait for adjustments
    QTime timer = QTime::currentTime().addSecs(4);
    while(QTime::currentTime() < timer){
        // do nothing
    }



    double currentWav = startWav;
    while(currentWav <= endWav){

        testData.append(channel.split('=')[1].trimmed().append(','));


        // set t100 wavelength
        QByteArray wavToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

        // set power meter wavelength
        QByteArray wavUnit = "nm";
        powerMeter->setWavelength(powerMeterSlotNum, wavToSet, wavUnit);

        // set switch wavelength
        swt->setRefWavelengthModuleCmd(swtSlotNum, wavToSet);

        // wait for adjustments
        QTime timer = QTime::currentTime().addSecs(4);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // get t100 output power
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));


        // write current t100 wavelength
        QByteArray t100Wav = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wav.split('=')[1].toDouble()).append(','));

        // write power meter reading
        QByteArray powerReading = powerMeter->measurePower(powerMeterSlotNum);

        // convert and write out
        double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
        testData.append(QByteArray::number(convertedPower));

        // end data line
        testData.append("\n");

        currentWav += wavStep;
    }

    // shut off laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";
}

void EXFO_T100_SWT_PM_WM_Test::runTestLoopWithWavemeter(QByteArray filename, int activeChannel, double startWav, double endWav, double wavStep, double power){

    // add .csv header to test data
    testData.append("SWITCH CHANNEL,");
    testData.append("T100 POWER,");
    testData.append("T100 WAVELENGTH,");
    testData.append("BRISTOL WAVELENGTH,");
    testData.append("POWER METER POWER");
    testData.append("\n");

    // enable laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // set laser power
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = QByteArray::number(power);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // int starting wavelength
    QByteArray startWavToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, startWavToSet);

    // wait for adjustments
    QTime timer = QTime::currentTime().addSecs(3);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentWav = startWav;
    while(currentWav <= endWav){

        // get active switch channel
        QByteArray channel = swt->getChannelForSignalAPC(swtSlotNum);
        testData.append(channel.split('=')[1].trimmed().append(','));

        // get t100 output power
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));

        // set t100 wavelength
        QByteArray wavToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

        // set power meter wavelength
        QByteArray wavUnit = "nm";
        powerMeter->setWavelength(powerMeterSlotNum, wavToSet, wavUnit);

        // set switch wavelength
        swt->setRefWavelengthModuleCmd(swtSlotNum, wavToSet);

        // wait for adjustments
        QTime timer = QTime::currentTime().addSecs(3);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // write current t100 wavelength
        QByteArray t100Wav = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wav.split('=')[1].toDouble()).append(','));


        // write wavemeter wavelength
        QByteArray bristolWav = bristol->measureWavelengthSingle();
        testData.append(bristolWav.trimmed().append(','));

        // write power meter reading
        QByteArray powerReading = powerMeter->measurePower(powerMeterSlotNum);
        // convert and write out
        double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
        testData.append(QByteArray::number(convertedPower));

        // end data line
        testData.append("\n");

        currentWav += wavStep;
    }

    // shut off laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";
}

void EXFO_T100_SWT_PM_WM_Test::writeTestDataToFile(QByteArray filename){
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

void EXFO_T100_SWT_PM_WM_Test::setStartWavelength(double startWav){
    this->startWav = startWav;
}
void EXFO_T100_SWT_PM_WM_Test::setEndWavelength(double endWav){
    this->endWav = endWav;
}
void EXFO_T100_SWT_PM_WM_Test::setWavelengthStep(double stepSize){
    this->wavStep = stepSize;
}
void EXFO_T100_SWT_PM_WM_Test::setPower(double power){
    this->power = power;
}
void EXFO_T100_SWT_PM_WM_Test::setPowerMeterSlotNum(int slotNum){
    this->powerMeterSlotNum = slotNum;
}
void EXFO_T100_SWT_PM_WM_Test::setActiveChannel(int channel){
    this->activeChannel = channel;
}
