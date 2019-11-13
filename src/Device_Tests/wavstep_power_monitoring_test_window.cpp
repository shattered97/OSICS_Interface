#include "wavstep_power_monitoring_test_window.h"
#include "ui_wavstep_power_monitoring_test_window.h"


WavStep_Power_Monitoring_Test_Window::WavStep_Power_Monitoring_Test_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WavStep_Power_Monitoring_Test_Window)
{
    ui->setupUi(this);

    // initialize settings
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    qRegisterMetaTypeStreamOperators<QMap<int, QByteArray>>("swtChannelToT100Map");

    // set default GUI value for filename
    QString timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss");
    QString defaultFilename = QDir::currentPath() + "/" + WAVSTEP_DEFAULT_CSV_FILENAME.arg(timestamp);
    ui->csvLocDisplay->setText(defaultFilename);

    ui->powerMeterTable->setColumnWidth(0, 500);
}

WavStep_Power_Monitoring_Test_Window::~WavStep_Power_Monitoring_Test_Window()
{
    delete settings;
    delete graphWindow;
    delete ui;
}

void WavStep_Power_Monitoring_Test_Window::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    if(!isConfigured){
        // setup gui elements
        populateSwitchChannelSelectionDropdowns();
        populateSwtChannelToT100Map();
        populatePowerMeterListWidget();

        // ask test class to start polling for power meter readings
        emit signalPollForPowerMeterReadings();

        isConfigured = true;
    }
}

void WavStep_Power_Monitoring_Test_Window::closeEvent(QCloseEvent* event)
{
    // signal to test class to stop all worker threads
    qDebug() << "CLOSE TEST THREADS/WINDOWS";
    emit signalStopAllWorkerThreads();
    emit signalTestWindowClosed();
    event->accept();
}

void WavStep_Power_Monitoring_Test_Window::slotTestCompleted(){
    // display message to users that the test is complete
    QMessageBox msgBox;
    msgBox.setText("Test is complete. You may close the window.");
    msgBox.exec();

    // re-enable appropriate buttons/fields
    enableFieldsOnTestFinish();

}

