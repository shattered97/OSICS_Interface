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

    QByteArray filename = "t100_1520_atn_power_test_full_range_wav_5_atn_05.csv";
    double startWav = 1465;
    double endWav = 1575;
    double wavStep = 5;

    double startAtn = 1.0;
    double endAtn = 60.0;
    double atnStep = 0.5;

    double startLaserPower = 0;
    double endLaserPower = 0;
    double powerStep = 1;

    runTestLoop(filename, startLaserPower, endLaserPower, powerStep,
                startWav, endWav, wavStep,
                startAtn, endAtn, atnStep);
}

void EXFO_T100_ATN_Power_Test::runTestLoop(QByteArray filename, double startPower, double endPower, double powerStep,
                                           double startWav, double endWav, double wavStep,
                                           double startAtn, double endAtn, double atnStep){

    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 POWER,";
    stream << "ATTENUATION";
    stream << "T100 WAVELENGTH,";
    stream << "POWER METER POWER" << endl;

    // init ATN
    QByteArray atnToSet = QByteArray::number(startAtn);
    atn->setModuleAttenuationCmd(atnSlotNum, atnToSet);

    // init T100 output power
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = QByteArray::number(startPower);
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    // init T100 wavelength
    QByteArray wavToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

    // loop through t100 power values
    double currentPower = startPower;
    while(currentPower <= endPower){

        // set power
        powerToSet = QByteArray::number(currentPower);
        t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);


        // start wavelength loop
        double currentWav = startWav;
        while(currentWav <= endWav){
            wavToSet = QByteArray::number(currentWav);
            t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

            // start attenuation loop
            double currentAtten = startAtn;
            while(currentAtten <= startAtn){

                // setAttenuation
                atnToSet = QByteArray::number(currentAtten);
                atn->setModuleAttenuationCmd(atnSlotNum, atnToSet);

                // wait for adjustments
                QTime timer = QTime::currentTime().addSecs(2);
                while(QTime::currentTime() < timer){
                    // do nothing
                }

                // write current output power
                QByteArray t100Power;
                t100->outputPowerModuleQuery(t100SlotNum, t100Power);
                stream << t100Power.split('=')[1].toDouble() << ",";

                // write current atteuation;
                QByteArray attenuation;
                atn->moduleAttenuationQuery(atnSlotNum, attenuation);
                stream << attenuation.split('=')[1].toDouble() << ",";

                // write current wavelength
                QByteArray t100Wav;
                t100->refWavelengthModuleQuery(t100SlotNum, t100Wav);
                stream << t100Wav.split('=')[1].toDouble() << ",";

                // power reading
                QByteArray powerReading;
                powerMeter->measurePower(powerMeterSlotNum, powerReading);
                // convert and write out
                double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
                stream << convertedPower << endl;

                currentAtten += atnStep;
            }
            currentWav += wavStep;
        }
        currentPower += powerStep;
    }
}
