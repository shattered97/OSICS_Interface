#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    orchestrator = new Orchestrator();

    loadTestTypesList();
    loadDeviceTypesList();

    // connect device creation signals/slots
    QObject::connect(this, SIGNAL(signalCreateN7714ADevice(QString, QByteArray, QByteArray)),
                     orchestrator, SLOT(slotCreateN7714ADevice(QString, QByteArray, QByteArray)));
    QObject::connect(this, SIGNAL(signalCreateN7745ADevice(QString, QByteArray, QByteArray)),
                     orchestrator, SLOT(slotCreateN7745ADevice(QString, QByteArray, QByteArray)));
}

MainWindow::~MainWindow()
{
    delete orchestrator;
    delete ui;
}

void MainWindow::loadDeviceTypesList(){
    for(auto e: DEVICE_TYPES){
        ui->devicetypeComboBox->addItem(e);
    }
}

void MainWindow::loadTestTypesList(){
    for(auto e: TEST_TYPES){
        ui->testTypeComboBox->addItem(e);
    }
}

void MainWindow::on_searchForDevTypeBtn_clicked()
{
    // clear found devices list
    ui->foundDevicesListWidget->clear();

    // disable cursor (re-enabled in slotReceiveDevices)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // get devices from orchestrator
    QObject::connect(this, SIGNAL(signalRequestDevicesFromOrchestrator()),
                     orchestrator, SLOT(slotLookForDevices()));
    emit signalRequestDevicesFromOrchestrator();
    QObject::disconnect(this, SIGNAL(signalRequestDevicesFromOrchestrator()), 0, 0);

}

void MainWindow::slotReceiveDevices(FoundInstr listOfDevices)
{
    QList<QByteArray> convertedDevices = resourcesQmapToQList(listOfDevices, ui->devicetypeComboBox->currentText().toLatin1());

    // populate ui list with devices
    for(auto e: convertedDevices){
        ui->foundDevicesListWidget->addItem(e);
    }

    QApplication::restoreOverrideCursor();

    // enable launch button
    if(ui->foundDevicesListWidget->count() > 0){
        ui->foundDevicesListWidget->setCurrentItem(ui->foundDevicesListWidget->itemAt(1,1));
        ui->addSelectedDeviceBtn->setEnabled(true);
    }
    else{
        ui->addSelectedDeviceBtn->setEnabled(false);
        QMessageBox msgBox;
        msgBox.setText("No instruments found.");
        msgBox.exec();
    }
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


void MainWindow::on_testTypeComboBox_currentIndexChanged(int index)
{
    // #TODO implement test windows
}

void MainWindow::on_addSelectedDeviceBtn_clicked()
{
    // copy over to selected devices list widget
    QByteArray instrumentInfo = ui->foundDevicesListWidget->currentItem()->text().toLatin1();
    ui->selectedDevicesListWidget->addItem(instrumentInfo);

    // determine which device to create (#TODO possibly convert to factory in future)
    QString currentDeviceType = ui->devicetypeComboBox->currentText();

    QByteArray instrumentAddress = instrumentInfo.split(' ')[0];
    QByteArray instrumentIdentity = instrumentInfo.mid(instrumentInfo.indexOf(' ') + 1, instrumentInfo.size());

    QApplication::setOverrideCursor(Qt::WaitCursor);

    // #TODO device factory?
    if(currentDeviceType == "N7714A"){
        // signal to orchestrator to create n7714a
        emit signalCreateN7714ADevice(currentDeviceType, instrumentAddress, instrumentIdentity);
    }
    else if(currentDeviceType == "N7745A"){
        // signal to orchestrator to create n7745a
        emit signalCreateN7745ADevice(currentDeviceType, instrumentAddress, instrumentIdentity);
    }

    QApplication::restoreOverrideCursor();
}

void MainWindow::on_startTestPushButton_clicked()
{
    // #TODO open test window
}

void MainWindow::on_selectedDevicesListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int indexOfClickedDevice = ui->selectedDevicesListWidget->currentRow();
    QVariant device = orchestrator->getDeviceAtIndex(indexOfClickedDevice);
    QByteArray deviceTypeName = QByteArray(device.typeName());

    // disable cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // open window (can cast QVariant as default b/c window knows specific type)
    DefaultInstrument *instrument = device.value<DefaultInstrument*>();
    instrument->getConfigWindow()->show();

    QApplication::restoreOverrideCursor();
}
