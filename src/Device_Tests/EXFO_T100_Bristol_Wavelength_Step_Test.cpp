#include "EXFO_T100_Bristol_Wavelength_Step_Test.h"
#include <QTime>
EXFO_T100_Bristol_Wavelength_Step_Test::EXFO_T100_Bristol_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_Bristol_Wavelength_Step_Test::areDevicesValidForTest(){
    // we need to find the EXFO T100, Bristol, and optionally a PowerMeter.
    bool t100Found = false;
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

    bool success = (t100Found && bristolFound);
    return success;

}

void EXFO_T100_Bristol_Wavelength_Step_Test::runDeviceTest(){
    qDebug() << "executing t100/bristol test";

    QByteArray filename = "t100_1520_EO193300135_WAVSTEP_BRISTOL_1500_1575_SPLITTER_4_1.csv";
    double startWav = 1500;
    double endWav = 1575;
    double wavStep = 1;

    if(powerMeter != nullptr){
        runTestLoopWithPowerMeter(filename, t100SlotNum, powerMeterSlotNum, startWav, endWav, wavStep);
    }
    else{
        runTestLoopBristolOnly(filename, t100SlotNum, startWav, endWav, wavStep);
    }
}

void EXFO_T100_Bristol_Wavelength_Step_Test::runTestLoopWithPowerMeter(QByteArray filename, int t100SlotNum, int powerMeterSlotNum, double startWav, double endWav, double wavStep){
    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 WAVELENGTH,";
    stream << "T100 POWER,";
    stream << "BRISTOL WAVELENGTH,";
    stream << "BRISTOL POWER,";
    stream << "POWER METER POWER" << endl;

    //set starting wavelength
    QByteArray wavelengthToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set power values
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = ("0");
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    double currentWav = startWav;
    while(currentWav <= endWav){
        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // wait for wavelength to adjust
        QTime timer = QTime::currentTime().addSecs(4);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // get wavelength reported by t100
        QByteArray t100Wavelength;
        t100->refWavelengthModuleQuery(t100SlotNum, t100Wavelength);
        stream << t100Wavelength.split('=')[1].toDouble() << ",";

        // get output power of t100
        QByteArray t100Power;
        t100->outputPowerModuleQuery(t100SlotNum, t100Power);
        stream << t100Power.split('=')[1].toDouble() << ",";

        // get wavelength reported by wavemeter
        QByteArray bristolWavelength;
        bristol->measureWavelengthSingle(bristolWavelength);
        stream << bristolWavelength.trimmed() << ",";

        // get power reported by wavemeter
        QByteArray bristolPower;
        bristol->measurePowerSingle(bristolPower);
        stream << bristolPower.trimmed() << ",";

        // get power reported by powerMeter
        QByteArray powerMeterReading;
        powerMeter->measurePower(powerMeterSlotNum, powerMeterReading);
        stream << powerMeterReading.trimmed() << endl;

        currentWav += wavStep;
    }
}


void EXFO_T100_Bristol_Wavelength_Step_Test::runTestLoopBristolOnly(QByteArray filename, int t100SlotNum, double startWav, double endWav, double wavStep)
{
    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 WAVELENGTH,";
    stream << "T100 POWER,";
    stream << "BRISTOL WAVELENGTH,";
    stream << "BRISTOL POWER" << endl;

    //set starting wavelength
    QByteArray wavelengthToSet = QByteArray::number(startWav);
    t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

    // set power values
    t100->setModulePowerUnitDBmCmd(t100SlotNum);
    QByteArray powerToSet = ("0");
    t100->setModuleOutputPowerCmd(t100SlotNum, powerToSet);

    double currentWav = startWav;
    while(currentWav <= endWav){
        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // wait for wavelength to adjust
        QTime timer = QTime::currentTime().addSecs(4);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // get wavelength reported by t100
        QByteArray t100Wavelength;
        t100->refWavelengthModuleQuery(t100SlotNum, t100Wavelength);
        stream << t100Wavelength.split('=')[1].toDouble() << ",";

        // get output power of t100
        QByteArray t100Power;
        t100->outputPowerModuleQuery(t100SlotNum, t100Power);
        stream << t100Power.split('=')[1].toDouble() << ",";

        // get wavelength reported by wavemeter
        QByteArray bristolWavelength;
        bristol->measureWavelengthSingle(bristolWavelength);
        stream << bristolWavelength.trimmed() << ",";

        // get power reported by wavemeter
        QByteArray bristolPower;
        bristol->measurePowerSingle(bristolPower);
        stream << bristolPower.trimmed() << endl;

        currentWav += wavStep;
    }
}
