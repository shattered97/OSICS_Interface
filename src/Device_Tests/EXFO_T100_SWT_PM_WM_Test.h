#ifndef EXFO_T100_SWT_PM_WM_TEST_H
#define EXFO_T100_SWT_PM_WM_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "EXFO_OSICS/EXFO_OSICS_SWT.h"
#include "Bristol_428A.h"
#include "PowerMeter.h"

#include <QTime>

class EXFO_T100_SWT_PM_WM_Test : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_SWT_PM_WM_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();
    void runTestLoop(QByteArray filename, double startWav, double endWav, double wavStep, double power, int switchNum);


private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    EXFO_OSICS_SWT *swt = nullptr;
    int swtSlotNum = 1;

    Bristol_428A *bristol = nullptr;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 1;

};

#endif // EXFO_T100_SWT_PM_WM_TEST_H
