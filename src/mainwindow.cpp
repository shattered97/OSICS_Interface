#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Orchestrator worker;
    loadDeviceTypesList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDeviceTypesList(){
    for(auto e: DEVICE_TYPES){
        ui->listWidget->addItem(e);
    }
}

void MainWindow::on_confirmDevTypeBtn_clicked()
{
    // disable cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // disable ui elements
    ui->listWidget->setEnabled(false);
    ui->confirmDevTypeBtn->setEnabled(false);

    // carry out search for devices
    QObject::connect(this, SIGNAL(signalRequestDevicesFromWorker()), &worker, SLOT(slotLookForDevices()));
    emit signalRequestDevicesFromWorker();

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

void MainWindow::on_listWidget_currentItemChanged()
{
    ui->confirmDevTypeBtn->setEnabled(true);
}

void MainWindow::slotReceiveDevices(FoundInstr listOfDevices)
{
    QList<QByteArray> convertedDevices = resourcesQmapToQList(listOfDevices, ui->listWidget->currentItem()->text().toLatin1());

    // populate ui list with devices
    for(auto e: convertedDevices){
        ui->foundDevicesListWidget->addItem(e);
    }

    QApplication::restoreOverrideCursor();
}

void MainWindow::on_launchSelectedDevice_clicked()
{
    // Launch appropriate window depending on device selected
    // Note: not a permanent method for matching devices to functions

    QByteArray currentDeviceType = ui->listWidget->currentItem()->text().toLatin1();
    QByteArray currentDeviceSelected = ui->foundDevicesListWidget->currentItem()->text().toLatin1();

    if(currentDeviceType == N7714A_DEVICE){

        QByteArray instrumentAddress = currentDeviceSelected.split(' ')[0];
        QByteArray instrumentIdentity = currentDeviceSelected.mid(currentDeviceSelected.indexOf(' ') + 1, currentDeviceSelected.size());

        // signal worker to create device
        QObject::connect(this, SIGNAL(signalCreateDevice(QByteArray, QByteArray)), &worker, SLOT(slotCreateN7714ADevice(QByteArray, QByteArray)));
        emit signalCreateDevice(instrumentAddress, instrumentIdentity);
    }
    // continue for other devices

}

QList<QByteArray> MainWindow::resourcesQmapToQList(FoundInstr foundResources, QByteArray deviceType)
{
    QList<QByteArray> convertedResourceInfo;

    for(auto e: foundResources){
        QByteArray deviceString = e.first + " " + e.second;

        if(deviceString.contains(deviceType)){                               // Note: not a permanent method for matching instruments
            convertedResourceInfo.append(e.first + " " + e.second.split('\n')[0]);
        }
    }
    return convertedResourceInfo;
}
