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

    void signalRequestDevicesFromOrchestrator();

    void signalCreateDevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

private:

    // main window user interface
    Ui::MainWindow *ui;

    // Orchestrator object that handles device communication
    Orchestrator *orchestrator;

    /**
     * @brief resourcesQmapToQList Returns a list of device identities that match a particular device type
     * @param foundResources QMap of all VISA resources found on system
     * @param deviceType Type of device to search for
     * @return List of device identities matching device type
     */
    QList<QByteArray> resourcesQmapToQList(FoundInstr foundResources, QByteArray deviceType);

    /**
     * @brief loadDeviceTypesList Populates the widget of possible device types
     */
    void loadDeviceTypesList();

};

#endif // MAINWINDOW_H
