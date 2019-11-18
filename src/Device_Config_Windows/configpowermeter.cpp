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

        // disable cursor (re-enabled in slotUpdateWindow)
        QApplication::setOverrideCursor(Qt::WaitCursor);

        emit signalUpdateConfigSettings(device, settings);

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

    windowConfigured = true;

    // re-enable cursor
    QApplication::restoreOverrideCursor();
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
    totalTimeInSeconds = settings->value(PM_TOTAL_TIME).value<QList<QByteArray>>();
    periodTimeInSeconds = settings->value(PM_PERIOD_TIME).value<QList<QByteArray>>();
    avgTimeInSeconds = settings->value(PM_AVERAGING_TIME).value<QList<QByteArray>>();
    minMaxMode = settings->value(PM_MINMAX_MODE).value<QList<QByteArray>>();
    minMaxDataPoints = settings->value(PM_MINMAX_DATA_POINTS).value<QList<QByteArray>>();
}

void ConfigPowerMeter::populateAllValues()
{
    // call all methods needed to re-populate GUI
    populateIdentityAndLoc();
    populatePower();
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
    populateTotalTime();
    populatePeriodTime();
    populateAvgTime();
    populateMinMaxMode();
    populateMinMaxDataPoints();
}

void ConfigPowerMeter::populateMinMaxMode(){


    if(PM_CONTINUOUS_MODE_STRING.contains(minMaxMode[slotNum - 1])){
        // select the continuous radio button
        ui->continuousRadioBtn->setChecked(true);
    }
    else{
        // the two modes "WINDOW" AND "REFRESH" are the same
        // select the refresh radio button
        ui->refreshRadioBtn->setChecked(true);
    }
}

void ConfigPowerMeter::populateMinMaxDataPoints(){
    // convert to double for easy formatting
    double dataPoints = minMaxDataPoints[slotNum - 1].toDouble();
    ui->dataPointsEdit->setText(QByteArray::number(dataPoints));
}

void ConfigPowerMeter::populateTotalTime(){
    // get time in seconds and convert to dropdown unit
    QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
    double timeToConvert = totalTimeInSeconds[slotNum - 1].toDouble();
    double convertedTime = ConversionUtilities::convertTimeFromSeconds(timeToConvert, unit);
    ui->totalTimeDisplay->setText(QByteArray::number(convertedTime));
}

void ConfigPowerMeter::populateAvgTime(){
    // get time in seconds and convert to dropdown unit
    QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
    double timeToConvert = avgTimeInSeconds[slotNum - 1].toDouble();
    double convertedTime = ConversionUtilities::convertTimeFromSeconds(timeToConvert, unit);
    ui->avgTimeDisplay->setText(QByteArray::number(convertedTime));
}

void ConfigPowerMeter::populatePeriodTime(){
    // get time in seconds and convert to dropdown unit
    QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
    double timeToConvert = periodTimeInSeconds[slotNum - 1].toDouble();
    double convertedTime = ConversionUtilities::convertTimeFromSeconds(timeToConvert, unit);
    ui->periodTimeDisplay->setText(QByteArray::number(convertedTime));
}

void ConfigPowerMeter::populateIdentityAndLoc(){
    // set address and identity information
    ui->instrumentInfoLabel->setText(deviceNickname);
    ui->instrumentAddressLabel->setText(deviceAddress);
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
            wavelengthFieldColored.append(false);
            totalTimeTextColored.append(false);
            periodTimeTextColored.append(false);
            avgTimeTextColored.append(false);
            minMaxDataPointsColored.append(false);
            minMaxRefreshModeColored.append(false);
            minMaxContinuousModeColored.append(false);
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
//    populatePowerUnit();
    populatePower();
}

void ConfigPowerMeter::on_wavelengthComboBox_currentIndexChanged()
{
    // re-populate fields to convert values based on unit
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
    populateTotalTime();
    populatePeriodTime();
    populateAvgTime();
    populateMinMaxMode();
    populateMinMaxDataPoints();
}

