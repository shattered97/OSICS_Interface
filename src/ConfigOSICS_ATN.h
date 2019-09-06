#ifndef CONFIGOSICS_ATN_H
#define CONFIGOSICS_ATN_H

#include <QMainWindow>

namespace Ui {
class ConfigOSICS_ATN;
}

class ConfigOSICS_ATN : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_ATN(QVariant &device, QWidget *parent = nullptr);
    ~ConfigOSICS_ATN();

private:
    Ui::ConfigOSICS_ATN *ui;
};

#endif // CONFIGOSICS_ATN_H
