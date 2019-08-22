#include "confign7714awindow.h"
#include "ui_confign7714awindow.h"
#include <QtMath>

ConfigN7714AWindow::ConfigN7714AWindow(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigN7714AWindow)
{
    ui->setupUi(this);
    this->device = device;
}

ConfigN7714AWindow::~ConfigN7714AWindow()
{
    delete ui;
}

void ConfigN7714AWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    slotNum = 1;

    // initialize settings and signal to orchestrator to update them from device
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
    emit signalUpdateConfigSettings(device, *settings);
}

void ConfigN7714AWindow::slotUpdateWindow()
{
    qDebug() << "n7714a slotUpdateWindow()";
    // clear text entry fields
    ui->laserWavelengthEdit->clear();
    ui->laserFrequencyEdit->clear();
    ui->laserOutputPowerEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();
}

void ConfigN7714AWindow::getValuesFromConfig()
{
    qDebug() << "n7714a get values from config";
    powerSettings = settings->value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
    qDebug() << "power settings " << powerSettings;
    minPowerSettings = settings->value(N7714A_MIN_POWER).value<QList<QByteArray>>();
    qDebug() << "min power " << minPowerSettings;
    maxPowerSettings = settings->value(N7714A_MAX_POWER).value<QList<QByteArray>>();
    qDebug() << "max power " << maxPowerSettings;
    laserStates = settings->value(N7714A_LASER_STATE).value<QList<QByteArray>>();
    qDebug() << "laser state " << laserStates;

    wavelengthSettings = settings->value(N7714A_WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    qDebug() << "wavelength settings " << wavelengthSettings;
    minWavelengths = settings->value(N7714A_MIN_WAVELENGTH).value<QList<QByteArray>>();
    qDebug() << "min wavelengths " << minWavelengths;
    maxWavelengths = settings->value(N7714A_MAX_WAVELENGTH).value<QList<QByteArray>>();
    qDebug() << "max wavelengths " << maxWavelengths;

    frequencySettings = settings->value(N7714A_FREQUENCY_SETTINGS).value<QList<QByteArray>>();
    qDebug() << "frequency settings " << frequencySettings;
    minFrequencies = settings->value(N7714A_MIN_FREQUENCY).value<QList<QByteArray>>();
    qDebug() << "min frequencies " << minFrequencies;
    maxFrequencies = settings->value(N7714A_MAX_FREQUENCY).value<QList<QByteArray>>();
    qDebug() << "max frequencies " << maxFrequencies;
}

void ConfigN7714AWindow::populateAllValues()
{
    qDebug() << "n7714a populate all values()";
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

}

// ********************************************* Laser Power ****************************************************

void ConfigN7714AWindow::populateLaserOutputPowerUnit()
{
    qDebug() << "populateLaserOutputPowerUnit()";
    // update the unit display field and labels
    QByteArray unitText = ui->powerUnitComboBox->currentText().toLatin1();
    ui->powerDisplayUnitLabel->setText(unitText);
    ui->powerUnitEditLabel->setText(unitText);
    ui->minPowerDisplayUnitLabel->setText(unitText);
    ui->maxPowerDisplayUnitLabel->setText(unitText);
}

void ConfigN7714AWindow::populateLaserOutputPower()
{
    qDebug() << "populateLaserOutputPower()";
    qDebug() << powerSettings;
    qDebug() << slotNum;
    double power = powerSettings[slotNum - 1].toDouble();
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }
    ui->laserOutputPowerDisplay->setText(QByteArray::number(converted));
}

void ConfigN7714AWindow::populateLaserMinPower()
{
    qDebug() << "populateLaserMinPower()";
    qDebug() << minPowerSettings;
    double power = minPowerSettings[slotNum - 1].toDouble();
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }

    ui->laserMinPowerDisplay->setText(QByteArray::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxPower()
{
    qDebug() << "populateLaserMaxPower()";
    qDebug() << maxPowerSettings;
    double power = maxPowerSettings[slotNum - 1].toDouble();
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }
    ui->laserMaxPowerDisplay->setText(QByteArray::number(converted));
}

void ConfigN7714AWindow::populateLaserState()
{
    qDebug() << "populateLaserState()";
    ui->laserStateDisplay->setText(laserStates[slotNum - 1]);
}

// ********************************************* Laser Wavelength ****************************************************

void ConfigN7714AWindow::populateLaserWavelengthUnit()
{
    QByteArray unitText = ui->wavelengthUnitComboBox->currentText().toLatin1();
    ui->wavelengthDisplayUnitLabel->setText(unitText);
    ui->wavelengthEditUnitLabel->setText(unitText);
    ui->minWavlengthUnitLabel->setText(unitText);
    ui->maxWavelengthUnitLabel->setText(unitText);
}

