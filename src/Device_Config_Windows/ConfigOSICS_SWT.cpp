#include "ConfigOSICS_SWT.h"
#include "ui_ConfigOSICS_SWT.h"
#include "ConversionUtilities.h"

ConfigOSICS_SWT::ConfigOSICS_SWT(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_SWT)
{
    ui->setupUi(this);
    this->device = device;
    slotNum = 1;

    // initialize settings
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
}

ConfigOSICS_SWT::~ConfigOSICS_SWT()
{
    delete ui;
}

void ConfigOSICS_SWT::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if(!windowConfigured){
        emit signalUpdateConfigSettings(device, *settings);
    }

    if(wavelengthSetting == ""){
        QMessageBox msgBox;
        msgBox.setText("No optical input to switch module.");
        msgBox.exec();
        this->close();
    }
    else{
        windowConfigured = true;
    }




}

void ConfigOSICS_SWT::slotUpdateWindow()
{
    qDebug() << "SWT slotUpdateWindow()";
    // clear text entry fields
    ui->wavelengthEdit->clear();
    ui->frequencyEdit->clear();
    ui->powerEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigOSICS_SWT::getValuesFromConfig()
{
    qDebug() << "getValuesFromConfig() SWT";

    moduleIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    moduleLocation = settings->value(DEVICE_ADDRESS).value<QByteArray>();
    outputPowerStatus = settings->value(EXFO_OSICS_SWT_OUTPUT_STATUS).value<QByteArray>().trimmed();
    operatingMode = settings->value(EXFO_OSICS_SWT_OPMODE).value<QByteArray>().trimmed();
    activeChannel = settings->value(EXFO_OSICS_SWT_ACTIVE_CHANNEL).value<QByteArray>();
    powerSetting = settings->value(EXFO_OSICS_SWT_POWER_SETTING).value<QByteArray>();
    wavelengthSetting = settings->value(EXFO_OSICS_SWT_WAVELENGTH_SETTING).value<QByteArray>();
    frequencySetting = settings->value(EXFO_OSICS_SWT_FREQUENCY_SETTING).value<QByteArray>();

    qDebug() << "****************************************";
    qDebug() << outputPowerStatus;
    qDebug() << operatingMode;
    qDebug() << activeChannel;
    qDebug() << powerSetting;
    qDebug() << wavelengthSetting;
    qDebug() << frequencySetting;
    qDebug() << "****************************************";

}

void ConfigOSICS_SWT::populateDeviceInfo(){
    ui->instrumentInfoLabel->setText(moduleIdentity);
    ui->instrumentAddressLabel->setText(moduleLocation);
}

void ConfigOSICS_SWT::populateAllValues()
{
    qDebug() << "swt populate all values()";

    populateOperatingMode();
    populateDeviceInfo();

    // power values
    populateOutputPowerStatus();
    populatePowerUnit();
    populatePower();
    populateMinPower();
    populateMaxPower();

    // wavelength values
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();

    // frequency values
    populateFrequencyUnit();
    populateFrequency();
    populateMinFrequency();
    populateMaxFrequency();

}

void ConfigOSICS_SWT::populateOutputPowerStatus(){
    ui->outputStatusDisplay->setText(outputPowerStatus);
}

void ConfigOSICS_SWT::populateOperatingMode()
{
    if(operatingMode == "ECL"){
        ui->opModeRadioBtnFullBand->setChecked(true);
    }
    else if(operatingMode == "SWT"){
        ui->opModeRadioBtnSwitch->setChecked(true);
    }
}

void ConfigOSICS_SWT::populatePowerUnit()
{
    QByteArray unitText = ui->powerUnitComboBox->currentText().toLatin1();
    ui->powerEditUnitLabel->setText(unitText);
    ui->powerDisplayUnitLabel->setText(unitText);
    ui->minPowerDisplayUnitLabel->setText(unitText);
    ui->maxPowerDisplayUnitLabel->setText(unitText);
}

void ConfigOSICS_SWT::populatePower()
{
    if(powerSetting == "DISABLED"){
        ui->powerDisplay->setText(powerSetting);
    }
    else{
        // power is stored in dBm (output of module)
        double convertedPower = powerSetting.toDouble();
        if(ui->powerUnitComboBox->currentText() == "Watt"){
            convertedPower = ConversionUtilities::convertDBmToWatt(convertedPower);
        }
        ui->powerDisplay->setText(QByteArray::number(convertedPower));
    }

}

void ConfigOSICS_SWT::populateMinPower()
{
    // power is stored in dBm (output of module)
    double convertedPower = EXFO_OSICS_SWT_MIN_POWER_DBM.toDouble();
    if(ui->powerUnitComboBox->currentText() == "Watt"){
        convertedPower = ConversionUtilities::convertDBmToWatt(convertedPower);
    }
    ui->minPowerDisplay->setText(QByteArray::number(convertedPower));
}

void ConfigOSICS_SWT::populateMaxPower()
{
    // power is stored in dBm (output of module)
    double convertedPower = EXFO_OSICS_SWT_MAX_POWER_DBM.toDouble();
    if(ui->powerUnitComboBox->currentText() == "Watt"){
        convertedPower = ConversionUtilities::convertDBmToWatt(convertedPower);
    }
    ui->maxPowerDisplay->setText(QByteArray::number(convertedPower));
}


void ConfigOSICS_SWT::populateWavelength()
{
    ui->wavelengthDisplay->setText(QByteArray::number(wavelengthSetting.toDouble()));
}

void ConfigOSICS_SWT::populateMinWavelength()
{
    ui->minWavelengthDisplay->setText(EXFO_OSICS_SWT_MIN_WAV_NM);
}

void ConfigOSICS_SWT::populateMaxWavelength()
{
    ui->maxWavelengthDisplay->setText(EXFO_OSICS_SWT_MAX_WAV_NM);
}

void ConfigOSICS_SWT::populateFrequencyUnit()
{
    QByteArray unitText = ui->frequencyUnitComboBox->currentText().toLatin1();
    ui->frequencyDisplayUnitLabel->setText(unitText);
    ui->frequencyEditUnitLabel->setText(unitText);
    ui->minFrequencyDisplayUnitLabel->setText(unitText);
    ui->maxFrequencyDisplayUnitLabel->setText(unitText);
}

void ConfigOSICS_SWT::populateFrequency()
{
    // frequency is stored in the backend as GHz
    // convert to hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double frequencyGHz = frequencySetting.toDouble();
    double frequencyHz = ConversionUtilities::convertFrequencyToHz(frequencyGHz, "GHz");
    double convertedFrequency = ConversionUtilities::convertFrequencyFromHz(frequencyHz, unit);

    ui->frequencyDisplay->setText(QByteArray::number(convertedFrequency));
}

void ConfigOSICS_SWT::populateMinFrequency()
{
    // get min frequency by converting max wavelength

    double maxWavelengthNM = EXFO_OSICS_SWT_MAX_WAV_NM.toDouble();
    // convert to meters
    double maxWavelengthM = ConversionUtilities::convertWavelengthToMeter(maxWavelengthNM, "nm");
    double minFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(maxWavelengthM);
    // convert from Hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double minFrequencyConverted = ConversionUtilities::convertFrequencyFromHz(minFrequencyHz, unit);
    ui->minFrequencyDisplay->setText(QByteArray::number(minFrequencyConverted));

}

void ConfigOSICS_SWT::populateMaxFrequency()
{
    // get max frequency by converting min wavelength

    double minWavelengthNM = EXFO_OSICS_SWT_MIN_WAV_NM.toDouble();
    // convert to meters
    double minWavelengthM = ConversionUtilities::convertWavelengthToMeter(minWavelengthNM, "nm");
    double maxFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(minWavelengthM);
    // convert from Hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double maxFrequencyConverted = ConversionUtilities::convertFrequencyFromHz(maxFrequencyHz, unit);
    ui->maxFrequencyDisplay->setText(QByteArray::number(maxFrequencyConverted));
}

void ConfigOSICS_SWT::on_opModeRadioBtnFullBand_clicked()
{
    // show other setting displays (only available for full-band mode)
    ui->powerSettingsGroup->show();
    ui->wavelengthSettingsGroup->show();
    ui->frequencySettingsGroup->show();

    operatingMode = "ECL";
    settings->setValue(EXFO_OSICS_SWT_OPMODE, QVariant::fromValue(operatingMode));
    populateOperatingMode();
}

void ConfigOSICS_SWT::on_opModeRadioBtnSwitch_clicked()
{
    // hide other setting displays (only available for full-band mode)
    ui->powerSettingsGroup->hide();
    ui->wavelengthSettingsGroup->hide();
    ui->frequencySettingsGroup->hide();

    operatingMode = "SWT";
    settings->setValue(EXFO_OSICS_SWT_OPMODE, QVariant::fromValue(operatingMode));
    populateOperatingMode();
}


void ConfigOSICS_SWT::on_ch1Radio_clicked()
{
    activeChannel = ui->ch1Radio->text().split(' ')[1].toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch2Radio_clicked()
{
    activeChannel = ui->ch2Radio->text().split(' ')[1].toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch3Radio_clicked()
{
    activeChannel = ui->ch3Radio->text().split(' ')[1].toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch4Radio_clicked()
{
    activeChannel = ui->ch4Radio->text().split(' ')[1].toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_powerUnitComboBox_currentIndexChanged(const QString &arg1)
{
    // refresh displayed powervalues
    populateOutputPowerStatus();
    populatePowerUnit();
    populatePower();
    populateMinPower();
    populateMaxPower();
}

void ConfigOSICS_SWT::on_wavelengthUnitComboBox_currentIndexChanged(const QString &arg1)
{
    // refresh displayed wavelength values
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigOSICS_SWT::on_frequencyUnitComboBox_currentIndexChanged(const QString &arg1)
{
    // refresh displayed frequency values
    populateFrequencyUnit();
    populateFrequency();
    populateMinFrequency();
    populateMaxFrequency();
}

bool ConfigOSICS_SWT::isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue)
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
void ConfigOSICS_SWT::on_powerEdit_editingFinished()
{
    QByteArray powerValue = ui->powerEdit->text().toLatin1();
    QByteArray minPower = ui->minPowerDisplay->text().toLatin1();
    QByteArray maxPower = ui->maxPowerDisplay->text().toLatin1();

    if(isInputValueValid(powerValue, minPower, maxPower)){
        // convert to dBm if value is in Watt
        double powDouble = powerValue.toDouble();
        QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
        double converted = powDouble;
        if(unit == "Watt"){
            converted = ConversionUtilities::convertWattToDBm(powDouble);
        }
        powerSetting = QByteArray::number(converted);

        // update settings object
        settings->setValue(EXFO_OSICS_SWT_POWER_SETTING, QVariant::fromValue(powerSetting));
        qDebug() << "@@@@@@@@@ " << powerSetting;

        populatePower();
    }
}

void ConfigOSICS_SWT::on_wavelengthEdit_editingFinished()
{
    QByteArray wavelengthValue = ui->wavelengthEdit->text().toLatin1();
    QByteArray minWavelength = ui->minWavelengthDisplay->text().toLatin1();
    QByteArray maxWavelength = ui->maxWavelengthDisplay->text().toLatin1();

    if(isInputValueValid(wavelengthValue, minWavelength, maxWavelength)){
        // wavelength is valid, insert into list
        double wavDouble = wavelengthValue.toDouble();
        wavelengthSetting = QByteArray::number(wavDouble);

        // update the settings object
        settings->setValue(EXFO_OSICS_SWT_WAVELENGTH_SETTING, QVariant::fromValue(wavelengthSetting));
        populateWavelength();

        // update frequency b/c the values are related
        double frequency = ConversionUtilities::convertWavelengthToFrequency(wavDouble);
        frequencySetting = QByteArray::number(frequency);
        settings->setValue(EXFO_OSICS_SWT_FREQUENCY_SETTING, QVariant::fromValue(frequencySetting));
        populateFrequency();
    }
}

void ConfigOSICS_SWT::on_frequencyEdit_editingFinished()
{
    QByteArray frequencyValue = ui->frequencyEdit->text().toLatin1();
    QByteArray minFrequencyValue = ui->minFrequencyDisplay->text().toLatin1();
    QByteArray maxFrequencyValue = ui->maxFrequencyDisplay->text().toLatin1();

    if(isInputValueValid(frequencyValue, minFrequencyValue, maxFrequencyValue)){
        // convert frequency value to GHz to store
        double freqDouble = frequencyValue.toDouble();
        QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
        double frequencyHz = ConversionUtilities::convertFrequencyToHz(freqDouble, unit);
        double frequencyGHz = ConversionUtilities::convertFrequencyFromHz(frequencyHz, "GHz");
        frequencySetting = QByteArray::number(frequencyGHz);

        // update the settings object
        settings->setValue(EXFO_OSICS_SWT_FREQUENCY_SETTING, QVariant::fromValue(frequencySetting));
        populateFrequency();

        // update wavelength b/c the values are related
        double wavelengthM = ConversionUtilities::convertFrequencyToWavelength(frequencyHz);
        double wavelengthNM = ConversionUtilities::convertWavelengthFromMeter(wavelengthM, "nm");
        wavelengthSetting = QByteArray::number(wavelengthNM);
        settings->setValue(EXFO_OSICS_SWT_WAVELENGTH_SETTING, QVariant::fromValue(wavelengthSetting));
        populateWavelength();
    }
}

void ConfigOSICS_SWT::on_loadSettingsButton_clicked()
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

void ConfigOSICS_SWT::on_saveSettingsButton_clicked()
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

bool ConfigOSICS_SWT::loadSettings()
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

bool ConfigOSICS_SWT::saveSettings()
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

void ConfigOSICS_SWT::on_saveChangesButton_clicked()
{
    settings->sync();

    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}


void ConfigOSICS_SWT::on_toggleOutputButton_clicked()
{
    // swap output power status
    if(outputPowerStatus.toUpper() == "DISABLED"){
        outputPowerStatus = "ENABLED";
    }
    else{
        outputPowerStatus = "DISABLED";
    }

    settings->setValue(EXFO_OSICS_SWT_OUTPUT_STATUS, QVariant::fromValue(outputPowerStatus));

    populateOutputPowerStatus();
}
