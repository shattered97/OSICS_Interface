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
    void runTestLoopWithWavemeter(QByteArray filename, double startWav, double endWav, double wavStep, double power);
    void runTestLoopPowerMeterOnly(QByteArray filename, double startWav, double endWav, double wavStep, double power);

    void setStartWavelength(double startWav);
    void setEndWavelength(double endWav);
    void setWavelengthStep(double stepSize);
    void setPower(double power);
    void setPowerMeterSlotNum(int slotNum);
    void setActiveChannel(int channelNum);

private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    EXFO_OSICS_SWT *swt = nullptr;
    int swtSlotNum = 1;
    int activeChannel = 1;

    Bristol_428A *bristol = nullptr;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 3;

    double startWav = 1465;
    double endWav = 1575;
    double wavStep = 1; // change back to 1
    double power = 0;

    QByteArray constructOutputFilename();
    void writeTestDataToFile(QByteArray filename);
    QList<QString> testData;


};

#endif // EXFO_T100_SWT_PM_WM_TEST_H
