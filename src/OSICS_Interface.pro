#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T12:21:48
#
#-------------------------------------------------

CONFIG += static
QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSICS_Interface
TEMPLATE = app

win32: LIBS += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/visa32.lib"

INCLUDEPATH += "C:/Program Files/IVI Foundation/VISA/Win64/Include" \
                Windows \
                Device_Tests \
                Device_Config_Windows \
                shared \
                shared/Devices \
                shared/Devices/EXFO_OSICS \
                shared/Devices/Keysight_N7714A \
                shared/Devices/ANDO_AQ6331 \
                shared/Devices/Bristol_428A \
                shared/Devices/Power_Meters

DEPENDPATH += "C:/Program Files/IVI Foundation/VISA/Win64/Include"


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Device_Tests/EXFO_T100_SWT_PM_WM_Test.cpp \
        Device_Tests/WavStepWithPowerMonitoringTest.cpp \
        Device_Tests/exfo_operationaltest_t100_swt_atn.cpp \
        Device_Tests/exfo_operationaltest_t100_swt_atn_window.cpp \
        Device_Tests/exfo_t100_pm_power_step_test.cpp \
        Device_Tests/powermeterpollingworker.cpp \
        Device_Tests/snapshotgraphdialog.cpp \
        Device_Tests/wavstep_power_monitoring_file_worker.cpp \
        Device_Tests/wavstep_power_monitoring_graph_window.cpp \
        Device_Tests/wavstep_power_monitoring_test_window.cpp \
        Device_Tests/wavstep_power_monitoring_test_worker.cpp \
        main.cpp \
        mainwindow.cpp \
        Device_Config_Windows/confign7714awindow.cpp \
        Device_Config_Windows/ConfigOSICS_ATN.cpp \
        Device_Config_Windows/ConfigOSICS_SWT.cpp \
        Device_Config_Windows/ConfigOSICS_T100.cpp \
        Device_Config_Windows/configpowermeter.cpp \
        Device_Config_Windows/OSICSMainframeSetupWindow.cpp \
        Device_Tests/DeviceTest.cpp \
        Device_Tests/DeviceTestFactory.cpp \
        Device_Tests/EXFO_T100_ATN_Power_Test.cpp \
        Device_Tests/EXFO_T100_Bristol_Wavelength_Step_Test.cpp \
        Device_Tests/EXFO_T100_SWT_OSA_WavelengthTest.cpp \
        Device_Tests/OSA_Wavelength_Step_Test.cpp \
        shared/ConversionUtilities.cpp \
        shared/Logging.cpp \
        shared/Orchestrator.cpp \
        shared/VisaInterface.cpp \
        shared/WindowFactory.cpp \
        shared/Devices/DefaultInstrument.cpp \
        shared/Devices/Ando_AQ6331/Ando_AQ6331.cpp \
        shared/Devices/Bristol_428A/Bristol_428A.cpp \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_ATN.cpp \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_MAINFRAME.cpp \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_SWT.cpp \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_T100.cpp \
        shared/Devices/Keysight_N7714A/N7714A.cpp \
        shared/Devices/Power_Meters/KeysightPowerMeter.cpp \
        shared/Devices/Power_Meters/PowerMeter.cpp \
        shared/Devices/Power_Meters/PowerMeterFactory.cpp


HEADERS += \
        Device_Tests/EXFO_T100_SWT_PM_WM_Test.h \
        Device_Tests/exfo_operationaltest_t100_swt_atn.h \
        Device_Tests/exfo_operationaltest_t100_swt_atn_window.h \
        Device_Tests/exfo_t100_pm_power_step_test.h \
        Device_Tests/powermeterpollingworker.h \
        Device_Tests/snapshotgraphdialog.h \
        Device_Tests/wavstep_power_monitoring_file_worker.h \
        Device_Tests/wavstep_power_monitoring_graph_window.h \
        Device_Tests/wavstep_power_monitoring_test_window.h \
        Device_Tests/wavstep_power_monitoring_test_worker.h \
        mainwindow.h \
        Device_Config_Windows/confign7714awindow.h \
        Device_Config_Windows/ConfigOSICS_ATN.h \
        Device_Config_Windows/ConfigOSICS_SWT.h \
        Device_Config_Windows/ConfigOSICS_T100.h \
        Device_Config_Windows/configpowermeter.h \
        Device_Config_Windows/OSICSMainframeSetupWindow.h \
        Device_Tests/DeviceTest.h \
        Device_Tests/DeviceTestFactory.h \
        Device_Tests/EXFO_T100_ATN_Power_Test.h \
        Device_Tests/EXFO_T100_Bristol_Wavelength_Step_Test.h \
        Device_Tests/EXFO_T100_SWT_OSA_WavelengthTest.h \
        Device_Tests/OSA_Wavelength_Step_Test.h \
        Device_Tests/WavStepWithPowerMonitoringTest.h \
        shared/constants.h \
        shared/ConversionUtilities.h \
        shared/Logging.h \
        shared/Orchestrator.h \
        shared/VisaInterface.h \
        shared/WindowFactory.h \
        shared/Devices/DefaultInstrument.h \
        shared/Devices/Ando_AQ6331/Ando_AQ6331.h \
        shared/Devices/Bristol_428A/Bristol_428A.h \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_ATN.h \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_MAINFRAME.h \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_SWT.h \
        shared/Devices/EXFO_OSICS/EXFO_OSICS_T100.h \
        shared/Devices/Keysight_N7714A/N7714A.h \
        shared/Devices/Power_Meters/KeysightPowerMeter.h \
        shared/Devices/Power_Meters/PowerMeter.h \
        shared/Devices/Power_Meters/PowerMeterFactory.h


FORMS += \
        Device_Tests/exfo_operationaltest_t100_swt_atn_window.ui \
        Device_Tests/snapshotgraphdialog.ui \
        Device_Tests/wavstep_power_monitoring_graph_window.ui \
        Device_Tests/wavstep_power_monitoring_test_window.ui \
        mainwindow.ui \
        Device_Config_windows/confign7714awindow.ui \
        Device_Config_windows/ConfigOSICS_ATN.ui \
        Device_Config_windows/ConfigOSICS_SWT.ui \
        Device_Config_windows/ConfigOSICS_T100.ui \
        Device_Config_windows/configpowermeter.ui \
        Device_Config_windows/OSICSMainframeSetupWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    devicetestimages.qrc
