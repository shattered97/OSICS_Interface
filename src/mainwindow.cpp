#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DefaultInstrument.h"
#include "N7714A.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);





//    QByteArray theIdentity = foundResources.first().second;
//    QByteArray theInstrLoc = foundResources.first().first;

////    // ****** TEST DEFAULT INSTRUMENT *******
////    DefaultInstrument testInstrument(theIdentity, theInstrLoc);


////    // ****** TEST N7714A ******
//    N7714A testInstrument(theIdentity, theInstrLoc);

//    QByteArray rspSTB;
//    testInstrument.DefaultInstrument::querySTB(defaultSession, currentSession, rspSTB);
//    qDebug() << "STB: " << rspSTB;

//    QByteArray rspESE;
//    testInstrument.queryESE(defaultSession, currentSession, rspESE);
//    qDebug() << "ESE: " << rspESE;

//    QByteArray rspESR;
//    testInstrument.queryESR(defaultSession, currentSession, rspESR);
//    qDebug() << "ESR: " << rspESR;

//    QByteArray rspOPC;
//    testInstrument.queryOPC(defaultSession, currentSession, rspOPC);
//    qDebug() << "OPC : " << rspOPC;

//    QByteArray rspTST;
//    testInstrument.queryTST(defaultSession, currentSession, rspTST);
//    qDebug() << "TST: " << rspTST;

//    QByteArray rspOPT;
//    testInstrument.queryOPT(defaultSession, currentSession, rspOPT);
//    qDebug() << "OPT: " << rspOPT;

//    QByteArray rspIDN;
//    testInstrument.queryIDN(defaultSession, currentSession, rspIDN);
//    qDebug() << "IDN: " << rspIDN;


//////// ******* Run default commands with no response *******

//    testInstrument.execESE(defaultSession, currentSession, 8);
//    QByteArray testSetESE;
//    testInstrument.queryESE(defaultSession, currentSession, testSetESE);
//    qDebug() << "ESE: " << testSetESE;

//    testInstrument.execCLS(defaultSession, currentSession);
//    testInstrument.execOPC(defaultSession, currentSession);
//    testInstrument.execRST(defaultSession, currentSession);
//    testInstrument.execWAI(defaultSession, currentSession);


////// ******** TEST N7714A SPECIFIC COMMANDS




}

MainWindow::~MainWindow()
{
    delete ui;
    theCommBus.closeDefaultSession(defaultSession);

}


void MainWindow::on_comboBox_activated(int index)
{
    // TEMPORARY
    // ALSO need to create a way to determine which child class to construct
    // update selected resource
    QMessageBox selectionBox;
    selectionBox.setInformativeText("Confirm Instrument Selection");
    selectionBox.setMinimumSize(400, 400);
    selectionBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    selectionBox.setText(QString(foundResources.value(index + 1).first) + " " + foundResources.value(index + 1).second.split('\n')[0]);

    if(selectionBox.exec() == QMessageBox::Ok){
          selectedResource = N7714A(foundResources.value(index + 1).second, foundResources.value(index + 1).first);

        // populate fields
        populateGUIFields();
    }
    else{
        ui->comboBox->setCurrentIndex(-1);
    }



}

void MainWindow::populateGUIFields(){

    // ***** BREAK INTO SEPARATE METHODS LATER *****

    // send command to check power state
    QByteArray response;
    QByteArray command = "sour1:pow:stat?\n";
    selectedResource.sendCmdRsp(defaultSession, currentSession, command, response);

    // parse out power state
    int power = response.at(0) - '0';

    if(power == 0){
        qDebug() << "Power is OFF" << power;
        ui->powerToggle->setChecked(false);

        ui->powerStatusIndicator->setAutoFillBackground(true);
        QPalette offPalette;
        offPalette.setColor(QPalette::Window, Qt::gray);
        ui->powerStatusIndicator->setPalette(offPalette);
        ui->powerStatusIndicator->setText("OFF");
    }
    else{
        qDebug() << "Power is ON" << power;
        ui->powerToggle->setChecked(true);

        ui->powerStatusIndicator->setAutoFillBackground(true);
        QPalette onPalette;
        onPalette.setColor(QPalette::Window, Qt::green);
        ui->powerStatusIndicator->setPalette(onPalette);
        ui->powerStatusIndicator->setText("ON");
    }

    // send command to read power level
    QByteArray powerLevelResponse;
    QByteArray powerLevelCommand = "sour1:pow?";
    selectedResource.sendCmdRsp(defaultSession, currentSession, powerLevelCommand, powerLevelResponse);

    // parse out power level
    QByteArray powerLevel = powerLevelResponse.split('\n')[0];
    ui->powerLevelField->clear();
    ui->powerLevelField->setPlainText(powerLevel);





//    qDebug() << "Power Read: " << power;
//    QByteArray commandPowerON = "sour1:pow:stat on\n";
//    selectedResource.sendCmdNoRsp(defaultSession, currentSession, commandPowerON);


}



void MainWindow::on_pushButton_clicked()
{
    // disable dropdown
    ui->comboBox->setEnabled(false);

    // clear current list of instruments
    ui->comboBox->clear();
    // clear foundResources
    foundResources.clear();

    // look for resources
    theCommBus.createDefaultRM(defaultSession);
    theCommBus.displayResources(defaultSession, instrAddr, currentSession, &numInstruments, &findList, foundResources);

    // turn resource map into a list of strings to populate comboBox
    QStringList resourcesStringList = QStringList();
    for(auto e : foundResources.keys()){
        ui->comboBox->addItem(foundResources.value(e).second.split('\n')[0]);
    }

    // makes selection blank on start-up
    ui->comboBox->setCurrentIndex(-1);

    // re-enable
    ui->comboBox->setEnabled(true);
}

void MainWindow::on_powerToggle_stateChanged(int arg1)
{
    if(arg1 == 0){
        // turn off power
    }
    else{
        // turn on power
    }
}
