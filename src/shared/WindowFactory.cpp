#include "WindowFactory.h"
#include "KeysightPowerMeter.h"

WindowFactory::WindowFactory(QObject *parent) : QObject(parent)
{

}

QMainWindow *WindowFactory::makeWindow(QString windowType, QVariant &deviceVariant){
    if (windowType.contains("N7745A")){
        // create window
        KeysightPowerMeter *device = deviceVariant.value<KeysightPowerMeter*>();
        QMainWindow *window = new ConfigPowerMeter(device);

        return window;
    }
    else if(windowType.contains("N7714A")){
        N7714A *device = deviceVariant.value<N7714A*>();
        QMainWindow * window = new ConfigN7714AWindow(device);
        return window;
    }
    else{
        return nullptr;
    }
}
