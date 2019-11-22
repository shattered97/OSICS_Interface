#include "snapshotgraphdialog.h"
#include "ui_snapshotgraphdialog.h"
#include <QDebug>
#include <QDateTime>

SnapshotGraphDialog::SnapshotGraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnapshotGraphDialog)
{
    ui->setupUi(this);

    // hide the startAndEndTime groupBox because it is not the default selected option
    ui->startAndEndTimeGroupBox->hide();

    ui->okButton->clearFocus();

    // workaround for the "OK" button being pressed when the user hits enter
    // create a dummy button, set it to default (so it gets the focus) and hide it
    ui->dummyButton->setDefault(true);
    ui->dummyButton->hide();

    QObject::connect(this, SIGNAL(signalInputValidated()), this, SLOT(accept()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

SnapshotGraphDialog::~SnapshotGraphDialog()
{
    delete ui;
}

void SnapshotGraphDialog::setTestStartTime(double testStartTime){
    this->testStartTimeInSec = testStartTime;
    int timeInMsec = testStartTimeInSec * 1000;
    QString displayTime = QTime::fromMSecsSinceStartOfDay(timeInMsec).toString("hh:mm:ss:zzz");
    ui->testStartTimeDisplay->setText(displayTime);
}

void SnapshotGraphDialog::setTestCurrentTime(double testCurrentTime){
    this->testCurrentTimeInSec = testCurrentTime;
    int timeInMsec = testCurrentTimeInSec * 1000;
    QString displayTime =  QTime::fromMSecsSinceStartOfDay(timeInMsec).toString("hh:mm:ss:zzz");
    ui->currentRuntimeDisplay->setText(displayTime);
}

QByteArray SnapshotGraphDialog::getTestStartTime(){
    return ui->snapshotStartTimeEdit->text().toLatin1();
}

QByteArray SnapshotGraphDialog::getTestCurrentTime(){
    return ui->snapshotEndTimeEdit->text().toLatin1();
}

double SnapshotGraphDialog::getGraphStartTime(){
    return graphStartTimeInSec;

}
double SnapshotGraphDialog::getGraphEndTime(){
    return graphEndTimeInSec;
}

void SnapshotGraphDialog::on_graphPastTimeRadioBtn_clicked()
{
    // swap the groupBoxes shown
    ui->startAndEndTimeGroupBox->hide();
    ui->pastTimeGroupBox->show();
    makePastTimeGraph = true;
}

void SnapshotGraphDialog::on_graphCustomStartEndRadioBtn_clicked()
{
    // swap the groupBoxes shown
    ui->startAndEndTimeGroupBox->show();
    ui->pastTimeGroupBox->hide();
    makePastTimeGraph = false;
}

void SnapshotGraphDialog::on_snapshotGoBackTimeEdit_editingFinished()
{
    ui->snapshotGoBackTimeEdit->blockSignals(true);

    QString timeValue = ui->snapshotGoBackTimeEdit->text();
    if(isInputValueNumeric(timeValue)){
        double timeValueDouble = timeValue.toDouble();

        // the time to go back can't exceed start minus end
        double maxTimeToGoBackSeconds = testCurrentTimeInSec - testStartTimeInSec;

        QByteArray unit = ui->goBackUnitComboBox->currentText().toLatin1();
        double timeValueInSeconds = ConversionUtilities::convertTimeToSeconds(timeValueDouble, unit);

        if(timeValueInSeconds > maxTimeToGoBackSeconds){
            QMessageBox msgBox;
            msgBox.setText("Value entered is too large.");
            msgBox.exec();
            ui->snapshotGoBackTimeEdit->clear();
        }
        else if(timeValueDouble <= 0){
            QMessageBox msgBox;
            msgBox.setText("Value must be greater than 0.");
            msgBox.exec();

            ui->snapshotGoBackTimeEdit->clear();
        }
        else{
            // set graph start and end
            timeToGoBackInSec = timeValueInSeconds;
            qDebug() << "TIME VALUE ENTERED (S) " << timeValueInSeconds;
            graphStartTimeInSec = testCurrentTimeInSec - timeValueInSeconds;
            graphEndTimeInSec = testCurrentTimeInSec;

            qDebug() << "GRAPH START TIME " << graphStartTimeInSec;
            qDebug() << "GRAPH END  TIME " << graphEndTimeInSec;
        }
    }
    else{
        ui->snapshotGoBackTimeEdit->clear();
    }

    ui->snapshotGoBackTimeEdit->clearFocus();
    ui->snapshotGoBackTimeEdit->blockSignals(false);
}


void SnapshotGraphDialog::on_snapshotStartTimeEdit_editingFinished()
{
    ui->snapshotStartTimeEdit->blockSignals(true);

    QString timeValue = ui->snapshotStartTimeEdit->text();
    if(isInputValueNumeric(timeValue)){
        double timeValueDouble = timeValue.toDouble();

        // the graph start time cannot be lower than the test start time
        QByteArray unit = ui->startAndEndTimeUnitComboBox->currentText().toLatin1();
        double timeValueInSeconds =  ConversionUtilities::convertTimeToSeconds(timeValueDouble, unit);

        if(timeValueInSeconds < testStartTimeInSec || timeValueInSeconds > testCurrentTimeInSec){
            QMessageBox msgBox;
            msgBox.setText("Time is not within the Test Start Time -> Current Test Time.");
            msgBox.exec();
            ui->snapshotStartTimeEdit->clear();
        }
        else{
            // set graph start
            graphStartTimeInSec = timeValueInSeconds;
            qDebug() << "GRAPH START TIME: " << graphStartTimeInSec;
        }
    }
    else{
        ui->snapshotStartTimeEdit->clear();
    }

    ui->snapshotStartTimeEdit->clearFocus();
    ui->snapshotStartTimeEdit->blockSignals(false);
}

void SnapshotGraphDialog::on_snapshotEndTimeEdit_editingFinished()
{
    ui->snapshotEndTimeEdit->blockSignals(true);

    QString timeValue = ui->snapshotEndTimeEdit->text();
    if(isInputValueNumeric(timeValue)){
        double timeValueDouble = timeValue.toDouble();

        // the graph start time cannot be lower than the test start time
        QByteArray unit = ui->startAndEndTimeUnitComboBox->currentText().toLatin1();
        double timeValueInSeconds =  ConversionUtilities::convertTimeToSeconds(timeValueDouble, unit);

        if(timeValueInSeconds < testStartTimeInSec || timeValueInSeconds > testCurrentTimeInSec){
            QMessageBox msgBox;
            msgBox.setText("Time is not within the Test Start Time -> Current Test Time.");
            msgBox.exec();
            ui->snapshotEndTimeEdit->clear();
        }
        else{
            // set graph end
            graphEndTimeInSec = timeValueInSeconds;
            qDebug() << "GRAPH END TIME: " << graphEndTimeInSec;
        }
    }
    else{
        ui->snapshotEndTimeEdit->clear();
    }

    ui->snapshotEndTimeEdit->clearFocus();
    ui->snapshotEndTimeEdit->blockSignals(false);
}


void SnapshotGraphDialog::on_goBackUnitComboBox_currentIndexChanged(const QString &unit)
{
    QByteArray currentValue = ui->snapshotGoBackTimeEdit->text().toLatin1();

    if(currentValue.trimmed() != ""){
        double convertedValue = ConversionUtilities::convertTimeFromSeconds(timeToGoBackInSec, unit.toLatin1());
        ui->snapshotGoBackTimeEdit->setText(QByteArray::number(convertedValue));
    }
}

void SnapshotGraphDialog::on_startAndEndTimeUnitComboBox_currentTextChanged(const QString &unit)
{
    QByteArray startTimeValueInField = ui->snapshotStartTimeEdit->text().toLatin1();
    QByteArray endTimeValueInField = ui->snapshotEndTimeEdit->text().toLatin1();

    if(startTimeValueInField.trimmed() != ""){
        double convertedValue = ConversionUtilities::convertTimeFromSeconds(graphStartTimeInSec, unit.toLatin1());
        ui->snapshotStartTimeEdit->setText(QByteArray::number(convertedValue));
    }

    if(endTimeValueInField.trimmed() != ""){
        double convertedValue = ConversionUtilities::convertTimeFromSeconds(graphEndTimeInSec, unit.toLatin1());
        ui->snapshotEndTimeEdit->setText(QByteArray::number(convertedValue));
    }
}


bool SnapshotGraphDialog::isInputValueNumeric(QString inputValue)
{
    // only check if the input value is not empty
    bool valueIsNumeric = true;
    inputValue.toDouble(&valueIsNumeric);

    if(inputValue.trimmed() != ""){

        if(!valueIsNumeric){
            QMessageBox msgBox;
            msgBox.setText("Value entered is non-numeric.");
            msgBox.exec();
        }
    }

    return valueIsNumeric;
}


void SnapshotGraphDialog::on_okButton_clicked()
{

    if(isAllInputValid()){
         emit signalInputValidated();
    }

}

bool SnapshotGraphDialog::isAllInputValid(){
    bool success = true;

    if(makePastTimeGraph){
        // there is only one field to check for this radio option
        if(ui->snapshotGoBackTimeEdit->text().trimmed().isEmpty()){
            success = false;
        }
    }
    else{
        // there are two fields to check for the start-to-end option
        bool startFieldEmpty = ui->snapshotStartTimeEdit->text().trimmed().isEmpty();
        bool endFieldEmpty = ui->snapshotEndTimeEdit->text().trimmed().isEmpty();
        if(startFieldEmpty || endFieldEmpty){
            success = false;
        }
    }

    // inform users that expected fields are empty
    if(!success){
        QMessageBox msgBox;
        msgBox.setText("Required fields are empty.");
        msgBox.exec();
    }

    return success;
}


