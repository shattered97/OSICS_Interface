#ifndef DEVICETESTFACTORY_H
#define DEVICETESTFACTORY_H

#include <QObject>
#include "OSA_Wavelength_Step_Test.h"
#include "EXFO_T100_SWT_OSA_WavelengthTest.h"
#include "EXFO_T100_Bristol_Wavelength_Step_Test.h"

class DeviceTestFactory : public QObject
{
    Q_OBJECT

public:
    explicit DeviceTestFactory(QObject *parent = nullptr);

    static DeviceTest *makeDeviceTest(QString deviceTestType, QList<QVariant> &selectedDevices);
};

#endif // DEVICETESTFACTORY_H
