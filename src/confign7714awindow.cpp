#include "confign7714awindow.h"
#include "ui_confign7714awindow.h"
#include <QtMath>

ConfigN7714AWindow::ConfigN7714AWindow(N7714A *device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigN7714AWindow)
{
    ui->setupUi(this);

    this->device = device;

    setupWindow();
}

ConfigN7714AWindow::~ConfigN7714AWindow()
{
    delete ui;
    delete device;
}

void ConfigN7714AWindow::setupWindow()
{
    // display device information
    ui->instrumentInfoLabel->setText(ui->instrumentInfoLabel->text() + device->getInstrIdentity());
    ui->instrumentAddressLabel->setText(ui->instrumentAddressLabel->text() + device->getInstrLocation());

    // set initial slot number
    slotNum = 1;

    // make sure "auto mode" is turned on for instrument
    setupAutoMode();

    // initialize starting exponent indices to meters and Hz
    wavelengthExponentIndex = WAV_EXPONENT_LIST.indexOf(M_UNIT);
    frequencyExponentIndex = FREQ_EXPONENT_LIST.indexOf(HZ_UNIT);

    // initialize power displays on all channels/slots
    initPowerUnits();
    initPowerSettings();
    initMinPower();
    initMaxPower();

    // initialize wavelength displays on all channels/slots
    initWavelengthSettings();
    initMinWavelengths();
    initMaxWavelengths();

    // initialize frequency displays on all channels/slots
    initFrequencySettings();
    initMinFrequencies();
    initMaxFrequencies();

    // update displayed values
    populateAllValues();
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

void ConfigN7714AWindow::initPowerUnits(){
    // loop for each slot and read power unit into list
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray unit;
        device->queryPowerUnit(i, unit);

        if(unit.toInt() == 0){
            powerUnits.append("dBm");
        }
        else{
            powerUnits.append("Watt");
        }
    }
}

void ConfigN7714AWindow::initPowerSettings(){
    // loop for each slot and get the current power setting
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray power;
        device->queryPowerLevel(i, power);

        double powerDouble = power.toDouble();
        powerSettings.append(powerDouble);
    }
}

void ConfigN7714AWindow::initPowerState(){
    // loop for each slot and get the current power state
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray status;
        device->queryPowerStatus(i, status);

        if(status.toInt() == 0){
            laserState.append("OFF");
        }
        else{
            laserState.append("ON");
        }
    }
}

void ConfigN7714AWindow::initMinPower(){
    // loop for each slot and get the current min power
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray minPower;
        device->queryPowerLevel(i, minPower, "MIN");

        double powerDouble = minPower.toDouble();
        minPowers.append(powerDouble);
    }
}

void ConfigN7714AWindow::initMaxPower(){
    // loop for each slot and get the current max power
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray maxPower;
        device->queryPowerLevel(i, maxPower, "MAX");

        double powerDouble = maxPower.toDouble();
        maxPowers.append(powerDouble);
    }
}

void ConfigN7714AWindow::initWavelengthSettings(){
    // loop for each slot and get current wavelength setting
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray wavelength;
        device->queryWavelength(i, wavelength);

        double wavelengthDouble = wavelength.toDouble();
        wavelengthSettings.append(wavelengthDouble);
    }
}

void ConfigN7714AWindow::initMinWavelengths(){
    // loop for each slot and get min wavelengths
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray minWavelength;
        device->queryWavelength(i, minWavelength);

        double wavelengthDouble = minWavelength.toDouble();
        minWavelengths.append(wavelengthDouble);
    }
}

void ConfigN7714AWindow::initMaxWavelengths(){
    // loop for each slot and get max wavelengths
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray maxWavelength;
        device->queryWavelength(i, maxWavelength);

        double wavelengthDouble = maxWavelength.toDouble();
        maxWavelengths.append(wavelengthDouble);
    }
}

void ConfigN7714AWindow::initFrequencySettings(){
    // loop for each slot and get current frequency setting
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray frequency;
        device->queryFrequency(i, frequency);

        double frequencyDouble = frequency.toDouble();
        frequencySettings.append(frequencyDouble);
    }
}

void ConfigN7714AWindow::initMinFrequencies(){
    // loop for each slot and get min frequencies
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray minFrequency;
        device->queryFrequency(i, minFrequency, "MIN");

        double frequencyDouble = minFrequency.toDouble();
        minFrequencies.append(frequencyDouble);
    }
}

