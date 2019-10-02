#ifndef EXFO_OPERATIONALTEST_T100_SWT_ATN_H
#define EXFO_OPERATIONALTEST_T100_SWT_ATN_H

#include "DeviceTest.h"
#include "EXFO_T100_SWT_PM_WM_Test.h"
#include "EXFO_T100_ATN_Power_Test.h"
#include "exfo_t100_pm_power_step_test.h"
#include "EXFO_T100_Bristol_Wavelength_Step_Test.h"
#include "constants.h"

class EXFO_OperationalTest_T100_SWT_ATN : public DeviceTest
{
    Q_OBJECT

public:
    EXFO_OperationalTest_T100_SWT_ATN(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();

signals:
    void signalTestingComplete();
public slots:
    void slotBeginNextTestStep();
    void slotGetCurrentStepDirections(QByteArray &resourcePath, QByteArray &directions);

private:
    EXFO_T100_SWT_PM_WM_Test *switchTest;
    EXFO_T100_ATN_Power_Test *attenuatorTest;
    EXFO_T100_Bristol_Wavelength_Step_Test *t100WavTest;
    EXFO_T100_PM_Power_Step_Test *t100PowerTest;

    bool powerStepTestComplete = false;
    bool wavelengthStepTestComplete = false;
    bool attenuationTestComplete = false;
    bool swtTestComplete = false;

    int numSwitchTestsCompleted = 0;

    QList<QByteArray> directionsTextList;
    QList<QByteArray> resourcePathList;
    int directionsListIndex = 0;


    void initializeDirectionsTextList();
    void initializeResourcePathList();

    void runPowerStepTest();
    void runWavelengthStepTest();
    void runAttenuationTest();
    void runSwitchTest();
};

#endif // EXFO_OPERATIONALTEST_T100_SWT_ATN_H
