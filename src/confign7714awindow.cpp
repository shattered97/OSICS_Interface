#include "confign7714awindow.h"
#include "ui_confign7714awindow.h"
#include <QtMath>

ConfigN7714AWindow::ConfigN7714AWindow(Orchestrator &orchestrator, N7714A *device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigN7714AWindow)
{
    ui->setupUi(this);

    // set device info
    this->device = device;
    ui->instrumentInfoLabel->setText(ui->instrumentInfoLabel->text() + device->getInstrIdentity());
    ui->instrumentAddressLabel->setText(ui->instrumentAddressLabel->text() + device->getInstrLocation());

    // set initial slot number
    slotNum = 1;

    // set power unit field to -1
    ui->powerUnitComboBox->setCurrentIndex(-1);

    // make sure "auto mode" is turned on for instrument
    setupAutoMode();

    populateAllValues();

}

ConfigN7714AWindow::~ConfigN7714AWindow()
{
    delete ui;
    delete device;
}

void ConfigN7714AWindow::setupAutoMode(){
    // To be able to set wavelength and frequency values on the N7714A, AUTO mode must be turned on
    // AUTO mode can only be turned on if the laser is powered off

    // query if auto mode is turned on
    QByteArray response;
    device->queryAutoWavMode(slotNum, response);
    if(response.toInt() != 1){
        // if auto mode is turned off, we need to make sure the laser is off
        // then we can set AUTO mode to 'on'

        qDebug() << "auto mode is off";

        // get laser power status
        QByteArray response;
        device->queryPowerStatus(slotNum, response);


        if(response.toInt() == 0){
            // if laser is off, send command
            device->turnOnAutoWavMode(slotNum);
        }
        else{
            // if laser is on, turn off, send command then turn laser back on
            device->execPowerOffModule(slotNum);
            device->turnOnAutoWavMode(slotNum);
            device->execPowerOnModule(slotNum);
        }
    }

}

void ConfigN7714AWindow::populateAllValues(){

    // disable cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // power values
    populateLaserOutputPowerUnit();
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
    populateLaserState();

    // wavelength values
    populateLaserWavelengthUnit();
    populateLaserWavelength();
    populateLaserMinWavelength();
    populateLaserMaxWavelength();

    // frequency values
    populateLaserFrequencyUnit();
    populateLaserFrequency();
    populateLaserMinFrequency();
    populateLaserMaxFrequency();

    QApplication::restoreOverrideCursor();
}

// ********************************************* Laser Power ****************************************************

void ConfigN7714AWindow::populateLaserOutputPowerUnit(){

    QByteArray response;
    device->queryPowerUnit(slotNum, response);
    QByteArray value = response.split('\n')[0];

    if(value.toInt() == 0){
        ui->outputPowerUnitDisplay->setText("dBm");
        int index = ui->powerUnitComboBox->findText("dBm");
        ui->powerUnitComboBox->setCurrentIndex(index);
    }
    else{
        ui->outputPowerUnitDisplay->setText("Watt");
        int index = ui->powerUnitComboBox->findText("Watt");
        ui->powerUnitComboBox->setCurrentIndex(index);
    }
}

void ConfigN7714AWindow::populateLaserOutputPower(){
    QByteArray response;
    device->queryPowerLevel(slotNum, response);
    QByteArray value = response.split('\n')[0];

    double valueDouble = value.toDouble();
    ui->laserOutputPowerDisplay->setText(QByteArray::number(valueDouble));
}

void ConfigN7714AWindow::populateLaserMinPower(){
    QByteArray response;
    device->queryPowerLevel(slotNum, response, "MIN");

    QByteArray value = response.split('\n')[0];

    double valueDouble = value.toDouble();
    ui->laserMinPowerDisplay->setText(QByteArray::number(valueDouble));
}

void ConfigN7714AWindow::populateLaserMaxPower(){
    QByteArray response;
    device->queryPowerLevel(slotNum, response, "MAX");

    QByteArray value = response.split('\n')[0];
    double valueDouble = value.toDouble();
    ui->laserMaxPowerDisplay->setText(QByteArray::number(valueDouble));

}

void ConfigN7714AWindow::populateLaserState(){
    QByteArray response;
    device->queryPowerStatus(slotNum, response);

    QByteArray value = response.split('\n')[0];
    if(value.toInt() == 0){
        ui->laserStateDisplay->setText("OFF");
    }
    else{
        ui->laserStateDisplay->setText("ON");
    }

}


// ********************************************* Laser Wavelength ****************************************************

