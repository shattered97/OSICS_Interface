#ifndef EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H
#define EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class EXFO_OperationalTest_T100_SWT_ATN_Window;
}

class EXFO_OperationalTest_T100_SWT_ATN_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit EXFO_OperationalTest_T100_SWT_ATN_Window(QWidget *parent = nullptr);
    ~EXFO_OperationalTest_T100_SWT_ATN_Window();

    void showEvent(QShowEvent* event);
    void setTestingCompleteStatus(bool status);

signals:
    void signalBeginNextTestStep();
    void signalSkipTestStep();
    void signalGetCurrentStepDirections(QByteArray &resourcePath, QByteArray &directions);

public slots:
    void slotTestingComplete();

private slots:

    void on_runTestButton_clicked();

    void on_skipStepButton_clicked();

private:
    Ui::EXFO_OperationalTest_T100_SWT_ATN_Window *ui;

    bool testingComplete = false;

    void runTest();


};

#endif // EXFO_OPERATIONALTEST_T100_SWT_ATN_WINDOW_H
