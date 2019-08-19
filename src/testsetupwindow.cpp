#include "testsetupwindow.h"
#include "ui_testsetupwindow.h"
#include <QDebug>
#include <QtMath>
#include <QCheckBox>

TestSetupWindow::TestSetupWindow(QByteArray laserInfo, QByteArray powerMeterInfo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestSetupWindow)
{
    ui->setupUi(this);
    qDebug() << "creating test setup window";

    // create instruments
    QByteArray laserLocation = laserInfo.split(' ')[0];
    QByteArray laserIdentity = laserInfo.mid(laserInfo.indexOf(' ') + 1, laserInfo.size());
    QByteArray powerMeterLocation = powerMeterInfo.split(' ')[0];
    QByteArray powerMeterIdentity = powerMeterInfo.mid(powerMeterInfo.indexOf(' ') + 1, powerMeterInfo.size());

    laserSource = new N7714A(laserIdentity, laserLocation);
    powerMeter = new KeysightPowerMeter(powerMeterIdentity, powerMeterLocation);

    qDebug("----------------------------------------------------------");

    addPowerMeterChannels();
    getMinMaxWavelength();

}

TestSetupWindow::~TestSetupWindow()
{
    delete ui;
    delete laserSource;
    delete powerMeter;
}


void TestSetupWindow::addPowerMeterChannels(){
    // adds channel(s)? from keysight power meter to list

    int channels = powerMeter->getNumPowerMeterChannels();
    ui->powerMeterTable->setRowCount(channels);
    ui->powerMeterTable->setColumnWidth(0, 150);
    ui->powerMeterTable->setColumnWidth(1, 550);
    ui->powerMeterTable->setColumnWidth(2, 50);


    QByteArray device = powerMeter->getInstrLocation() + powerMeter->getInstrIdentity();
    for(int i = 0; i < channels; i++){
        ui->powerMeterTable->setItem(i, 0, new QTableWidgetItem("Channel " + QString::number(i + 1)));
        ui->powerMeterTable->setItem(i, 1, new QTableWidgetItem(QString(device)));
        QCheckBox *checkBox = new QCheckBox("", this);

        QTableWidgetItem *item = new QTableWidgetItem();
        item->data(Qt::CheckStateRole);
        item->setCheckState(Qt::Unchecked);
        ui->powerMeterTable->setCellWidget(i, 2, checkBox);
    }
}

void TestSetupWindow::getMinMaxWavelength(){
    QByteArray minWavelengthString;
    QByteArray maxWavelengthString;

    laserSource->queryWavelength(1, minWavelengthString, "MIN");
    laserSource->queryWavelength(1, maxWavelengthString, "MAX");

    minWavelength = convertSciToDouble(minWavelengthString.split('\n')[0]);
    qDebug() << "Display Min: " << minWavelength;

    maxWavelength = convertSciToDouble(maxWavelengthString.split('\n')[0]);
    qDebug() << "Display Max: " << maxWavelength;
}

void TestSetupWindow::on_testCommandEdit_returnPressed()
{
    qDebug() << "---------- Test Command -----------------";
    qDebug() << ui->testCommandEdit->text();

    QByteArray response;
    powerMeter->testCommand(ui->testCommandEdit->text().toLatin1(), response);
    qDebug() << "Response: " << response;
    qDebug() << "--------------------------------------";
}

double TestSetupWindow::convertSciToDouble(QByteArray sci){
    // format: "+1.52760488E-006"
    bool positive = false;

    // remove sign
    char sign = sci.at(0);
    sci.remove(0, 1);
    sign == '+' ? positive=true : positive=false;

    int exponent = sci.split('E')[1].toInt();
    qDebug() << exponent;
    double base = sci.split('E')[0].toDouble();
    qDebug() << base;
    double meters = base * qPow(10, exponent);
    qDebug() << meters;

    return convertMeterToNanoMeter(meters);
}

double TestSetupWindow::convertMeterToNanoMeter(double meter){
    return meter * qPow(10, 9);
}

void TestSetupWindow::on_startWavLineEdit_returnPressed()
{
    // check if value entered is numeric
    QByteArray enteredWavelength = ui->startWavLineEdit->text().toLatin1();
    qDebug() << enteredWavelength;
    bool conversionSuccess = false;
    double doubleWavelength = enteredWavelength.toDouble(&conversionSuccess);

    // add dialog box for failed conversion
    qDebug() << conversionSuccess;

    // add dialog box for wavelength not in range

    if(doubleWavelength < minWavelength || doubleWavelength > maxWavelength){
        qDebug() << "Entered wavelength not in range";
    }
    qDebug() << "Entered wavelength: " << enteredWavelength;
    startWavelength = doubleWavelength;
}

void TestSetupWindow::on_endWavLineEdit_returnPressed()
{
    // check if value entered is numeric
    QByteArray enteredWavelength = ui->endWavLineEdit->text().toLatin1();
    qDebug() << enteredWavelength;
    bool conversionSuccess = false;
    double doubleWavelength = enteredWavelength.toDouble(&conversionSuccess);

    // add dialog box for failed conversion
    qDebug() << conversionSuccess;

    // add dialog box for wavelength not in range

    if(doubleWavelength < minWavelength || doubleWavelength > maxWavelength){
        qDebug() << "Entered wavelength not in range";
    }
    qDebug() << "Entered wavelength: " << enteredWavelength;
    // value was valid
    endWavelength = doubleWavelength;
}

void TestSetupWindow::on_dwellLineEdit_returnPressed()
{
    QByteArray enteredDwell = ui->dwellLineEdit->text().toLatin1();
    bool conversionSuccess = false;
    int intDwell = enteredDwell.toInt(&conversionSuccess);

    dwell = intDwell;
}

void TestSetupWindow::on_stepSizeLineEdit_returnPressed()
{
    QByteArray enteredStepSize = ui->stepSizeLineEdit->text().toLatin1();
    bool conversionSuccess = false;
    double doubleStepSize = enteredStepSize.toDouble(&conversionSuccess);

    stepSize = doubleStepSize;

    // update calculated time
    int numberOfSteps = (endWavelength - startWavelength) / stepSize;
    double calculatedTime = dwell * numberOfSteps;
    qDebug() << "Time: " << calculatedTime;
    qDebug() << "( " << endWavelength << " - " << startWavelength << " ) / " << stepSize;
    qDebug() << dwell << " * " << numberOfSteps;
    setTime(calculatedTime);

    // activate begin test button
    ui->beginTestPB->setEnabled(true);
}

void TestSetupWindow::setTime(double calculatedTime){
    QString stringTime = QDateTime::fromTime_t(calculatedTime).toUTC().toString("hh:mm:ss");
    ui->estimatedTimeDisplay->setText(stringTime);
}

void TestSetupWindow::on_beginTestPB_clicked()
{
    // set wavelength to "start wavelength"

    QByteArray paramString = QByteArray::number(startWavelength) + "nm";
    laserSource->execWavelength(1, paramString);

    // display wavelength in box
    QByteArray currentWavelength;
    laserSource->queryWavelength(1, currentWavelength);
    qDebug() << "Current wavelength: " << currentWavelength;
    double wavelengthNm = convertSciToDouble(currentWavelength.split('\n')[0]);
    qDebug() << wavelengthNm;
    ui->currentWavDisplay->setText(QString::number(wavelengthNm));


}
