#include "OSA_Wavelength_Step_Test.h"

OSA_Wavelength_Step_Test::OSA_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow) : DeviceTest (selectedDevices, configWindow)
{

}

OSA_Wavelength_Step_Test::~OSA_Wavelength_Step_Test()
{

}

bool OSA_Wavelength_Step_Test::areDevicesValidForTest(){

    //
    return true;
}

void OSA_Wavelength_Step_Test::runDeviceTest(){
    qDebug() << "in OSA_Wavelength_Step_Test runDeviceTest()";
    // assume (for now) that the device at the first index is the ando and the
    // device at the second index is the exfo mainframe
    // #TODO add a way to sort these out if they're out of order


    // *********** TESTING EXFO ************
    QVariant exfoVariant = selectedDevices->at(0);
    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();
    qDebug() << exfo->getModuleSlotQVariantMap();
    t100 = exfo->getModuleAtSlot(4).value<EXFO_OSICS_T100*>();
    t100->enableModuleLaserCmd(4);



//    QVariant andoVariant = selectedDevices->at(0);
//    qDebug() << "1";
//    andoOSA = andoVariant.value<Ando_AQ6331*>();
//    qDebug() << "2";

//    qDebug() << andoVariant.typeName();

//    QVariant exfoVariant = selectedDevices->at(1);
//    qDebug() << "3";
//    EXFO_OSICS_MAINFRAME *exfo = exfoVariant.value<EXFO_OSICS_MAINFRAME*>();
//    qDebug() << "4";

//    int slotNum = 1;

//    qDebug() << "5";



//    andoOSA->runSingleSweep();


}
