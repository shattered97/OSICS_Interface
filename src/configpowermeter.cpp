#include "configpowermeter.h"
#include "ui_configpowermeter.h"


ConfigPowerMeter::ConfigPowerMeter(PowerMeter *device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigPowerMeter)
{
    ui->setupUi(this);

    this->device = device;

    setupWindow();
}

ConfigPowerMeter::~ConfigPowerMeter()
{
    delete ui;
}

void ConfigPowerMeter::setupWindow()
{
    // display device information
    ui->instrumentInfoLabel->setText(ui->instrumentInfoLabel->text() + device->getInstrIdentity());
    ui->instrumentAddressLabel->setText(ui->instrumentAddressLabel->text() + device->getInstrLocation());

    // get number of channels/slots on power meter and initialize display to show info for first channel/slot
    numSlots = device->getNumPowerMeterChannels();
    slotNum = 1;

    // display a radio button for each channel/slot available
    initChannelRadioButtons();

    // initialize list of units
    QByteArray units;
    device->getAllPowerUnits(units);
    powerUnits = device->formatPowerUnits(units, numSlots);

    // init wavelength unit to meters
    wavelengthExponentIndex = WAV_EXPONENT_LIST.indexOf(M_UNIT);

    // initialize wavelength displays on all channels/slots
    initWavelengthReadings();
    initMinWavelengths();
    initMaxWavelengths();

    // update displayed values
    populateAllValues();
}

void ConfigPowerMeter::initChannelRadioButtons(){

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

void ConfigPowerMeter::initWavelengthReadings(){
    // loop for each channel and get the current wavelength (m)
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength;
        device->queryWavelength(i, wavelength);
        wavelengthReadings.append(wavelength.toDouble());
    }
}
void ConfigPowerMeter::initMinWavelengths(){
    // loop for each channel and get the min wavelength (m)
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength;
        device->queryWavelength(i, wavelength, "MIN");

        minWavelengths.append(wavelength.toDouble());
    }
}

void ConfigPowerMeter::initMaxWavelengths(){
    // loop for each channel and get the max wavelength (m)
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength;
        device->queryWavelength(i, wavelength, "MAX");

        maxWavelengths.append(wavelength.toDouble());
    }
}

void ConfigPowerMeter::populateAllValues()
{
    populatePowerUnit();
    populatePower();
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

void ConfigPowerMeter::populatePowerUnit()
{
    // update the unit display field and unit labels
    QByteArray unitText = powerUnits.at(slotNum - 1);
    ui->powerUnitDisplay->setText(unitText);
    ui->powerDisplayUnit->setText(unitText);

    // change dropdown to the current unit
    int unitDropdownIndex = ui->powerUnitComboBox->findText(unitText);
    ui->powerUnitComboBox->setCurrentIndex(unitDropdownIndex);
}

void ConfigPowerMeter::populatePower()
{
    // send command to get power reading from current slot
    QByteArray response;
    device->measurePower(slotNum, response);

    QByteArray value = response;
    double valueDouble = value.toDouble();

    ui->powerDisplay->setText(QByteArray::number(valueDouble));
}

void ConfigPowerMeter::populateWavelengthUnit()
{
    QByteArray unit = ui->wavelengthComboBox->currentText().toLatin1();
    ui->wavelengthUnitDisplay->setText(unit);

    // iterate through wavelength exponents to find index of current unit
    for(int i = 0; i < WAV_EXPONENT_LIST.size(); i++){
        QByteArray unitInList = WAV_EXPONENT_LIST.at(i).second;
        if(unitInList == unit){
            wavelengthExponentIndex = i;
        }
    }

    // change wavelength unit labels
    QByteArray unitFromList = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).second;

    ui->wavelengthDisplayUnitLabel->setText(unitFromList);
    ui->wavelengthEditUnitLabel->setText(unitFromList);
    ui->minWavelengthUnitLabel->setText(unitFromList);
    ui->maxWavelengthUnitLabel->setText(unitFromList);
}

void ConfigPowerMeter::populateWavelength()
{
    // convert to selected unit and display
    double converted = convertWavelengthFromMeter(wavelengthReadings[slotNum - 1]);
    ui->wavelengthDisplay->setText(QString::number(converted));
}

void ConfigPowerMeter::populateMinWavelength()
{
    // convert wavelength and apply to display field
    double converted = convertWavelengthFromMeter(minWavelengths[slotNum - 1]);
    ui->minWavelengthDisplay->setText(QString::number(converted));
}

