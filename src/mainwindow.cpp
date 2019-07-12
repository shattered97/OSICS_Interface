#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "QMessageBox"
#include "QThread"
#include "EXFO_OSICS/EXFO_OSICS_MAINFRAME.h"
#include "Worker.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Worker worker;
    loadDeviceTypesList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete n7714aNewWindow;
}

void MainWindow::loadDeviceTypesList(){
    for(auto e: DEVICE_TYPES){
        ui->listWidget->addItem(e);
    }
}

void MainWindow::on_confirmDevTypeBtn_clicked()
{
    // get selected option
    QByteArray selected = ui->listWidget->currentItem()->text().toLatin1();

    // disable cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // disable ui elements
    ui->listWidget->setEnabled(false);
    ui->confirmDevTypeBtn->setEnabled(false);

    // carry out search for device type
    QObject::connect(this, SIGNAL(signalRequestDevicesFromWorker(QByteArray)), &worker, SLOT(slotLookForDevices(QByteArray)));
    emit signalRequestDevicesFromWorker(selected);

    // enable launch button
    if(ui->foundDevicesListWidget->count() > 0){
        ui->launchSelectedDevice->setEnabled(true);
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("No instruments found.");
        msgBox.exec();
    }

}

void MainWindow::openN7714AView()
{
    // opens window to N7714A (window will be replaced in future by plugin)
    n7714awindow *testwindow;
    testwindow = new n7714awindow(&worker);
    testwindow->show();
}

void MainWindow::on_listWidget_currentItemChanged()
{
    // activate the confirmation button
    ui->confirmDevTypeBtn->setEnabled(true);
}

void MainWindow::searchforSelectedResource(QByteArray selected)
{
    // get resources returned from IDN call
    emit signalRequestDevicesFromWorker(selected);
}

void MainWindow::slotReceiveDevices(QList<QByteArray> listOfDevices)
{
    // populate ui list with devices
    for(auto e: listOfDevices){
        ui->foundDevicesListWidget->addItem(e);
    }

    QApplication::restoreOverrideCursor();
}

void MainWindow::on_launchSelectedDevice_clicked()
{
    // Launch appropriate window for device (I'm looking for a more elegant way to do this)

    QByteArray currentDeviceType = ui->listWidget->currentItem()->text().toLatin1();
    QByteArray currentDeviceSelected = ui->foundDevicesListWidget->currentItem()->text().toLatin1();

    if(currentDeviceType == N7714A_DEVICE){

        QByteArray instrumentAddress = currentDeviceSelected.split(' ')[0];
        QByteArray instrumentIdentity = currentDeviceSelected.mid(currentDeviceSelected.indexOf(' ') + 1, currentDeviceSelected.size());

        // signal worker to create device
        QObject::connect(this, SIGNAL(signalCreateDevice(QByteArray, QByteArray)), &worker, SLOT(slotCreateN7714ADevice(QByteArray, QByteArray)));
        emit signalCreateDevice(instrumentAddress, instrumentIdentity);

        // launch N7714A interface, pass in worker
        n7714aNewWindow = new n7714awindow(&worker);
        n7714aNewWindow->show();
    }
    // continue for other devices

}
