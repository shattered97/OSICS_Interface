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

    ui->progressBar->hide();
    qDebug() << "Displaying PM Power Step Test Window";
    if(!isConfigured)
    {
        // setup GUI elements
//        populateT100SelectionComboBox();
//        populatePowerMeterSlotComboBox();

        populateAvailableT100s();
        populatePowerMeterSlots();

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

//void EXFO_T100_PM_Power_Step_Test_Window::populateT100SelectionComboBox()
//{
//    /*
//     * The test .cpp file will do the logic to return a list of strings
//     * by reference where each element is formatted: "<T100 type>, Slot <x>".
//     */
//    QList<QByteArray> displayNames;
//    emit signalGetT100DisplayNames(displayNames);

//    for(auto name : displayNames){
//        ui->t100ComboBox->addItem(name);
//    }

//    // set default value to first item in dropdown
//    ui->t100ComboBox->setCurrentIndex(0);
//}

//void EXFO_T100_PM_Power_Step_Test_Window::populatePowerMeterSlotComboBox()
//{
//    int numberOfSlots;

//    // get number of slots from test class by reference
//    emit signalGetPowerMeterChannels(numberOfSlots);

//    for(int i = 1; i <= numberOfSlots; i++){
//        ui->powerMeterComboBox->addItem(QString::number(i));
//    }

//    // set default value to first item in dropdown
//    ui->powerMeterComboBox->setCurrentIndex(0);
//}

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
            // disable cursor (until test is finished)
            QApplication::setOverrideCursor(Qt::WaitCursor);

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
    ui->startPowerEdit->setEnabled(true);
    ui->endPowerEdit->setEnabled(true);
    ui->powerStepSizeEdit->setEnabled(true);
    ui->dwellEdit->setEnabled(true);
    ui->wavelengthEdit->setEnabled(true);
    ui->startTestButton->setEnabled(true);


}

void EXFO_T100_PM_Power_Step_Test_Window::disableFieldsOnTestStart()
{
    ui->startPowerEdit->setEnabled(false);
    ui->endPowerEdit->setEnabled(false);
    ui->powerStepSizeEdit->setEnabled(false);
    ui->dwellEdit->setEnabled(false);
    ui->wavelengthEdit->setEnabled(false);
    ui->startTestButton->setEnabled(false);

    // clear progress bar
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}

