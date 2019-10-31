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

    if(!windowConfigured){
        // initialize settings and signal to orchestrator to update them from device
        settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
        settings->clear();
        emit signalUpdateConfigSettings(device, *settings);

        windowConfigured = true;
    }

}

void ConfigPowerMeter::slotUpdateWindow()
{
    // clear text entry fields
    ui->wavelengthEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // setup radio buttons
    initChannelRadioButtons();

    // reset text fields
    resetDisplayFieldColoredStatus();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigPowerMeter::getValuesFromConfig()
{
    // parses config values from QSettings object
    deviceAddress = settings->value(DEVICE_ADDRESS).value<QByteArray>();
    deviceIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    deviceNickname = settings->value(DEVICE_NICKNAME).value<QByteArray>();
    numSlots = settings->value(NUM_CHANNELS).value<int>();
    powerReadings = settings->value(POWER_READINGS).value<QList<QByteArray>>();
    wavelengthSettings = settings->value(WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    minWavelengths = settings->value(MIN_WAVELENGTHS).value<QList<QByteArray>>();
    maxWavelengths = settings->value(MAX_WAVELENGTHS).value<QList<QByteArray>>();
}

void ConfigPowerMeter::populateAllValues()
{
    // call all methods needed to re-populate GUI
    populateIdentityAndLoc();
    populatePowerUnit();
    populatePower();
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigPowerMeter::populateIdentityAndLoc(){
    // set address and identity information
    ui->instrumentInfoLabel->setText(deviceNickname);
    ui->instrumentAddressLabel->setText(deviceAddress);
}

void ConfigPowerMeter::populatePowerUnit()
{
    // update the displayed power unit from the dropdown value
    QByteArray unitText = ui->powerUnitComboBox->currentText().toLatin1();
    ui->powerDisplayUnit->setText(unitText);
}

void ConfigPowerMeter::populatePower()
{
    // get appropriate power reading for selected channel
    double power = powerReadings[slotNum - 1].toDouble();

    // convert if necessary
    double converted = power;
    if(ui->powerUnitComboBox->currentText() == "dBm"){
        converted = ConversionUtilities::convertWattToDBm(power);
    }

    // display converted value
    ui->powerDisplay->setText(QByteArray::number(converted));
}

void ConfigPowerMeter::populateWavelengthUnit()
{
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
    displayField->setText(QByteArray::number(converted));
}

void ConfigPowerMeter::populateWavelength()
{
    // display wavelength setting in correct unit
    convertAndDisplayWavelength(wavelengthSettings, ui->wavelengthDisplay);
}

void ConfigPowerMeter::populateMinWavelength()
{
    // display min wavelength in correct unit
    convertAndDisplayWavelength(minWavelengths, ui->minWavelengthDisplay);
}

void ConfigPowerMeter::populateMaxWavelength()
{
    // display max wavelength in correct unit
    convertAndDisplayWavelength(maxWavelengths, ui->maxWavelengthDisplay);
}

void ConfigPowerMeter::initChannelRadioButtons()
{
    if(!windowConfigured){
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

            // create colored flag for each channel
            displayTextColored.append(false);
        }

        // set first item as default selected
        buttons[0]->setChecked(true);

        // apply layout
        ui->radioButtonGroupBox->setLayout(hBox);
    }
}

void ConfigPowerMeter::slot_radio_button_clicked()
{
    // set the slot number to value indicated by selected button
    for(int i = 0; i < numSlots; i++){
        if(buttons[i]->isChecked()){
            slotNum = i + 1;
        }
    }

    // refresh display values
    populateAllValues();

    // color the wavelength field
    colorDisplayFieldText();
}

void ConfigPowerMeter::on_powerUnitComboBox_currentIndexChanged()
{
    // re-query power values to convert to the new unit
    populatePowerUnit();
    populatePower();
}

void ConfigPowerMeter::on_wavelengthComboBox_currentIndexChanged()
{
    // re-populate fields to convert values based on unit
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigPowerMeter::on_wavelengthEdit_editingFinished()
{
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

                // update the wavelength field to have the new value
                populateWavelength();

                // set to colored to indicate this value has not been sent to device yet
                displayTextColored[slotNum - 1] = true;
            }
        }
    }
    colorDisplayFieldText();

    // clear edit field and remove focus
    ui->wavelengthEdit->clear();
    ui->wavelengthEdit->clearFocus();
}

void ConfigPowerMeter::on_loadSettingsButton_pressed()
{
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

void ConfigPowerMeter::loadSettings()
{
    // get config file QSettings
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    // for each "setting" in the file, copy its values to our local QSettings object
    QStringList keys = settingsFromFile.allKeys();
    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
    {
        settings->setValue( *i, settingsFromFile.value( *i ) );
    }

    settings->sync();

    // signal to apply the new settings
    emit signalApplyConfigSettings(device, *settings);

}

void ConfigPowerMeter::saveSettings()
{
    // get config file QSettings
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    // for each "setting" in our local QSettings object, copy values to the config file version
    QStringList keys = settings->allKeys();
    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
    {
        settingsFromFile.setValue( *i, settings->value( *i ) );
    }

    // sync to make sure changes are applied
    settingsFromFile.sync();
}

void ConfigPowerMeter::on_saveChangesButton_clicked()
{
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values in the QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}

void ConfigPowerMeter::resetDisplayFieldColoredStatus()
{
    // reset the status list to all false
    for(int i = 0; i < displayTextColored.size(); i++){
        displayTextColored[i] = false;
    }

    // update displayed colors
    colorDisplayFieldText();
}

void ConfigPowerMeter::colorDisplayFieldText()
{
    // color the wavelength field
    colorText(ui->wavelengthDisplay, displayTextColored.at(slotNum - 1));
}

void ConfigPowerMeter::colorText(QLineEdit *textField, bool colored){
    if(colored){
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 255);}");
    }
    else{
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 0);}");
    }
}

void ConfigPowerMeter::on_setNicknameBtn_clicked()
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
