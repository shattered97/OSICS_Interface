#ifndef EXFO_T100_SWT_OSA_WAVELENGTHTEST_H
#define EXFO_T100_SWT_OSA_WAVELENGTHTEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "EXFO_OSICS/EXFO_OSICS_SWT.h"
#include "Ando_AQ6331.h"
#include <QDateTime>

class EXFO_T100_SWT_OSA_WavelengthTest : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_SWT_OSA_WavelengthTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();

    void runTestLoop(QByteArray filename, int t100SlotNum, int swtSlotNum,
                     double startWav, double endWav, double t100Power, double wavStep);

    void setStartWavelength(double startWavelength);
    void setEndWavelength(double endWavelength);
    void setPower(double power);
    void setWavelengthStepSize(double stepSize);

private:
    EXFO_OSICS_T100 *t100;
    int t100SlotNum = 1;

    EXFO_OSICS_SWT *swt;
    int swtSlotNum = 1;

    Ando_AQ6331 *andoOSA;

    double startWavelength = 1465;
    double endWavelength = 1575;
    double t100Power = 3;
    double wavelengthStepSize = 1;

    QByteArray constructOutputFilename();
    void writeTestDataToFile(QByteArray filename);
    QList<QString> testData;
};

#endif // EXFO_T100_SWT_OSA_WAVELENGTHTEST_H
