#include "n7714awindow.h"
#include "ui_n7714awindow.h"
#include "Worker.h"

n7714awindow::n7714awindow(Worker *worker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::n7714awindow)
{
    ui->setupUi(this);

    this->worker = worker;

    qDebug() << "opened new window";

}

n7714awindow::~n7714awindow()
{
    delete ui;
}
