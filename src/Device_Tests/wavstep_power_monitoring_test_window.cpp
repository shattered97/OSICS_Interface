#include "wavstep_power_monitoring_test_window.h"
#include "ui_wavstep_power_monitoring_test_window.h"
#include "ConversionUtilities.h"
#include <QCheckBox>

WavStep_Power_Monitoring_Test_Window::WavStep_Power_Monitoring_Test_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WavStep_Power_Monitoring_Test_Window)
{
    ui->setupUi(this);

    // initialize settings
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    qRegisterMetaTypeStreamOperators<QMap<int, QByteArray>>("swtChannelToT100Map");
}

WavStep_Power_Monitoring_Test_Window::~WavStep_Power_Monitoring_Test_Window()
{
    delete ui;
}

void WavStep_Power_Monitoring_Test_Window::showEvent(QShowEvent* event){
    QWidget::showEvent(event);

    populateSwitchChannelSelectionDropdowns();
    populateSwtChannelToT100Map();
    populatePowerMeterListWidget();

    emit signalPollForPowerMeterReadings();
}



void WavStep_Power_Monitoring_Test_Window::slotDisplayPowerReadings(QByteArray powerMeterIdentity, QList<QByteArray> readings){


    for(int i = 0; i < readings.size(); i++){
        // find row index based on identity and channel (i - 1)
        int rowCount = ui->powerMeterTable->rowCount();
        int rowIndex = 0;

        for(int j = 0; j < rowCount; j++){

            QByteArray identityInRow = ui->powerMeterTable->item(j, 0)->text().toLatin1();
            int channelNum = ui->powerMeterTable->item(j, 1)->text().toInt();

            if(identityInRow == powerMeterIdentity && channelNum == i + 1){
                rowIndex = j;
            }
        }
        // make cell to display power meter reading
        QTableWidgetItem *powerReadingCell = new QTableWidgetItem;
        ui->powerMeterTable->setItem(rowIndex, 3, powerReadingCell);

        double readingInDBm = ConversionUtilities::convertWattToDBm(readings[i].toDouble());
        powerReadingCell->setText(QByteArray::number(readingInDBm));
    }
}

void WavStep_Power_Monitoring_Test_Window::populatePowerMeterListWidget(){
    // power meter, channel number, graph, power reading

    // signal to test class to get QList of power meter name, channel number pairs
    emit signalGetPowerMeterDisplayPairs(powerMeterDisplayPairs);

    if(powerMeterDisplayPairs.size() > 0){
        for(int i = 0; i < powerMeterDisplayPairs.size(); i++){
            ui->powerMeterTable->insertRow(i);

            // create cell for power meter identity info
            QTableWidgetItem *identityCell = new QTableWidgetItem;
            ui->powerMeterTable->setItem(i, 0, identityCell);
            identityCell->setText(powerMeterDisplayPairs[i].first);

            // create cell for power meter channel num
            QTableWidgetItem *channelCell = new QTableWidgetItem;
            channelCell->setTextAlignment(Qt::AlignCenter);
            ui->powerMeterTable->setItem(i, 1, channelCell);
            channelCell->setText(QByteArray::number(powerMeterDisplayPairs[i].second));

            // create checkboxes for graphing
            QWidget *checkBox = new QCheckBox();
            ui->powerMeterTable->setCellWidget(i, 2, checkBox);

        }
    }
}

void WavStep_Power_Monitoring_Test_Window::on_openGraphWindowButton_clicked()
{
    emit signalShowGraphWindow();
}


void WavStep_Power_Monitoring_Test_Window::populateSwtChannelToT100Map(){
    swtChannelToT100Map.clear();
    swtChannelToT100Map.insert(1, ui->swtChannel1ComboBox->currentText().toLatin1());
    swtChannelToT100Map.insert(2, ui->swtChannel2ComboBox->currentText().toLatin1());
    swtChannelToT100Map.insert(3, ui->swtChannel3ComboBox->currentText().toLatin1());
    swtChannelToT100Map.insert(4, ui->swtChannel4ComboBox->currentText().toLatin1());
}

bool WavStep_Power_Monitoring_Test_Window::areAllFieldsCompleted(){
    bool success = true;

    bool dwellEmpty = ui->dwellLineEdit->text().isEmpty();
    qDebug() << dwellEmpty;
    bool stepSizeEmpty = ui->stepSizeLineEdit->text().isEmpty();
    qDebug() << stepSizeEmpty;
    bool startWavEmpty = ui->startWavLineEdit->text().isEmpty();
    qDebug() << startWavEmpty;
    bool endWavEmpty = ui->endWavLineEdit->text().isEmpty();
    qDebug() << endWavEmpty;

    if(dwellEmpty || stepSizeEmpty || startWavEmpty || endWavEmpty){
        QMessageBox msgBox;
        msgBox.setText("Make sure all fields for start/end wavelength, dwell and step size are complete.");
        msgBox.exec();
        success = false;
    }

    return success;
}

