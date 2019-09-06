#include "ConfigOSICS_ATN.h"
#include "ui_ConfigOSICS_ATN.h"

ConfigOSICS_ATN::ConfigOSICS_ATN(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_ATN)
{
    ui->setupUi(this);
}

ConfigOSICS_ATN::~ConfigOSICS_ATN()
{
    delete ui;
}
