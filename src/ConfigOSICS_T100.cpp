#include "ConfigOSICS_T100.h"
#include "ui_ConfigOSICS_T100.h"
#include "ConversionUtilities.h"
ConfigOSICS_T100::ConfigOSICS_T100(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_T100)
{
    ui->setupUi(this);
    this->device = device;

    slotNum = 1;

    // initialize settings and signal to orchestrator to update them from device
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    qDebug() << "CREATING T100 CONFIG WINDOW *******************************************";

}

ConfigOSICS_T100::~ConfigOSICS_T100()
{
    delete ui;
}

void ConfigOSICS_T100::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    emit signalUpdateConfigSettings(device, *settings);
}

void ConfigOSICS_T100::slotUpdateWindow()
{
    qDebug() << "t100 slotUpdateWindow()";
    // clear text entry fields
    ui->laserWavelengthEdit->clear();
    ui->laserFrequencyEdit->clear();
    ui->laserOutputPowerEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigOSICS_T100::getValuesFromConfig()
{
    qDebug() << "getValuesFromConfig() t100";
    powerSetting = settings->value(EXFO_OSICS_T100_POWER).value<QByteArray>();
    qDebug() << powerSetting;
    minPower = settings->value(EXFO_OSICS_T100_MIN_POWER).value<QByteArray>();
    qDebug() << minPower;
    maxPower = settings->value(EXFO_OSICS_T100_MAX_POWER).value<QByteArray>();
    qDebug() << maxPower;
    laserState = settings->value(EXFO_OSICS_T100_LASER_STATE).value<QByteArray>();
    qDebug() << laserState;

    wavelengthSetting = settings->value(EXFO_OSICS_T100_WAVELENGTH).value<QByteArray>();
    qDebug() << wavelengthSetting;
    minWavelength = settings->value(EXFO_OSICS_T100_MIN_WAVELENGTH).value<QByteArray>();
    qDebug() << minWavelength;
    maxWavelength = settings->value(EXFO_OSICS_T100_MAX_WAVELENGTH).value<QByteArray>();
    qDebug() << maxWavelength;

    frequencySetting = settings->value(EXFO_OSICS_T100_FREQUENCY).value<QByteArray>();
    qDebug() << frequencySetting;
    minFrequency = settings->value(EXFO_OSICS_T100_MIN_FREQUENCY).value<QByteArray>();
    qDebug() << minFrequency;
    maxFrequency = settings->value(EXFO_OSICS_T100_MAX_FREQUENCY).value<QByteArray>();
    qDebug() << maxFrequency;
}


void ConfigOSICS_T100::populateAllValues()
{
    qDebug() << "t100 populate all values()";
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

void ConfigOSICS_T100::populateLaserOutputPowerUnit(){
    QByteArray unitText = ui->powerUnitComboBox->currentText().toLatin1();
    ui->powerDisplayUnitLabel->setText(unitText);
    ui->powerUnitEditLabel->setText(unitText);
    ui->minPowerDisplayUnitLabel->setText(unitText);
    ui->maxPowerDisplayUnitLabel->setText(unitText);
}

void ConfigOSICS_T100::populateLaserOutputPower(){
    ui->laserOutputPowerDisplay->setText(QByteArray::number(powerSetting.toDouble()));
}

void ConfigOSICS_T100::populateLaserMinPower(){
    ui->laserMinPowerDisplay->setText(QByteArray::number(minPower.toDouble()));
}

void ConfigOSICS_T100::populateLaserMaxPower(){
    ui->laserMaxPowerDisplay->setText(QByteArray::number(maxPower.toDouble()));
}

void ConfigOSICS_T100::populateLaserState(){
    qDebug() << laserState;
    ui->laserStateDisplay->setText(laserState);
}

// ********************************************* Laser Wavelength ****************************************************


void ConfigOSICS_T100::populateLaserWavelengthUnit(){
    QByteArray unitText = ui->wavelengthUnitComboBox->currentText().toLatin1();
    ui->wavelengthDisplayUnitLabel->setText(unitText);
    ui->wavelengthEditUnitLabel->setText(unitText);
    ui->minWavlengthUnitLabel->setText(unitText);
    ui->maxWavelengthUnitLabel->setText(unitText);
}
void ConfigOSICS_T100::populateLaserWavelength(){
    ui->laserWavelengthDisplay->setText(QByteArray::number(wavelengthSetting.toDouble()));
}
void ConfigOSICS_T100::populateLaserMinWavelength(){
    ui->minWavelengthDisplay->setText(QByteArray::number(minWavelength.toDouble()));
}
void ConfigOSICS_T100::populateLaserMaxWavelength(){
    ui->maxWavelengthDisplay->setText(QByteArray::number(maxWavelength.toDouble()));
}

// ********************************************* Laser Frequency ****************************************************

void ConfigOSICS_T100::populateLaserFrequencyUnit(){
    QByteArray unitText = ui->frequencyUnitComboBox->currentText().toLatin1();
    ui->laserFrequencyDisplayUnitLabel->setText(unitText);
    ui->frequencyEditUnitLabel->setText(unitText);
    ui->minFrequencyUnitLabel->setText(unitText);
    ui->maxFrequencyUnitLabel->setText(unitText);
}
void ConfigOSICS_T100::populateLaserFrequency(){
    ui->laserFrequencyDisplay->setText(QByteArray::number(frequencySetting.toDouble()));
}
void ConfigOSICS_T100::populateLaserMinFrequency(){
    ui->minFrequencyDisplay->setText(QByteArray::number(minFrequency.toDouble()));
}
void ConfigOSICS_T100::populateLaserMaxFrequency(){
    ui->maxFrequencyDisplay->setText(QByteArray::number(maxFrequency.toDouble()));
}

// ********************************************* UI Slots ****************************************************


void ConfigOSICS_T100::on_powerUnitComboBox_currentIndexChanged(int index)
{
    // refresh displayed power values
    populateLaserOutputPowerUnit();
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
}

void ConfigOSICS_T100::on_wavelengthUnitComboBox_currentIndexChanged(int index)
{
    // refresh displayed wavelength values
    populateLaserWavelengthUnit();
    populateLaserWavelength();
    populateLaserMinWavelength();
    populateLaserMaxWavelength();
}

void ConfigOSICS_T100::on_frequencyUnitComboBox_currentIndexChanged(int index)
{
    // refresh displayed frequency values
    populateLaserFrequencyUnit();
    populateLaserFrequency();
    populateLaserMinFrequency();
    populateLaserMaxFrequency();
}

bool ConfigOSICS_T100::isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue)
{
    bool valid = true;

    if(inputValue == ""){
        valid = false;
    }
    else{
        bool conversionOk = true;
        double valueToDouble = inputValue.toDouble(&conversionOk);

        if(!conversionOk){
            valid = false;
            QMessageBox msgBox;
            msgBox.setText("Value entered is invalid (non-numeric).");
            msgBox.exec();
        }
        else{
            double minValToDouble = minValue.toDouble();
            double maxValToDouble = maxValue.toDouble();

            if(valueToDouble < minValToDouble || valueToDouble > maxValToDouble){
                valid = false;
                QMessageBox msgBox;
                msgBox.setText("Value entered is invalid (out of min/max range).");
                msgBox.exec();
            }
        }
    }
    return valid;
}

void ConfigOSICS_T100::on_laserOutputPowerEdit_editingFinished()
{
    QByteArray powerValue = ui->laserOutputPowerEdit->text().toLatin1();
    QByteArray minPower = ui->laserMinPowerDisplay->text().toLatin1();
    QByteArray maxPower = ui->laserMaxPowerDisplay->text().toLatin1();

    if(isInputValueValid(powerValue, minPower, maxPower)){
        // convert to dBm if value is in Watt
        double powDouble = powerSetting.toDouble();
        QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
        double converted = powDouble;
        if(unit == "Watt"){
            converted = ConversionUtilities::convertWattToDBm(powDouble);
        }
        powerSetting = QByteArray::number(converted);

        // update settings object
        settings->setValue(EXFO_OSICS_T100_POWER, QVariant::fromValue(powerSetting));
        populateLaserOutputPower();
    }
}

void ConfigOSICS_T100::on_laserWavelengthEdit_editingFinished()
{
    QByteArray wavelengthValue = ui->laserWavelengthEdit->text().toLatin1();
    QByteArray minWavelength = ui->minWavelengthDisplay->text().toLatin1();
    QByteArray maxWavelength = ui->maxWavelengthDisplay->text().toLatin1();

    if(isInputValueValid(wavelengthValue, minWavelength, maxWavelength)){
        // wavelength is valid, insert into list
        double wavDouble = wavelengthValue.toDouble();
        QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
        double converted = ConversionUtilities::convertWavelengthToMeter(wavDouble, unit);
        wavelengthSetting = QByteArray::number(converted);

        // update the settings object
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
        populateLaserWavelength();

        // update frequency b/c the values are related
        double frequency = ConversionUtilities::convertWavelengthToFrequency(converted);
        frequencySetting = QByteArray::number(frequency);
        settings->setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequencySetting));
        populateLaserFrequency();
    }
}

