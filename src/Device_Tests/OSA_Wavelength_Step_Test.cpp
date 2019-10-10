#include "OSA_Wavelength_Step_Test.h"

OSA_Wavelength_Step_Test::OSA_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) : DeviceTest (selectedDevices, configWindow)
{

}

OSA_Wavelength_Step_Test::~OSA_Wavelength_Step_Test()
{

}

bool OSA_Wavelength_Step_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100 and Ando OSA
    bool t100Found = false;
    bool andoFound = false;

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
            }
        }
        else if(typeName == "Ando_AQ6331"){
            QVariant bristolVariant = selectedDevices->at(i);
            andoOSA = bristolVariant.value<Ando_AQ6331*>();
            andoFound = true;
        }
    }

    bool success = (t100Found && andoFound);
    return success;
}

QByteArray OSA_Wavelength_Step_Test::constructOutputFilename(){
    // construct filename
    QByteArray identityInfo = t100->identificationModuleQuery(t100SlotNum);

    // the serial number is the third item when comma-separated, the module type is the second item
    QByteArray serialNumber = identityInfo.split(',')[2];
    QByteArray moduleType = identityInfo.split(',')[1];
    QByteArray testName = "OSA_wavelength_step";
    QByteArray timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss").toLatin1();

    QStringList filenameElements = {serialNumber, moduleType, testName, timestamp};
    QByteArray filename = filenameElements.join('_').toLatin1();
    QByteArray extension = ".csv";
    filename.append(extension);

    return filename;
}

void OSA_Wavelength_Step_Test::writeTestDataToFile(QByteArray filename){
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

void OSA_Wavelength_Step_Test::runDeviceTest(){
    qDebug() << "in OSA_Wavelength_Step_Test runDeviceTest()";

    QByteArray filename = constructOutputFilename();

    runTestLoop(filename, startWav, endWav, wavStep, span, power);

}

void OSA_Wavelength_Step_Test::runTestLoop(QByteArray filename, double startWav, double endWav,
                                           double wavStep, double span, double power){

    // init .csv header
    testData.append("T100 Wavelength,");
    testData.append("OSA Wavelength,");
    testData.append("OSA Power Level");
    testData.append("\n");

    t100->enableModuleLaserCmd(t100SlotNum);

    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = QByteArray::number(power);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    QByteArray startWavString = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, startWavString);

    // wait for wav adjustment
    QTime timer = QTime::currentTime().addSecs(2);
    while(QTime::currentTime() < timer){
        // do nothing
    }

    double currentWavelength = startWav;
    while(currentWavelength <= endWav){

        // set current wavelength on exfo
        QByteArray currentWavString = QByteArray::number(currentWavelength);
        t100->setRefWavelengthModuleCmd(t100SlotNum, currentWavString);
        testData.append(currentWavString.append(','));

        // wait for wav adjustment
        QTime timer = QTime::currentTime().addSecs(2);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // set OSA values
        andoOSA->setCenterWavelength(currentWavString);
        QByteArray spanToSet = QByteArray::number(span);
        andoOSA->setSpan(spanToSet);
        andoOSA->runSingleSweep();

        // wait for sweep
        QTime sweepTimer = QTime::currentTime().addSecs(2);
        while(QTime::currentTime() < sweepTimer){
            // do nothing
        }

        QByteArray peakWav;
        QByteArray peakPower;
        andoOSA->getPeakDataFromTrace(peakWav, peakPower);
        testData.append(peakWav.append(','));
        testData.append(peakPower);

        // end data line
        testData.append("\n");
        currentWavelength += wavStep;
    }

    // shut off laser
    t100->disableModuleLaserCmd(t100SlotNum);

    // write file contents
    writeTestDataToFile(filename);

    qDebug() << "================================= COMPLETE ===================================";

}

void OSA_Wavelength_Step_Test::setStartWavelength(double startWav){
    this->startWav = startWav;
}
void OSA_Wavelength_Step_Test::setEndWavelength(double endWav){
    this->endWav = endWav;
}
void OSA_Wavelength_Step_Test::setWavelengthStep(double stepSize){
    this-> wavStep = stepSize;
}
void OSA_Wavelength_Step_Test::setSpan(double span){
    this->span = span;
}
void OSA_Wavelength_Step_Test::setPower(double power){
    this->power = power;
}
