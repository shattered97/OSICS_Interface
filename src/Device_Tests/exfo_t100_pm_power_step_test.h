#ifndef EXFO_T100_PM_POWER_STEP_TEST_H
#define EXFO_T100_PM_POWER_STEP_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "PowerMeter.h"

class EXFO_T100_PM_Power_Step_Test : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_PM_Power_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);


    bool areDevicesValidForTest();
    void runDeviceTest();
    void runTestLoop(QByteArray filename, double startPow, double endPow, double powStep, double wavelength);

private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 1;
};

#endif // EXFO_T100_PM_POWER_STEP_TEST_H