void WavStep_Power_Monitoring_Test_Window::slotDisplayPowerReadings(QByteArray powerMeterIdentity,
                                                                    QList<QByteArray> readings)
{
    // parse list of power readings into the appropriate cell in the table
    for(int i = 0; i < readings.size(); i++){

        int rowCount = ui->powerMeterTable->rowCount();
        int rowIndex = 0;

        for(int j = 0; j < rowCount; j++){

            QByteArray identityInRow = ui->powerMeterTable->item(j, 0)->text().toLatin1();
            int channelNum = ui->powerMeterTable->item(j, 1)->text().toInt();
            if(identityInRow.contains(powerMeterIdentity) && channelNum == i + 1){
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
    bool stepSizeEmpty = ui->stepSizeLineEdit->text().isEmpty();
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
        msgBox.setText(WAVSTEP_NO_T100_MODULES_SELECTED);
        msgBox.exec();
    }
    // if a file hasn't been chosen for data output, error message
    if(ui->csvLocDisplay->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText(WAVSTEP_NO_FILE_CHOSEN);
        msgBox.exec();
    }
    else if(areAllFieldsCompleted()){
        // create graph window
        QList<QByteArray> seriesNames = getSeriesNames();

        if(seriesNames.size() <= 0){
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_NO_SERIES_SELECTED);
            msgBox.exec();
        }
        else{
            // enable/disable appropriate buttons and fields
            disableFieldsOnTestStart();

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

    settings->setValue(WAV_STEP_TEST_CSV_FILENAME, QVariant::fromValue(ui->csvLocDisplay->text()));
    settings->setValue(WAV_STEP_TEST_POWER_POLL_RATE, QVariant::fromValue(ui->graphRefreshRateEdit->text()));
    settings->setValue(WAV_STEP_TEST_START_WAVELENGTH, QVariant::fromValue(ui->startWavLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_END_WAVELENGTH, QVariant::fromValue(ui->endWavLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_WAV_STEP_SIZE, QVariant::fromValue(ui->stepSizeLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_DWELL_SECONDS, QVariant::fromValue(ui->dwellLineEdit->text()));
    settings->setValue(WAV_STEP_TEST_SWT_CHANNELS_TO_T100, QVariant::fromValue(swtChannelToT100Map));
    settings->setValue(WAV_STEP_TEST_CHANNELS_TO_GRAPH, QVariant::fromValue(seriesNames));
    settings->setValue(WAV_STEP_TEST_POINTS_PER_SERIES, QVariant::fromValue(ui->seriesDataPointsEdit->text()));
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

void WavStep_Power_Monitoring_Test_Window::handleSwitchDropdownAction(QComboBox &dropdown)
{
    // get text from dropdown
    QString dropdownText = dropdown.currentText().toLatin1();

    // you can't choose a T100 that has already been selected
    bool selectionValid = true;
    for(auto e : swtChannelToT100Map.keys()){
        // you can't choose a T100 that has already been selected
        QByteArray t100TypeAndSlot = swtChannelToT100Map.value(e);
        if((dropdownText == t100TypeAndSlot) && (dropdownText != "<None>")){
            selectionValid = false;
        }
    }

    if(selectionValid){
        // valid - we can add assign this switch channel to the selected T100
        populateSwtChannelToT100Map();
    }
    else{
        // invalid - display error message
        QMessageBox msgBox;
        msgBox.setText(QString(WAVSTEP_SWITCH_CHANNEL_TAKEN).arg(dropdownText));
        msgBox.exec();
        dropdown.setCurrentIndex(0);
    }

    // if all dropdowns are <none> set flag t100SelectedForSwitch to false
    if(ui->swtChannel1ComboBox->currentText() != "<None>" || ui->swtChannel2ComboBox->currentText() != "<None>" ||
       ui->swtChannel3ComboBox->currentText() != "<None>" || ui->swtChannel4ComboBox->currentText() != "<None>" ){
       t100SelectedForSwitch = true;
    }
    else{
        t100SelectedForSwitch = false;
    }

    // emit signal to test class that the switch selections have changed
    emit signalSwitchMapChanged(swtChannelToT100Map);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel1ComboBox_currentIndexChanged()
{
    handleSwitchDropdownAction(*ui->swtChannel1ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel2ComboBox_currentIndexChanged()
{
    handleSwitchDropdownAction(*ui->swtChannel2ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel3ComboBox_currentIndexChanged()
{
    handleSwitchDropdownAction(*ui->swtChannel3ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::on_swtChannel4ComboBox_currentIndexChanged()
{
    handleSwitchDropdownAction(*ui->swtChannel4ComboBox);
}

void WavStep_Power_Monitoring_Test_Window::slotUpdateMinMaxWavelength(double minWav, double maxWav){
    // populate the min/max wavelength gui fields
    ui->minWavDisplay->setText(QByteArray::number(minWav));
    ui->maxWavDisplay->setText(QByteArray::number(maxWav));
}

void WavStep_Power_Monitoring_Test_Window::on_startWavLineEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->startWavLineEdit->blockSignals(true);

    QByteArray startWav = ui->startWavLineEdit->text().toLatin1().replace(" " , "");
    QByteArray endWav = ui->endWavLineEdit->text().toLatin1().replace(" " , "");

    if(isInputValueValid(startWav)){
        // check wavelength specific error cases
        handleWavelengthErrorCases(ui->startWavLineEdit);

        if(startWav.toDouble() >= endWav.toDouble() && endWav != ""){
            // if start wavelength is greater than end wavelength - error message
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_START_NOT_LESS_THAN_END);
            msgBox.exec();
            ui->startWavLineEdit->clear();
        }
    }
    else{
        // invalid - clear field
        ui->startWavLineEdit->clear();
    }

    // update test runtime
    calculateTestRuntime();

    ui->startWavLineEdit->clearFocus();
    ui->startWavLineEdit->blockSignals(false);
}


void WavStep_Power_Monitoring_Test_Window::on_endWavLineEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->endWavLineEdit->blockSignals(true);

    QByteArray endWav = ui->endWavLineEdit->text().toLatin1().replace(" " , "");
    QByteArray startWav = ui->startWavLineEdit->text().toLatin1().replace(" " , "");

    if(isInputValueValid(endWav)){
        // check wavelength specific error cases
        handleWavelengthErrorCases(ui->endWavLineEdit);

        if(endWav.toDouble() <= startWav.toDouble() && startWav != ""){
            // if start wavelength is less than end wavelength - error message
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_END_NOT_GREATER_THAN_START);
            msgBox.exec();
            ui->endWavLineEdit->clear();
        }
    }
    else{
        // not valid - clear field
        ui->endWavLineEdit->clear();
    }

    // update estimated runtime
    calculateTestRuntime();

    ui->endWavLineEdit->clearFocus();
    ui->endWavLineEdit->blockSignals(false);
}

void WavStep_Power_Monitoring_Test_Window::handleWavelengthErrorCases(QLineEdit *lineEdit)
{
    QByteArray wavelength = lineEdit->text().toLatin1().replace(" " , "");
    QByteArray minWav = ui->minWavDisplay->text().toLatin1();
    QByteArray maxWav = ui->maxWavDisplay->text().toLatin1();

    // check if there is a switch module assigned (if not, there's no baseline for min/max)
    if(minWav.toDouble() <= 0 || maxWav.toDouble() <= 0){
        QMessageBox msgBox;
        msgBox.setText(WAVSTEP_NO_T100_ASSIGNED_TO_SWT);
        msgBox.exec();
        lineEdit->clear();
    }
    // check if the wavelength is within min/max range
    else if(wavelength.toDouble() < minWav.toDouble() || wavelength.toDouble() > maxWav.toDouble()){
        QMessageBox msgBox;
        msgBox.setText(WAVSTEP_VALUE_OUT_OF_RANGE);
        msgBox.exec();
        lineEdit->clear();
    }
}

bool WavStep_Power_Monitoring_Test_Window::isInputValueValid(QByteArray inputValue)
{
    bool valid = true;
    if(inputValue == ""){
        // invalid if empty, but no error message needed
        valid = false;
    }
    else{
        bool conversionOk = true;
        inputValue.toDouble(&conversionOk);

        if(!conversionOk){
            // if we can't convert to double, value is non-numeric - error message
            valid = false;
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_VALUE_NON_NUMERIC);
            msgBox.exec();
        }
    }

    return valid;
}

void WavStep_Power_Monitoring_Test_Window::on_dwellLineEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->dwellLineEdit->blockSignals(true);

    // check if dwell time entered is valid
    QByteArray dwellTime = ui->dwellLineEdit->text().toLatin1();
    if(isInputValueValid(dwellTime)){
        if(dwellTime.toDouble() < 0){
            // can't be below 0 - error message and clear field
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_DWELL_TIME_INVALID);
            msgBox.exec();
            ui->dwellLineEdit->clear();
        }
        else{
            // value is valid - convert to seconds and store
            dwellTimeInSeconds = convertDwellToSeconds(dwellTime.toDouble());
        }
    }
    else{
        // value was invalid - clear field
        ui->dwellLineEdit->clear();
    }

    // update estimated runtime
    calculateTestRuntime();

    ui->dwellLineEdit->clearFocus();
    ui->dwellLineEdit->blockSignals(false);
}

void WavStep_Power_Monitoring_Test_Window::on_stepSizeLineEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->stepSizeLineEdit->blockSignals(true);

    // check if step size entered is valid
    QByteArray stepSize = ui->stepSizeLineEdit->text().toLatin1();
    if(isInputValueValid(stepSize)){
        if(stepSize.toDouble() <= 0){
            // can't be below 0 - error message and clear field
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_STEP_SIZE_INVALID);
            msgBox.exec();
            ui->stepSizeLineEdit->clear();
        }
    }
    else{
        // value was invalid - clear field
        ui->stepSizeLineEdit->clear();
    }

    // update estimated runtime
    calculateTestRuntime();

    // unblock signals and clear focus
    ui->stepSizeLineEdit->clearFocus();
    ui->stepSizeLineEdit->blockSignals(false);
}

void WavStep_Power_Monitoring_Test_Window::on_seriesDataPointsEdit_editingFinished()
{
    // block signals (to prevent QT bug for double-enter)
    ui->seriesDataPointsEdit->blockSignals(true);

    // check if number of data points is valid
    QByteArray dataPoints = ui->seriesDataPointsEdit->text().toLatin1();
    if(isInputValueValid(dataPoints)){
        if(dataPoints.toInt() <= 0){
            // can't be below 0 - error message and clear field
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_SERIES_DATA_POINTS_INVALID);
            msgBox.exec();
            ui->seriesDataPointsEdit->clear();
        }
        else{
            // re-display as int (in case users enter a decimal)
            ui->seriesDataPointsEdit->setText(QByteArray::number(dataPoints.toInt()));
        }
    }
    else{
        // value was invalid - clear field
        ui->seriesDataPointsEdit->clear();
    }

    // unblock signals and clear focus
    ui->seriesDataPointsEdit->clearFocus();
    ui->seriesDataPointsEdit->blockSignals(false);
}


void WavStep_Power_Monitoring_Test_Window::calculateTestRuntime()
{
    // #TODO add a factor for communication time

    // gather all variables we need
    QByteArray startWav = ui->startWavLineEdit->text().toLatin1();
    QByteArray endWav = ui->endWavLineEdit->text().toLatin1();
    QByteArray dwell = ui->dwellLineEdit->text().toLatin1();
    QByteArray stepSize = ui->stepSizeLineEdit->text().toLatin1();
    QByteArray pmPollRate = ui->graphRefreshRateEdit->text().toLatin1();

    // check if any fields are missing
    if(startWav == "" || endWav == "" || dwell == "" || stepSize == "" || pmPollRate == ""){
        ui->estimatedTimeDisplay->clear();
    }
    else{
        // all necessary fields are present - calculate time: number of steps in range * dwell
        double wavelengthRange = endWav.toDouble() - startWav.toDouble();
        double numSteps = wavelengthRange / stepSize.toDouble();
        double estimatedTime = numSteps * dwellTimeInSeconds;
        QByteArray displayTime = QDateTime::fromTime_t(estimatedTime).toUTC().toString("hh:mm:ss").toLatin1();
        ui->estimatedTimeDisplay->setText(displayTime);
    }
}

double WavStep_Power_Monitoring_Test_Window::convertDwellToSeconds(double dwell)
{
    double convertedDwell = dwell;
    if(ui->dwellSRadioButton->isChecked()){
        // already displayed as seconds - no need to convert
        convertedDwell = dwell;
    }
    else if(ui->dwellMsecRadioButton->isChecked()){
        // displayed as milliseconds, convert to seconds
        convertedDwell = dwell / SEC_TO_MSEC_MULTIPLIER;
    }
    else if(ui->dwellMinRadioButton->isChecked()){
        // displayed as minutes, convert to seconds
        convertedDwell = dwell * 60;
    }
    return convertedDwell;
}


void WavStep_Power_Monitoring_Test_Window::on_dwellMinRadioButton_clicked()
{
    // convert the stored dwell time (sec) to minutes
    double displayDwell = dwellTimeInSeconds / MIN_TO_SEC_MULTIPLIER;
    if(dwellTimeInSeconds >= 0){
        // if valid, display converted value
        ui->dwellLineEdit->setText(QByteArray::number(displayDwell));
    }
}

void WavStep_Power_Monitoring_Test_Window::on_dwellSRadioButton_clicked()
{
    if(dwellTimeInSeconds >= 0){
        // if valid, display stored value (seconds is native)
        ui->dwellLineEdit->setText(QByteArray::number(dwellTimeInSeconds));
    }
}

void WavStep_Power_Monitoring_Test_Window::on_dwellMsecRadioButton_clicked()
{
    // convert the stored dwell time (sec) to milliseconds
    double displayDwell = dwellTimeInSeconds * SEC_TO_MSEC_MULTIPLIER;
    if(dwellTimeInSeconds >= 0){
        // if valid, display converted value
        ui->dwellLineEdit->setText(QByteArray::number(displayDwell));
    }
}

void WavStep_Power_Monitoring_Test_Window::on_openGraphWindowButton_clicked()
{
    // emit signal to open graph window
    emit signalShowGraphWindow();
}

void WavStep_Power_Monitoring_Test_Window::on_selectCsvLocButton_clicked()
{
    // open QFileDialog so the user can select a file
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Output .csv File"), "",
            tr("Data (*.csv);;All Files (*)"));

    // check if a file was actually selected
    if (!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite)){
            // error message if the file can't be opened
            QMessageBox::information(this, tr(WAVSTEP_CANT_OPEN_FILE), file.errorString());
        }
        else{
            // file is valid, update displayed csv filename field
            QByteArray outputCsvFilename = file.fileName().toLatin1();
            ui->csvLocDisplay->setText(outputCsvFilename);
            file.close();
        }
    }
}

void WavStep_Power_Monitoring_Test_Window::on_graphRefreshRateEdit_editingFinished()
{
    // block signals (known Qt Bug - users will double-enter if blockSignals() is not called
    ui->graphRefreshRateEdit->blockSignals(true);

    // check if value entered is valid
    QByteArray refreshRate = ui->graphRefreshRateEdit->text().toLatin1();
    if(isInputValueValid(refreshRate)){
        if(refreshRate.toDouble() <= 0){
            // not valid - display error message and clear field
            QMessageBox msgBox;
            msgBox.setText(WAVSTEP_GRAPH_REFRESH_INVALID);
            msgBox.exec();
            ui->graphRefreshRateEdit->clear();
        }
    }
    else{
        // not valid - clear field
        ui->graphRefreshRateEdit->clear();
    }

    // clear focus and un-block signals
    ui->graphRefreshRateEdit->clearFocus();
    ui->graphRefreshRateEdit->blockSignals(false);

}

void WavStep_Power_Monitoring_Test_Window::slotDisplayCurrentWavelength(QByteArray wavelength){
    // display the wavelength in the Current Wav field
    ui->currentWavDisplay->setText(wavelength);
}


void WavStep_Power_Monitoring_Test_Window::on_saveConfigBtn_clicked()
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
            updateSettings();
            saveSettings();
        }
    }
}

