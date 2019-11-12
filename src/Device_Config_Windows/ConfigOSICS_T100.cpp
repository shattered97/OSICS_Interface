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

    minPower = EXFO_OSICS_T100_MIN_POWER_DBM;
    maxPower = EXFO_OSICS_T100_MAX_POWER_DBM;

}

ConfigOSICS_T100::~ConfigOSICS_T100()
{
    delete ui;
}

void ConfigOSICS_T100::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if(!windowConfigured){
        emit signalUpdateConfigSettings(device, settings);
    }

    windowConfigured = true;

    // disable cursor (re-enabled in slotUpdateWindow)
    QApplication::setOverrideCursor(Qt::WaitCursor);

}

void ConfigOSICS_T100::slotUpdateWindow()
{
    // clear text entry fields
    ui->laserWavelengthEdit->clear();
    ui->laserFrequencyEdit->clear();
    ui->laserOutputPowerEdit->clear();

    // reset text fields
    resetDisplayFieldColoredStatus();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));

    // enable cursor
    QApplication::restoreOverrideCursor();
}

void ConfigOSICS_T100::getValuesFromConfig()
{
    moduleIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    moduleLocation = settings->value(DEVICE_ADDRESS).value<QByteArray>();
    deviceNickname = settings->value(DEVICE_NICKNAME).value<QByteArray>();
    powerSetting = settings->value(EXFO_OSICS_T100_POWER).value<QByteArray>();
    laserState = settings->value(EXFO_OSICS_T100_LASER_STATE).value<QByteArray>();
    wavelengthSetting = settings->value(EXFO_OSICS_T100_WAVELENGTH).value<QByteArray>();
    minWavelength = settings->value(EXFO_OSICS_T100_MIN_WAVELENGTH).value<QByteArray>();
    maxWavelength = settings->value(EXFO_OSICS_T100_MAX_WAVELENGTH).value<QByteArray>();
    frequencySetting = settings->value(EXFO_OSICS_T100_FREQUENCY).value<QByteArray>();
    minFrequency = settings->value(EXFO_OSICS_T100_MIN_FREQUENCY).value<QByteArray>();
    maxFrequency = settings->value(EXFO_OSICS_T100_MAX_FREQUENCY).value<QByteArray>();
}

void ConfigOSICS_T100::populateDeviceInfo(){
    ui->instrumentInfoLabel->setText(deviceNickname);
    ui->instrumentAddressLabel->setText(moduleLocation);
}

void ConfigOSICS_T100::populateAllValues()
{
    populateDeviceInfo();

    // power values
    populateLaserOutputPowerUnit();
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
    populateLaserState();

    // wavelength values
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
    if(powerSetting == "Disabled"){
        ui->laserOutputPowerDisplay->setText(powerSetting);
    }
    else{
        double convertedPower = powerSetting.toDouble();
        if(ui->powerUnitComboBox->currentText() == "Watt"){
            convertedPower = ConversionUtilities::convertDBmToWatt(convertedPower);
        }
        ui->laserOutputPowerDisplay->setText(QByteArray::number(convertedPower));
    }
}

void ConfigOSICS_T100::populateLaserMinPower(){
    double convertedMinPower = minPower.toDouble();
    if(ui->powerUnitComboBox->currentText() == "Watt"){
        convertedMinPower = ConversionUtilities::convertDBmToWatt(convertedMinPower);
    }
    ui->laserMinPowerDisplay->setText(QByteArray::number(convertedMinPower));
}

void ConfigOSICS_T100::populateLaserMaxPower(){
    double convertedMaxPower = maxPower.toDouble();
    if(ui->powerUnitComboBox->currentText() == "Watt"){
        convertedMaxPower = ConversionUtilities::convertDBmToWatt(convertedMaxPower);
    }
    ui->laserMaxPowerDisplay->setText(QByteArray::number(convertedMaxPower));
}

void ConfigOSICS_T100::populateLaserState(){
    ui->laserStateDisplay->setText(laserState.toUpper());
}

// ********************************************* Laser Wavelength ****************************************************


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
    // frequency is stored as GHz
    // convert to hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double frequencyGHz = frequencySetting.toDouble();
    double frequencyHz = ConversionUtilities::convertFrequencyToHz(frequencyGHz, "GHz");
    double convertedFrequency = ConversionUtilities::convertFrequencyFromHz(frequencyHz, unit);

    ui->laserFrequencyDisplay->setText(QByteArray::number(convertedFrequency));
}
void ConfigOSICS_T100::populateLaserMinFrequency(){
    // frequency is stored as GHz
    // convert to hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double frequencyGHz = minFrequency.toDouble();
    double frequencyHz = ConversionUtilities::convertFrequencyToHz(frequencyGHz, "GHz");
    double convertedFrequency = ConversionUtilities::convertFrequencyFromHz(frequencyHz, unit);

    ui->minFrequencyDisplay->setText(QByteArray::number(convertedFrequency));
}
void ConfigOSICS_T100::populateLaserMaxFrequency(){
    // frequency is stored as GHz
    // convert to hz
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double frequencyGHz = maxFrequency.toDouble();
    double frequencyHz = ConversionUtilities::convertFrequencyToHz(frequencyGHz, "GHz");
    double convertedFrequency = ConversionUtilities::convertFrequencyFromHz(frequencyHz, unit);

    ui->maxFrequencyDisplay->setText(QByteArray::number(convertedFrequency));
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
    ui->laserOutputPowerEdit->blockSignals(true);

    QByteArray powerValue = ui->laserOutputPowerEdit->text().toLatin1();
    QByteArray minPower = ui->laserMinPowerDisplay->text().toLatin1();
    QByteArray maxPower = ui->laserMaxPowerDisplay->text().toLatin1();

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
        settings->setValue(EXFO_OSICS_T100_POWER, QVariant::fromValue(powerSetting));
        powerSettingColored = true;
        populateLaserOutputPower();
    }

    colorDisplayFieldText();
    ui->laserOutputPowerEdit->clearFocus();
    ui->laserOutputPowerEdit->clear();
    ui->laserOutputPowerEdit->blockSignals(false);
}

