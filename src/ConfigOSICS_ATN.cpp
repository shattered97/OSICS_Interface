#include "ConfigOSICS_ATN.h"
#include "ui_ConfigOSICS_ATN.h"

ConfigOSICS_ATN::ConfigOSICS_ATN(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigOSICS_ATN)
{
    ui->setupUi(this);
    this->device = device;
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
    if(!windowConfigured){
        emit signalUpdateConfigSettings(device, *settings);
    }

    windowConfigured = true;

}

void ConfigOSICS_ATN::slotUpdateWindow()
{
    qDebug() << "atn slotUpdateWindow()";
    // clear text entry fields
    ui->attenuationEdit->clear();
    ui->attenuationOffsetEdit->clear();

    // reset text fields
    resetDisplayFieldColoredStatus();

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

    moduleIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    moduleLocation = settings->value(DEVICE_LOCATION).value<QByteArray>();
    attenuationSetting = settings->value(EXFO_OSICS_ATN_ATTENUATION).value<QByteArray>();
    firstMinAttenuation = settings->value(EXFO_OSICS_ATN_MIN_ATTENUATION_1).value<QByteArray>();
    firstMaxAttenuation = settings->value(EXFO_OSICS_ATN_MAX_ATTENUATION_1).value<QByteArray>();
    secondMinAttenuation = settings->value(EXFO_OSICS_ATN_MIN_ATTENUATION_2).value<QByteArray>();
    secondMaxAttenuation = settings->value(EXFO_OSICS_ATN_MAX_ATTENUATION_2).value<QByteArray>();
    refWavelengthNumber = settings->value(EXFO_OSICS_ATN_REF_WAV_NUMBER).value<QByteArray>();
    firstRefWavelength = settings->value(EXFO_OSICS_ATN_REF_WAVELENGTH_1).value<QByteArray>();
    secondRefWavelength = settings->value(EXFO_OSICS_ATN_REF_WAVELENGTH_2).value<QByteArray>();
    firstOffset = settings->value(EXFO_OSICS_ATN_OFFSET_1).value<QByteArray>();
    secondOffset = settings->value(EXFO_OSICS_ATN_OFFSET_2).value<QByteArray>();

}

void ConfigOSICS_ATN::populateAllValues()
{
    populateRefWavelength();
    populateDeviceInfo();
    populateAttenuation();
    populateMinAttenuation();
    populateMaxAttenuation();
    populateOffset();
}

void ConfigOSICS_ATN::populateDeviceInfo(){
    ui->instrumentInfoLabel->setText(moduleIdentity);
    ui->instrumentAddressLabel->setText(moduleLocation);
}
void ConfigOSICS_ATN::populateAttenuation()
{
    ui->attenuationDisplay->setText(QByteArray::number(attenuationSetting.toDouble()));
}

void ConfigOSICS_ATN::populateMinAttenuation()
{
    if(refWavelengthNumber.toInt() == 1){
        ui->minAttenuationDisplay->setText(QByteArray::number(firstMinAttenuation.toDouble()));
    }
    else{
        ui->minAttenuationDisplay->setText(QByteArray::number(secondMinAttenuation.toDouble()));
    }
}

void ConfigOSICS_ATN::populateMaxAttenuation()
{
    if(refWavelengthNumber.toInt() == 1){
        ui->maxAttenuationDisplay->setText(QByteArray::number(firstMaxAttenuation.toDouble()));
    }
    else{
        ui->maxAttenuationDisplay->setText(QByteArray::number(secondMaxAttenuation.toDouble()));
    }
}

void ConfigOSICS_ATN::populateRefWavelength()
{
    ui->refWavelengthRadioButton1->setText(QByteArray::number(firstRefWavelength.toDouble()));
    ui->refWavelengthRadioButton2->setText(QByteArray::number(secondRefWavelength.toDouble()));
}

