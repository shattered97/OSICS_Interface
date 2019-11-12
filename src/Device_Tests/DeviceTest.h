#ifndef DEVICETEST_H
#define DEVICETEST_H

#include <QMainWindow>
#include <QVariant>

class DeviceTest : public QObject
{
    Q_OBJECT

public:
    DeviceTest(QList<QVariant> selectedDevices, QMainWindow &configWindow);

    virtual bool areDevicesValidForTest() = 0;
    virtual void runDeviceTest() = 0;

    QList<QVariant> selectedDevices;
    QMainWindow *configWindow;

    void setWindowConfigureable(bool status);
    bool isWindowConfigureable();

public slots:
    void slotShowConfigWindow();

private:
    bool windowConfigureable = false;



};

#endif // DEVICETEST_H
