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
    ui->directionsImageLabel->setPixmap(QPixmap(resourcePath));
    ui->directionsTextField->setText(directions);
    ui->progressBar->hide();
//    ui->directionsTextField->show();
}

EXFO_OperationalTest_T100_SWT_ATN_Window::~EXFO_OperationalTest_T100_SWT_ATN_Window()
{
    delete ui;
}



void EXFO_OperationalTest_T100_SWT_ATN_Window::runTest(){
    // signal to the test class to start the next step
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Confirm", "Confirm to continue with test.", QMessageBox::Yes | QMessageBox::No);

    if(msgBox == QMessageBox::Yes){
        ui->progressBar->reset();
        ui->progressBar->show();
        QApplication::setOverrideCursor(Qt::WaitCursor);

        emit signalBeginNextTestStep();

        QApplication::restoreOverrideCursor();

        QMessageBox stepFinishedMsgBox;
        stepFinishedMsgBox.setText("Test step completed. Click 'run' to start next step.");
        stepFinishedMsgBox.exec();
        ui->progressBar->hide();

        // get new image/directions
        QByteArray resourcePath = "";
        QByteArray directions = "";
        emit signalGetCurrentStepDirections(resourcePath, directions);
        ui->directionsImageLabel->setPixmap(QPixmap(resourcePath));
        ui->directionsTextField->setText(directions);



        // disable button (re-enabled when signal is received the previous test has completed
    }
}

void EXFO_OperationalTest_T100_SWT_ATN_Window::slotReceiveTestProgressInGUI(double progressPercent){
    ui->progressBar->setValue(progressPercent);
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

void EXFO_OperationalTest_T100_SWT_ATN_Window::on_skipStepButton_clicked()
{
    if (testingComplete){
        QMessageBox msgBox;
        msgBox.setText("All testing is complete.");
        ui->directionsTextField->setText("All Testing is complete.");
    }
    else{
        // signal to the test class to skip the next step
        QMessageBox::StandardButton msgBox;
        msgBox = QMessageBox::question(this, "Confirm", "Confirm to skip test step.", QMessageBox::Yes | QMessageBox::No);

        if(msgBox == QMessageBox::Yes){
            qDebug() << "emitting signal to skip test";
            emit signalSkipTestStep();

            // get new image/directions
            QByteArray resourcePath = "";
            QByteArray directions = "";
            emit signalGetCurrentStepDirections(resourcePath, directions);
            ui->directionsImageLabel->setPixmap(QPixmap(resourcePath));
            ui->directionsTextField->setText(directions);

            QMessageBox stepFinishedMsgBox;
            stepFinishedMsgBox.setText("Test step skipped. Click 'run' to start next step.");
            stepFinishedMsgBox.exec();

            // disable button (re-enabled when signal is received the previous test has completed
        }
    }
}
