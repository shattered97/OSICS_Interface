#include "ConfigOSICS_T100.h"
#include "ui_ConfigOSICS_T100.h"

ConfigOSICS_T100::ConfigOSICS_T100(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_T100)
{
    ui->setupUi(this);
}

ConfigOSICS_T100::~ConfigOSICS_T100()
{
    delete ui;
}
