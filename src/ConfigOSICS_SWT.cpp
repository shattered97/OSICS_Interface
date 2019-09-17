#include "ConfigOSICS_SWT.h"
#include "ui_ConfigOSICS_SWT.h"
#include "ConversionUtilities.h"

ConfigOSICS_SWT::ConfigOSICS_SWT(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_SWT)
{
    ui->setupUi(this);

    slotNum = 1;

    // initialize settings and signal to orchestrator to update them from device
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

    emit signalUpdateConfigSettings(device, *settings);
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
    qDebug() << "getValuesFromConfig() t100";

    operatingMode = settings->value(EXFO_OSICS_SWT_OPMODE).value<QByteArray>().trimmed();
    qDebug() << operatingMode;

    activeChannel = settings->value(EXFO_OSICS_SWT_ACTIVE_CHANNEL).value<QByteArray>();
    qDebug() << activeChannel;

    powerSetting = settings->value(EXFO_OSICS_SWT_POWER_SETTING).value<QByteArray>();
    qDebug() << powerSetting;

    wavelengthSetting = settings->value(EXFO_OSICS_SWT_WAVELENGTH_SETTING).value<QByteArray>();
    qDebug() << wavelengthSetting;

    frequencySetting = settings->value(EXFO_OSICS_SWT_FREQUENCY_SETTING).value<QByteArray>();
    qDebug() << frequencySetting;
}

void ConfigOSICS_SWT::populateAllValues()
{
    qDebug() << "swt populate all values()";

    populateOperatingMode();

    // power values
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
//    if(operatingMode == "ECL"){
//        ui->opModeRadioBtnFullBand->setChecked(true);
//    }
//    else{
//        ui->opModeRadioBtnSwitch->setChecked(true);
//    }
}

void ConfigOSICS_SWT::populatePower()
{
    // power is stored in dBm (output of module)
    double convertedPower = powerSetting.toDouble();
    if(ui->powerUnitComboBox->currentText() == "Watt"){
        convertedPower = ConversionUtilities::convertDBmToWatt(convertedPower);
    }
    ui->powerDisplay->setText(QByteArray::number(convertedPower));
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
    ui->frequencyDisplay->setText(QByteArray::number(frequencySetting.toDouble()));
}

void ConfigOSICS_SWT::populateMinFrequency()
{
    // get min frequency by converting min wavelength

    double minWavelengthNM = EXFO_OSICS_SWT_MIN_WAV_NM.toDouble();
    // convert to meters
    double minWavelengthM = ConversionUtilities::convertWavelengthToMeter(minWavelengthNM, "nm");
    double minFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(minWavelengthM);
    // convert from Hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double minFrequencyConverted = ConversionUtilities::convertFrequencyFromHz(minFrequencyHz, unit);
    ui->minFrequencyDisplay->setText(QByteArray::number(minFrequencyConverted));

}

void ConfigOSICS_SWT::populateMaxFrequency()
{
    // get max frequency by converting ax wavelength

    double maxWavelengthNM = EXFO_OSICS_SWT_MAX_WAV_NM.toDouble();
    // convert to meters
    double maxWavelengthM = ConversionUtilities::convertWavelengthToMeter(maxWavelengthNM, "nm");
    double maxFrequencyHz = ConversionUtilities::convertWavelengthToFrequency(maxWavelengthM);
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
    activeChannel = ui->ch1Radio->text().toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch2Radio_clicked()
{
    activeChannel = ui->ch1Radio->text().toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch3Radio_clicked()
{
    activeChannel = ui->ch1Radio->text().toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_ch4Radio_clicked()
{
    activeChannel = ui->ch1Radio->text().toLatin1();
    settings->setValue(EXFO_OSICS_SWT_ACTIVE_CHANNEL, QVariant::fromValue(activeChannel));
}

void ConfigOSICS_SWT::on_powerUnitComboBox_currentIndexChanged(const QString &arg1)
{
    // refresh displayed powervalues
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
        double powDouble = powerSetting.toDouble();
        QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
        double converted = powDouble;
        if(unit == "Watt"){
            converted = ConversionUtilities::convertWattToDBm(powDouble);
        }
        powerSetting = QByteArray::number(converted);

        // update settings object
        settings->setValue(EXFO_OSICS_T100_POWER, QVariant::fromValue(powerSetting));
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
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
        populateWavelength();

        // update frequency b/c the values are related
        double frequency = ConversionUtilities::convertWavelengthToFrequency(wavDouble);
        frequencySetting = QByteArray::number(frequency);
        settings->setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequencySetting));
        populateFrequency();
    }
}

void ConfigOSICS_SWT::on_frequencyEdit_editingFinished()
{
    QByteArray frequencyValue = ui->frequencyEdit->text().toLatin1();
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
        populateFrequency();

        // update wavelength b/c the values are related
        double wavelength = ConversionUtilities::convertFrequencyToWavelength(converted);
        wavelengthSetting = QByteArray::number(wavelength);
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
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
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}

