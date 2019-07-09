#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VisaInterface.h"
#include "DefaultInstrument.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_powerToggle_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    VisaInterface theCommBus;
    ViFindList findList;
    ViSession defaultSession;
    ViSession currentSession;
    ViUInt32 numInstruments;
    QByteArray instrAddr;
    FoundInstr foundResources;
    InstrData selectedResourceInfo;
    DefaultInstrument selectedResource;

    void populateGUIFields();
};

#endif // MAINWINDOW_H