void ConfigN7714AWindow::populateLaserWavelengthUnit(){
    // the N7714A does not have a configurable wavelength unit
    // you can enter wavelength with a unit (pm | nm |um | mm | m)
    // but you can only read wavelength as meters
    // we need to read wavelength then convert from meters to the currently selected unit

    bool success = false;
    QByteArray unit = ui->wavelngthUnitComboBox->currentText().toLatin1();

    ui->laserWavelengthUnitDisplay->setText(unit);

    for(int i = 0; i < WAV_EXPONENT_LIST.size(); i++){
        QByteArray current = WAV_EXPONENT_LIST.at(i).second;
        if (WAV_EXPONENT_LIST.at(i).second == unit){
            wavelengthExponentIndex = i;
            success = true;
        }
    }

    // change wavelength unit labels
    unit = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).second;

    ui->wavelengthDisplayUnitLabel->setText(unit);
    ui->wavelengthEditUnitLabel->setText(unit);
    ui->minWavlengthUnitLabel->setText(unit);
    ui->maxWavelengthUnitLabel->setText(unit);

    QByteArray testWavelength = "1520";
    convertWavelengthToMeter(testWavelength);

}

void ConfigN7714AWindow::populateLaserWavelength(){
    QByteArray response;
    device->queryWavelength(slotNum, response);
    qDebug() << response;
    QByteArray value = response.split('\n')[0];


    convertWavelengthFromMeter(value);

    double valueDouble = value.toDouble();

    ui->laserWavelengthDisplay->setText(QString::number(valueDouble));

}

void ConfigN7714AWindow::populateLaserMinWavelength(){
    QByteArray response;
    device->queryWavelength(slotNum, response, "MIN");

    QByteArray value = response.split('\n')[0];

    convertWavelengthFromMeter(value);

    double valueDouble = value.toDouble();


    ui->minWavelengthDisplay->setText(QString::number(valueDouble));

}

void ConfigN7714AWindow::populateLaserMaxWavelength(){
    QByteArray response;
    device->queryWavelength(slotNum, response, "MAX");

    QByteArray value = response.split('\n')[0];

    convertWavelengthFromMeter(value);

    double valueDouble = value.toDouble();

    ui->maxWavelengthDisplay->setText(QString::number(valueDouble));

}


// ********************************************* Laser Frequency ****************************************************

void ConfigN7714AWindow::populateLaserFrequencyUnit(){
    // the N7714A does not have a configurable frequency unit
    // you can enter frequency with a unit
    // but you can only read frequency as Hz

    bool success = false;
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();

    ui->laserFrequencyUnitDisplay->setText(unit);

    for(int i = 0; i < FREQ_EXPONENT_LIST.size(); i++){
        QByteArray current = FREQ_EXPONENT_LIST.at(i).second;
        if (FREQ_EXPONENT_LIST.at(i).second == unit){
            frequencyExponentIndex = i;
            success = true;
        }
    }

    // change frequency unit labels
    unit = FREQ_EXPONENT_LIST.at(frequencyExponentIndex).second;

    ui->laserFrequencyDisplayUnitLabel->setText(unit);
    ui->frequencyEditUnitLabel->setText(unit);
    ui->minFrequencyUnitLabel->setText(unit);
    ui->maxFrequencyUnitLabel->setText(unit);

}

void ConfigN7714AWindow::populateLaserFrequency(){
    QByteArray response;
    device->queryFrequency(slotNum, response);

    QByteArray value = response.split('\n')[0];
    convertFrequencyFromHz(value);
    double valueDouble = value.toDouble();

    ui->laserFrequencyDisplay->setText(QString::number(valueDouble));

}

void ConfigN7714AWindow::populateLaserMinFrequency(){
    QByteArray response;
    device->queryFrequency(slotNum, response, "MIN");

    QByteArray value = response.split('\n')[0];

    convertFrequencyFromHz(value);
    double valueDouble = value.toDouble();

    ui->minFrequencyDisplay->setText(QString::number(valueDouble));

}

void ConfigN7714AWindow::populateLaserMaxFrequency(){
    QByteArray response;
    device->queryFrequency(slotNum, response, "MAX");

    QByteArray value = response.split('\n')[0];
    convertFrequencyFromHz(value);
    double valueDouble = value.toDouble();

    ui->maxFrequencyDisplay->setText(QString::number(valueDouble));

}


// ********************************************* UI Slots ****************************************************

void ConfigN7714AWindow::on_powerUnitComboBox_currentIndexChanged(const QString &unit)
{
    // send command to set unit
    QByteArray unitByteArray = unit.toLatin1();
    device->execPowerUnit(slotNum, unitByteArray);

    // change unit display field and labels
    ui->outputPowerUnitDisplay->setText(unit);
    ui->powerDisplayUnitLabel->setText(unit);
    ui->powerUnitEditLabel->setText(unit);
    ui->minPowerDisplayUnitLabel->setText(unit);
    ui->maxPowerDisplayUnitLabel->setText(unit);

    // re-query display values to convert to the new unit
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
}