void ConfigPowerMeter::on_wavelengthEdit_editingFinished()
{
    ui->wavelengthEdit->blockSignals(true);
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
                wavelengthFieldColored[slotNum - 1] = true;
            }
        }
    }
    colorDisplayFieldText();

    // clear edit field and remove focus
    ui->wavelengthEdit->clear();
    ui->wavelengthEdit->clearFocus();
    ui->wavelengthEdit->blockSignals(false);
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

    // disable cursor (re-enabled in slotUpdateWindow)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to apply the new settings
    emit signalApplyConfigSettings(device, settings);

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
    emit signalApplyConfigSettings(device, settings);
}

void ConfigPowerMeter::resetDisplayFieldColoredStatus()
{
    // reset the color status lists to all false
    for(int i = 0; i < wavelengthFieldColored.size(); i++){
        wavelengthFieldColored[i] = false;
        totalTimeTextColored[i] = false;
        periodTimeTextColored[i] = false;
        avgTimeTextColored[i] = false;
        minMaxDataPointsColored[i] = false;
        minMaxRefreshModeColored[i] = false;
        minMaxContinuousModeColored[i] = false;
    }

    // update displayed colors
    colorDisplayFieldText();
}

void ConfigPowerMeter::colorDisplayFieldText()
{
    // color the wavelength field
    colorText(ui->wavelengthDisplay, wavelengthFieldColored.at(slotNum - 1));

    // color the integration time fields
    colorText(ui->totalTimeDisplay, totalTimeTextColored.at(slotNum - 1));
    colorText(ui->periodTimeDisplay, periodTimeTextColored.at(slotNum - 1));
    colorText(ui->avgTimeDisplay, avgTimeTextColored.at(slotNum - 1));

    // color the minmax mode fields and data points field
    colorText(ui->dataPointsEdit, minMaxDataPointsColored.at(slotNum - 1));

    // color the radio buttons separate b/c they are not QLineEdits
    if(minMaxRefreshModeColored[slotNum - 1]){
        ui->refreshRadioBtn->setStyleSheet("QRadioButton {color: rgb(0, 0, 255);}");
    }
    else{
        ui->refreshRadioBtn->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");
    }

    if(minMaxContinuousModeColored[slotNum - 1]){
        ui->continuousRadioBtn->setStyleSheet("QRadioButton {color: rgb(0, 0, 255);}");
    }
    else{
        ui->continuousRadioBtn->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");
    }
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

void ConfigPowerMeter::on_totalTimeDisplay_editingFinished()
{
    ui->totalTimeDisplay->blockSignals(true);

    QByteArray fieldText = ui->totalTimeDisplay->text().toLatin1();

    if(fieldText != ""){

        // see if value can be converted to double
        bool ok;
        double totalTimeDouble =fieldText.toDouble(&ok);

        // if conversion can't be made, error message
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Value entered is invalid (non-numeric).");
            msgBox.exec();

            // return to set value
            populateTotalTime();
        }
        else{
            // convert time to seconds
            QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
            double timeinSecDouble = ConversionUtilities::convertTimeToSeconds(totalTimeDouble, unit);


            if(timeinSecDouble < PM_MIN_TOTAL_TIME_SECONDS ||
               timeinSecDouble > PM_MAX_TOTAL_TIME_SECONDS){

                QMessageBox msgBox;
                QString rangeString = " Range: %1 to %2.";
                rangeString = rangeString.arg(PM_MIN_TOTAL_TIME_SECONDS).arg(PM_MAX_TOTAL_TIME_SECONDS);
                msgBox.setText("Value entered is invalid (out of min/max range)." + rangeString);
                msgBox.exec();

                // return to set value
                populateTotalTime();
            }
            else{

                // if the set time is the same as the time in settings, don't set the colored flag
                // (happens if a user clicks then un-clicks the field).
                if(timeinSecDouble != totalTimeInSeconds[slotNum - 1].toDouble()){
                     totalTimeTextColored[slotNum - 1] = true;
                }
                // total time is valid, update the settings object
                totalTimeInSeconds[slotNum - 1] = QByteArray::number(timeinSecDouble);
                settings->setValue(PM_TOTAL_TIME, QVariant::fromValue(totalTimeInSeconds));

            }
        }
    }
    else{
        // return to set value
        populateTotalTime();
    }
    colorDisplayFieldText();
    ui->totalTimeDisplay->clearFocus();
    ui->totalTimeDisplay->blockSignals(false);
}

