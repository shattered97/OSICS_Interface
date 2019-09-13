#include "ConfigOSICS_ATN.h"
#include "ui_ConfigOSICS_ATN.h"

ConfigOSICS_ATN::ConfigOSICS_ATN(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_ATN)
{
    ui->setupUi(this);

    slotNum = 1;

    // initialize settings and signal to orchestrator to update them from device
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
}

ConfigOSICS_ATN::~ConfigOSICS_ATN()
{
    delete ui;
}

void ConfigOSICS_ATN::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    emit signalUpdateConfigSettings(device, *settings);
}

void ConfigOSICS_ATN::slotUpdateWindow()
{
    qDebug() << "atn slotUpdateWindow()";
    // clear text entry fields
    ui->attenuationEdit->clear();
    ui->attenuationOffsetEdit->clear();

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));
}

void ConfigOSICS_ATN::getValuesFromConfig()
{
    qDebug() << "getValuesFromConfig() atn";

    attenuationSetting = settings->value(EXFO_OSICS_ATN_ATTENUATION).value<QByteArray>();
    firstMinAttenuation = settings->value(EXFO_OSICS_ATN_MIN_ATTENUATION_1).value<QByteArray>();
    firstMaxAttenuation = settings->value(EXFO_OSICS_ATN_MAX_ATTENUATION_1).value<QByteArray>();
    secondMinAttenuation = settings->value(EXFO_OSICS_ATN_MIN_ATTENUATION_2).value<QByteArray>();
    secondMaxAttenuation = settings->value(EXFO_OSICS_ATN_MAX_ATTENUATION_2).value<QByteArray>();
    refWavelengthNumber = settings->value(EXFO_OSICS_ATN_REF_WAV_NUMBER).value<QByteArray>();
    firstRefWavelength = settings->value(EXFO_OSICS_ATN_REF_WAVELENGTH_1).value<QByteArray>();
    secondRefWavelength = settings->value(EXFO_OSICS_ATN_REF_WAVELENGTH_2).value<QByteArray>();
    offset = settings->value(EXFO_OSICS_ATN_OFFSET).value<QByteArray>();
}

void ConfigOSICS_ATN::populateAllValues()
{
    populateAttenuation();
    populateMinAttenuation();
    populateMaxAttenuation();
    populateRefWavelength();
    populateOffset();
}

void ConfigOSICS_ATN::populateAttenuation()
{
    ui->attenuationDisplay->setText(attenuationSetting);
}

void ConfigOSICS_ATN::populateMinAttenuation()
{
    if(refWavelengthNumber.toInt() == 1){
        ui->minAttenuationDisplay->setText(firstMinAttenuation);
    }
    else{
        ui->minAttenuationDisplay->setText(secondMinAttenuation);
    }
}

void ConfigOSICS_ATN::populateMaxAttenuation()
{
    if(refWavelengthNumber.toInt() == 1){
        ui->minAttenuationDisplay->setText(firstMaxAttenuation);
    }
    else{
        ui->minAttenuationDisplay->setText(secondMaxAttenuation);
    }
}

void ConfigOSICS_ATN::populateRefWavelength()
{
    ui->refWavelengthRadioButton1->setText(firstRefWavelength);
    ui->refWavelengthRadioButton2->setText(secondRefWavelength);
}

void ConfigOSICS_ATN::populateOffset()
{
    ui->attenuationOffsetDisplay->setText(offset);
}

bool ConfigOSICS_ATN::isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue)
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

bool ConfigOSICS_ATN::loadSettings()
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

bool ConfigOSICS_ATN::saveSettings()
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

void ConfigOSICS_ATN::on_attenuationEdit_editingFinished()
{
    QByteArray enteredAtten = ui->attenuationEdit->text().toLatin1();

    if(isInputValueValid(enteredAtten, firstMinAttenuation, firstMinAttenuation)){
        attenuationSetting = enteredAtten;
        settings->setValue(EXFO_OSICS_ATN_ATTENUATION, QVariant::fromValue(attenuationSetting));
    }
}

void ConfigOSICS_ATN::on_attenuationOffsetEdit_editingFinished()
{
    QByteArray enteredOffset = ui->attenuationOffsetEdit->text().toLatin1();
    if(isInputValueValid(enteredOffset, EXFO_OSICS_ATN_MIN_OFFSET, EXFO_OSICS_ATN_MAX_OFFSET)){
        offset = enteredOffset;
        settings->setValue(EXFO_OSICS_ATN_OFFSET, QVariant::fromValue(offset));
    }
}

void ConfigOSICS_ATN::on_loadSettingsButton_clicked()
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

void ConfigOSICS_ATN::on_saveSettingsButton_clicked()
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

void ConfigOSICS_ATN::on_saveChangesButton_clicked()
{
    // disable cursor until finished
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // signal to orchestrator to update the device with the values from QSettings
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}

void ConfigOSICS_ATN::on_wavelengthUnitComboBox_currentIndexChanged(const QString &arg1)
{
    // refresh wavelength values


}

void ConfigOSICS_ATN::on_refWavelengthRadioButton1_clicked()
{
    refWavelengthNumber = "1";

}

void ConfigOSICS_ATN::on_refWavelengthRadioButton2_clicked()
{
    refWavelengthNumber = "2";
}
