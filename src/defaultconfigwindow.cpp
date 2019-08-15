#include "defaultconfigwindow.h"
#include "ui_defaultconfigwindow.h"

DefaultConfigWindow::DefaultConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DefaultConfigWindow)
{
    ui->setupUi(this);
}

DefaultConfigWindow::~DefaultConfigWindow()
{
    delete ui;
}
