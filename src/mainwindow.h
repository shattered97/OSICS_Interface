#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VisaInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    VisaInterface theCommBus;
    ViPFindList findList;
    ViSession defaultSession;
    ViSession currentSession;
    ViUInt32 numInstruments;
    QByteArray instrAddr;
    FoundInstr foundResources;
};

#endif // MAINWINDOW_H
