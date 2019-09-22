#include "configpowermeter.h"
#include "ui_configpowermeter.h"


ConfigPowerMeter::ConfigPowerMeter(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigPowerMeter)
{
    ui->setupUi(this);
    this->device = device;
}

ConfigPowerMeter::~ConfigPowerMeter()
{
    delete ui;
}

void ConfigPowerMeter::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );

    // initialize settings and signal to orchestrator to update them from device
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
    emit signalUpdateConfigSettings(device, *settings);
}

void ConfigPowerMeter::slotUpdateWindow()
{
    qDebug() << "power meter update config";
    // clear text entry fields
    ui->wavelengthEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display slot radio buttons
    initChannelRadioButtons();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigPowerMeter::getValuesFromConfig()
{
    qDebug() << "getValuesFromConfig()";
    numSlots = settings->value(NUM_CHANNELS).value<int>();
    powerReadings = settings->value(POWER_READINGS).value<QList<QByteArray>>();
    wavelengthSettings = settings->value(WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    minWavelengths = settings->value(MIN_WAVELENGTHS).value<QList<QByteArray>>();
    maxWavelengths = settings->value(MAX_WAVELENGTHS).value<QList<QByteArray>>();
}

void ConfigPowerMeter::populateAllValues()
{
    qDebug() << "populateAllValues()";
    populatePowerUnit();
    populatePower();
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigPowerMeter::populatePowerUnit()
{
    qDebug() << "populatePowerUnit()";
    // update the unit display field and unit labels
    QByteArray unitText = ui->powerUnitComboBox->currentText().toLatin1();
    ui->powerDisplayUnit->setText(unitText);
}

void ConfigPowerMeter::populatePower()
{
    qDebug() << "populatePower()";
    double power = powerReadings[slotNum - 1].toDouble();
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }

    ui->powerDisplay->setText(QByteArray::number(converted));
}

void ConfigPowerMeter::populateWavelengthUnit()
{
    qDebug() << "populateWavelengthUnit()";
    QByteArray unitText = ui->wavelengthComboBox->currentText().toLatin1();
    ui->wavelengthDisplayUnitLabel->setText(unitText);
    ui->wavelengthEditUnitLabel->setText(unitText);
    ui->minWavelengthUnitLabel->setText(unitText);
    ui->maxWavelengthUnitLabel->setText(unitText);
}

void ConfigPowerMeter::convertAndDisplayWavelength(QList<QByteArray> wavelengthList, QLineEdit* displayField){
    double wavelength = wavelengthList[slotNum - 1].toDouble();
    QByteArray unit = ui->wavelengthComboBox->currentText().toLatin1();
    double converted = ConversionUtilities::convertWavelengthFromMeter(wavelength, unit);
    qDebug() << wavelength << " to " << converted;
    displayField->setText(QByteArray::number(converted));
}

void ConfigPowerMeter::populateWavelength()
{
    qDebug() << "populateWavelength()";
    convertAndDisplayWavelength(wavelengthSettings, ui->wavelengthDisplay);
}

void ConfigPowerMeter::populateMinWavelength()
{
    qDebug() << "populateMinWavelength()";
    convertAndDisplayWavelength(minWavelengths, ui->minWavelengthDisplay);
}

void ConfigPowerMeter::populateMaxWavelength()
{
    qDebug() << "populateMaxWavelength()";
    convertAndDisplayWavelength(maxWavelengths, ui->maxWavelengthDisplay);
}

void ConfigPowerMeter::initChannelRadioButtons()
{
    qDebug() << "initChannelRadioButtons()";

    // set default displayed slot/channel
    slotNum = 1;

    // use horizontal layout
    QHBoxLayout *hBox = new QHBoxLayout;

    for(int i = 1; i <= numSlots; i++){
        // make button and add to layout
        QRadioButton *button = new QRadioButton();
        button->setText("Slot " + QString::number(i));
        hBox->addWidget(button);
        buttons.append(button);

        // connect button to signal
        connect(button,SIGNAL(clicked()),this,SLOT(slot_radio_button_clicked()));
    }

    // set first item as default selected
    buttons[0]->setChecked(true);

    ui->radioButtonGroupBox->setLayout(hBox);
}

void ConfigPowerMeter::slot_radio_button_clicked()
{
    qDebug() << "slot_radio_button_clicked()";
    // set the slot number to value indicated by selected button
    for(int i = 0; i < numSlots; i++){
        if(buttons[i]->isChecked()){
            slotNum = i + 1;
        }
    }

    // refresh display values
    populateAllValues();
}

void ConfigPowerMeter::on_powerUnitComboBox_currentIndexChanged(const QString &unit)
{
    qDebug() << "on_powerUnitComboBox_currentIndexChanged()";
    // re-query power values to convert to the new unit
    populatePowerUnit();
    populatePower();
}

void ConfigPowerMeter::on_wavelengthComboBox_currentIndexChanged(int unit)
{
    qDebug() << "on_wavelengthComboBox_currentIndexChanged()";

    // re-populate fields to convert values based on unit
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigPowerMeter::on_wavelengthEdit_editingFinished()
{
    qDebug() << "on_wavelengthEdit_editingFinished()";

    QByteArray fieldText = ui->wavelengthEdit->text().toLatin1();

    if(fieldText != ""){
        // convert entered wavelength to double
        bool ok;
        double wavDouble =fieldText.toDouble(&ok);

        // if conversion can't be made, error message
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
                // entered wavelength is valid - we can place it in the list
                QByteArray unit = ui->wavelengthComboBox->currentText().toLatin1();
                double converted = ConversionUtilities::convertWavelengthToMeter(wavDouble, unit);
                wavelengthSettings[slotNum - 1] = QByteArray::number(converted);

                // update the settings object
                settings->setValue(WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));
            }
        }
    }
    ui->wavelengthEdit->clearFocus();
}

void ConfigPowerMeter::on_loadSettingsButton_pressed()
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

void ConfigPowerMeter::on_saveSettingsButton_pressed()
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

bool ConfigPowerMeter::loadSettings()
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

bool ConfigPowerMeter::saveSettings()
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

void ConfigPowerMeter::on_saveChangesButton_clicked()
{
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values in the QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}
