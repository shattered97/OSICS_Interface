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

public slots:
    void slotDisplayDecisionErrorMsg(QString errorMsg);
    void slotDisplaySimpleErrorMsg(QString errorMsg);

private slots:

    void on_searchForDevTypeBtn_clicked();

    void slotReceiveDevices(FoundInstr listOfDevices);

    void on_addSelectedDeviceBtn_clicked();

    void on_startTestPushButton_clicked();

    void on_selectedDevicesListWidget_itemDoubleClicked();

    void on_clearSelectedListButton_clicked();

    void on_devicetypeComboBox_currentIndexChanged(int index);

signals:

    void signalDeviceTypeSelected(QByteArray deviceType);

    void signalRequestDevicesFromOrchestrator();

    void signalCreateN7714ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void signalCreateN7745ADevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void signalCreateDevice(QString type, QByteArray instrumentAddress, QByteArray instrumentIdentity);

    void signalBeginTest(QString type);

    void signalClearSelectedDevices();
private:

    // main window user interface
    Ui::MainWindow *ui;

    // Orchestrator object that handles device communication
    Orchestrator *orchestrator;
    WindowFactory *windowFactory;
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

    /**
     * @brief setFontSizes Sets the font sizes in pixels so the font won't resize on monitors with high DPI
     */
    void setFontSizes();

    bool hasDeviceBeenSelected(QByteArray deviceAddress);
};

#endif // MAINWINDOW_H
