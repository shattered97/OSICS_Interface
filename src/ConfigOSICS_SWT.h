#ifndef CONFIGOSICS_SWT_H
#define CONFIGOSICS_SWT_H

#include <QMainWindow>

namespace Ui {
class ConfigOSICS_SWT;
}

class ConfigOSICS_SWT : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_SWT(QVariant &device, QWidget *parent = nullptr);
    ~ConfigOSICS_SWT();

private:
    Ui::ConfigOSICS_SWT *ui;
};

#endif // CONFIGOSICS_SWT_H
