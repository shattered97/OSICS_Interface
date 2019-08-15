#ifndef DEVICESETUPWINDOW_H
#define DEVICESETUPWINDOW_H

#include <QMainWindow>
namespace Ui {
class DeviceSetupWindow;
}

class DeviceSetupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceSetupWindow(QWidget *parent = nullptr);
    ~DeviceSetupWindow();

private:
    Ui::DeviceSetupWindow *ui;
};

#endif // DEVICESETUPWINDOW_H

