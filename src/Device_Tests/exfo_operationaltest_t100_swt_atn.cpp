#include "exfo_operationaltest_t100_swt_atn.h"


EXFO_OperationalTest_T100_SWT_ATN::EXFO_OperationalTest_T100_SWT_ATN(QList<QVariant> &selectedDevices, QMainWindow &configWindow) :
    DeviceTest (selectedDevices, configWindow)
{
    // initialize tests
    switchTest = new EXFO_T100_SWT_PM_WM_Test(selectedDevices, configWindow);
    attenuatorTest = new EXFO_T100_ATN_Power_Test(selectedDevices, configWindow);
    t100WavTest = new EXFO_T100_Bristol_Wavelength_Step_Test(selectedDevices, configWindow);
    t100PowerTest = new EXFO_T100_PM_Power_Step_Test(selectedDevices, configWindow);

    // init directions
    initializeDirectionsTextList();
    initializeResourcePathList();

    // connect signals/slots
    QObject::connect(&configWindow, SIGNAL(signalBeginNextTestStep()), this, SLOT(slotBeginNextTestStep()));
    QObject::connect(&configWindow, SIGNAL(signalSkipTestStep()), this, SLOT(slotSkipTestStep()));
    QObject::connect(&configWindow, SIGNAL(signalGetCurrentStepDirections(QByteArray &, QByteArray &)),
                     this, SLOT(slotGetCurrentStepDirections(QByteArray &, QByteArray &)));
    QObject::connect(this, SIGNAL(signalTestingComplete()), &configWindow, SLOT(slotTestingComplete()));
    QObject::connect(t100WavTest, SIGNAL(signalSendTestProgressToGUI(double)),
                     &configWindow, SLOT(slotReceiveTestProgressInGUI(double)));
    QObject::connect(t100PowerTest, SIGNAL(signalSendTestProgressToGUI(double)),
                     &configWindow, SLOT(slotReceiveTestProgressInGUI(double)));
}

void EXFO_OperationalTest_T100_SWT_ATN::initializeResourcePathList(){
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_POWER_STEP_TEST.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_WAVELENGTH_STEP_TEST.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_ATTENUATION_STEP_TEST.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_SWITCH_POWER_TEST_CH1.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_SWITCH_POWER_TEST_CH2.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_SWITCH_POWER_TEST_CH3.PNG");
    resourcePathList.append(":/img/img/EXFO_DRAWING_OPTEST1_SETUP_T100_SWITCH_POWER_TEST_CH4.PNG");
}

void EXFO_OperationalTest_T100_SWT_ATN::initializeDirectionsTextList(){
    QByteArray powerStepTestDirections = "T100 Power Step Test\n 1. Connect T100 output to Power Meter.";
    directionsTextList.append(powerStepTestDirections);

    QByteArray wavelengthTestDirections = "T100 Wavelength Step Test\n 1. Connect T100 output to Bristol Wavelength meter.";
    directionsTextList.append(wavelengthTestDirections);

    QByteArray attenuationTestDirections = "T100 / ATN Power Step Test\n 1. Connect T100 output to ATN input.\n 2. Connect "
                                           " ATN output to Power Meter.";
    directionsTextList.append(attenuationTestDirections);

    QByteArray swtTestChannel1Directions = "T100 / SWT Power Step Test\n Connect T100 output to SWT Channel 1.\n 2. Connect "
                                           "SWT output to Power Meter.";
    directionsTextList.append(swtTestChannel1Directions);

    QByteArray swtTestChannel2Directions = "T100 / SWT Power Step Test\n Connect T100 output to SWT Channel 2.\n 2. Connect "
                                           "SWT output to Power Meter.";
    directionsTextList.append(swtTestChannel2Directions);

    QByteArray swtTestChannel3Directions = "T100 / SWT Power Step Test\n Connect T100 output to SWT Channel 3.\n 2. Connect "
                                           "SWT output to Power Meter.";
    directionsTextList.append(swtTestChannel3Directions);

    QByteArray swtTestChannel4Directions = "T100 / SWT Power Step Test\n Connect T100 output to SWT Channel 4.\n 2. Connect "
                                           "SWT output to Power Meter.";
    directionsTextList.append(swtTestChannel4Directions);
}