void ConfigOSICS_T100::on_laserWavelengthEdit_editingFinished()
{
    ui->laserWavelengthEdit->blockSignals(true);
    QByteArray wavelengthValue = ui->laserWavelengthEdit->text().toLatin1();
    QByteArray minWavelength = ui->minWavelengthDisplay->text().toLatin1();
    QByteArray maxWavelength = ui->maxWavelengthDisplay->text().toLatin1();

    if(isInputValueValid(wavelengthValue, minWavelength, maxWavelength)){
        // update the settings object
        wavelengthSetting = wavelengthValue;
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
        wavelengthSettingColored = true;
        populateLaserWavelength();

        // update frequency b/c the values are related
        double wavelengthM = ConversionUtilities::convertWavelengthToMeter(wavelengthSetting.toDouble(), "nm");
        double frequencyHz = ConversionUtilities::convertWavelengthToFrequency(wavelengthM);
        double frequencyGHz = ConversionUtilities::convertFrequencyFromHz(frequencyHz, "GHz");

        frequencySetting = QByteArray::number(frequencyGHz);
        settings->setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequencySetting));
        frequencySettingColored = true;
        populateLaserFrequency();
    }

    colorDisplayFieldText();
    ui->laserFrequencyEdit->clearFocus();
    ui->laserFrequencyEdit->clear();
    ui->laserWavelengthEdit->blockSignals(false);
}

void ConfigOSICS_T100::on_laserFrequencyEdit_editingFinished()
{
    ui->laserFrequencyEdit->blockSignals(true);

    QByteArray frequencyValue = ui->laserFrequencyEdit->text().toLatin1();
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
        settings->setValue(EXFO_OSICS_T100_FREQUENCY, QVariant::fromValue(frequencySetting));
        // flag value for coloring
        frequencySettingColored = true;
        populateLaserFrequency();

        // update wavelength b/c the values are related
        double wavelengthM = ConversionUtilities::convertFrequencyToWavelength(frequencyHz);
        double wavelengthNm = ConversionUtilities::convertWavelengthFromMeter(wavelengthM, "nm");
        wavelengthSetting = QByteArray::number(wavelengthNm);
        settings->setValue(EXFO_OSICS_T100_WAVELENGTH, QVariant::fromValue(wavelengthSetting));
        wavelengthSettingColored = true;
        populateLaserWavelength();
    }
    colorDisplayFieldText();
    ui->laserFrequencyEdit->clearFocus();
    ui->laserFrequencyEdit->clear();
    ui->laserFrequencyEdit->blockSignals(false);
}

void ConfigOSICS_T100::on_togglePowerButton_clicked()
{
    QByteArray state = ui->laserStateDisplay->text().toLatin1().trimmed();
    qDebug() << state;
    if(state == "ENABLED"){
        // change to off
        laserState = "DISABLED";
    }
    else if(state == "DISABLED"){
       // change to on
        laserState = "ENABLED";
    }

    laserStateColored = true;
    settings->setValue(EXFO_OSICS_T100_LASER_STATE, QVariant::fromValue(laserState));
    colorDisplayFieldText();
    populateLaserState();

}

void ConfigOSICS_T100::on_saveChangesButton_clicked()
{
    // disable cursor until finished (re-enabled in slotUpdateWindow)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, settings);

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

    // disable cursor (re-enabled in slotUpdateWindow)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    emit signalApplyConfigSettings(device, settings);

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


void ConfigOSICS_T100::colorText(QLineEdit *textField, bool colored){
    if(colored){
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 255);}");
    }
    else{
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 0);}");
    }
}

void ConfigOSICS_T100::colorDisplayFieldText(){
    colorText(ui->laserOutputPowerDisplay, powerSettingColored);
    colorText(ui->laserStateDisplay, laserStateColored);
    colorText(ui->laserWavelengthDisplay, wavelengthSettingColored);
    colorText(ui->laserFrequencyDisplay, frequencySettingColored);
}

void ConfigOSICS_T100::resetDisplayFieldColoredStatus(){
    powerSettingColored = false;
    laserStateColored = false;
    wavelengthSettingColored = false;
    frequencySettingColored = false;

    colorDisplayFieldText();
}



void ConfigOSICS_T100::on_setNicknameBtn_clicked()
{
    // open dialog box with text entry field
    bool ok;
    QString nicknameText = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Enter desired nickname for device. Update will be applied when you submit device changes."),
                                                 QLineEdit::Normal, "", &ok);
    if(ok && !nicknameText.trimmed().isEmpty()){
        deviceNickname = nicknameText.toLatin1();
                        settings->setValue(DEVICE_NICKNAME, QVariant::fromValue(deviceNickname));
    }

}
