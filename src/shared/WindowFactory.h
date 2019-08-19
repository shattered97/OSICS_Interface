#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include <QObject>
#include "configpowermeter.h"
#include "confign7714awindow.h"


class WindowFactory : public QObject
{
    Q_OBJECT
public:
    explicit WindowFactory(QObject *parent = nullptr);

    static QMainWindow *makeWindow(QString windowType, QVariant &deviceVariant);
};

#endif // WINDOWFACTORY_H
