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

void EXFO_T100_ATN_Power_Test::runDeviceTest(){
    qDebug() << "executing t100/atn/powermeter test";


    // get min attenuation
    QByteArray minMaxAtten;
    atn->moduleAttenuationMinMaxQuery(atnSlotNum, "2", minMaxAtten);

    minMaxAtten = minMaxAtten.split('=')[1].trimmed();
    QByteArray maxAttenRaw = minMaxAtten.mid(minMaxAtten.size() / 2);
    QByteArray minAttenRaw = minMaxAtten.mid(0, minMaxAtten.size() / 2);

    double startAtn = minAttenRaw.toDouble();
    double endAtn = maxAttenRaw.toDouble();


//    QByteArray filename = "t100_1520_E0193000335_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1465;


//    QByteArray filename = "t100_1520_1575_E0193000335_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1575;

//    QByteArray filename = "t100_1520_1520_E0193000335_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1520;


//    QByteArray filename = "t100_1520_1575_E0193400235_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1575;

//    QByteArray filename = "t100_1520_1465_E0193400235_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1465;

//    QByteArray filename = "t100_1520_1520_E0193400235_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1520;

//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);
// ********************************************************************
//    QByteArray filename = "t100_1520_1465_E0193300135_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1465;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

//    filename = "t100_1520_1520_E0193300135_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    atnStep = 0.1;
//    power = 0;
//    wavelength = 1520;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

//    filename = "t100_1520_1575_E0193300135_ATN_RANGE_POWER_STEP_TEST_01.csv";
//    atnStep = 0.1;
//    power = 0;
//    wavelength = 1575;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

//// **********************************************************************

//    QByteArray filename = "t100_E0193500135_1465_atn_test.csv";
//    double atnStep = 0.1;
//    double power = 0;
//    double wavelength = 1465;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

//    filename = "t100_E0193500135_1520_atn_test.csv";
//    atnStep = 0.1;
//    power = 0;
//    wavelength = 1520;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

//    filename = "t100_E0193500135_1575_atn_test.csv";
//    atnStep = 0.1;
//    power = 0;
//    wavelength = 1575;
//    runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);


    // **********************************************************************

        QByteArray filename = "t100_E0193400135_1465_atn_test.csv";
        double atnStep = 0.1;
        double power = 0;
        double wavelength = 1465;
        runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

        filename = "t100_E0193400135_1520_atn_test.csv";
        atnStep = 0.1;
        power = 0;
        wavelength = 1520;
        runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);

        filename = "t100_E0193400135_1575_atn_test.csv";
        atnStep = 0.1;
        power = 0;
        wavelength = 1575;
        runTestLoop(filename, power, wavelength, startAtn, endAtn, atnStep);
}

void EXFO_T100_ATN_Power_Test::runTestLoop(QByteArray filename, double power, double wavelength,
                                           double startAtn, double endAtn, double atnStep){

    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "ATTENUATION,";
    stream << "T100 POWER,";
    stream << "T100 WAVELENGTH,";
    stream << "PM WAVELENGTH,";
    stream << "POWER METER POWER" << endl;

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
    QByteArray wavToSet = QByteArray::number(wavelength);
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
        stream << attenuation.split('=')[1].toDouble() << ",";

        // write current output power
        QByteArray t100Power;
        t100->outputPowerModuleQuery(t100SlotNum, t100Power);
        stream << t100Power.split('=')[1].toDouble() << ",";

        // write current wavelength
        QByteArray t100Wav;
        t100->refWavelengthModuleQuery(t100SlotNum, t100Wav);
        stream << t100Wav.split('=')[1].toDouble() << ",";

        // write wavelength set on power meter
        QByteArray powerMeterWav;
        powerMeter->queryWavelength(powerMeterSlotNum, powerMeterWav);
        QByteArray unit = "nm";
        double convertedWav = ConversionUtilities::convertWavelengthFromMeter(powerMeterWav.toDouble(), unit);
        stream << convertedWav << ",";

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
        stream << convertedPower << endl;

        currentAtten += atnStep;

    }

    t100->disableModuleLaserCmd(t100SlotNum);
    qDebug() << "COMPLETED";
}