void WavStep_Power_Monitoring_Test_Window::on_loadConfigBtn_clicked()
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

void WavStep_Power_Monitoring_Test_Window::saveSettings(){
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    QStringList keys = settings->allKeys();
    for(auto key : keys){
        settingsFromFile.setValue(key, settings->value(key));
    }
//    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
//    {
//        settingsFromFile.setValue( *i, settings->value( *i ) );
//    }

    settingsFromFile.sync();

}

void WavStep_Power_Monitoring_Test_Window::loadSettings(){
    QSettings settingsFromFile(settingsFileName, QSettings::IniFormat);

    QStringList keys = settingsFromFile.allKeys();
    for( QStringList::iterator i = keys.begin(); i != keys.end(); i++ )
    {
        settings->setValue( *i, settingsFromFile.value( *i ) );
    }

    settings->sync();

    // update the fields with the values from the config file
    QByteArray csvFilename = settings->value(WAV_STEP_TEST_CSV_FILENAME).value<QByteArray>();
    double startWav = settings->value(WAV_STEP_TEST_START_WAVELENGTH).value<double>();
    double graphRefreshRate = settings->value(WAV_STEP_TEST_POWER_POLL_RATE).value<double>();
    double endWav = settings->value(WAV_STEP_TEST_END_WAVELENGTH).value<double>();
    double wavStepSize = settings->value(WAV_STEP_TEST_WAV_STEP_SIZE).value<double>();
    dwellTimeInSeconds = settings->value(WAV_STEP_TEST_DWELL_SECONDS).value<double>();
    QMap<int, QByteArray> swtChannelToT100Map = settings->value(WAV_STEP_TEST_SWT_CHANNELS_TO_T100).value<QMap<int, QByteArray>>();
    QList<QByteArray> channelsToGraph = settings->value(WAV_STEP_TEST_CHANNELS_TO_GRAPH).value<QList<QByteArray>>();
    int maxSeriesDataPoints = settings->value(WAV_STEP_TEST_POINTS_PER_SERIES).value<int>();

    // reset channel dropdowns
    ui->swtChannel1ComboBox->setCurrentIndex(0);
    ui->swtChannel2ComboBox->setCurrentIndex(0);
    ui->swtChannel3ComboBox->setCurrentIndex(0);
    ui->swtChannel4ComboBox->setCurrentIndex(0);

    // fill in first channel dropdown
    int index1 = ui->swtChannel1ComboBox->findText(swtChannelToT100Map.value(1));
    ui->swtChannel1ComboBox->setCurrentIndex(index1);

    // fill in second channel dropdown
    int index2 = ui->swtChannel2ComboBox->findText(swtChannelToT100Map.value(2));
    ui->swtChannel2ComboBox->setCurrentIndex(index2);

    // fill in third channel dropdown
    int index3 = ui->swtChannel3ComboBox->findText(swtChannelToT100Map.value(3));
    ui->swtChannel3ComboBox->setCurrentIndex(index3);

    // fill in third channel dropdown
    int index4 = ui->swtChannel4ComboBox->findText(swtChannelToT100Map.value(4));
    ui->swtChannel4ComboBox->setCurrentIndex(index4);

    // fill in remaining fields
    ui->startWavLineEdit->setText(QByteArray::number(startWav));
    ui->endWavLineEdit->setText(QByteArray::number(endWav));
    ui->graphRefreshRateEdit->setText(QByteArray::number(graphRefreshRate));
    ui->stepSizeLineEdit->setText(QByteArray::number(wavStepSize));
    ui->dwellSRadioButton->setChecked(true);
    ui->dwellLineEdit->setText(QByteArray::number(dwellTimeInSeconds));
    ui->csvLocDisplay->setText(csvFilename);
    ui->seriesDataPointsEdit->setText(QByteArray::number(maxSeriesDataPoints));

    // re-calculate estimated time
    calculateTestRuntime();

    updateSettings();
}