void WavStep_Power_Monitoring_Test_Window::on_beginTestPB_clicked()
{
    // if there is no t100 selected for any SWT slot, error message
    if(!t100SelectedForSwitch){
        QMessageBox msgBox;
        msgBox.setText("No T100 modules selected for switch channels.");
        msgBox.exec();
    }
    // if a file hasn't been chosen for data output, error message
    if(ui->csvLocDisplay->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Choose output .csv file for test data.");
        msgBox.exec();
    }
    else if(areAllFieldsCompleted()){
        // create graph window
        QList<QByteArray> seriesNames = getSeriesNames();

        if(seriesNames.size() <= 0){
            QMessageBox msgBox;
            msgBox.setText("Select at least one series to graph.");
            msgBox.exec();
        }
        else{
            ui->beginTestPB->setEnabled(false);
            ui->openGraphWindowButton->setEnabled(true);

            updateSettings();

            emit signalBeginTest(settings);

        }


    }

}

QList<QByteArray> WavStep_Power_Monitoring_Test_Window::getSeriesNames(){
    // see which checkboxes are selected
    seriesNames.clear();
    int rowCount = ui->powerMeterTable->rowCount();
    qDebug() << "row count: " << rowCount;
    for(int i = 0; i < rowCount; i++){
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->powerMeterTable->cellWidget(i, 2));
        if(checkBox->isChecked()){
            QByteArray identity = ui->powerMeterTable->item(i, 0)->text().toLatin1();
            QByteArray channel = " Channel " + ui->powerMeterTable->item(i,1)->text().toLatin1();
            QByteArray seriesName =  identity + channel;
            qDebug() << "adding name " << seriesName;
            seriesNames.append(seriesName);
        }
    }
    return seriesNames;
}

