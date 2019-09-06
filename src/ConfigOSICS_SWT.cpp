#include "ConfigOSICS_SWT.h"
#include "ui_ConfigOSICS_SWT.h"

ConfigOSICS_SWT::ConfigOSICS_SWT(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_SWT)
{
    ui->setupUi(this);
}

ConfigOSICS_SWT::~ConfigOSICS_SWT()
{
    delete ui;
}
