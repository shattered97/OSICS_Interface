#include "EXFO_T100_SWT_OSA_WavelengthTest.h"


EXFO_T100_SWT_OSA_WavelengthTest::EXFO_T100_SWT_OSA_WavelengthTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow) : DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_SWT_OSA_WavelengthTest::areDevicesValidForTest(){
    // we need to find the EXFO T100, SWT, and Ando OSA
    bool t100Found = false;
    bool swtFound = false;
    bool andoFound = false;

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
        else if(typeName == "Ando_AQ6331"){
            QVariant bristolVariant = selectedDevices.at(i);
            andoOSA = bristolVariant.value<Ando_AQ6331*>();
            andoFound = true;
        }
    }

    bool success = (t100Found && swtFound && andoFound);
    return success;
}

QByteArray EXFO_T100_SWT_OSA_WavelengthTest::constructOutputFilename(){
    // construct filename
    QByteArray identityInfo = swt->identificationModuleQuery(swtSlotNum);

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

void EXFO_T100_SWT_OSA_WavelengthTest::writeTestDataToFile(QByteArray filename){
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


void EXFO_T100_SWT_OSA_WavelengthTest::runDeviceTest(){

    QVariant exfoVariant = selectedDevices.at(0);
    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();

    t100 = exfo->getModuleAtSlot(t100SlotNum).value<EXFO_OSICS_T100*>();
    swt = exfo->getModuleAtSlot(swtSlotNum).value<EXFO_OSICS_SWT*>();

    QByteArray filename = constructOutputFilename();


    runTestLoop(filename, t100SlotNum, swtSlotNum, startWavelength, endWavelength, t100Power, wavelengthStepSize);

}

void EXFO_T100_SWT_OSA_WavelengthTest::runTestLoop(QByteArray filename, int t100SlotNum, int swtSlotNum, double startWav, double endWav,
                                                  double t100Power, double wavStep){
    // add .csv header
    testData.append("T100 WAVELENGTH,");
    testData.append("SWT WAVELENGTH,");
    testData.append("T100 POWER,");
    testData.append("SWT POWER");
    testData.append("\n");

    // turn on laser
    t100->enableModuleLaserCmd(t100SlotNum);

    // init laser power
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = QByteArray::number(t100Power);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // set power on swt
    swt->setModuleOutputPowerCmd(swtSlotNum, powerToSet);

    double currentWav = startWav;
    while(currentWav <= endWav){
        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // get wavelength reported by t100
        QByteArray t100Wavelength = t100->refWavelengthModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Wavelength.split('=')[1].toDouble()).append(','));

        // set wavelength on swt
        swt->setRefWavelengthModuleCmd(swtSlotNum, wavelengthToSet);

        // get wavelength reported by swt
        QByteArray swtWavelength = swt->refWavelengthModuleQuery(swtSlotNum);
        testData.append(QByteArray::number(swtWavelength.split('=')[1].toDouble()).append(','));

        // get output power of t100
        QByteArray t100Power = t100->outputPowerModuleQuery(t100SlotNum);
        testData.append(QByteArray::number(t100Power.split('=')[1].toDouble()).append(','));

        // get power of SWT
        QByteArray swtPower = swt->outputPowerModuleQuery(swtSlotNum);
        testData.append(QByteArray::number(swtPower.split('=')[1].toDouble()));

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

void EXFO_T100_SWT_OSA_WavelengthTest::setStartWavelength(double startWavelength){
    this->startWavelength = startWavelength;
}
void EXFO_T100_SWT_OSA_WavelengthTest::setEndWavelength(double endWavelength){
    this->endWavelength = endWavelength;
}
void EXFO_T100_SWT_OSA_WavelengthTest::setPower(double power){
    this->t100Power = power;
}
void EXFO_T100_SWT_OSA_WavelengthTest::setWavelengthStepSize(double stepSize){
    this->wavelengthStepSize = stepSize;
}
