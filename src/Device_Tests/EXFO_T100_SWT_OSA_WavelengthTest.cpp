#include "EXFO_T100_SWT_OSA_WavelengthTest.h"

EXFO_T100_SWT_OSA_WavelengthTest::EXFO_T100_SWT_OSA_WavelengthTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow) : DeviceTest (selectedDevices, configWindow)
{

}

bool EXFO_T100_SWT_OSA_WavelengthTest::areDevicesValidForTest(){
    return true;
}

void EXFO_T100_SWT_OSA_WavelengthTest::runDeviceTest(){
    QVariant exfoVariant = selectedDevices->at(0);
    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();

    // #TODO programatically find t100
    // #TODO programatically find swt

    int t100SlotNum = 4;
    int swtSlotNum = 1;

    t100 = exfo->getModuleAtSlot(t100SlotNum).value<EXFO_OSICS_T100*>();
    swt = exfo->getModuleAtSlot(swtSlotNum).value<EXFO_OSICS_SWT*>();

    QByteArray filename = "T100_SWT_POWER_STABILITY_1465_1575_1.csv";
    double startWavelength = 1465;
    double endWavelength = 1575;
    double t100Power = 3;
    double wavelengthStepSize = 1;

    runTestLoop(filename, t100SlotNum, swtSlotNum, startWavelength, endWavelength, t100Power, wavelengthStepSize);

    qDebug() << "========================= COMPLETE ============================";
}

void EXFO_T100_SWT_OSA_WavelengthTest::runTestLoop(QByteArray filename, int t100SlotNum, int swtSlotNum, double startWav, double endWav,
                                                   double t100Power, double wavStep){
    // init output file
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "T100 WAVELENGTH,";
    stream << "SWT WAVELENGTH,";
    stream << "T100 POWER,";
    stream << "SWT POWER" << endl;


    double currentWav = startWav;
    while(currentWav <= endWav){
        // set wavelength on t100
        QByteArray wavelengthToSet = QByteArray::number(currentWav);
        t100->setRefWavelengthModuleCmd(t100SlotNum, wavelengthToSet);

        // get wavelength reported by t100
        QByteArray t100Wavelength;
        t100->refWavelengthModuleQuery(t100SlotNum, t100Wavelength);
        stream << t100Wavelength.split('=')[1].toDouble() << ",";

        // set wavelength on swt
        swt->setRefWavelengthModuleCmd(swtSlotNum, wavelengthToSet);

        // get wavelength reported by swt
        QByteArray swtWavelength;
        swt->refWavelengthModuleQuery(swtSlotNum, swtWavelength);
        stream << swtWavelength.split('=')[1].toDouble() << ",";

        // get output power of t100
        QByteArray t100Power;
        t100->outputPowerModuleQuery(t100SlotNum, t100Power);
        stream << t100Power.split('=')[1].toDouble() << ",";

        // get power of SWT
        QByteArray swtPower;
        swt->outputPowerModuleQuery(swtSlotNum, swtPower);
        stream << swtPower.split('=')[1].toDouble() << endl;

        currentWav += wavStep;
    }

}
