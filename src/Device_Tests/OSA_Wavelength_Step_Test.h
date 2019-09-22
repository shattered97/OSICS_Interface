#ifndef OSA_WAVELENGTH_STEP_TEST_H
#define OSA_WAVELENGTH_STEP_TEST_H

#include "DeviceTest.h"
#include "EXFO_OSICS/EXFO_OSICS_T100.h"
#include "Ando_AQ6331.h"

class OSA_Wavelength_Step_Test : public DeviceTest
{
    Q_OBJECT

public:
    OSA_Wavelength_Step_Test(QList<QVariant> &selectedDevices, QMainWindow &configWindow);
    ~OSA_Wavelength_Step_Test();

    bool areDevicesValidForTest();
    void runDeviceTest();

private:
    EXFO_OSICS_T100 *t100;
    Ando_AQ6331 *andoOSA;
};

#endif // OSA_WAVELENGTH_STEP_TEST_H