void ConfigPowerMeter::on_periodTimeDisplay_editingFinished()
{
    ui->periodTimeDisplay->blockSignals(true);

    QByteArray fieldText = ui->periodTimeDisplay->text().toLatin1();

    if(fieldText != ""){

        // see if value can be converted to double
        bool ok;
        double periodTimeDouble =fieldText.toDouble(&ok);

        // if conversion can't be made, error message
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Value entered is invalid (non-numeric).");
            msgBox.exec();

            // return to set value
            populatePeriodTime();
        }
        else{
            // convert time to seconds
            QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
            double timeInSecDouble =  ConversionUtilities::convertTimeToSeconds(periodTimeDouble, unit);

            if(timeInSecDouble < PM_MIN_AVG_TIME_SECONDS ||
               timeInSecDouble > PM_MAX_AVG_TIME_SECONDS){

                QMessageBox msgBox;
                msgBox.setText("Value entered is invalid (out of min/max range).");
                msgBox.exec();

                // return to set value
                populatePeriodTime();
            }
            else{
                // if the set time is the same as the time in settings, don't set the colored flag
                // (happens if a user clicks then un-clicks the field).
                if(timeInSecDouble != periodTimeInSeconds[slotNum - 1].toDouble()){
                     periodTimeTextColored[slotNum - 1] = true;
                }
                periodTimeInSeconds[slotNum - 1] = QByteArray::number(timeInSecDouble);
                // period time is valid, update the settings object
                settings->setValue(PM_PERIOD_TIME, QVariant::fromValue(periodTimeInSeconds));

            }
        }
    }
    else{
        // return to set value
        populatePeriodTime();
    }
    colorDisplayFieldText();
    ui->periodTimeDisplay->clearFocus();
    ui->periodTimeDisplay->blockSignals(false);
}

void ConfigPowerMeter::on_avgTimeDisplay_editingFinished()
{
    ui->avgTimeDisplay->blockSignals(true);

    QByteArray fieldText = ui->avgTimeDisplay->text().toLatin1();

    if(fieldText != ""){

        // see if value can be converted to double
        bool ok;
        double avgTimeDouble =fieldText.toDouble(&ok);

        // if conversion can't be made, error message
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Value entered is invalid (non-numeric).");
            msgBox.exec();
            ui->avgTimeDisplay->clear();

            // return to set value
            populateAvgTime();
        }
        else{
            // convert time to seconds
            QByteArray unit = ui->timeUnitComboBox->currentText().toLatin1();
            double timeInSecDouble = ConversionUtilities::convertTimeToSeconds(avgTimeDouble, unit);


            if(timeInSecDouble < PM_MIN_AVG_TIME_SECONDS ||
               timeInSecDouble > PM_MAX_AVG_TIME_SECONDS){
                QMessageBox msgBox;
                msgBox.setText("Value entered is invalid (out of min/max range).");
                msgBox.exec();

                // return to set value
                populateAvgTime();
            }
            else{

                if(timeInSecDouble != avgTimeInSeconds[slotNum - 1].toDouble()){
                     avgTimeTextColored[slotNum - 1] = true;
                }
                // period time is valid, update the settings object
                avgTimeInSeconds[slotNum - 1] = QByteArray::number(timeInSecDouble);
                settings->setValue(PM_AVERAGING_TIME, QVariant::fromValue(avgTimeInSeconds));
                // set to colored to indicate this value has not been sent to device yet

            }
        }
    }
    else{
        // return to set value
        populateAvgTime();
    }
    colorDisplayFieldText();
    ui->avgTimeDisplay->clearFocus();
    ui->avgTimeDisplay->blockSignals(false);
}


