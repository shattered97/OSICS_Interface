#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "QMessageBox"
#include "Orchestrator.h"

#include <QMainWindow>
#include <QObject>

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

    void on_confirmDevTypeBtn_clicked();

    void on_listWidget_currentItemChanged();

    void slotReceiveDevices(FoundInstr listOfDevices);

    void on_launchSelectedDevice_clicked();

signals:

    void signalDeviceTypeSelected(QByteArray deviceType);

    void signalRequestDevicesFromWorker();

    void signalCreateDevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

private:
    Ui::MainWindow *ui;
    Orchestrator worker;

    void loadDeviceTypesList();

    QList<QByteArray> resourcesQmapToQList(FoundInstr foundResources, QByteArray deviceType);

};

#endif // MAINWINDOW_H
