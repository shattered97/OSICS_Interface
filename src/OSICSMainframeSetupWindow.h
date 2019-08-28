#ifndef OSICSMAINFRAMESETUPWINDOW_H
#define OSICSMAINFRAMESETUPWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include "constants.h"

namespace Ui {
class OSICSMainframeSetupWindow;
}

class OSICSMainframeSetupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSICSMainframeSetupWindow(QVariant &device, QWidget *parent = 0);
    ~OSICSMainframeSetupWindow();

signals:
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);
    void signalGetEXFOModuleQVariants(QList<QVariant> &modules, QList<QByteArray> moduleTypes, QVariant &device);

public slots:
    void slotUpdateWindow();

private slots:
    void on_configSlot1Btn_clicked();

    void on_configSlot2Btn_clicked();

    void on_configSlot3Btn_clicked();

    void on_configSlot4Btn_clicked();

    void on_configSlot5Btn_clicked();

    void on_configSlot6Btn_clicked();

    void on_configSlot7Btn_clicked();

    void on_configSlot8Btn_clicked();

private:
    Ui::OSICSMainframeSetupWindow *ui;

    QVariant device;
    QString settingsFileName;
    QSettings *settings;

    // device values
    int numInstalledModules = 0;
    QByteArray deviceIdentity;
    QByteArray deviceLocation;
    QList<QByteArray> moduleNames;
    QList<QVariant> modules;

    void populateAllValues();
    void getValuesFromConfig();

    void populateIdentityAndLoc();
    void populateModuleNames();

    void showEvent(QShowEvent* event);

};

#endif // OSICSMAINFRAMESETUPWINDOW_H
