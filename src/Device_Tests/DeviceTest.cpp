#include "DeviceTest.h"

DeviceTest::DeviceTest(QList<QVariant> selectedDevices, QMainWindow &configWindow)
{
    this->selectedDevices = selectedDevices;
    this->configWindow = &configWindow;
}

void DeviceTest::slotShowConfigWindow(){
    configWindow->show();
}
void DeviceTest::setWindowConfigureable(bool status){
    windowConfigureable = status;
}

bool DeviceTest::isWindowConfigureable(){
    return windowConfigureable;
}
