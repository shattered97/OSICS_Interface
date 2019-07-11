#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "QMessageBox"
#include "QThread"
#include "EXFO_OSICS/EXFO_OSICS_MAINFRAME.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    theCommBus.closeDefaultSession(defaultSession);


    // ***** Test OSICS MAINFRAME COMMANDS *****
    QByteArray emptyResponse;
    EXFO_OSICS_MAINFRAME testOsics("", "");
    testOsics.disableMainframeLaserCmd(defaultSession, currentSession);
    testOsics.enableMainframeLaserCmd(defaultSession, currentSession);
    testOsics.laserStateMainframeQuery(defaultSession, currentSession, emptyResponse);
    testOsics.setMainframeSpectralUnitGHzCmd(defaultSession, currentSession);
    testOsics.setMainframeSpectralUnitNMCmd(defaultSession, currentSession);
    testOsics.spectralUnitMainframeQuery(defaultSession, currentSession, emptyResponse);
    testOsics.setMainframePowerUnitDBmCmd(defaultSession, currentSession);
    testOsics.setMainframePowerUnitMWCmd(defaultSession, currentSession);
    testOsics.powerUnitMainframeQuery(defaultSession, currentSession, emptyResponse);
    QByteArray power = "11.11";
    testOsics.setMainframeOutputPowerCmd(defaultSession, currentSession, power);
    testOsics.outputPowerMainframeQuery(defaultSession, currentSession, emptyResponse);
    QByteArray mod = "INT";
    testOsics.setMainframeModSrcTypeCmd(defaultSession, currentSession, mod);
    testOsics.outputPowerMainframeQuery(defaultSession, currentSession, emptyResponse);
    testOsics.modSrcTypeMainframeQuery(defaultSession, currentSession, emptyResponse);
    QByteArray frequency = "7000";
    testOsics.setMainframeFrequencyQuery(defaultSession, currentSession, frequency);
    testOsics.frequencyMainframeQuery(defaultSession, currentSession, emptyResponse);
    QByteArray config = "A";
    testOsics.saveManframeConfigCmd(defaultSession, currentSession, config);
    testOsics.recallMainframeConfigCmd(defaultSession, currentSession, config);
    testOsics.remoteInterlockMainframeQuery(defaultSession, currentSession, emptyResponse);
    testOsics.moduleTypeAtSlotQuery(defaultSession, currentSession, 1, emptyResponse);
}

void MainWindow::on_comboBox_activated(int index)
{

    // make user confirm selection in selection box
    QMessageBox selectionBox;
    selectionBox.setInformativeText("Confirm Instrument Selection");
    selectionBox.setMinimumSize(400, 400);
    selectionBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    selectionBox.setText(QString(foundResources.value(index + 1).first) + " " + foundResources.value(index + 1).second.split('\n')[0]);

    // create instance of resource otherwise reset combo box
    if(selectionBox.exec() == QMessageBox::Ok){
        selectedResource = N7714A(foundResources.value(index + 1).second, foundResources.value(index + 1).first);
        ui->listWidget->addItem(selectedResource.getInstrIdentity().split('\n')[0]);
        // populate fields
        populateGUIFields();
    }
}

void MainWindow::setPowerStatusIndicatorOn()
{
    ui->powerStatusIndicator->setAutoFillBackground(true);
    QPalette onPalette;
    onPalette.setColor(QPalette::Window, Qt::green);
    ui->powerStatusIndicator->setPalette(onPalette);
    ui->powerStatusIndicator->setText("ON");
}

void MainWindow::setPowerStatusIndicatorOff()
{
    ui->powerStatusIndicator->setAutoFillBackground(true);
    QPalette offPalette;
    offPalette.setColor(QPalette::Window, Qt::gray);
    ui->powerStatusIndicator->setPalette(offPalette);
    ui->powerStatusIndicator->setText("OFF");
}

void MainWindow::populateGUIFields()
{
    // activate fields
    ui->powerToggle->setEnabled(true);
    ui->newLevelField->setEnabled(true);
    ui->resetNewLevelBtn->setEnabled(true);
    ui->setNewLevelBtn->setEnabled(true);

    // send command to check power state
    QByteArray response;
    selectedResource.queryPowerStatus(defaultSession, currentSession, 1, response);

    // parse out power state
    int power = response.at(0) - '0';

    if(power == 0){
        ui->powerToggle->setChecked(false);
        setPowerStatusIndicatorOff();
    }
    else{
        ui->powerToggle->setChecked(true);
        setPowerStatusIndicatorOn();
    }

    // send command to read power level
    QByteArray powerLevelResponse;
    selectedResource.queryPowerLevel(defaultSession, currentSession, 1, powerLevelResponse);

    // parse out power level
    QByteArray powerLevel = powerLevelResponse.split('\n')[0];
    ui->powerLevelField->clear();
    ui->powerLevelField->setPlainText(powerLevel);
}

void MainWindow::on_pushButton_clicked()
{
    // clear instruments and found resources list
    ui->comboBox->clear();
    foundResources.clear();

    // disable dropdown and mouse
    ui->comboBox->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // look for resources
    theCommBus.createDefaultRM(defaultSession);
    theCommBus.displayResources(defaultSession, instrAddr, currentSession, &numInstruments, &findList, foundResources);

    // turn resource map into a list of strings to populate comboBox
    QStringList resourcesStringList = QStringList();
    for(auto e : foundResources.keys()){
        ui->comboBox->addItem(foundResources.value(e).second.split('\n')[0]);
    }

    // restore combo box and mouse
    ui->comboBox->setEnabled(true);
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_powerToggle_stateChanged(int arg1)
{
    if(arg1 == 0){
        // turn off power
        if (selectedResource.execPowerOffModule(defaultSession, currentSession, 1))
            setPowerStatusIndicatorOff();
    }
    else{
        // turn on power
        if(selectedResource.execPowerOnModule(defaultSession, currentSession, 1)){
            setPowerStatusIndicatorOn();
        }
    }
}

void MainWindow::on_resetNewLevelBtn_clicked()
{
    // get unit
    QByteArray response;
    selectedResource.queryPowerLevel(defaultSession, currentSession, 1 , response);

    // set power to default
    selectedResource.execPowerLevel(defaultSession, currentSession, 1, "DEF");

    QByteArray responseafter;
    selectedResource.queryPowerLevel(defaultSession, currentSession, 1, responseafter);

    // update display in field
    ui->powerLevelField->setPlainText(responseafter.split('\n')[0]);

}

void MainWindow::on_setNewLevelBtn_clicked()
{

    // verify that the text entered will be accepted by device
    QString fieldContents = ui->newLevelField->toPlainText();

    selectedResource.execPowerLevel(defaultSession, currentSession, 1, fieldContents.toLatin1());

    // update display in field
    QByteArray response;
    selectedResource.queryPowerLevel(defaultSession, currentSession, 1 , response);

    ui->powerLevelField->setPlainText(response.split('\n')[0]);

    // if setting the level was successful clear field
    ui->newLevelField->clear();
}

