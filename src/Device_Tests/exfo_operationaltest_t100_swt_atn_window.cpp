#include "exfo_operationaltest_t100_swt_atn_window.h"
#include "ui_exfo_operationaltest_t100_swt_atn_window.h"
#include <QPixmap>
#include <QDebug>

EXFO_OperationalTest_T100_SWT_ATN_Window::EXFO_OperationalTest_T100_SWT_ATN_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EXFO_OperationalTest_T100_SWT_ATN_Window)
{
    ui->setupUi(this);


}

void EXFO_OperationalTest_T100_SWT_ATN_Window::showEvent(QShowEvent* event){
    QWidget::showEvent(event);

    // get initial directions


    QByteArray directions = "";
    QByteArray resourcePath = "";
    emit signalGetCurrentStepDirections(resourcePath, directions);
    qDebug() << "************************************************* " << resourcePath;
    ui->directionsImageLabel->setPixmap(QPixmap(resourcePath));
    ui->directionsTextField->setText(directions);
//    ui->directionsTextField->show();
}

EXFO_OperationalTest_T100_SWT_ATN_Window::~EXFO_OperationalTest_T100_SWT_ATN_Window()
{
    delete ui;
}


void EXFO_OperationalTest_T100_SWT_ATN_Window::on_outputFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Output File"), "",
            tr("Settings (*.csv);;All Files (*)"));

    if (!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite)){
            QMessageBox::information(this, tr("Can't open file"), file.errorString());
        }
        else{
            outputFilename = file.fileName().toLatin1();
            file.close();

            // update the field showing the filename
            ui->outuptFilenameLineEdit->setText(outputFilename);

        }
    }
}

void EXFO_OperationalTest_T100_SWT_ATN_Window::runTest(){
    // signal to the test class to start the next step
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Confirm", "Confirm to continue with test.", QMessageBox::Yes | QMessageBox::No);

    if(msgBox == QMessageBox::Yes){
        emit signalBeginNextTestStep();

        // get new image/directions
        QByteArray resourcePath = "";
        QByteArray directions = "";
        emit signalGetCurrentStepDirections(resourcePath, directions);
        ui->directionsImageLabel->setPixmap(QPixmap(resourcePath));
        ui->directionsTextField->setText(directions);

        QMessageBox stepFinishedMsgBox;
        stepFinishedMsgBox.setText("Test step completed. Click 'run' to start next step.");
        stepFinishedMsgBox.exec();

        // disable button (re-enabled when signal is received the previous test has completed
    }
}
void EXFO_OperationalTest_T100_SWT_ATN_Window::on_runTestButton_clicked()
{

    if (testingComplete){
        QMessageBox msgBox;
        msgBox.setText("All testing is complete.");
        ui->directionsTextField->setText("All Testing is complete.");
    }
    else{
        runTest();
    }
}

void EXFO_OperationalTest_T100_SWT_ATN_Window::slotTestingComplete(){
    testingComplete = true;
}