void ConfigN7714AWindow::initMaxFrequencies(){
    // loop for each slot and get max frequencies
    for(int i = 1; i <= N7714A_NUM_SLOTS; i++){
        QByteArray maxFrequency;
        device->queryFrequency(i, maxFrequency, "MAX");

        double frequencyDouble = maxFrequency.toDouble();
        maxFrequencies.append(frequencyDouble);
    }
}

void ConfigN7714AWindow::populateAllValues()
{
    // power values
    populateLaserOutputPowerUnit();
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
    populateLaserState();

    // wavelength values
    populateLaserWavelengthUnit();
    populateLaserWavelength();
    qDebug() << "?????";
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
    // update the unit display field and labels
    QByteArray unitText = powerUnits.at(slotNum - 1);

    ui->outputPowerUnitDisplay->setText(unitText);
    ui->powerDisplayUnitLabel->setText(unitText);
    ui->powerUnitEditLabel->setText(unitText);
    ui->minPowerDisplayUnitLabel->setText(unitText);
    ui->maxPowerDisplayUnitLabel->setText(unitText);

    // change dropdown to current unit
    int unitDropdownIndex = ui->powerUnitComboBox->findText(unitText);
    ui->powerUnitComboBox->setCurrentIndex(unitDropdownIndex);
}

void ConfigN7714AWindow::populateLaserOutputPower()
{
    // convert power to selected unit and apply to display field
    // #TODO convert
    ui->laserOutputPowerDisplay->setText(QByteArray::number(powerSettings[slotNum - 1]));
}

void ConfigN7714AWindow::populateLaserMinPower()
{
    // convert power to selected unit and apply to display field
    // #TODO convert
    ui->laserMinPowerDisplay->setText(QByteArray::number(minPowers[slotNum - 1]));
}

void ConfigN7714AWindow::populateLaserMaxPower()
{
    // convert power to selected unit and apply to display field
    // #TODO convert
    ui->laserMaxPowerDisplay->setText(QByteArray::number(maxPowers[slotNum - 1]));

}

void ConfigN7714AWindow::populateLaserState(){
    ui->laserStateDisplay->setText(laserState[slotNum - 1]);
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

}

void ConfigN7714AWindow::populateLaserWavelength(){
    // convert to selected unit and display
    double converted = convertWavelengthFromMeter(wavelengthSettings[slotNum - 1]);
    ui->laserWavelengthDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMinWavelength(){
    // convert min wavelength and apply to display field
    double converted = convertWavelengthFromMeter(minWavelengths[slotNum - 1]);
    ui->minWavelengthDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxWavelength(){
    // convert max wavelength and apply to display field
    double converted = convertWavelengthFromMeter(maxWavelengths[slotNum - 1]);
    ui->maxWavelengthDisplay->setText(QString::number(converted));
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
    // convert frequency and apply to display field
    double converted = convertFrequencyFromHz(frequencySettings[slotNum - 1]);
    ui->laserFrequencyDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMinFrequency(){
    // convert frequency and apply to display field
    double converted = convertFrequencyFromHz(minFrequencies[slotNum - 1]);
    ui->minFrequencyDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxFrequency(){
    // convert frequency and apply to display field
    double converted = convertFrequencyFromHz(maxFrequencies[slotNum - 1]);
    ui->maxFrequencyDisplay->setText(QString::number(converted));
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

double ConfigN7714AWindow::convertWavelengthFromMeter(double wavelengthInMeter){
    int exponent = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).first;
    double converted = wavelengthInMeter * qPow(10, exponent * -1);
    return converted;
}

double ConfigN7714AWindow:: convertWavelengthToMeter(double wavelengthInOtherUnit){
    int exponent = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).first;
    double converted = wavelengthInOtherUnit * qPow(10, exponent);
    return converted;
}

double ConfigN7714AWindow::convertFrequencyFromHz(double frequencyInHz){
    int exponent = FREQ_EXPONENT_LIST.at(frequencyExponentIndex).first;
    double converted = frequencyInHz * qPow(10, exponent * -1);
    return converted;
}

double ConfigN7714AWindow::convertFrequencyToHz(double frequencyInOtherUnit){
    int exponent = FREQ_EXPONENT_LIST.at(frequencyExponentIndex).first;
    double converted = frequencyInOtherUnit * qPow(10, exponent);
    return converted;
}

void ConfigN7714AWindow::on_testEdit_editingFinished()
{
    QByteArray response;
    QByteArray command = ui->testEdit->text().toLatin1();
    device->testCommand(command, response);
    qDebug() << response;
}
