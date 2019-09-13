#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T12:21:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSICS_Interface
TEMPLATE = app

win32: LIBS += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/visa32.lib"

INCLUDEPATH += "C:/Program Files/IVI Foundation/VISA/Win64/Include" \
                Windows \
                shared \
                EXFO_OSICS \
                shared/Keysight_N7714A \
                shared/ANDO_AQ6331 \
                shared/Power_Meters

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
        ConfigOSICS_ATN.cpp \
        ConfigOSICS_SWT.cpp \
        ConfigOSICS_T100.cpp \
        OSICSMainframeSetupWindow.cpp \
        confign7714awindow.cpp \
        configpowermeter.cpp \
        defaultconfigwindow.cpp \
        devicesetupwindow.cpp \
        graphwindow.cpp \
        main.cpp \
        mainwindow.cpp \
        shared/ConversionUtilities.cpp \
        shared/DefaultInstrument.cpp \
        shared/Orchestrator.cpp \
        shared/Power_Meters/PowerMeterFactory.cpp \
        shared/VisaInterface.cpp \
        shared/Logging.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_ATN.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_MAINFRAME.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_SWT.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_T100.cpp \
        shared/Keysight_N7714A/N7714A.cpp \
        shared/Ando_AQ6331/Ando_AQ6331.cpp \
        shared/Power_Meters/KeysightPowerMeter.cpp \
        shared/Power_Meters/PowerMeter.cpp \
        shared/WindowFactory.cpp \
        testsetupwindow.cpp


HEADERS += \
        ConfigOSICS_ATN.h \
        ConfigOSICS_SWT.h \
        ConfigOSICS_T100.h \
        OSICSMainframeSetupWindow.h \
        confign7714awindow.h \
        configpowermeter.h \
        defaultconfigwindow.h \
        devicesetupwindow.h \
        graphwindow.h \
        mainwindow.h \
        shared/ConversionUtilities.h \
        shared/DefaultInstrument.h \
        shared/Orchestrator.h \
        shared/Power_Meters/PowerMeterFactory.h \
        shared/VisaInterface.h \
        shared/Logging.h \
        shared/WindowFactory.h \
        shared/constants.h \
        shared/EXFO_OSICS/EXFO_OSICS_ATN.h \
        shared/EXFO_OSICS/EXFO_OSICS_MAINFRAME.h \
        shared/EXFO_OSICS/EXFO_OSICS_SWT.h \
        shared/EXFO_OSICS/EXFO_OSICS_T100.h \
        shared/Keysight_N7714A/N7714A.h \
        shared/Ando_AQ6331/Ando_AQ6331.h \
        shared/Power_Meters/PowerMeter.h \
        shared/Power_Meters/KeysightPowerMeter.h \
        testsetupwindow.h


FORMS += \
        ConfigOSICS_ATN.ui \
        ConfigOSICS_SWT.ui \
        ConfigOSICS_T100.ui \
        OSICSMainframeSetupWindow.ui \
        confign7714awindow.ui \
        configpowermeter.ui \
        defaultconfigwindow.ui \
        devicesetupwindow.ui \
        graphwindow.ui \
        mainwindow.ui \
        testsetupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