void ConfigOSICS_T100::on_laserFrequencyEdit_editingFinished()
{
    QByteArray frequencyValue = ui->laserFrequencyEdit->text().toLatin1();
    QByteArray minFrequencyValue = ui->minFrequencyDisplay->text().toLatin1();
    QByteArray maxFrequencyValue = ui->maxFrequencyDisplay->text().toLatin1();

    if(isInputValueValid(frequencyValue, minFrequencyValue, maxFrequencyValue)){
        // frequency is valid, insert into list
        double freqDouble = frequencyValue.toDouble();
        QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
        double converted = ConversionUtilities::convertFrequencyToHz(freqDouble, unit);
        frequencySetting = QByteArray::number(converted);

        // update the settings object
        settings->setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequencySetting));
        populateLaserFrequency();

        // update wavelength b/c the values are related
        double wavelength = ConversionUtilities::convertFrequencyToWavelength(converted);
        wavelengthSetting = QByteArray::number(wavelength);
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
        populateLaserWavelength();

    }
}

void ConfigOSICS_T100::on_togglePowerButton_clicked()
{
    QByteArray state = ui->laserStateDisplay->text().toLatin1();
    if(state == "Enabled"){
        // change to off
        laserState = "Disabled";
    }
    else if(state == "Disabled"){
       // change to on
        laserState = "Enabled";
    }

    settings->setValue(EXFO_OSICS_T100_LASER_STATE, QVariant::fromValue(laserState));
    populateLaserState();

}

