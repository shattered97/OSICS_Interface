#include "ConfigOSICS_T100.h"
#include "ui_ConfigOSICS_T100.h"

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
