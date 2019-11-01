#ifndef CONFIGOSICS_SWT_H
#define CONFIGOSICS_SWT_H

#include <QMainWindow>
#include <QSettings>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "constants.h"
#include "ConversionUtilities.h"

namespace Ui {
class ConfigOSICS_SWT;
}

class ConfigOSICS_SWT : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_SWT(QVariant &device, QWidget *parent = nullptr);
    ~ConfigOSICS_SWT();

    void populateOutputPowerStatus();
    void populatePowerUnit();
    void populatePower();
    void populateMinPower();
    void populateMaxPower();
    void populateOperatingMode();
    void populateActiveChannel();

    void populateWavelength();
    void populateMinWavelength();
    void populateMaxWavelength();

    void populateFrequencyUnit();
    void populateFrequency();
    void populateMinFrequency();
    void populateMaxFrequency();

signals:
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);

public slots:
    void slotUpdateWindow();

private slots:
    void on_opModeRadioBtnFullBand_clicked();

    void on_opModeRadioBtnSwitch_clicked();

    void on_loadSettingsButton_clicked();

    void on_saveSettingsButton_clicked();

    void on_saveChangesButton_clicked();

    void on_ch1Radio_clicked();

    void on_ch2Radio_clicked();

    void on_ch3Radio_clicked();

    void on_ch4Radio_clicked();

    void on_powerUnitComboBox_currentIndexChanged(const QString &arg1);

    void on_wavelengthUnitComboBox_currentIndexChanged(const QString &arg1);

    void on_frequencyUnitComboBox_currentIndexChanged(const QString &arg1);

    void on_powerEdit_editingFinished();

    void on_wavelengthEdit_editingFinished();

    void on_frequencyEdit_editingFinished();

    void on_toggleOutputButton_clicked();

    void on_setNicknameBtn_clicked();

private:
    Ui::ConfigOSICS_SWT *ui;

    QVariant device;
    QSettings *settings;
    QString settingsFileName;
    bool windowConfigured = false;
    int slotNum;
    QByteArray moduleIdentity;
    QByteArray moduleLocation;
    QByteArray deviceNickname;              // nickname of device

    QByteArray operatingMode;
    QByteArray activeChannel;
    QByteArray powerSetting;
    QByteArray wavelengthSetting;
    QByteArray frequencySetting;
    QByteArray outputPowerStatus;
    QByteArray minWavelength;
    QByteArray maxWavelength;

    bool fullBandOpModeColored = false;
    bool switchOpModeColored = false;
    bool activeChannelColored[EXFO_OSICS_SWT_NUM_CHANNELS] = {false};
    bool outputStatusColored = false;
    bool outputPowerColored = false;
    bool wavelengthSettingColored = false;
    bool frequencySettingColored = false;

    void colorText(QLineEdit *textField, bool colored);
    void colorDisplayFieldText();
    void resetDisplayFieldColoredStatus();
    void resetActiveChannelRadioColor();

    void showEvent(QShowEvent* event);
    void getValuesFromConfig();
    void populateAllValues();
    bool isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue);
    bool loadSettings();
    bool saveSettings();
    void populateDeviceInfo();
};

#endif // CONFIGOSICS_SWT_H
