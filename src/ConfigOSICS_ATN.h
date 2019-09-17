#ifndef CONFIGOSICS_ATN_H
#define CONFIGOSICS_ATN_H

#include <QMainWindow>
#include <QSettings>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "constants.h"


namespace Ui {
class ConfigOSICS_ATN;
}

class ConfigOSICS_ATN : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_ATN(QVariant &device, QWidget *parent = nullptr);
    ~ConfigOSICS_ATN();

    void populateDeviceInfo();
    void populateAttenuation();
    void populateMinAttenuation();
    void populateMaxAttenuation();
    void populateRefWavelength();
    void populateOffset();

signals:
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);

public slots:
    void slotUpdateWindow();

private slots:
    void on_attenuationEdit_editingFinished();

    void on_attenuationOffsetEdit_editingFinished();

    void on_loadSettingsButton_clicked();

    void on_saveSettingsButton_clicked();

    void on_saveChangesButton_clicked();

    void on_refWavelengthRadioButton1_clicked();

    void on_refWavelengthRadioButton2_clicked();

private:
    Ui::ConfigOSICS_ATN *ui;

    QVariant device;
    QSettings *settings;
    QString settingsFileName;

    int slotNum;
    QByteArray moduleIdentity;
    QByteArray moduleLocation;
    QByteArray attenuationSetting;
    QByteArray firstMinAttenuation;
    QByteArray firstMaxAttenuation;
    QByteArray secondMinAttenuation;
    QByteArray secondMaxAttenuation;
    QByteArray refWavelengthNumber = "1";
    QByteArray firstRefWavelength;
    QByteArray secondRefWavelength;
    QByteArray firstOffset;
    QByteArray secondOffset;

    void showEvent(QShowEvent* event);
    void getValuesFromConfig();
    void populateAllValues();
    bool isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue);

    bool loadSettings();
    bool saveSettings();
};

#endif // CONFIGOSICS_ATN_H
