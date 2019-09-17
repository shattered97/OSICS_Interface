#ifndef EXFO_T100_SWT_OSA_WAVELENGTHTEST_H
#define EXFO_T100_SWT_OSA_WAVELENGTHTEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "EXFO_OSICS/EXFO_OSICS_SWT.h"
#include "Ando_AQ6331.h"

class EXFO_T100_SWT_OSA_WavelengthTest : public DeviceTest
{
    Q_OBJECT
public:
    EXFO_T100_SWT_OSA_WavelengthTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    bool areDevicesValidForTest();
    void runDeviceTest();

    void runTestLoop(QByteArray filename, int t100SlotNum, int swtSlotNum,
                     double startWav, double endWav, double t100Power, double wavStep);

private:
    EXFO_OSICS_T100 *t100;
    EXFO_OSICS_SWT *swt;
    Ando_AQ6331 *andoOSA;
};

#endif // EXFO_T100_SWT_OSA_WAVELENGTHTEST_H
