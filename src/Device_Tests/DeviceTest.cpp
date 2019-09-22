#include "DeviceTest.h"

DeviceTest::DeviceTest(QList<QVariant> &selectedDevices, QMainWindow &configWindow)
{
    this->selectedDevices = &selectedDevices;
    this->configWindow = &configWindow;
}
