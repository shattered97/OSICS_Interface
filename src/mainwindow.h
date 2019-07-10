#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VisaInterface.h"
#include "DefaultInstrument.h"
#include "N7714A.h"

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

    void on_resetNewLevelBtn_clicked();

    void on_setNewLevelBtn_clicked();

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
    N7714A selectedResource;

    void setPowerStatusIndicatorOff();

    void setPowerStatusIndicatorOn();

    void populateGUIFields();
};

#endif // MAINWINDOW_H
