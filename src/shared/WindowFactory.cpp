#include "WindowFactory.h"

WindowFactory::WindowFactory(QObject *parent) : QObject(parent)
{

}

QMainWindow *WindowFactory::makeWindow(QString windowType, Orchestrator &orchestrator, PowerMeter *device){
    if (windowType.contains("N7745A")){
        // create window
        QMainWindow *window = new ConfigPowerMeter(orchestrator, device);

        return window;
    }
    else{
        return nullptr;
    }
}
