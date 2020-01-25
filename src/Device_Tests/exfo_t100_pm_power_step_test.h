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

    void setStartPower(double startPower);
    void setEndPower(double endPower);
    void setPowerStep(double powerStep);
    void setWavelength(double wavelength);
    void setPowerMeterSlotNum(int slotNum);
    void calculateNumberOfSteps();
    double calculateProgress();

signals:
    void signalSendTestProgressToGUI(double progressPercent);

private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 3;

    double startPower = 0;
    double endPower = 10;
    double powerStep = 0.2; // change back to 0.02
    double wavelength = 1520;

    int numberOfSteps = 1;
    int currentStep = 1;

    QByteArray constructOutputFilename();
    void writeTestDataToFile(QByteArray filename);
    QList<QString> testData;
};

#endif // EXFO_T100_PM_POWER_STEP_TEST_H