void ConfigOSICS_T100::on_saveChangesButton_clicked()
{
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}

bool ConfigOSICS_T100::loadSettings()
{
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    QStringList keys = settingsFromFile.allKeys();
    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
    {
        settings->setValue( *i, settingsFromFile.value( *i ) );
    }

    settings->sync();

    emit signalApplyConfigSettings(device, *settings);

    return true;
}

bool ConfigOSICS_T100::saveSettings()
{
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    QStringList keys = settings->allKeys();
    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
    {
        settingsFromFile.setValue( *i, settings->value( *i ) );
    }

    settingsFromFile.sync();
    return true;
}

void ConfigOSICS_T100::on_loadSettingsButton_clicked()
{
    qDebug() << "on_loadSettingsButton_pressed()";
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Settings File"), "",
            tr("Settings (*.ini);;All Files (*)"));

    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite)){
            QMessageBox::information(this, tr("Can't open file"), file.errorString());
        }
        else{
            settingsFileName = file.fileName();

            file.close();
            loadSettings();
        }
    }
}

void ConfigOSICS_T100::on_saveSettingsButton_clicked()
{
    qDebug() << "on_saveSettingsButton_pressed()";
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Settings File"), "",
            tr("Settings (*.ini);;All Files (*)"));

    if (!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite)){
            QMessageBox::information(this, tr("Can't open file"), file.errorString());
        }
        else{
            settingsFileName = file.fileName();

            file.close();
            saveSettings();
        }
    }
}