void ConfigPowerMeter::on_continuousRadioBtn_clicked()
{
    minMaxMode[slotNum - 1] = PM_CONTINUOUS_MODE_STRING;
    settings->setValue(PM_MINMAX_MODE, QVariant::fromValue(minMaxMode));

    // swap colored status and update colors
    minMaxRefreshModeColored[slotNum - 1] = false;
    minMaxContinuousModeColored[slotNum - 1] = true;

    colorDisplayFieldText();
}

void ConfigPowerMeter::on_refreshRadioBtn_clicked()
{
    minMaxMode[slotNum - 1] = PM_REFRESH_MODE_STRING;
    settings->setValue(PM_MINMAX_MODE, QVariant::fromValue(minMaxMode));

    // swap colored status and update colors
    minMaxRefreshModeColored[slotNum - 1] = true;
    minMaxContinuousModeColored[slotNum - 1] = false;

    colorDisplayFieldText();
}


void ConfigPowerMeter::on_dataPointsEdit_editingFinished()
{
    ui->dataPointsEdit->blockSignals(true);

    QByteArray fieldText = ui->dataPointsEdit->text().toLatin1();

    if(fieldText != ""){

        // see if value can be converted to double
        bool ok;
        double dataPoints = fieldText.toDouble(&ok);

        // if conversion can't be made, error message
        if(!ok){
            QMessageBox msgBox;
            msgBox.setText("Value entered is invalid (non-numeric).");
            msgBox.exec();
            ui->dataPointsEdit->clear();
        }
        else{
            if(dataPoints < 1){
                QMessageBox msgBox;
                msgBox.setText("Data points must be greater than 0.");
                msgBox.exec();
                ui->dataPointsEdit->clear();
            }
            else{
                // if the data points value was not changed, don't set colored flag
                if(dataPoints != minMaxDataPoints[slotNum - 1].toInt()){
                     minMaxDataPointsColored[slotNum - 1] = true;
                }

                minMaxDataPoints[slotNum - 1] = QByteArray::number(dataPoints);

                // update the settings object
                settings->setValue(PM_MINMAX_DATA_POINTS, QVariant::fromValue(minMaxDataPoints));
            }
        }
    }

    colorDisplayFieldText();
    ui->dataPointsEdit->clearFocus();
    ui->dataPointsEdit->blockSignals(false);
}

void ConfigPowerMeter::on_timeUnitComboBox_currentIndexChanged(const QString &unit)
{
    // change labels to match new unit
    ui->avgTimeUnitLabel->setText(unit);
    ui->periodTimeUnitLabel->setText(unit);

    // convert current values to new unit
    if(ui->totalTimeDisplay->text() != ""){
        double totalTime = totalTimeInSeconds[slotNum - 1].toDouble();
        double newTotalTime = ConversionUtilities::convertTimeFromSeconds(totalTime, unit.toLatin1());
        ui->totalTimeDisplay->setText(QByteArray::number(newTotalTime));
    }
    if(ui->periodTimeDisplay->text() != ""){
        double periodTime = periodTimeInSeconds[slotNum - 1].toDouble();
        double newPeriodTime = ConversionUtilities::convertTimeFromSeconds(periodTime, unit.toLatin1());
        ui->periodTimeDisplay->setText(QByteArray::number(newPeriodTime));
    }
    if(ui->avgTimeDisplay->text() != ""){
        double avgTime = avgTimeInSeconds[slotNum - 1].toDouble();
        double newAvgTime = ConversionUtilities::convertTimeFromSeconds(avgTime, unit.toLatin1());
        ui->avgTimeDisplay->setText(QByteArray::number(newAvgTime));
    }
}
