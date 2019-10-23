#include "confign7714awindow.h"
#include "ui_confign7714awindow.h"

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

    // reset text fields
    resetDisplayFieldColoredStatus();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigN7714AWindow::getValuesFromConfig()
{
    powerSettings = settings->value(N7714A_POWER_SETTINGS).value<QList<QByteArray>>();
    minPowerSettings = settings->value(N7714A_MIN_POWER).value<QList<QByteArray>>();
    maxPowerSettings = settings->value(N7714A_MAX_POWER).value<QList<QByteArray>>();
    laserStates = settings->value(N7714A_LASER_STATE).value<QList<QByteArray>>();

    wavelengthSettings = settings->value(N7714A_WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    minWavelengths = settings->value(N7714A_MIN_WAVELENGTH).value<QList<QByteArray>>();
    maxWavelengths = settings->value(N7714A_MAX_WAVELENGTH).value<QList<QByteArray>>();

    frequencySettings = settings->value(N7714A_FREQUENCY_SETTINGS).value<QList<QByteArray>>();
    minFrequencies = settings->value(N7714A_MIN_FREQUENCY).value<QList<QByteArray>>();
    maxFrequencies = settings->value(N7714A_MAX_FREQUENCY).value<QList<QByteArray>>();
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

void ConfigN7714AWindow::convertAndDisplayPower(QList<QByteArray> powerList, QLineEdit* displayField){
    double power = powerList[slotNum - 1].toDouble();
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }
    displayField->setText(QByteArray::number(converted));
}

void ConfigN7714AWindow::populateLaserOutputPower()
{
    qDebug() << "populateLaserOutputPower()";
    convertAndDisplayPower(powerSettings, ui->laserOutputPowerDisplay);
}

void ConfigN7714AWindow::populateLaserMinPower()
{
    qDebug() << "populateLaserMinPower()";
    convertAndDisplayPower(minPowerSettings, ui->laserMinPowerDisplay);
}

void ConfigN7714AWindow::populateLaserMaxPower()
{
    qDebug() << "populateLaserMaxPower()";
    convertAndDisplayPower(maxPowerSettings, ui->laserMaxPowerDisplay);
}

void ConfigN7714AWindow::populateLaserState()
{
    qDebug() << "populateLaserState()";

    int state = laserStates[slotNum - 1].toInt();
    if(!state){
        ui->laserStateDisplay->setText("OFF");
    }
    else{
        ui->laserStateDisplay->setText("ON");
    }
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

void ConfigN7714AWindow::convertAndDisplayWavelength(QList<QByteArray> wavelengthList, QLineEdit* displayField){
    double wavelength = wavelengthList[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertWavelengthFromMeter(wavelength, unit);
    displayField->setText(QByteArray::number(converted));
}

void ConfigN7714AWindow::populateLaserWavelength(){
    // convert to selected unit and display
    convertAndDisplayWavelength(wavelengthSettings, ui->laserWavelengthDisplay);
}

void ConfigN7714AWindow::populateLaserMinWavelength(){
    // convert min wavelength and apply to display field
    convertAndDisplayWavelength(minWavelengths, ui->minWavelengthDisplay);
}

void ConfigN7714AWindow::populateLaserMaxWavelength(){
    // convert max wavelength and apply to display field
    convertAndDisplayWavelength(maxWavelengths, ui->maxWavelengthDisplay);
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

void ConfigN7714AWindow::convertAndDisplayFrequency(QList<QByteArray> frequencyList, QLineEdit *displayField){
    double frequency = frequencyList[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    displayField->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserFrequency(){
    // convert frequency and apply to display field
    convertAndDisplayFrequency(frequencySettings, ui->laserFrequencyDisplay);
}

void ConfigN7714AWindow::populateLaserMinFrequency(){
    // convert frequency and apply to display field
    convertAndDisplayFrequency(minFrequencies, ui->minFrequencyDisplay);
}

void ConfigN7714AWindow::populateLaserMaxFrequency(){
    // convert frequency and apply to display field
    convertAndDisplayFrequency(maxFrequencies, ui->maxFrequencyDisplay);
}

// ********************************************* UI Slots ****************************************************

void ConfigN7714AWindow::on_powerUnitComboBox_currentIndexChanged(const QString &unit)
{
    // refresh displayed power values
    populateLaserOutputPowerUnit();
    populateLaserOutputPower();
    populateLaserMinPower();
    populateLaserMaxPower();
}

void ConfigN7714AWindow::on_wavelengthUnitComboBox_currentIndexChanged()
{
    // refresh displayed wavelength values
    populateLaserWavelengthUnit();
    populateLaserWavelength();
    populateLaserMinWavelength();
    populateLaserMaxWavelength();
}

void ConfigN7714AWindow::on_frequencyUnitComboBox_currentIndexChanged()
{
    // refresh displayed frequency values
    populateLaserFrequencyUnit();
    populateLaserFrequency();
    populateLaserMinFrequency();
    populateLaserMaxFrequency();
}

void ConfigN7714AWindow::on_slot1RadioBtn_clicked()
{
    slotNum = 1;
    populateAllValues();
    colorDisplayFieldText();
}

void ConfigN7714AWindow::on_slot2RadioBtn_clicked()
{
    slotNum = 2;
    populateAllValues();
    colorDisplayFieldText();
}

void ConfigN7714AWindow::on_slot3RadioBtn_clicked()
{
    slotNum = 3;
    populateAllValues();
    colorDisplayFieldText();
}

void ConfigN7714AWindow::on_slot4RadioBtn_clicked()
{
    slotNum = 4;
    populateAllValues();
    colorDisplayFieldText();
}

bool ConfigN7714AWindow::isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue)
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

void ConfigN7714AWindow::on_laserOutputPowerEdit_editingFinished()
{
    qDebug() << "on_laserOutputPowerEdit_editingFinished()";

    QByteArray powerValue = ui->laserOutputPowerEdit->text().toLatin1();
    QByteArray minPower = ui->laserMinPowerDisplay->text().toLatin1();
    QByteArray maxPower = ui->laserMaxPowerDisplay->text().toLatin1();

    if(isInputValueValid(powerValue, minPower, maxPower)){
        // power is valid, insert into list
        double powDouble = powerValue.toDouble();
        QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
        double converted = powDouble;
        if(unit == "dBm"){
            converted = ConversionUtilities::convertDBmToWatt(powDouble);
            qDebug() << powDouble << " to " << converted;
        }
        powerSettings[slotNum - 1] = QByteArray::number(converted);

        // update the settings object
        settings->setValue(N7714A_POWER_SETTINGS, QVariant::fromValue(powerSettings));
        populateLaserOutputPower();
        powerSettingDisplayTextColored[slotNum - 1] = true;
    }

    colorDisplayFieldText();
    ui->laserOutputPowerEdit->clearFocus();
}

void ConfigN7714AWindow::on_laserWavelengthEdit_editingFinished()
{
    qDebug() << "on_laserWavelengthEdit_editingFinished()";

    QByteArray wavelengthValue = ui->laserWavelengthEdit->text().toLatin1();
    QByteArray minWavelength = ui->minWavelengthDisplay->text().toLatin1();
    QByteArray maxWavelength = ui->maxWavelengthDisplay->text().toLatin1();

    if(isInputValueValid(wavelengthValue, minWavelength, maxWavelength)){
        // wavelength is valid, insert into list
        double wavDouble = wavelengthValue.toDouble();
        QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
        double converted = ConversionUtilities::convertWavelengthToMeter(wavDouble, unit);
        wavelengthSettings[slotNum - 1] = QByteArray::number(converted);

        // update the settings object
        settings->setValue(N7714A_WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
        populateLaserWavelength();
        wavelengthDisplayTextColored[slotNum - 1] = true;

        // update frequency b/c the values are related
        double frequency = ConversionUtilities::convertWavelengthToFrequency(converted);
        frequencySettings[slotNum - 1] = QByteArray::number(frequency);
        settings->setValue(N7714A_FREQUENCY_SETTINGS, QVariant::fromValue(frequencySettings));
        populateLaserFrequency();
        frequencyDisplayTextColored[slotNum - 1] = true;

    }
    colorDisplayFieldText();
    ui->laserWavelengthEdit->clearFocus();
}

void ConfigN7714AWindow::on_laserFrequencyEdit_editingFinished()
{
    qDebug() << "on_laserFrequencyEdit_editingFinished()";

    QByteArray frequencyValue = ui->laserFrequencyEdit->text().toLatin1();
    QByteArray minFrequencyValue = ui->minFrequencyDisplay->text().toLatin1();
    QByteArray maxFrequencyValue = ui->maxFrequencyDisplay->text().toLatin1();

    if(isInputValueValid(frequencyValue, minFrequencyValue, maxFrequencyValue)){
        // frequency is valid, insert into list
        double freqDouble = frequencyValue.toDouble();
        QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
        double converted = ConversionUtilities::convertFrequencyToHz(freqDouble, unit);
        frequencySettings[slotNum - 1] = QByteArray::number(converted);

        // update the settings object
        settings->setValue(N7714A_FREQUENCY_SETTINGS, QVariant::fromValue(frequencySettings));
        populateLaserFrequency();
        frequencyDisplayTextColored[slotNum - 1] = true;

        // update wavelength b/c the values are related
        double wavelength = ConversionUtilities::convertFrequencyToWavelength(converted);
        wavelengthSettings[slotNum - 1] = QByteArray::number(wavelength);
        settings->setValue(N7714A_WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
        populateLaserWavelength();
        wavelengthDisplayTextColored[slotNum - 1] = true;
    }

    colorDisplayFieldText();
    ui->laserFrequencyEdit->clearFocus();
}

void ConfigN7714AWindow::on_togglePowerButton_clicked()
{
    QByteArray state = ui->laserStateDisplay->text().toLatin1();
    if(state == "OFF"){
        // change to on
        laserStates[slotNum - 1] = "1";
    }
    else if(state == "ON"){
       // change to off
        laserStates[slotNum - 1] = "0";
    }

    settings->setValue(N7714A_LASER_STATE, QVariant::fromValue(laserStates));
    populateLaserState();
    powerStatusDisplayTextColored[slotNum - 1] = true;
    colorDisplayFieldText();
}

void ConfigN7714AWindow::on_saveChangesButton_clicked()
{
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}

bool ConfigN7714AWindow::loadSettings()
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

bool ConfigN7714AWindow::saveSettings()
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

void ConfigN7714AWindow::on_loadSettingsButton_clicked()
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

void ConfigN7714AWindow::on_saveSettingsButton_clicked()
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

void ConfigN7714AWindow::colorText(QLineEdit *textField, bool colored){
    if(colored){
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 255);}");
    }
    else{
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 0);}");
    }
}

void ConfigN7714AWindow::colorDisplayFieldText()
{
    colorText(ui->laserOutputPowerDisplay, powerSettingDisplayTextColored[slotNum - 1]);
    colorText(ui->laserStateDisplay, powerStatusDisplayTextColored[slotNum - 1]);
    colorText(ui->laserWavelengthDisplay, wavelengthDisplayTextColored[slotNum - 1]);
    colorText(ui->laserFrequencyDisplay, frequencyDisplayTextColored[slotNum - 1]);
}

void ConfigN7714AWindow::resetDisplayFieldColoredStatus(){
    qDebug() << "resetDisplayFieldColoredStatus()";

    for(int i = 0; i < N7714A_NUM_SLOTS; i++){
        powerSettingDisplayTextColored[i] = false;
        powerStatusDisplayTextColored[i] = false;
        wavelengthDisplayTextColored[i] = false;
        frequencyDisplayTextColored[i] = false;
    }

    colorDisplayFieldText();
}
