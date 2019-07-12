#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Worker.h"
#include "n7714awindow.h"

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

    void openN7714AView();

    void slotReceiveDevices(QList<QByteArray> listOfDevices);

    void on_launchSelectedDevice_clicked();

signals:

    void signalDeviceTypeSelected(QByteArray deviceType);

    void signalRequestDevicesFromWorker(QByteArray deviceType);

    void signalCreateDevice(QByteArray instrumentAddress, QByteArray instrumentIdentity);

private:
    Ui::MainWindow *ui;
    Worker worker;
    n7714awindow *n7714aNewWindow;

    void loadDeviceTypesList();

    void searchforSelectedResource(QByteArray selected);
};


#endif // MAINWINDOW_H
