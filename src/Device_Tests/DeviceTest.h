#ifndef DEVICETEST_H
#define DEVICETEST_H

#include <QMainWindow>
#include <QVariant>

class DeviceTest : public QObject
{
    Q_OBJECT

public:
    DeviceTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow);

    virtual bool areDevicesValidForTest() = 0;
    virtual void runDeviceTest() = 0;

    QList<QVariant> *selectedDevices;
    QMainWindow *configWindow;
};

#endif // DEVICETEST_H
