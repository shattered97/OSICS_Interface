#ifndef CONFIGOSICS_T100_H
#define CONFIGOSICS_T100_H

#include <QMainWindow>

namespace Ui {
class ConfigOSICS_T100;
}

class ConfigOSICS_T100 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_T100(QWidget *parent = nullptr);
    ~ConfigOSICS_T100();

private:
    Ui::ConfigOSICS_T100 *ui;
};

#endif // CONFIGOSICS_T100_H
