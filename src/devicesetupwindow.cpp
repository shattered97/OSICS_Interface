#include "devicesetupwindow.h"
#include "ui_devicesetupwindow.h"

DeviceSetupWindow::DeviceSetupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceSetupWindow)
{
    ui->setupUi(this);
}

DeviceSetupWindow::~DeviceSetupWindow()
{
    delete ui;
}
