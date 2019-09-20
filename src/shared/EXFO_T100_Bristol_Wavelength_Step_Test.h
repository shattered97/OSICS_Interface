#ifndef EXFO_T100_BRISTOL_WAVELENGTH_STEP_TEST_H
#define EXFO_T100_BRISTOL_WAVELENGTH_STEP_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "Bristol_428A.h"
#include "PowerMeter.h"

class EXFO_T100_Bristol_Wavelength_Step_Test : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_Bristol_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();
    void runTestLoopBristolOnly(QByteArray filename, int t100slotNum, double startWav, double endWav, double wavStep);
    void runTestLoopWithPowerMeter(QByteArray filename, int t100slotNum, int powerMeterSlotNum, double startWav, double endWav, double wavStep);


private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    Bristol_428A *bristol = nullptr;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 1;
};

#endif // EXFO_T100_BRISTOL_WAVELENGTH_STEP_TEST_H
