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

void ConfigN7714AWindow::populateLaserWavelength(){
    // convert to selected unit and display
    double wavelength = wavelengthSettings[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
    qDebug() << wavelength << " " << unit;
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
    double wavelength = maxWavelengths[slotNum - 1].toDouble();
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
    double frequency = minFrequencies[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    ui->minFrequencyDisplay->setText(QString::number(converted));
}

void ConfigN7714AWindow::populateLaserMaxFrequency(){
    // convert frequency and apply to display field
    double frequency = maxFrequencies[slotNum - 1].toDouble();
    QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertFrequencyFromHz(frequency, unit);
    ui->maxFrequencyDisplay->setText(QString::number(converted));
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
    qDebug() << "on_laserOutputPowerEdit_editingFinished()";

    QByteArray fieldText = ui->laserOutputPowerEdit->text().toLatin1();

    if(fieldText != ""){
        // try to convert to double
        bool ok;
        double powDouble = fieldText.toDouble(&ok);

        // display error dialog if conversion can't be made
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Power entered is invalid (non-numeric).");
            msgBox.exec();
        }
        else{
            double minPower = ui->laserMinPowerDisplay->text().toDouble();
            double maxPower = ui->laserMaxPowerDisplay->text().toDouble();

            if(powDouble < minPower || powDouble > maxPower){
                QMessageBox msgBox;
                msgBox.setText("Power entered is invalid (out of min/max range).");
                msgBox.exec();
            }
            else{
                // power is valid, insert into list
                QByteArray unit = ui->powerUnitComboBox->currentText().toLatin1();
                double converted = powDouble;
                if(unit == "dBm"){
                    converted = ConversionUtilities::convertDBmToWatt(powDouble);
                    qDebug() << powDouble << " to " << converted;
                }
                powerSettings[slotNum - 1] = QByteArray::number(converted);

                // update the settings object
                settings->setValue(N7714A_POWER_SETTINGS, QVariant::fromValue(powerSettings));
            }
        }
        ui->laserOutputPowerEdit->clearFocus();
    }
}

void ConfigN7714AWindow::on_laserWavelengthEdit_editingFinished()
{
    qDebug() << "on_laserWavelengthEdit_editingFinished()";

    QByteArray fieldText = ui->laserWavelengthEdit->text().toLatin1();
    if(fieldText != ""){
        // try to convert to double
        bool ok;
        double wavDouble = fieldText.toDouble(&ok);

        // display error dialog if conversion can't be made
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Wavelength entered is invalid (non-numeric).");
            msgBox.exec();
        }
        else{
            double minWavelength = ui->minWavelengthDisplay->text().toDouble();
            double maxWavelength = ui->maxWavelengthDisplay->text().toDouble();

            if(wavDouble < minWavelength || wavDouble > maxWavelength){
                QMessageBox msgBox;
                msgBox.setText("Wavelength entered is invalid (out of min/max range).");
                msgBox.exec();
            }
            else{
                // wavelength is valid, insert into list
                QByteArray unit = ui->wavelengthUnitComboBox->currentText().toLatin1();
                double converted = ConversionUtilities::convertWavelengthToMeter(wavDouble, unit);
                wavelengthSettings[slotNum - 1] = QByteArray::number(converted);

                // update the settings object
                settings->setValue(N7714A_WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
            }
        }
    }
        ui->laserWavelengthEdit->clearFocus();
}

void ConfigN7714AWindow::on_laserFrequencyEdit_editingFinished()
{
    qDebug() << "on_laserFrequencyEdit_editingFinished()";

    QByteArray fieldText = ui->laserFrequencyEdit->text().toLatin1();
    if(fieldText != ""){
        // try to convert to double
        bool ok;
        double freqDouble = fieldText.toDouble(&ok);

        // display error dialog if conversion can't be made
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Frequency entered is invalid (non-numeric).");
            msgBox.exec();
        }
        else{
            double minFrequency = ui->minFrequencyDisplay->text().toDouble();
            double maxFrequency = ui->maxFrequencyDisplay->text().toDouble();

            if(freqDouble < minFrequency || freqDouble > maxFrequency){
                QMessageBox msgBox;
                msgBox.setText("Frequency entered is invalid (out of min/max range).");
                msgBox.exec();
            }
            else{
                // frequency is valid, insert into list
                QByteArray unit = ui->frequencyUnitComboBox->currentText().toLatin1();
                double converted = ConversionUtilities::convertFrequencyToHz(freqDouble, unit);
                frequencySettings[slotNum - 1] = QByteArray::number(converted);

                // update the settings object
                settings->setValue(N7714A_FREQUENCY_SETTINGS, QVariant::fromValue(frequencySettings));
            }
        }
    }
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
