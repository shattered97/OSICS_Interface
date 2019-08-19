#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
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

    void on_searchForDevTypeBtn_clicked();

    void slotReceiveDevices(FoundInstr listOfDevices);

    void on_testTypeComboBox_currentIndexChanged(int index);

    void on_addSelectedDeviceBtn_clicked();

    void on_startTestPushButton_clicked();

    void on_selectedDevicesListWidget_itemDoubleClicked(QListWidgetItem *item);

signals:

    void signalDeviceTypeSelected(QByteArray deviceType);

    void signalRequestDevicesFromOrchestrator();

    void signalCreateN7714ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void signalCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

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
     * @brief loadDeviceTypesList Populates the device types drop down combo box with possible device types
     */
    void loadDeviceTypesList();

    /**
     * @brief loadTestTypesList Populates the test types dropdown combo box with possible test types
     */
    void loadTestTypesList();

    /**
     * @brief resetMainWindow Resets the GUI to the starting state
     */
    void resetMainWindow();

};

#endif // MAINWINDOW_H