void WavStep_Power_Monitoring_Test_Window::disableFieldsOnTestStart(){
    // disable all fields except for the display graph button
    ui->swtChannel1ComboBox->setEnabled(false);
    ui->swtChannel2ComboBox->setEnabled(false);
    ui->swtChannel3ComboBox->setEnabled(false);
    ui->swtChannel4ComboBox->setEnabled(false);
    ui->startWavLineEdit->setEnabled(false);
    ui->endWavLineEdit->setEnabled(false);
    ui->dwellLineEdit->setEnabled(false);
    ui->dwellSRadioButton->setEnabled(false);
    ui->dwellMinRadioButton->setEnabled(false);
    ui->dwellMsecRadioButton->setEnabled(false);
    ui->stepSizeLineEdit->setEnabled(false);
    ui->graphRefreshRateEdit->setEnabled(false);
    ui->loadConfigBtn->setEnabled(false);
    ui->saveConfigBtn->setEnabled(false);
    ui->beginTestPB->setEnabled(false);
    ui->selectCsvLocButton->setEnabled(false);

    ui->openGraphWindowButton->setEnabled(true);
}

void WavStep_Power_Monitoring_Test_Window::enableFieldsOnTestFinish(){
    ui->swtChannel1ComboBox->setEnabled(true);
    ui->swtChannel2ComboBox->setEnabled(true);
    ui->swtChannel3ComboBox->setEnabled(true);
    ui->swtChannel4ComboBox->setEnabled(true);
    ui->startWavLineEdit->setEnabled(true);
    ui->endWavLineEdit->setEnabled(true);
    ui->dwellLineEdit->setEnabled(true);
    ui->dwellSRadioButton->setEnabled(true);
    ui->dwellMinRadioButton->setEnabled(true);
    ui->dwellMsecRadioButton->setEnabled(true);
    ui->stepSizeLineEdit->setEnabled(true);
    ui->graphRefreshRateEdit->setEnabled(true);
    ui->loadConfigBtn->setEnabled(true);
    ui->saveConfigBtn->setEnabled(true);
    ui->beginTestPB->setEnabled(true);
    ui->selectCsvLocButton->setEnabled(true);

    ui->openGraphWindowButton->setEnabled(false);
}

