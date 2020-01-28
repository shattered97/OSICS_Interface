#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windowFactory = new WindowFactory();
    deviceTestFactory = new DeviceTestFactory();
    orchestrator = new Orchestrator(windowFactory, deviceTestFactory);
    QThread *orchestratorThread = new QThread;
    orchestrator->moveToThread(orchestratorThread);
    QThread::currentThread()->setObjectName("MAIN THREAD");
    orchestratorThread->setObjectName("ORCHESTRATOR THREAD");
    connect(orchestrator, SIGNAL(finished()), orchestratorThread, SLOT(quit()));
    connect(orchestratorThread, SIGNAL(started()), orchestrator, SLOT(slotStartOrchestrator()));
    connect(orchestrator, SIGNAL(finished()), orchestrator, SLOT(deleteLater()));
    connect(orchestratorThread, SIGNAL(finished()), orchestratorThread, SLOT(deleteLater()));
    orchestratorThread->start();

    loadTestTypesList();
    loadDeviceTypesList();
    QObject::connect(orchestrator, SIGNAL(signalSendDecisionErrorMsg(QString)),
                     this, SLOT(slotDisplayDecisionErrorMsg(QString)));
    QObject::connect(this, SIGNAL(signalBeginTest(QString)), orchestrator, SLOT(slotBeginTest(QString)));
    QObject::connect(this, SIGNAL(signalCreateDevice(QString, QByteArray, QByteArray)),
                     orchestrator, SLOT(slotCreateDevice(QString, QByteArray, QByteArray)), Qt::AutoConnection);
    QObject::connect(this, SIGNAL(signalClearSelectedDevices()), orchestrator, SLOT(slotClearSelectedDevices()));
    QObject::connect(orchestrator, SIGNAL(signalSendSimpleErrorMsg(QString)),
                     this, SLOT(slotDisplaySimpleErrorMsg(QString)));
    QObject::connect(orchestrator, SIGNAL(signalDeviceCreated()), this, SLOT(slotDeviceCreated()));

}

MainWindow::~MainWindow()
{
    delete orchestrator;
    delete ui;
}

void MainWindow::setFontSizes(){
    // set all fonts with pixel size
    QFont twelvePixel("MS Shell Dlg 2", 12);
    twelvePixel.setPointSize(12);
    ui->addSelectedDeviceBtn->setFont(twelvePixel);
}

void MainWindow::loadDeviceTypesList(){
    for(auto deviceType: DEVICE_TYPES){
        // append any display notes to device model numbers
        if(KEYSIGHT_OPTICAL_POWER_METERS.contains(deviceType)){
            deviceType = deviceType + KEYSIGHT_OPTICAL_PM_NOTE;
        }
        else if(KEYSIGHT_LASER_SOURCES.contains(deviceType)){
            deviceType = deviceType + KEYSIGHT_LASER_NOTE;
        }
        else if(EXFO_DEVICES.contains(deviceType)){
            deviceType = deviceType + EXFO_CHASSIS_NOTE;
        }
        else if(ANDO_OSAS.contains(deviceType)){
            deviceType = deviceType + ANDO_OSA_NOTE;
        }
        else if(BRISTOL_WAVEMETERS.contains(deviceType)){
            deviceType = deviceType + BRISTOL_WAVEMETER_NOTE;
        }
        ui->devicetypeComboBox->addItem(deviceType);
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
    QObject::disconnect(this, SIGNAL(signalRequestDevicesFromOrchestrator()), nullptr, nullptr);

}

void MainWindow::slotReceiveDevices(FoundInstr listOfDevices)
{

    // get the model number (device type) without the note (all notes should start w/ left paren)
    QByteArray deviceType = ui->devicetypeComboBox->currentText().split('(')[0].trimmed().toLatin1();
    qDebug() << deviceType;
    QList<QByteArray> convertedDevices = resourcesQmapToQList(listOfDevices, deviceType);

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
        qDebug() << "??????? " << deviceString;
        if(deviceString.contains(deviceType)){
            convertedResourceInfo.append(e.first + " " + e.second.split('\n')[0]);
        }
    }
    return convertedResourceInfo;
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

void MainWindow::slotDeviceCreated(){
    QApplication::restoreOverrideCursor();
    ui->addSelectedDeviceBtn->setEnabled(true);
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
        QString currentDeviceType = ui->devicetypeComboBox->currentText().split('(')[0].trimmed();
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
        QApplication::restoreOverrideCursor();
    }


}

void MainWindow::on_startTestPushButton_clicked()
{
    // open dialog for the user to confirm
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Confirm selections to begin test.",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        // send signal with test type name from dropdown to Orchestrator
        QString testTypeName = ui->testTypeComboBox->currentText();

        // start test
        emit signalBeginTest(testTypeName);
    }
}

void MainWindow::on_selectedDevicesListWidget_itemDoubleClicked()
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

void MainWindow::slotDisplaySimpleErrorMsg(QString errorMsg){
    QMessageBox msgBox;
    msgBox.setText(errorMsg);
    msgBox.exec();
}

void MainWindow::slotDisplayDecisionErrorMsg(QString errorMsg){
    qDebug() << "slotCreateErrorDialog";
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Error", errorMsg, QMessageBox::Abort | QMessageBox::Retry);
    if(msgBox == QMessageBox::Abort){
        // close program
        exit(EXIT_FAILURE);
    }
}

void MainWindow::on_clearSelectedListButton_clicked()
{
    emit signalClearSelectedDevices();
    // clear items in list widget
    ui->selectedDevicesListWidget->clear();
}

void MainWindow::on_devicetypeComboBox_currentIndexChanged(int index)
{
    // clear the contents of the list widget
    ui->foundDevicesListWidget->clear();
}

void MainWindow::on_pbConfTest_clicked()
{

}
