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
    void signalGetEXFOModuleConfigPairs(QVariant &device, QMap<int, ModuleConfigPair> &moduleConfigPairs);
public slots:
    void slotUpdateWindow();
    void slotForwardApplyConfigSettings(QVariant &deviceVariant, QSettings &configSettings);
    void slotForwardUpdateConfigSettings(QVariant &deviceVariant, QSettings &configSettings);

private slots:
    void on_configButton_clicked(int index);

private:
    Ui::OSICSMainframeSetupWindow *ui;

    QVariant device;
    QString settingsFileName;
    QSettings *settings;
    bool windowConfigured = false;
    // device values
    int numInstalledModules = 0;
    QByteArray deviceIdentity;
    QByteArray deviceLocation;
    QList<QByteArray> moduleNames;
    QMap<int, ModuleConfigPair> moduleConfigPairs;
    QList<bool> moduleConfiguredStatusList = {false, false, false, false, false, false, false, false};

    void populateAllValues();
    void getValuesFromConfig();

    void populateIdentityAndLoc();
    void populateModuleNames();

    void showEvent(QShowEvent* event);

};

#endif // OSICSMAINFRAMESETUPWINDOW_H
