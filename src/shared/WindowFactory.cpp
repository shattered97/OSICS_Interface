#include "WindowFactory.h"
#include "KeysightPowerMeter.h"

WindowFactory::WindowFactory(QObject *parent) : QObject(parent)
{

}

QMainWindow *WindowFactory::makeWindow(QString windowType, QVariant &deviceVariant){
    if (windowType.contains("N7745A")){
        QMainWindow *window = new ConfigPowerMeter(deviceVariant);
        return window;
    }
    else if(windowType.contains("N7714A")){
        QMainWindow * window = new ConfigN7714AWindow(deviceVariant);
        return window;
    }
    else if(windowType.contains("EXFO,OSICS")){
        QMainWindow *window = new OSICSMainframeSetupWindow(deviceVariant);
        return window;
    }
    else{
        // #TODO error/exit
        return nullptr;
    }
}
