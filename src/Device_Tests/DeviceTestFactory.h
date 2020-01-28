#ifndef DEVICETESTFACTORY_H
#define DEVICETESTFACTORY_H

#include <QObject>
#include "OSA_Wav_Step_Test/OSA_Wavelength_Step_Test.h"
#include "EXFO_T100_ATN_Power_Test/EXFO_T100_ATN_Power_Test.h"
#include "EXFO_T100_Bristol_Wav_Step_Test/EXFO_T100_Bristol_Wavelength_Step_Test.h"
#include "EXFO_T100_SWT_Power_Wav_Test/EXFO_T100_SWT_PM_WM_Test.h"
#include "EXFO_T100_PM_Power_Step_Test/exfo_t100_pm_power_step_test.h"
#include "OSA_Wav_Step_Test_With_SWT/EXFO_T100_SWT_OSA_WavelengthTest.h"
#include "EXFO_Operational_Test/exfo_operationaltest_t100_swt_atn.h"
#include "EXFO_Operational_Test/exfo_operationaltest_t100_swt_atn_window.h"
#include "Wav_Step_Test_With_Power_Monitoring_Graphing/WavStepWithPowerMonitoringTest.h"
#include "Wav_Step_Test_With_Power_Monitoring_Graphing/wavstep_power_monitoring_test_window.h"
#include "EXFO_T100_PM_Power_Step_Test/EXFO_T100_PM_Power_Step_Test_Window.h"


class DeviceTestFactory : public QObject
{
    Q_OBJECT

public:
    explicit DeviceTestFactory(QObject *parent = nullptr);

public slots:
    DeviceTest *makeDeviceTest(QString deviceTestType, QList<QVariant> selectedDevices);
};

#endif // DEVICETESTFACTORY_H