void ConfigN7714AWindow::on_slot1RadioBtn_clicked()
{
    // set the current slot number
    slotNum = 1;
    setupAutoMode();
    populateAllValues();
}

void ConfigN7714AWindow::on_slot2RadioBtn_clicked()
{
    // set the current slot number
    slotNum = 2;
    setupAutoMode();
    populateAllValues();
}

void ConfigN7714AWindow::on_slot3RadioBtn_clicked()
{
    // set the current slot number
    slotNum = 3;
    setupAutoMode();
    populateAllValues();
}

void ConfigN7714AWindow::on_slot4RadioBtn_clicked()
{
    // set the current slot number
    slotNum = 4;
    setupAutoMode();
    populateAllValues();
}

void ConfigN7714AWindow::on_laserOutputPowerEdit_editingFinished()
{
    // send command to set power
    QByteArray powerLevel = ui->laserOutputPowerEdit->text().toLatin1();
    QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
    device->execPowerLevel(slotNum, powerLevel, unit);

    // re-populate power level display
    populateLaserOutputPower();
}

void ConfigN7714AWindow::on_laserWavelengthEdit_editingFinished()
{
    // send command to set wavelength
    QByteArray wavelength = ui->laserWavelengthEdit->text().toLatin1();
    QByteArray unit = ui->wavelngthUnitComboBox->currentText().toLatin1();
    device->execWavelength(slotNum, wavelength, unit);

    // re-populate wavelength display
    populateLaserWavelength();
}

void ConfigN7714AWindow::on_laserFrequencyEdit_editingFinished()
{
    // send command to set frequency
    QByteArray frequency = ui->laserFrequencyEdit->text().toLatin1();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    device->execFrequency(slotNum, frequency, unit);

    // re-populate frequency display
    populateLaserFrequency();
}


void ConfigN7714AWindow::on_togglePowerButton_clicked()
{

    if(ui->laserStateDisplay->text() == "OFF"){
        // turn power on
        device->execPowerOnModule(slotNum);
    }
    else{
       // turn power off
        device->execPowerOffModule(slotNum);
    }

    // change display
    populateLaserState();

}

void ConfigN7714AWindow::on_wavelngthUnitComboBox_currentIndexChanged()
{
    populateLaserWavelengthUnit();

    // re-populate values to convert values based on unit
    populateLaserWavelength();
    populateLaserMinWavelength();
    populateLaserMaxWavelength();


}

void ConfigN7714AWindow::on_frequencyUnitComboBox_currentIndexChanged()
{
    populateLaserFrequencyUnit();

    // re-populate values to convert values based on unit
    populateLaserFrequency();
    populateLaserMinFrequency();
    populateLaserMaxFrequency();
}

void ConfigN7714AWindow::convertWavelengthFromMeter(QByteArray &wavelengthInMeter){
    double meters = wavelengthInMeter.toDouble();
    int exponent = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).first;
    double converted = meters * qPow(10, exponent * -1);
    wavelengthInMeter = QByteArray::number(converted);
}

void ConfigN7714AWindow:: convertWavelengthToMeter(QByteArray &wavelengthInOtherUnit){
    double otherUnit = wavelengthInOtherUnit.toDouble();
    int exponent = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).first;
    double converted = otherUnit * qPow(10, exponent);
    wavelengthInOtherUnit = QByteArray::number(converted);
}

void ConfigN7714AWindow::convertFrequencyFromHz(QByteArray &frequencyInHz){
    double hz = frequencyInHz.toDouble();
    int exponent = FREQ_EXPONENT_LIST.at(frequencyExponentIndex).first;
    double converted = hz * qPow(10, exponent * -1);
    frequencyInHz = QByteArray::number(converted);
}

void ConfigN7714AWindow::convertFrequencyToHz(QByteArray &frequencyInOtherUnit){
    double otherUnit = frequencyInOtherUnit.toDouble();
    int exponent = FREQ_EXPONENT_LIST.at(frequencyExponentIndex).first;
    double converted = otherUnit * qPow(10, exponent);
    frequencyInOtherUnit = QByteArray::number(converted);
}

void ConfigN7714AWindow::on_testEdit_editingFinished()
{
    QByteArray response;
    QByteArray command = ui->testEdit->text().toLatin1();
    device->testCommand(command, response);
    qDebug() << response.split('\n')[0];
}
