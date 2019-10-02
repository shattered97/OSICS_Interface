#include "EXFO_T100_ATN_Power_Test.h"
#include <QTime>
#include "ConversionUtilities.h"
EXFO_T100_ATN_Power_Test::EXFO_T100_ATN_Power_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_ATN_Power_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100, EXFO ATN and a PowerMeter
    bool t100Found = false;
    bool atnFound = false;
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
                else if(moduleType == "EXFO_OSICS_ATN"){
                    // create atn if it doesn't already exist
                    if(atn == nullptr){
                        atnSlotNum = e;
                        atn = exfoModuleSlotQMap.value(e).value<EXFO_OSICS_ATN*>();
                        atnFound = true;
                    }
                }
            }
        }
        else if(typeName == "PowerMeter"){
            // *NOTE* for now we only use the first slot on a power meter.
            powerMeterSlotNum = 1;
            QVariant powerMeterVariant = selectedDevices->at(i);
            powerMeter = powerMeterVariant.value<PowerMeter*>();
            powerMeterFound = true;
        }
    }

    qDebug() << t100Found << " " << atnFound << " " << powerMeterFound;
    bool success = (t100Found && atnFound && powerMeterFound);
    return success;
}



void EXFO_T100_ATN_Power_Test::writeTestDataToFile(QByteArray filename){
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

QByteArray EXFO_T100_ATN_Power_Test::constructOutputFilename(){

    //construct filename
    QByteArray identityInfo;
    atn->identificationModuleQuery(atnSlotNum, identityInfo);

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

void EXFO_T100_ATN_Power_Test::runDeviceTest(){
    qDebug() << "executing t100/atn/powermeter test";

    QByteArray filename = constructOutputFilename();

    // get min and max attenuation
    QByteArray minMaxAtten;
    atn->moduleAttenuationMinMaxQuery(atnSlotNum, "2", minMaxAtten);

    minMaxAtten = minMaxAtten.split('=')[1].trimmed();
    QByteArray maxAttenRaw = minMaxAtten.mid(minMaxAtten.size() / 2);
    QByteArray minAttenRaw = minMaxAtten.mid(0, minMaxAtten.size() / 2);

    double startAtn = minAttenRaw.toDouble();
    double endAtn = maxAttenRaw.toDouble();

    runTestLoop(filename, power, startWav, endWav, wavStep, startAtn, endAtn, atnStep);
}

void EXFO_T100_ATN_Power_Test::runTestLoop(QByteArray filename, double power, double startWav,
                                           double endWav, double wavStep, double startAtn,
                                           double endAtn, double atnStep){
    // add .csv header to test data
    testData.append("ATTENUATION,");
    testData.append("T100 POWER,");
    testData.append("T100 WAVELENGTH,");
    testData.append("PM WAVELENGTH,");
    testData.append("POWER METER POWER");
    testData.append("\n");

    // init ATN
    QByteArray atnToSet = QByteArray::number(startAtn);
    atn->setModuleAttenuationCmd(atnSlotNum, atnToSet);

    // enable laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // init T100 output power
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = QByteArray::number(power);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // init T100 wavelength
    QByteArray wavToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

    // init wavelength on power meter
    QByteArray unit = "nm";
    powerMeter->setWavelength(powerMeterSlotNum, wavToSet, unit);

    // wait for adjustments
    QTime timer = QTime::currentTime().addSecs(1);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    // start wavelength loop
    double currentWav = startWav;
    while(currentWav <= endWav){

        // init T100 wavelength
        QByteArray wavToSet = QByteArray::number(startWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

        // init wavelength on power meter
        QByteArray unit = "nm";
        powerMeter->setWavelength(powerMeterSlotNum, wavToSet, unit);

        // wait for adjustments
        QTime timer = QTime::currentTime().addSecs(1);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // start attenuation loop
        double currentAtten = startAtn;
        while(currentAtten <= endAtn){

            // setAttenuation
            atnToSet = QByteArray::number(currentAtten);
            atn->setModuleAttenuationCmd(atnSlotNum, atnToSet);

            // write current atteuation;
            QByteArray attenuation;
            atn->moduleAttenuationQuery(atnSlotNum, attenuation);
            testData.append(QByteArray::number(attenuation.split('=')[1].toDouble()).append(','));

            // write current output power
            QByteArray t100Power;
            t100->outputPowerModuleQuery(t100SlotNum, t100Power);
            testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));

            // write current wavelength
            QByteArray t100Wav;
            t100->refWavelengthModuleQuery(t100SlotNum, t100Wav);
            testData.append(QByteArray::number(t100Wav.split('=')[1].toDouble()).append(','));

            // write wavelength set on power meter
            QByteArray powerMeterWav;
            powerMeter->queryWavelength(powerMeterSlotNum, powerMeterWav);
            QByteArray unit = "nm";
            double convertedWav = ConversionUtilities::convertWavelengthFromMeter(powerMeterWav.toDouble(), unit);
            testData.append(QByteArray::number(convertedWav).append(','));


            // wait for adjustments
            QTime timer = QTime::currentTime().addSecs(1);
            while(QTime::currentTime() < timer){
                // do nothing
            }

            // power reading
            QByteArray powerReading;
            powerMeter->measurePower(powerMeterSlotNum, powerReading);
            // convert and write out
            double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
            testData.append(QByteArray::number(convertedPower).append(','));

            currentAtten += atnStep;
        }
        currentWav += wavStep;
    }

    // shut off laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

}

void EXFO_T100_ATN_Power_Test::setAttenuationStep(double atnStep){
    this->atnStep = atnStep;
}

void EXFO_T100_ATN_Power_Test::setPower(double power){
    this->power = power;
}

void EXFO_T100_ATN_Power_Test::setStartWavelength(double startWav){
    this->startWav = startWav;
}

void EXFO_T100_ATN_Power_Test::setEndWavelength(double endWav){
    this->endWav = endWav;
}

void EXFO_T100_ATN_Power_Test::setWavStep(double wavStep){
    this->wavStep = wavStep;
}

void EXFO_T100_ATN_Power_Test::setPowerMeterSlotNum(int slotNum){
    this->powerMeterSlotNum = slotNum;
}

