#ifndef OSICSMAINFRAMESETUPWINDOW_H
#define OSICSMAINFRAMESETUPWINDOW_H

#include <QMainWindow>

namespace Ui {
class OSICSMainframeSetupWindow;
}

class OSICSMainframeSetupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSICSMainframeSetupWindow(QVariant &device, QWidget *parent = 0);
    ~OSICSMainframeSetupWindow();

private:
    Ui::OSICSMainframeSetupWindow *ui;

//    QVariant device;
};

#endif // OSICSMAINFRAMESETUPWINDOW_H
