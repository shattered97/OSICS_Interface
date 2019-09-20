#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    orchestrator = new Orchestrator();

    loadTestTypesList();
    loadDeviceTypesList();
    QObject::connect(orchestrator, SIGNAL(signalCreateErrorDialog(QByteArray)),
                     this, SLOT(slotCreateErrorDialog(QByteArray)));
    QObject::connect(this, SIGNAL(signalBeginTest(QString)), orchestrator, SLOT(slotBeginTest(QString)));
    QObject::connect(this, SIGNAL(signalCreateDevice(QString, QByteArray, QByteArray)),
                     orchestrator, SLOT(slotCreateDevice(QString, QByteArray, QByteArray)));
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

        if(deviceString.contains(deviceType)){
            convertedResourceInfo.append(e.first + " " + e.second.split('\n')[0]);
        }
    }
    return convertedResourceInfo;
}

void MainWindow::on_testTypeComboBox_currentIndexChanged(int index)
{
    // #TODO implement test windows
}

bool MainWindow::hasDeviceBeenSelected(QByteArray deviceAddress){
    // get device address
    bool success = true;

    // get list of addresses already selected

    for(int i = 0; i < ui->selectedDevicesListWidget->count(); i++){
        QByteArray selectedDeviceIDString = ui->selectedDevicesListWidget->item(i)->text().toLatin1();
        QByteArray selectedDeviceAddress = selectedDeviceIDString.split(' ')[0];

        if(selectedDeviceAddress == deviceAddress){
            success = false;
        }
    }

    return success;
}

void MainWindow::on_addSelectedDeviceBtn_clicked()
{
    ui->addSelectedDeviceBtn->setEnabled(false);

    // check if device has already been added to list
    QByteArray deviceAddress = ui->foundDevicesListWidget->selectedItems()[0]->text().split(' ')[0].toLatin1();
    if(hasDeviceBeenSelected(deviceAddress)){
        // copy over to selected devices list widget
        QByteArray instrumentInfo = ui->foundDevicesListWidget->currentItem()->text().toLatin1();
        ui->selectedDevicesListWidget->addItem(instrumentInfo);

        // determine which device to create (#TODO possibly convert to factory in future)
        QString currentDeviceType = ui->devicetypeComboBox->currentText();
        qDebug() << "device type from combo " << currentDeviceType;
        QByteArray instrumentAddress = instrumentInfo.split(' ')[0];
        QByteArray instrumentIdentity = instrumentInfo.mid(instrumentInfo.indexOf(' ') + 1, instrumentInfo.size());
        QApplication::setOverrideCursor(Qt::WaitCursor);
        qDebug() << "addr/identity " << instrumentAddress << " " << instrumentIdentity;
        emit signalCreateDevice(currentDeviceType, instrumentAddress, instrumentIdentity);
    }
    else{
        // create error dialog
        QMessageBox msgBox;
        msgBox.setText("This device has already been added to the \"Selected Devices\" list.");
        msgBox.exec();
    }

    QApplication::restoreOverrideCursor();
    ui->addSelectedDeviceBtn->setEnabled(true);
}

void MainWindow::on_startTestPushButton_clicked()
{
    // #TODO open test window
    // assuming power meter at [0], exfo at [1]
//    orchestrator->testOSACommands();

    // send signal with test type name from dropdown to Orchestrator
    QString testTypeName = ui->testTypeComboBox->currentText();

    emit signalBeginTest(testTypeName);
}

void MainWindow::on_selectedDevicesListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int indexOfClickedDevice = ui->selectedDevicesListWidget->currentRow();
    QVariant device = orchestrator->getDeviceAtIndex(indexOfClickedDevice);
    QByteArray deviceTypeName = QByteArray(device.typeName());
    qDebug() << deviceTypeName;
    // disable cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // open window (can cast QVariant as default b/c window knows specific type)
    DefaultInstrument *instrument = device.value<DefaultInstrument*>();
    qDebug() << typeid(instrument->getConfigWindow()).name();
    instrument->getConfigWindow()->show();

    QApplication::restoreOverrideCursor();
}


void MainWindow::slotCreateErrorDialog(QByteArray errorMsg){
    qDebug() << "slotCreateErrorDialog";
    QMessageBox msgBox;
    msgBox.setText(errorMsg);
    msgBox.exec();
}
