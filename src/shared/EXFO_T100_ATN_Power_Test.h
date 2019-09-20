#ifndef EXFO_T100_ATN_POWER_TEST_H
#define EXFO_T100_ATN_POWER_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_ATN.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "PowerMeter.h"

class EXFO_T100_ATN_Power_Test : public DeviceTest
{
    Q_OBJECT

public:
    EXFO_T100_ATN_Power_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();
    void runTestLoop(QByteArray filename, double startPower, double endPower, double powerStep,
                     double startWav, double endWav, double wavStep,
                     double startAtn, double endAtn, double atnStep);

private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    EXFO_OSICS_ATN *atn = nullptr;
    int atnSlotNum = 1;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 1;
};

#endif // EXFO_T100_ATN_POWER_TEST_H