bool EXFO_OperationalTest_T100_SWT_ATN::areDevicesValidForTest(){
    // check the device validity for each test
    return(switchTest->areDevicesValidForTest() && attenuatorTest->areDevicesValidForTest()&&
           t100WavTest->areDevicesValidForTest() && t100PowerTest->areDevicesValidForTest());
}

void EXFO_OperationalTest_T100_SWT_ATN::slotSkipTestStep(){
    qDebug() << "in slotSkipTestStep()";
    if(swtTestComplete){
        qDebug() << "returning signal that testing is complete";
         emit signalTestingComplete();
    }

    if(!powerStepTestComplete){
        powerStepTestComplete = true;
    }
    else if(!wavelengthStepTestComplete){
        wavelengthStepTestComplete = true;
    }
    else if(!attenuationTestComplete){
        attenuationTestComplete = true;
    }
    else if(!swtTestComplete){
        qDebug() << " skipping switch test";
        numSwitchTestsCompleted++;
        if(numSwitchTestsCompleted == EXFO_OSICS_SWT_NUM_CHANNELS){
            swtTestComplete = true;

        }
    }

    if(!swtTestComplete){
        directionsListIndex ++;
        qDebug() << "next direction: " << directionsTextList[directionsListIndex];
    }

}

void  EXFO_OperationalTest_T100_SWT_ATN::runDeviceTest(){

    if(swtTestComplete){
        qDebug() << "returning signal that testing is complete";
         emit signalTestingComplete();
    }
    // 1. power step test
    // 2. wavelength step test
    // 3. atn test
    // 4. swt test
    //      channel 1
    //      channel 2
    //      channel 3
    //      channel 4

    if(!powerStepTestComplete){
        runPowerStepTest();
    }
    else if(!wavelengthStepTestComplete){
        runWavelengthStepTest();
    }
    else if(!attenuationTestComplete){
        runAttenuationTest();
    }
    else if(!swtTestComplete){
        runSwitchTest();
    }

    if(!swtTestComplete){
        directionsListIndex ++;
        qDebug() << "next direction: " << directionsTextList[directionsListIndex];
    }

}

void EXFO_OperationalTest_T100_SWT_ATN::slotGetCurrentStepDirections(QByteArray &resourcePath, QByteArray &directions){

    directions = directionsTextList[directionsListIndex];
    qDebug() << directionsListIndex;
    resourcePath = resourcePathList[directionsListIndex];

}

void EXFO_OperationalTest_T100_SWT_ATN::runPowerStepTest(){

    // run it
    t100PowerTest->setPowerMeterSlotNum(3);
    t100PowerTest->runDeviceTest();
    powerStepTestComplete = true;
}

void EXFO_OperationalTest_T100_SWT_ATN::runWavelengthStepTest(){

    // run it
    t100WavTest->runDeviceTest();
    wavelengthStepTestComplete = true;
}

void EXFO_OperationalTest_T100_SWT_ATN::runAttenuationTest(){

    // run it
    attenuatorTest->setPowerMeterSlotNum(3);
    attenuatorTest->runDeviceTest();
    attenuationTestComplete = true;
}

void EXFO_OperationalTest_T100_SWT_ATN::runSwitchTest(){
    // set switch channel num
    switchTest->setActiveChannel(numSwitchTestsCompleted + 1);

    // run it
    switchTest->setPowerMeterSlotNum(3);
    switchTest->runDeviceTest();

    // increment num tests completed
    numSwitchTestsCompleted++;

    // if four tests have been completed (number of switch modules), we are done
    if(numSwitchTestsCompleted == EXFO_OSICS_SWT_NUM_CHANNELS){
        swtTestComplete = true;
    }
}

void EXFO_OperationalTest_T100_SWT_ATN::slotBeginNextTestStep(){
    qDebug() << "slotBeginNextTestStep()";
    runDeviceTest();
}
