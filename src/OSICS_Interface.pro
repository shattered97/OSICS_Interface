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
                EXFO_OSICS


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
        Worker.cpp \
        n7714awindow.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_ATN.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_MAINFRAME.cpp \
        shared/DefaultInstrument.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_SWT.cpp \
        shared/EXFO_OSICS/EXFO_OSICS_T100.cpp \
        shared/Logging.cpp \
        shared/N7714A.cpp \
        shared/VisaInterface.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Worker.h \
        n7714awindow.h \
        shared/EXFO_OSICS/EXFO_OSICS_ATN.h \
        shared/EXFO_OSICS/EXFO_OSICS_MAINFRAME.h \
        shared/DefaultInstrument.h \
        shared/EXFO_OSICS/EXFO_OSICS_SWT.h \
        shared/EXFO_OSICS/EXFO_OSICS_T100.h \
        shared/Logging.h \
        shared/N7714A.h \
        shared/VisaInterface.h \
        shared/constants.h \
        mainwindow.h

FORMS += \
        mainwindow.ui \
        n7714awindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
