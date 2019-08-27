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

private slots:
    void on_configSlot1Btn_clicked();

    void on_configSlot2Btn_clicked();

    void on_configSlot3Btn_clicked();

    void on_configSlot4Btn_clicked();

    void on_configSlot5Btn_clicked();

    void on_configSlot6Btn_clicked();

    void on_configSlot7Btn_clicked();

    void on_configSlot8Btn_clicked();

private:
    Ui::OSICSMainframeSetupWindow *ui;

//    QVariant device;

};

#endif // OSICSMAINFRAMESETUPWINDOW_H
