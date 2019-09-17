#include "DeviceTestFactory.h"



DeviceTestFactory::DeviceTestFactory(QObject *parent) : QObject(parent)
{

}

DeviceTest *DeviceTestFactory::makeDeviceTest(QString deviceTypeName, QList<QVariant> &selectedDevices){
    qDebug() << deviceTypeName;
    if(deviceTypeName == EXFO_T100_ANDO_OSA_WAV_CYCLE_TEST){
        qDebug() << "device type was exfo_t100_and0_osa";
        QMainWindow *testWindow = new QMainWindow();
        OSA_Wavelength_Step_Test *test = new OSA_Wavelength_Step_Test(selectedDevices, *testWindow);
        return test;
    }
    else if(deviceTypeName == EXFO_T100_SWT_WAV_STEP_OSA_POWER_TEST){
        QMainWindow *testWindow = new QMainWindow();
        EXFO_T100_SWT_OSA_WavelengthTest *test = new EXFO_T100_SWT_OSA_WavelengthTest(selectedDevices, *testWindow);
        return test;
    }
    else if(deviceTypeName == EXFO_T100_BRISTOL_WAV_STEP_TEST){
        QMainWindow *testWindow = new QMainWindow();
        EXFO_T100_Bristol_Wavelength_Step_Test *test = new EXFO_T100_Bristol_Wavelength_Step_Test(selectedDevices, *testWindow);
        return test;
    }
    else{
        qDebug() << "device test type not recognized";
        // #TODO handle null
        return nullptr;
    }
}