void EXFO_T100_PM_Power_Step_Test_Window::updateSettings()
{
    settings->setValue(T100_PM_POWER_STEP_TEST_START_POWER, QVariant::fromValue(ui->startPowerEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_END_POWER, QVariant::fromValue(ui->endPowerEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_POWER_STEP, QVariant::fromValue(ui->powerStepSizeEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_DWELL, QVariant::fromValue(ui->dwellEdit->text()));
    settings->setValue(T100_PM_POWER_STEP_TEST_WAVELENGTH, QVariant::fromValue(ui->wavelengthEdit->text()));

//    settings->setValue(T100_SLOT_NUM_TO_PM_SLOT_NUM_MAP, QVariant::fromValue(ui->powerMeterComboBox->currentText()));

//    // some parsing needs to be done for the T100 slot number
//    QString selectedT100Text = ui->t100ComboBox->currentText();

//    // format is: "<T100 type>, Slot <x>" so we can expect the slot number to be the last index
//    QString t100SlotNum = QString(selectedT100Text.back());

//    settings->setValue(T100_PM_POWER_STEP_TEST_T100_SLOT_NUM, QVariant::fromValue(t100SlotNum));

    // we now need to pass via settings the T100 slot number/to Power Meter Channel relationship
    QMap<int, int> t100SlotToPMSlot;
    for(int i = 0; i < powerMeterDropdowns.size(); i++){
        // for each dropdown, if its value is not N/A we want to add this "row" to the settings
        if(powerMeterDropdowns[i]->currentText() != "N/A"){
            int t100SlotNum = QString(QString(t100DisplayNames[i]).back()).toInt();
            int powerMeterSlotNum = powerMeterDropdowns[i]->currentText().toInt();
            qDebug() << "t100 slot: " << t100SlotNum;
            qDebug() << "power meter slot: " << powerMeterSlotNum;
            t100SlotToPMSlot.insert(t100SlotNum, powerMeterSlotNum);
        }
    }

    settings->setValue(T100_SLOT_NUM_TO_PM_SLOT_NUM_MAP, QVariant::fromValue(t100SlotToPMSlot));

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

void EXFO_T100_PM_Power_Step_Test_Window::on_showTestDescriptionButton_clicked()
{
    // open small window with test description (steps)
    QMessageBox msgBox;

    msgBox.setText("1. The selected T100 module's output wavelength is set to the specified value.\n"
                   "2. The T100 module's output power is set to the specified start value.\n"
                   "3. The test waits for the amount of time specified in the 'Dwell' field. After waiting, a reading "
                   "is taken from the Power Meter.\n"
                   "4. The T100 module's output power is increased by the amount specified in the 'Power "
                   "Step Size' field.\n"
                   "5. Steps 3-4 are repeated until the 'End Power' value is reached.\n");
    msgBox.exec();
}

void EXFO_T100_PM_Power_Step_Test_Window::populateAvailableT100s()
{
    /*
     * The test .cpp file will do the logic to return a list of strings
     * by reference where each element is formatted: "<T100 type>, Slot <x>".
     */
    emit signalGetT100DisplayNames(t100DisplayNames);

    // use vertical layout
    QVBoxLayout *vBox = new QVBoxLayout();

    for(auto name : t100DisplayNames){
        // create a label with the display name
        QLabel *label = new QLabel();
        label->setText(name);
        vBox->addWidget(label);
        t100DisplayLabel.append(label);
    }

    ui->availableT100sGroupBox->setLayout(vBox);
}

void EXFO_T100_PM_Power_Step_Test_Window::populatePowerMeterSlots()
{
    // get number of slots from test class by reference
    int numberOfSlots;
    emit signalGetPowerMeterChannels(numberOfSlots);

    // use vertical layout
    QVBoxLayout *vBox = new QVBoxLayout();

    // add a dropdown for each T100 module
    for(auto t100 : t100DisplayNames)
    {
        QComboBox *comboBox = new QComboBox;

        // populate the combo box with "N/A"
        comboBox->addItem("N/A");
        allPowerMeterChannelOptions.append("N/A");

        // populate the combo box with numbers (1 thru # of power meter slots)
        for(int i = 1; i <= numberOfSlots; i++){
            comboBox->addItem(QByteArray::number(i));

            // also populate member variable that maintains all original channel options
            allPowerMeterChannelOptions.append(QByteArray::number(i));
        }

        // need to connect combo box to custom slot for maintaining the power meter channels in each dropdown
        connect(comboBox, SIGNAL(currentIndexChanged(int)),
                this, SLOT(slotProcessPowerMeterChannelChange(int)));

        powerMeterDropdowns.append(comboBox);
        vBox->addWidget(comboBox);
    }

    ui->powerMeterSlotsGroupBox->setLayout(vBox);

}

void EXFO_T100_PM_Power_Step_Test_Window::slotProcessPowerMeterChannelChange(int index)
{
    // it seems that if one dropdown box is changed this slot is activated for each one

    QList<QString> textInEachDropdown;
    QList<QString> selectedPowerMeters;

    for(auto dropdown : powerMeterDropdowns) {

        // disable signal while we perform this operation
        disconnect(dropdown, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(slotProcessPowerMeterChannelChange(int)));

        // note what was selected at the time
        QString text = dropdown->currentText();
        textInEachDropdown.append(text);

        if(dropdown->currentText() != "N/A"){
            selectedPowerMeters.append(dropdown->currentText());
        }
    }

    // create list of available power meter channels by subtracting selected channels from all channel options
    QSet<QString> availableChannelsSet = allPowerMeterChannelOptions.toSet().subtract(selectedPowerMeters.toSet());
    availablePowerMeterChannels = availableChannelsSet.toList();

    // sort items so that they're ordered
    availablePowerMeterChannels.sort();

    // refresh dropdown menus with the items only in the availablePowerMeterChannels
    for(int i = 0; i < powerMeterDropdowns.size(); i++){
        powerMeterDropdowns[i]->clear();
        powerMeterDropdowns[i]->addItems(availablePowerMeterChannels);

        // set the appropriate value
        powerMeterDropdowns[i]->insertItem(0, textInEachDropdown[i]);
        powerMeterDropdowns[i]->setCurrentIndex(0);
    }

    // re-connect dropdowns
    for(auto dropdown : powerMeterDropdowns){
        connect(dropdown, SIGNAL(currentIndexChanged(int)),
                this, SLOT(slotProcessPowerMeterChannelChange(int)));
    }

}

void EXFO_T100_PM_Power_Step_Test_Window::slotTestComplete()
{
    // re-enable buttons
    enableFieldsOnTestEnd();

    QApplication::restoreOverrideCursor();

    // show popup that test is complete
    QMessageBox msgBox;
    msgBox.setText("Test is complete!");
    msgBox.exec();


}

void EXFO_T100_PM_Power_Step_Test_Window::slotReceiveTestProgress(double progressPercent)
{
    ui->progressBar->setValue(progressPercent);
}
