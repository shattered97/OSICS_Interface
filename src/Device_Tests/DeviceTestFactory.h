#ifndef DEVICETESTFACTORY_H
#define DEVICETESTFACTORY_H

#include <QObject>
#include "OSA_Wavelength_Step_Test.h"
#include "EXFO_T100_SWT_OSA_WavelengthTest.h"
#include "EXFO_T100_Bristol_Wavelength_Step_Test.h"
#include "EXFO_T100_ATN_Power_Test.h"
#include "EXFO_T100_SWT_PM_WM_Test.h"
#include "exfo_t100_pm_power_step_test.h"
#include "exfo_operationaltest_t100_swt_atn.h"
#include "exfo_operationaltest_t100_swt_atn_window.h"
#include "WavStepWithPowerMonitoringTest.h"
#include "wavstep_power_monitoring_test_window.h"

class DeviceTestFactory : public QObject
{
    Q_OBJECT

public:
    explicit DeviceTestFactory(QObject *parent = nullptr);

public slots:
    DeviceTest *makeDeviceTest(QString deviceTestType, QList<QVariant> selectedDevices);
};

#endif // DEVICETESTFACTORY_H