void ConfigN7714AWindow::populateLaserWavelength(){
    // convert to selected unit and display
    double wavelength = wavelengthSettings[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertWavelengthFromMeter(wavelength, unit);
    ui->laserWavelengthDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMinWavelength(){
    // convert min wavelength and apply to display field
    double wavelength = minWavelengths[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertWavelengthFromMeter(wavelength, unit);
    ui->minWavelengthDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxWavelength(){
    // convert max wavelength and apply to display field
    double wavelength = minWavelengths[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertWavelengthFromMeter(wavelength, unit);
    ui->maxWavelengthDisplay->setText(QString::number(converted));
}

// ********************************************* Laser Frequency ****************************************************

void ConfigN7714AWindow::populateLaserFrequencyUnit()
{
    QByteArray unitText = ui->frequencyUnitComboBox->currentText().toLatin1();
    ui->laserFrequencyDisplayUnitLabel->setText(unitText);
    ui->frequencyEditUnitLabel->setText(unitText);
    ui->minFrequencyUnitLabel->setText(unitText);
    ui->maxFrequencyUnitLabel->setText(unitText);

}

void ConfigN7714AWindow::populateLaserFrequency(){
    // convert frequency and apply to display field
    double frequency = frequencySettings[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    ui->laserFrequencyDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMinFrequency(){
    // convert frequency and apply to display field
    double frequency = frequencySettings[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    ui->minFrequencyDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxFrequency(){
    // convert frequency and apply to display field
    double frequency = frequencySettings[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    ui->maxFrequencyDisplay->setText(QString::number(converted));
}


void ConfigN7714AWindow::setupWindow()
{
//    // display device information
//    ui->instrumentInfoLabel->setText(ui->instrumentInfoLabel->text() + device->getInstrIdentity());
//    ui->instrumentAddressLabel->setText(ui->instrumentAddressLabel->text() + device->getInstrLocation());

//    // set initial slot number
//    slotNum = 1;

//    // make sure "auto mode" is turned on for instrument
//    setupAutoMode();

//    // initialize starting exponent indices to meters and Hz
//    wavelengthExponentIndex = WAV_EXPONENT_LIST.indexOf(M_UNIT);
//    frequencyExponentIndex = FREQ_EXPONENT_LIST.indexOf(HZ_UNIT);

//    // initialize power displays on all channels/slots
//    initPowerUnits();
//    initPowerSettings();
//    initMinPower();
//    initMaxPower();

//    // initialize wavelength displays on all channels/slots
//    initWavelengthSettings();
//    initMinWavelengths();
//    initMaxWavelengths();

//    // initialize frequency displays on all channels/slots
//    initFrequencySettings();
//    initMinFrequencies();
//    initMaxFrequencies();

//    // update displayed values
//    populateAllValues();
}

void ConfigN7714AWindow::setupAutoMode(){
//    // To be able to set wavelength and frequency values on the N7714A, AUTO mode must be turned on
//    // AUTO mode can only be turned on if the laser is powered off

//    // query if auto mode is turned on
//    QByteArray response;
//    device->queryAutoWavMode(slotNum, response);
//    if(response.toInt() != 1){
//        // if auto mode is turned off, we need to make sure the laser is off
//        // then we can set AUTO mode to 'on'

//        qDebug() << "auto mode is off";

//        // get laser power status
//        QByteArray response;
//        device->queryPowerStatus(slotNum, response);


//        if(response.toInt() == 0){
//            // if laser is off, send command
//            device->turnOnAutoWavMode(slotNum);
//        }
//        else{
//            // if laser is on, turn off, send command then turn laser back on
//            device->execPowerOffModule(slotNum);
//            device->turnOnAutoWavMode(slotNum);
//            device->execPowerOnModule(slotNum);
//        }
//    }

}

void ConfigN7714AWindow::initPowerUnits()
{
//    // loop for each slot and read power unit into list
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray unit;
//        device->queryPowerUnit(i, unit);

//        if(unit.toInt() == 0){
//            powerUnits.append("dBm");
//        }
//        else{
//            powerUnits.append("Watt");
//        }
//    }
}

void ConfigN7714AWindow::initPowerSettings(){
//    // loop for each slot and get the current power setting
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray power;
//        device->queryPowerLevel(i, power);

//        double powerDouble = power.toDouble();
//        powerSettings.append(powerDouble);
//    }
}

void ConfigN7714AWindow::initPowerState(){
//    // loop for each slot and get the current power state
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray status;
//        device->queryPowerStatus(i, status);

//        if(status.toInt() == 0){
//            laserState.append("OFF");
//        }
//        else{
//            laserState.append("ON");
//        }
//    }
}

void ConfigN7714AWindow::initMinPower(){
//    // loop for each slot and get the current min power
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray minPower;
//        device->queryPowerLevel(i, minPower, "MIN");

//        double powerDouble = minPower.toDouble();
//        minPowers.append(powerDouble);
//    }
}

void ConfigN7714AWindow::initMaxPower(){
//    // loop for each slot and get the current max power
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray maxPower;
//        device->queryPowerLevel(i, maxPower, "MAX");

//        double powerDouble = maxPower.toDouble();
//        maxPowers.append(powerDouble);
//    }
}

void ConfigN7714AWindow::initWavelengthSettings(){
//    // loop for each slot and get current wavelength setting
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray wavelength;
//        device->queryWavelength(i, wavelength);

//        double wavelengthDouble = wavelength.toDouble();
//        wavelengthSettings.append(wavelengthDouble);
//    }
}

void ConfigN7714AWindow::initMinWavelengths(){
//    // loop for each slot and get min wavelengths
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray minWavelength;
//        device->queryWavelength(i, minWavelength);

//        double wavelengthDouble = minWavelength.toDouble();
//        minWavelengths.append(wavelengthDouble);
//    }
}

void ConfigN7714AWindow::initMaxWavelengths(){
//    // loop for each slot and get max wavelengths
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray maxWavelength;
//        device->queryWavelength(i, maxWavelength);

//        double wavelengthDouble = maxWavelength.toDouble();
//        maxWavelengths.append(wavelengthDouble);
//    }
}

void ConfigN7714AWindow::initFrequencySettings(){
//    // loop for each slot and get current frequency setting
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray frequency;
//        device->queryFrequency(i, frequency);

//        double frequencyDouble = frequency.toDouble();
//        frequencySettings.append(frequencyDouble);
//    }
}

void ConfigN7714AWindow::initMinFrequencies(){
//    // loop for each slot and get min frequencies
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray minFrequency;
//        device->queryFrequency(i, minFrequency, "MIN");

//        double frequencyDouble = minFrequency.toDouble();
//        minFrequencies.append(frequencyDouble);
//    }
}

void ConfigN7714AWindow::initMaxFrequencies(){
//    // loop for each slot and get max frequencies
//    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
//        QByteArray maxFrequency;
//        device->queryFrequency(i, maxFrequency, "MAX");

//        double frequencyDouble = maxFrequency.toDouble();
//        maxFrequencies.append(frequencyDouble);
//    }
}


// ********************************************* UI Slots ****************************************************

void ConfigN7714AWindow::on_powerUnitComboBox_currentIndexChanged(const QString &unit)
{
    // refresh displayed power values
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();

//    // send command to set unit
//    QByteArray unitByteArray = unit.toLatin1();
//    device->execPowerUnit(slotNum, unitByteArray);

//    // change unit display field and labels
//    ui->outputPowerUnitDisplay->setText(unit);
//    ui->powerDisplayUnitLabel->setText(unit);
//    ui->powerUnitEditLabel->setText(unit);
//    ui->minPowerDisplayUnitLabel->setText(unit);
//    ui->maxPowerDisplayUnitLabel->setText(unit);

//    // re-query display values to convert to the new unit
//    populateLaserOutputPower();
//    populateLaserMinPower();
//    populateLaserMaxPower();
}

void ConfigN7714AWindow::on_slot1RadioBtn_clicked()
{
    slotNum = 1;
    populateAllValues();
}

void ConfigN7714AWindow::on_slot2RadioBtn_clicked()
{
    slotNum = 2;
    populateAllValues();
}

void ConfigN7714AWindow::on_slot3RadioBtn_clicked()
{
    slotNum = 3;
    populateAllValues();
}

void ConfigN7714AWindow::on_slot4RadioBtn_clicked()
{
    slotNum = 4;
    populateAllValues();
}

void ConfigN7714AWindow::on_laserOutputPowerEdit_editingFinished()
{
//    // send command to set power
//    QByteArray powerLevel = ui->laserOutputPowerEdit->text().toLatin1();
//    QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
//    device->execPowerLevel(slotNum, powerLevel, unit);

//    // re-populate power level display
//    populateLaserOutputPower();
}

void ConfigN7714AWindow::on_laserWavelengthEdit_editingFinished()
{
//    // send command to set wavelength
//    QByteArray wavelength = ui->laserWavelengthEdit->text().toLatin1();
//    QByteArray unit = ui->wavelngthUnitComboBox->currentText().toLatin1();
//    device->execWavelength(slotNum, wavelength, unit);

//    // re-populate wavelength display
//    populateLaserWavelength();
}

void ConfigN7714AWindow::on_laserFrequencyEdit_editingFinished()
{
//    // send command to set frequency
//    QByteArray frequency = ui->laserFrequencyEdit->text().toLatin1();
//    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
//    device->execFrequency(slotNum, frequency, unit);

//    // re-populate frequency display
//    populateLaserFrequency();
}


void ConfigN7714AWindow::on_togglePowerButton_clicked()
{

//    if(ui->laserStateDisplay->text() == "OFF"){
//        // turn power on
//        device->execPowerOnModule(slotNum);
//    }
//    else{
//       // turn power off
//        device->execPowerOffModule(slotNum);
//    }

//    // change display
//    populateLaserState();

}

void ConfigN7714AWindow::on_wavelngthUnitComboBox_currentIndexChanged()
{
    // refresh display values
    populateLaserWavelengthUnit();
    populateLaserWavelength();
    populateLaserMinWavelength();
    populateLaserMaxWavelength();
}

void ConfigN7714AWindow::on_frequencyUnitComboBox_currentIndexChanged()
{
    // refresh display values
    populateLaserFrequencyUnit();
    populateLaserFrequency();
    populateLaserMinFrequency();
    populateLaserMaxFrequency();
}
