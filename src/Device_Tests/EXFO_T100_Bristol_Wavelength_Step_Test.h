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
    void runTestLoopBristolOnly(QByteArray filename, double startWav, double endWav, double wavStep);
    void runTestLoopWithPowerMeter(QByteArray filename, double startWav, double endWav, double wavStep);

    void setStartWavelength(double startWav);
    void setEndWavelength(double endWav);
    void setWavelengthStep(double wavStep);
    void setPowerMeterSlotNum(int slotNum);

private:
    EXFO_OSICS_T100 *t100 = nullptr;
    int t100SlotNum = 1;

    Bristol_428A *bristol = nullptr;

    PowerMeter *powerMeter = nullptr;
    int powerMeterSlotNum = 3;

    double startWav = 1465;
    double endWav = 1575;
    double wavStep = 0.1;

    QByteArray constructOutputFilename();
    void writeTestDataToFile(QByteArray filename);
    QList<QString> testData;
};

#endif // EXFO_T100_BRISTOL_WAVELENGTH_STEP_TEST_H