void ConfigOSICS_ATN::populateOffset()
{
    if(refWavelengthNumber.toInt() == 1){
        ui->attenuationOffsetDisplay->setText(QByteArray::number(firstOffset.toDouble()));
    }
    else{
        ui->attenuationOffsetDisplay->setText(QByteArray::number(secondOffset.toDouble()));
    }

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

    if(isInputValueValid(enteredAtten, firstMinAttenuation, firstMaxAttenuation)){
        attenuationSetting = enteredAtten;
        settings->setValue(EXFO_OSICS_ATN_ATTENUATION, QVariant::fromValue(attenuationSetting));
        attenuationDisplayTextColored = true;
    }

    colorDisplayFieldText();
    ui->attenuationEdit->clearFocus();
}

void ConfigOSICS_ATN::on_attenuationOffsetEdit_editingFinished()
{
    QByteArray enteredOffset = ui->attenuationOffsetEdit->text().toLatin1();
    if(isInputValueValid(enteredOffset, EXFO_OSICS_ATN_MIN_OFFSET, EXFO_OSICS_ATN_MAX_OFFSET)){
        QByteArray offset = enteredOffset;
        if(refWavelengthNumber.toInt() == 1){
            settings->setValue(EXFO_OSICS_ATN_OFFSET_1, QVariant::fromValue(offset));
            attenuationOffsetDisplay1Colored = true;
        }

        else{
            settings->setValue(EXFO_OSICS_ATN_OFFSET_2, QVariant::fromValue(offset));
            attenuationOffsetDisplay2Colored = true;
        }
    }

    colorDisplayFieldText();
    ui->attenuationOffsetEdit->clearFocus();
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
    qDebug() << device;
    emit signalApplyConfigSettings(device, *settings);

    QApplication::restoreOverrideCursor();
}


void ConfigOSICS_ATN::on_refWavelengthRadioButton1_clicked()
{
    refWavelengthNumber = "1";
    settings->setValue(EXFO_OSICS_ATN_REF_WAV_NUMBER, QVariant::fromValue(refWavelengthNumber));
    // change newly selected color to blue and remove color from other radio button
    ui->refWavelengthRadioButton1->setStyleSheet("QRadioButton {color: rgb(0, 0, 255);}");
    ui->refWavelengthRadioButton2->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");

    colorDisplayFieldText();
    populateAllValues();

}

void ConfigOSICS_ATN::on_refWavelengthRadioButton2_clicked()
{
    refWavelengthNumber = "2";
    settings->setValue(EXFO_OSICS_ATN_REF_WAV_NUMBER, QVariant::fromValue(refWavelengthNumber));
    // change newly selected color to blue and remove color from other radio button
    ui->refWavelengthRadioButton2->setStyleSheet("QRadioButton {color: rgb(0, 0, 255);}");
    ui->refWavelengthRadioButton1->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");
    colorDisplayFieldText();
    populateAllValues();
}

void ConfigOSICS_ATN::colorText(QLineEdit *textField, bool colored){
    if(colored){
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 255);}");
    }
    else{
        textField->setStyleSheet("QLineEdit {color: rgb(0, 0, 0);}");
    }
}

void ConfigOSICS_ATN::colorDisplayFieldText(){
    colorText(ui->attenuationDisplay, attenuationDisplayTextColored);

    // set color based on reference wavelength selected
    if(refWavelengthNumber == "1"){
        colorText(ui->attenuationOffsetDisplay, attenuationOffsetDisplay1Colored);
    }
    else{
        colorText(ui->attenuationOffsetDisplay, attenuationOffsetDisplay2Colored);
    }
}

void ConfigOSICS_ATN::resetDisplayFieldColoredStatus(){
    attenuationDisplayTextColored = false;
    attenuationOffsetDisplay1Colored = false;
    attenuationOffsetDisplay2Colored = false;

    ui->refWavelengthRadioButton1->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");
    ui->refWavelengthRadioButton2->setStyleSheet("QRadioButton {color: rgb(0, 0, 0);}");

    colorDisplayFieldText();
}
