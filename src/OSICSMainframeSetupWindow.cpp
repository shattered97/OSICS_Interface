#include "OSICSMainframeSetupWindow.h"
#include "ui_OSICSMainframeSetupWindow.h"

OSICSMainframeSetupWindow::OSICSMainframeSetupWindow(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSICSMainframeSetupWindow)
{
    ui->setupUi(this);

}

OSICSMainframeSetupWindow::~OSICSMainframeSetupWindow()
{
    delete ui;
}
