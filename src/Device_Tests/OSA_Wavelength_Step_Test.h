#ifndef OSA_WAVELENGTH_STEP_TEST_H
#define OSA_WAVELENGTH_STEP_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "Ando_AQ6331.h"
#include <QDateTime>

class OSA_Wavelength_Step_Test : public DeviceTest
{
    Q_OBJECT

public:
    OSA_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);
    ~OSA_Wavelength_Step_Test();

    bool areDevicesValidForTest();
    void runDeviceTest();

    void setStartWavelength(double startWav);
    void setEndWavelength(double endWav);
    void setWavelengthStep(double stepSize);
    void setSpan(double span);
    void setPower(double power);

private:
    EXFO_OSICS_T100 *t100;
    int t100SlotNum = 1;

    Ando_AQ6331 *andoOSA;

    QByteArray constructOutputFilename();
    void writeTestDataToFile(QByteArray filename);
    QList<QString> testData;

    double startWav = 1465;
    double endWav = 1575;
    double wavStep = 0.1;
    double span = 3;
    double power = 0;


    void runTestLoop(QByteArray filename, double startWav, double endWav, double wavStep, double span, double power);
};

#endif // OSA_WAVELENGTH_STEP_TEST_H
