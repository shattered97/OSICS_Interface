#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include <QObject>
#include "configpowermeter.h"
#include "confign7714awindow.h"
#include "OSICSMainframeSetupWindow.h"
#include "ConfigOSICS_ATN.h"
#include "ConfigOSICS_SWT.h"
#include "ConfigOSICS_T100.h"


class WindowFactory : public QObject
{
    Q_OBJECT
public:
    explicit WindowFactory(QObject *parent = nullptr);

public slots:
    QMainWindow *makeWindow(QString windowType, QVariant *deviceVariant);


};

#endif // WINDOWFACTORY_H
