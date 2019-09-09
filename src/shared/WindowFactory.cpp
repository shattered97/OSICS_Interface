#include "WindowFactory.h"
#include "KeysightPowerMeter.h"

WindowFactory::WindowFactory(QObject *parent) : QObject(parent)
{

}

QMainWindow *WindowFactory::makeWindow(QString windowType, QVariant &deviceVariant)
{
    QMainWindow *window;
    if (windowType.contains("N7745A")){
        window = new ConfigPowerMeter(deviceVariant);
    }
    else if(windowType.contains("N7714A")){
        window = new ConfigN7714AWindow(deviceVariant);
    }
    else if(windowType.contains("EXFO,OSICS")){
        window = new OSICSMainframeSetupWindow(deviceVariant);
    }
    else if(windowType.contains("T100")){
        qDebug() << "t100 window created";
        window = new ConfigOSICS_T100(deviceVariant);
    }
    else if(windowType.contains("ATN")){
        window = new ConfigOSICS_ATN(deviceVariant);
    }
    else if(windowType.contains("SWT")){
        window = new ConfigOSICS_SWT(deviceVariant);
    }
    else{
        // #TODO error/exit
        window = new QMainWindow();
    }
    return window;
}
