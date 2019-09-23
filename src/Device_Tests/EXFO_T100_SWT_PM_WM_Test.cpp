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

    bool success = (t100Found && swtFound && bristolFound && powerMeterFound);
    return success;
}

void EXFO_T100_SWT_PM_WM_Test::runDeviceTest(){

    // init switch
    swt->autoDetectT100Modules(swtSlotNum);
    QByteArray fullBandMode = "ECL";
    swt->setAPCModuleOperatingMode(swtSlotNum, fullBandMode);

// ***********************************************************************************

    QByteArray filename = "t100_1520_EO193400135_swt_ch1_wavstep_1.csv";
    double startWav = 1465;
    double endWav = 1575;
    double wavStep = 1;
    double power = 0;
    int switchNum = 1;

//    QByteArray filename = "t100_1520_EO193400135_swt_ch1_wavstep_2.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 2;

//    QByteArray filename = "t100_1520_EO193400135_swt_ch1_wavstep_3.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 3;

//    QByteArray filename = "t100_1520_EO193400135_swt_ch1_wavstep_4.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 4;

// ***********************************************************************************

//    QByteArray filename = "t100_1520_EO193300135_swt_ch1_wavstep_1.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 1;

//    QByteArray filename = "t100_1520_EO193300135_swt_ch1_wavstep_2.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 2;

//    QByteArray filename = "t100_1520_EO193300135_swt_ch1_wavstep_3.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 3;

//    QByteArray filename = "t100_1520_EO193300135_swt_ch1_wavstep_4.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 4;

// ***********************************************************************************
//    QByteArray filename = "t100_1520_EO193000335_swt_ch1_wavstep_1.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 1;

//    QByteArray filename = "t100_1520_EO193000335_swt_ch1_wavstep_2.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 2;

//    QByteArray filename = "t100_1520_EO193000335_swt_ch1_wavstep_3.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 3;

//    QByteArray filename = "t100_1520_EO193000335_swt_ch1_wavstep_4.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 4;

// ***********************************************************************************

//    QByteArray filename = "t100_1520_EO193400235_swt_ch1_wavstep_1.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 1;

//    QByteArray filename = "t100_1520_EO193400235_swt_ch1_wavstep_2.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 2;

//    QByteArray filename = "t100_1520_EO193400235_swt_ch1_wavstep_3.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 3;

//    QByteArray filename = "t100_1520_EO193400235_swt_ch1_wavstep_4.csv";
//    double startWav = 1465;
//    double endWav = 1575;
//    double wavStep = 1;
//    double power = 0;
//    int switchNum = 4;

    runTestLoop(filename, startWav, endWav, wavStep, power, switchNum);
}

void EXFO_T100_SWT_PM_WM_Test::runTestLoop(QByteArray filename, double startWav, double endWav, double wavStep, double power, int switchNum){

    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "SWITCH CHANNEL,";
    stream << "T100 POWER,";
    stream << "T100 WAVELENGTH,";
    stream << "BRISTOL WAVELENGTH,";
    stream << "POWER METER POWER" << endl;

    double currentWav = startWav;
    while(currentWav <= endWav){

        // get active switch channel
        QByteArray channel;
        swt->getChannelForSignalAPC(swtSlotNum, channel);
        stream << channel.split('=')[1].trimmed() << ",";

        // get t100 output power
        QByteArray t100Power;
        t100->outputPowerModuleQuery(t100SlotNum, t100Power);
        stream << t100Power.split('=')[1].toDouble() << ",";

        // set t100 wavelength
        QByteArray wavToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavToSet);

        // set power meter wavelength
        QByteArray wavUnit = "nm";
        powerMeter->setWavelength(powerMeterSlotNum, wavToSet, wavUnit);

        // wait for adjustments
        QTime timer = QTime::currentTime().addSecs(3);
        while(QTime::currentTime() < timer){
            // do nothing
        }

        // write current t100 wavelength
        QByteArray t100Wav;
        t100->refWavelengthModuleQuery(t100SlotNum, t100Wav);
        stream << t100Wav.split('=')[1].toDouble() << ",";

        // write wavemeter wavelength
        QByteArray bristolWav;
        bristol->measureWavelengthSingle(bristolWav);
        stream << bristolWav.trimmed() << ",";

        // write power meter reading
        QByteArray powerReading;
        powerMeter->measurePower(powerMeterSlotNum, powerReading);
        // convert and write out
        double convertedPower = ConversionUtilities::convertWattToDBm(powerReading.trimmed().toDouble());
        stream << convertedPower << endl;


        currentWav += wavStep;
    }


}