void WavStep_Power_Monitoring_Test_Window::updateSettings()
{
    qDebug() << "setting config values";
    settings->setValue(WAV_STEP_TEST_CSV_FILENAME, QVariant::fromValue(ui->csvLocDisplay->text()));
    settings->setValue(WAV_STEP_TEST_POWER_POLL_RATE, QVariant::fromValue(ui->pmReadingRefreshRateEdit));
    settings->setValue(WAV_STEP_TEST_START_WAVELENGTH, QVariant::fromValue(ui->startWavLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_END_WAVELENGTH, QVariant::fromValue(ui->endWavLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_WAV_STEP_SIZE, QVariant::fromValue(ui->stepSizeLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_DWELL_SECONDS, QVariant::fromValue(ui->dwellLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_SWT_CHANNELS_TO_T100, QVariant::fromValue(swtChannelToT100Map));
    settings->setValue(WAV_STEP_TEST_CHANNELS_TO_GRAPH, QVariant::fromValue(seriesNames));

}

void WavStep_Power_Monitoring_Test_Window::populateSwitchChannelSelectionDropdowns()
{
    QList<QByteArray> displayNames;
    emit signalGetT100DisplayNames(displayNames);
    for(auto e : displayNames){
        ui->swtChannel1ComboBox->addItem(e);
        ui->swtChannel2ComboBox->addItem(e);
        ui->swtChannel3ComboBox->addItem(e);
        ui->swtChannel4ComboBox->addItem(e);
    }
}

void WavStep_Power_Monitoring_Test_Window::handleSwitchDropdownAction(QComboBox *dropdown)
{
    QByteArray dropdownText = dropdown->currentText().toLatin1();

    // you can't choose a T100 that has already been selected
    bool selectionValid = true;
    for(auto e : swtChannelToT100Map.keys()){
        QByteArray mapValue = swtChannelToT100Map.value(e);
        if((dropdownText == mapValue) && (dropdownText != "<None>")){
            selectionValid = false;
        }
    }

    if(selectionValid){
        populateSwtChannelToT100Map();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("T100 Module " + dropdownText + " is already selected for another channel.");
        msgBox.exec();
        dropdown->setCurrentIndex(0);
    }

    // if all dropdowns are <none> set flag t100SelectedForSwitch to false
    if(ui->swtChannel1ComboBox->currentText() != "<None>" || ui->swtChannel2ComboBox->currentText() != "<None>" ||
       ui->swtChannel3ComboBox->currentText() != "<None>" || ui->swtChannel4ComboBox->currentText() != "<None>" ){
       t100SelectedForSwitch = true;
    }
    else{
        t100SelectedForSwitch = false;
    }


    emit signalSwitchMapChanged(swtChannelToT100Map);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel1ComboBox_currentIndexChanged(const QString &arg1)
{
    handleSwitchDropdownAction(ui->swtChannel1ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel2ComboBox_currentIndexChanged(const QString &arg1)
{
    handleSwitchDropdownAction(ui->swtChannel2ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel3ComboBox_currentIndexChanged(const QString &arg1)
{
    handleSwitchDropdownAction(ui->swtChannel3ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel4ComboBox_currentIndexChanged(const QString &arg1)
{
    handleSwitchDropdownAction(ui->swtChannel4ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::slotUpdateMinMaxWavelength(double minWav, double maxWav){
    ui->minWavDisplay->setText(QByteArray::number(minWav));
    ui->maxWavDisplay->setText(QByteArray::number(maxWav));
}

void WavStep_Power_Monitoring_Test_Window::on_startWavLineEdit_editingFinished()
{
    ui->startWavLineEdit->blockSignals(true);
    QByteArray startWav = ui->startWavLineEdit->text().toLatin1().replace(" " , "");
    QByteArray endWav = ui->endWavLineEdit->text().toLatin1().replace(" " , "");

    if(isInputValueValid(startWav)){
        handleWavelengthErrorCases(ui->startWavLineEdit);
        if(startWav.toDouble() >= endWav.toDouble() && endWav != ""){
            QMessageBox msgBox;
            msgBox.setText("Start wavelength should be less than the end wavelength.");
            msgBox.exec();
            ui->startWavLineEdit->clear();
        }
    }
    else{
        ui->startWavLineEdit->clear();
    }

    ui->startWavLineEdit->clearFocus();
    calculateTestRuntime();
    ui->startWavLineEdit->blockSignals(false);
}


void WavStep_Power_Monitoring_Test_Window::on_endWavLineEdit_editingFinished()
{
    ui->endWavLineEdit->blockSignals(true);
    QByteArray endWav = ui->endWavLineEdit->text().toLatin1().replace(" " , "");
    QByteArray startWav = ui->startWavLineEdit->text().toLatin1().replace(" " , "");

    if(isInputValueValid(endWav)){
        handleWavelengthErrorCases(ui->endWavLineEdit);

        if(endWav.toDouble() <= startWav.toDouble() && startWav != ""){
            QMessageBox msgBox;
            msgBox.setText("End wavelength should be greater than the start wavelength.");
            msgBox.exec();
            ui->endWavLineEdit->clear();
        }
    }
    else{
        ui->endWavLineEdit->clear();
    }

    ui->endWavLineEdit->clearFocus();
    calculateTestRuntime();
    ui->endWavLineEdit->blockSignals(false);
}

void WavStep_Power_Monitoring_Test_Window::handleWavelengthErrorCases(QLineEdit *lineEdit)
{
    QByteArray wavelength = lineEdit->text().toLatin1().replace(" " , "");
    QByteArray minWav = ui->minWavDisplay->text().toLatin1();
    QByteArray maxWav = ui->maxWavDisplay->text().toLatin1();

    if(minWav.toDouble() <= 0 || maxWav.toDouble() <= 0){
        QMessageBox msgBox;
        msgBox.setText("Assign T100 Modules to switch channels before setting wavelength.");
        msgBox.exec();
        lineEdit->clear();
    }
    else if(wavelength.toDouble() < minWav.toDouble() || wavelength.toDouble() > maxWav.toDouble()){
        QMessageBox msgBox;
        msgBox.setText("Value entered is invalid (out of min/max range).");
        msgBox.exec();
        lineEdit->clear();
    }
}

bool WavStep_Power_Monitoring_Test_Window::isInputValueValid(QByteArray inputValue){
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
    }

    return valid;
}

void WavStep_Power_Monitoring_Test_Window::on_dwellLineEdit_editingFinished()
{
    ui->dwellLineEdit->blockSignals(true);
    QByteArray dwellTime = ui->dwellLineEdit->text().toLatin1();

    if(isInputValueValid(dwellTime)){
        if(dwellTime.toDouble() < 0){
            QMessageBox msgBox;
            msgBox.setText("Dwell time must be greater than or equal to 0.");
            msgBox.exec();
            ui->dwellLineEdit->clear();
        }
        else{
            dwellTimeInSeconds = convertDwellToSeconds(dwellTime.toDouble());
        }
    }
    else{
        ui->dwellLineEdit->clear();
    }

    ui->dwellLineEdit->clearFocus();
    calculateTestRuntime();
    ui->dwellLineEdit->blockSignals(false);
}

void WavStep_Power_Monitoring_Test_Window::on_stepSizeLineEdit_editingFinished()
{
    ui->stepSizeLineEdit->blockSignals(true);
    QByteArray stepSize = ui->stepSizeLineEdit->text().toLatin1();

    if(isInputValueValid(stepSize)){
        if(stepSize.toDouble() <= 0){
            QMessageBox msgBox;
            msgBox.setText("Step size must be greater than 0.");
            msgBox.exec();
            ui->stepSizeLineEdit->clear();
        }
    }
    else{
        ui->stepSizeLineEdit->clear();
    }

    ui->stepSizeLineEdit->clearFocus();
    calculateTestRuntime();
    ui->stepSizeLineEdit->blockSignals(false);

}

void WavStep_Power_Monitoring_Test_Window::calculateTestRuntime(){
    QByteArray startWav = ui->startWavLineEdit->text().toLatin1();
    QByteArray endWav = ui->endWavLineEdit->text().toLatin1();
    QByteArray dwell = ui->dwellLineEdit->text().toLatin1();
    QByteArray stepSize = ui->stepSizeLineEdit->text().toLatin1();
    QByteArray pmPollRate = ui->pmReadingRefreshRateEdit->text().toLatin1();

    // check if any fields are missing
    if(startWav == "" || endWav == "" || dwell == "" || stepSize == "" || pmPollRate == ""){
        ui->estimatedTimeDisplay->clear();
    }
    else{
        // calculate time
        double wavelengthRange = endWav.toDouble() - startWav.toDouble();
        double numSteps = wavelengthRange / stepSize.toDouble();
        double estimatedTime = numSteps * dwellTimeInSeconds;
        QByteArray displayTime = QDateTime::fromTime_t(estimatedTime).toUTC().toString("hh:mm:ss").toLatin1();
        ui->estimatedTimeDisplay->setText(displayTime);
    }
}

double WavStep_Power_Monitoring_Test_Window::convertDwellToSeconds(double dwell){
    double convertedDwell = dwell;
    if(ui->dwellSRadioButton->isChecked()){
        convertedDwell = dwell;
    }
    else if(ui->dwellMsecRadioButton->isChecked()){
        convertedDwell = dwell / 1000;
    }
    else if(ui->dwellMinRadioButton->isChecked()){
        convertedDwell = dwell * 60;
    }
    return convertedDwell;
}


void WavStep_Power_Monitoring_Test_Window::on_dwellMinRadioButton_clicked()
{

    double displayDwell = dwellTimeInSeconds / 60;
    if(dwellTimeInSeconds >= 0){
        ui->dwellLineEdit->setText(QByteArray::number(displayDwell));
    }
}

void WavStep_Power_Monitoring_Test_Window::on_dwellSRadioButton_clicked()
{

    if(dwellTimeInSeconds >= 0){
        ui->dwellLineEdit->setText(QByteArray::number(dwellTimeInSeconds));
    }
}

void WavStep_Power_Monitoring_Test_Window::on_dwellMsecRadioButton_clicked()
{
    double displayDwell = dwellTimeInSeconds * 1000;
    if(dwellTimeInSeconds >= 0){
        ui->dwellLineEdit->setText(QByteArray::number(displayDwell));
    }
}


void WavStep_Power_Monitoring_Test_Window::on_selectCsvLocButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Output .csv File"), "",
            tr("Data (*.csv);;All Files (*)"));

    if (!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::Append)){
            QMessageBox::information(this, tr("Can't open file"), file.errorString());
        }
        else{
            QByteArray outputCsvFilename = file.fileName().toLatin1();
            ui->csvLocDisplay->setText(outputCsvFilename);
            file.close();
        }
    }
}

void WavStep_Power_Monitoring_Test_Window::on_pmReadingRefreshRateEdit_editingFinished()
{

    ui->pmReadingRefreshRateEdit->blockSignals(true);
    QByteArray pollRate = ui->pmReadingRefreshRateEdit->text().toLatin1();

    if(isInputValueValid(pollRate)){
        if(pollRate.toDouble() <= 0){
            QMessageBox msgBox;
            msgBox.setText("Graph refresh rate must be greater than 0 seconds.");
            msgBox.exec();
            ui->pmReadingRefreshRateEdit->clear();
        }
    }
    else{
        ui->pmReadingRefreshRateEdit->clear();
    }

    ui->pmReadingRefreshRateEdit->clearFocus();
    ui->pmReadingRefreshRateEdit->blockSignals(false);

}
