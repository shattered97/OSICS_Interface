#include "DeviceTestFactory.h"



DeviceTestFactory::DeviceTestFactory(QObject *parent) : QObject(parent)
{

}

DeviceTest *DeviceTestFactory::makeDeviceTest(QString deviceTypeName, QList<QVariant> selectedDevices){

    qDebug() << "22222222222 " << QThread::currentThread();
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
    else if(deviceTypeName == EXFO_T100_ATN_POWER_TEST){
        QMainWindow *testWindow = new QMainWindow();
        EXFO_T100_ATN_Power_Test *test = new EXFO_T100_ATN_Power_Test(selectedDevices, *testWindow);
        return test;
    }
    else if(deviceTypeName == EXFO_T100_SWT_PM_WM_TEST){
        QMainWindow *testWindow = new QMainWindow();
        EXFO_T100_SWT_PM_WM_Test *test = new EXFO_T100_SWT_PM_WM_Test(selectedDevices, *testWindow);
        return test;
    }
    else if(deviceTypeName == EXFO_T100_PM_POWER_STEP_TEST){
        QMainWindow *testWindow = new QMainWindow();
        EXFO_T100_PM_Power_Step_Test *test = new  EXFO_T100_PM_Power_Step_Test(selectedDevices, *testWindow);
        return test;
    }
    else if(deviceTypeName == EXFO_OPERATIONAL_TEST_T100_SWT_ATN){
        EXFO_OperationalTest_T100_SWT_ATN_Window *testWindow = new EXFO_OperationalTest_T100_SWT_ATN_Window();
        EXFO_OperationalTest_T100_SWT_ATN *test = new EXFO_OperationalTest_T100_SWT_ATN(selectedDevices, *testWindow);
        test->setWindowConfigureable(true);
        return test;
    }
    else if(deviceTypeName == WAV_STEP_TEST_WITH_POWER_MONITORING_TEST){
        WavStep_Power_Monitoring_Test_Window *testWindow = new WavStep_Power_Monitoring_Test_Window();
        WavStepWithPowerMonitoringTest *test = new WavStepWithPowerMonitoringTest(selectedDevices, *testWindow);
        test->setWindowConfigureable(true);
        return test;
    }
    else{
        qDebug() << "device test type not recognized";
        // #TODO handle null
        return nullptr;
    }
}
