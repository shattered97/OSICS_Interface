#include "EXFO_T100_PM_Power_Step_Test_Window.h"
#include "ui_EXFO_T100_PM_Power_Step_Test_Window.h"

EXFO_T100_PM_Power_Step_Test_Window::EXFO_T100_PM_Power_Step_Test_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EXFO_T100_PM_Power_Step_Test_Window)
{
    ui->setupUi(this);

    // initialize settings
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
}

EXFO_T100_PM_Power_Step_Test_Window::~EXFO_T100_PM_Power_Step_Test_Window()
{
    delete ui;
}

void EXFO_T100_PM_Power_Step_Test_Window::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    qDebug() << "Displaying PM Power Step Test Window";
    if(!isConfigured)
    {
        // setup GUI elements
        populateT100SelectionComboBox();
        populatePowerMeterSlotComboBox();

        isConfigured = true;
    }
}

void EXFO_T100_PM_Power_Step_Test_Window::on_t100ComboBox_currentIndexChanged(const QString &selectedText)
{
    // clear wavelength field (new T100 selected and previous wavelength entered may not be compatible)
    ui->wavelengthEdit->clear();
}

void EXFO_T100_PM_Power_Step_Test_Window::on_startPowerEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->startPowerEdit->blockSignals(true);

    QByteArray startPowerEntered = ui->startPowerEdit->text().toLatin1().replace(" ", "");

    if(isInputValueNumeric(startPowerEntered)){
        // #TODO error-checking: start power must be lower than the end power
        //       error-checking: start power must be < max (10 dBm) and > min (?)
    }
    else{
        // messagage boxes executed in isInputValueNumeric - just clear the field
        ui->startPowerEdit->clear();
    }

    // un-focus text edit and un-block signals
    ui->startPowerEdit->clearFocus();
    ui->startPowerEdit->blockSignals(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::on_endPowerEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->endPowerEdit->blockSignals(true);

    QByteArray endPowerEntered = ui->endPowerEdit->text().toLatin1().replace(" ", "");

    if(isInputValueNumeric(endPowerEntered)){
        // #TODO error-checking: end power must be higher than start power
        //       error-checking: end power must be < max (10 dBm) and > min (?)
    }
    else{
        // messagage boxes executed in isInputValueNumeric - just clear the field
        ui->endPowerEdit->clear();
    }

    // un-focus text edit and un-block signals
    ui->endPowerEdit->clearFocus();
    ui->endPowerEdit->blockSignals(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::on_powerStepSizeEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->powerStepSizeEdit->blockSignals(true);

    QByteArray powerStepSizeEntered = ui->powerStepSizeEdit->text().toLatin1().replace(" ", "");

    if(isInputValueNumeric(powerStepSizeEntered)){
        // #TODO error-checking: step size must be greater than zero
        //       error-checking: step size must be less than the the start/end dBm range
    }
    else{
        // messagage boxes executed in isInputValueNumeric - just clear the field
        ui->powerStepSizeEdit->clear();
    }

    // un-focus text edit and un-block signals
    ui->powerStepSizeEdit->clearFocus();
    ui->powerStepSizeEdit->blockSignals(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::on_dwellEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->dwellEdit->blockSignals(true);

    QByteArray dwellEntered = ui->dwellEdit->text().toLatin1().replace(" ", "");

    if(isInputValueNumeric(dwellEntered)){
        // error checking: dwell time must be greater than 0 seconds
        if(dwellEntered.toDouble() <= 0){
            QMessageBox msgBox;
            msgBox.setText("Dwell entered was invalid: must be greater than 0.");
            msgBox.exec();
            ui->dwellEdit->clear();
        }
    }
    else{
        // message boxes executed in isInputValueNumeric() - just clear the field
        ui->dwellEdit->clear();
    }

    // un-focus text edit and un-block signals
    ui->dwellEdit->clearFocus();
    ui->dwellEdit->blockSignals(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::on_wavelengthEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->wavelengthEdit->blockSignals(true);

    QByteArray wavelengthEntered = ui->wavelengthEdit->text().toLatin1().replace(" ", "");

    if(isInputValueNumeric(wavelengthEntered)){
        // #TODO error-checking: wavelength must be checked against the range for the *currently selected* T100
    }
    else{
        // message boxes executed in isInputValueNumeric - just clear the field
        ui->wavelengthEdit->clear();
    }

    // un-focus text edit and un-block signals
    ui->wavelengthEdit->clearFocus();
    ui->wavelengthEdit->blockSignals(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::populateT100SelectionComboBox()
{
    /*
     * The test .cpp file will do the logic to return a list of strings
     * by reference where each element is formatted: "<T100 type>, Slot <x>".
     */
    QList<QByteArray> displayNames;
    emit signalGetT100DisplayNames(displayNames);

    for(auto name : displayNames){
        ui->t100ComboBox->addItem(name);
    }

    // set default value to first item in dropdown
    ui->t100ComboBox->setCurrentIndex(0);
}

void EXFO_T100_PM_Power_Step_Test_Window::populatePowerMeterSlotComboBox()
{
    int numberOfSlots;

    // get number of slots from test class by reference
    emit signalGetPowerMeterChannels(numberOfSlots);

    for(int i = 1; i <= numberOfSlots; i++){
        ui->powerMeterComboBox->addItem(QString::number(i));
    }

    // set default value to first item in dropdown
    ui->powerMeterComboBox->setCurrentIndex(0);
}

bool EXFO_T100_PM_Power_Step_Test_Window::areAllFieldsCompleted()
{
    bool success = true;

    // declaring these for readability
    bool isStartPowerEmpty = ui->startPowerEdit->text().isEmpty();
    bool isEndPowerEmpty = ui->endPowerEdit->text().isEmpty();
    bool isStepSizeEmpty = ui->powerStepSizeEdit->text().isEmpty();
    bool isWavelengthEmpty = ui->wavelengthEdit->text().isEmpty();
    bool isDwellEmpty = ui->dwellEdit->text().isEmpty();

    if(isStartPowerEmpty || isEndPowerEmpty || isStepSizeEmpty || isWavelengthEmpty || isDwellEmpty)
    {
        QMessageBox msgBox;
        msgBox.setText("Cannot start test. Make sure all test settings are entered.");
        msgBox.exec();
        success = false;
    }

    return success;
}

void EXFO_T100_PM_Power_Step_Test_Window::on_startTestButton_clicked()
{
    // check if inputs are valid
    if(areAllFieldsCompleted()){
        // ask user to confirm
        QMessageBox msgBox;
        msgBox.setText("Confirm test settings.  The test will begin upon clicking 'OK'");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

        int buttonThatWasClicked = msgBox.exec();
        if(buttonThatWasClicked == QMessageBox::Ok){
            //disable fields and tell test class to start executing
            disableFieldsOnTestStart();

            // populates QSettings object
            updateSettings();

            emit signalBeginTest(settings);
        }
    }
    else{
       // do nothing - user was presented a dialog box in areAllFieldsCompleted()
    }
}

void EXFO_T100_PM_Power_Step_Test_Window::enableFieldsOnTestEnd()
{
    ui->t100ComboBox->setEnabled(true);
    ui->powerMeterComboBox->setEnabled(true);
    ui->startPowerEdit->setEnabled(true);
    ui->endPowerEdit->setEnabled(true);
    ui->powerStepSizeEdit->setEnabled(true);
    ui->dwellEdit->setEnabled(true);
    ui->wavelengthEdit->setEnabled(true);
    ui->startTestButton->setEnabled(true);
}

void EXFO_T100_PM_Power_Step_Test_Window::disableFieldsOnTestStart()
{
    ui->t100ComboBox->setEnabled(false);
    ui->powerMeterComboBox->setEnabled(false);
    ui->startPowerEdit->setEnabled(false);
    ui->endPowerEdit->setEnabled(false);
    ui->powerStepSizeEdit->setEnabled(false);
    ui->dwellEdit->setEnabled(false);
    ui->wavelengthEdit->setEnabled(false);
    ui->startTestButton->setEnabled(false);
}

void EXFO_T100_PM_Power_Step_Test_Window::updateSettings()
{
    settings->setValue(T100_PM_POWER_STEP_TEST_START_POWER, QVariant::fromValue(ui->startPowerEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_END_POWER, QVariant::fromValue(ui->endPowerEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_POWER_STEP, QVariant::fromValue(ui->powerStepSizeEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_DWELL, QVariant::fromValue(ui->dwellEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_WAVELENGTH, QVariant::fromValue(ui->wavelengthEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_PM_SLOT_NUM, QVariant::fromValue(ui->powerMeterComboBox->currentText()));

    // some parsing needs to be done for the T100 slot number
    QString selectedT100Text = ui->t100ComboBox->currentText();

    // format is: "<T100 type>, Slot <x>" so we can expect the slot number to be the last index
    QString t100SlotNum = QString(selectedT100Text.back());

    settings->setValue(T100_PM_POWER_STEP_TEST_T100_SLOT_NUM, QVariant::fromValue(t100SlotNum));
}

bool EXFO_T100_PM_Power_Step_Test_Window::isInputValueNumeric(QByteArray inputValue)
{
    bool isNumeric = true;
    if(inputValue == ""){
        // invalid if empty, but no error message needed
        isNumeric = false;
    }
    else{
        bool conversionOk = true;
        inputValue.toDouble(&conversionOk);

        if(!conversionOk){
            // if we can't convert to double, value is non-numeric - error message
            isNumeric = false;
            QMessageBox msgBox;
            msgBox.setText(GUI_ERR_NON_NUMERIC_VALUE);
            msgBox.exec();
        }
    }

    return isNumeric;
}