void ConfigPowerMeter::populateMaxWavelength()
{
    // convert wavelength and apply to display field
    double converted = convertWavelengthFromMeter(maxWavelengths[slotNum - 1]);
    ui->maxWavelengthDisplay->setText(QString::number(converted));
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
}

void ConfigPowerMeter::on_powerUnitComboBox_currentIndexChanged(const QString &unit)
{
    device->setPowerUnit(slotNum, unit.toLatin1());

    // change labels and QList of units
    ui->powerUnitDisplay->setText(unit);
    ui->powerDisplayUnit->setText(unit);
    powerUnits[slotNum - 1] = unit.toLatin1();

    // re-query power values to convert to the new unit
    populatePower();
}

void ConfigPowerMeter::on_wavelengthComboBox_currentIndexChanged()
{
    // re-populate values to convert values based on unit
    populateWavelengthUnit();
    populateWavelength();
    populateMinWavelength();
    populateMaxWavelength();
}

double ConfigPowerMeter::convertWavelengthFromMeter(double wavelengthInMeter)
{
    int exponent = WAV_EXPONENT_LIST.at(wavelengthExponentIndex).first;
    double converted = wavelengthInMeter * qPow(10, exponent * -1);
    return converted;
}

void ConfigPowerMeter::on_wavelengthEdit_editingFinished()
{
    QByteArray wavelength = ui->wavelengthEdit->text().toLatin1();
    QByteArray unit = ui->wavelengthComboBox->currentText().toLatin1();

    // #TODO check if wavelength is in range min < wavelength < max

    // send command to set wavelength
    device->setWavelength(slotNum, wavelength, unit);

    // query for updated wavelength
    QByteArray wavelengthReading;
    device->queryWavelength(slotNum, wavelengthReading);

    // re-populate wavelength display
    wavelengthReadings[slotNum - 1] = wavelengthReading.toDouble();
    populateWavelength();
}

void ConfigPowerMeter::on_testEdit_editingFinished()
{
    QByteArray response;
    QByteArray command = ui->testEdit->text().toLatin1();
    device->testCommand(command, response);
    qDebug() << response;
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

bool ConfigPowerMeter::loadSettings()
{
    QSettings settings(settingsFileName, QSettings::IniFormat);
    settings.beginGroup("Keysight Power Meter");

    // load the wavelength unit (same for all slots)
    QByteArray wavelengthUnit = settings.value("Wavelength Unit", QString()).toString().toLatin1();
    int wavelengthIndex = ui->wavelengthComboBox->findText(wavelengthUnit);
    ui->wavelengthComboBox->setCurrentIndex(wavelengthIndex);

    for(int i = 1; i <= numSlots; i++){
        QString slotIdentifier = "Slot " + QString::number(i);

        // set power unit for each slot
        QString powerUnitSettingsKey = ("Power Unit " + slotIdentifier);
        QString powerUnit = settings.value(powerUnitSettingsKey, QString()).toString();
        device->setPowerUnit(i, powerUnit.toLatin1());
        powerUnits[i - 1] = powerUnit.toLatin1();

        // set wavelength for each slot
        QString wavelengthSettingsKey = "Wavelength " + slotIdentifier;
        QByteArray wavelength = settings.value(wavelengthSettingsKey, QString()).toString().toLatin1();
        QByteArray nativeUnit = M_UNIT.second;
        device->setWavelength(i, wavelength, nativeUnit);

        QByteArray wavelengthReading;
        device->queryWavelength(i, wavelengthReading);
        wavelengthReadings[i - 1] = wavelengthReading.toDouble();
    }

    populateAllValues();

    qDebug() << "Loaded settings from file";
    settings.endGroup();
    return true;
}

bool ConfigPowerMeter::saveSettings()
{
    QSettings settings(settingsFileName, QSettings::IniFormat);
    settings.beginGroup("Keysight Power Meter");

    // save the wavelength unit (same for all slots)
    settings.setValue("Wavelength Unit", ui->wavelengthComboBox->currentText());

    // save power unit and wavelength for each slot
    for(int i = 1; i <= numSlots; i++){
        QString slotIdentifier = "Slot " + QString::number(i);

        QString powerUnitSettingsKey = ("Power Unit " + slotIdentifier);
        settings.setValue(powerUnitSettingsKey, powerUnits[i - 1]);

        QString wavelengthSettingsKey = "Wavelength " + slotIdentifier;
        settings.setValue(wavelengthSettingsKey, wavelengthReadings[i - 1]);
    }

    settings.endGroup();
    settings.sync();
    return true;
}
