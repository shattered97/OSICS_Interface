#ifndef CONFIGOSICS_T100_H
#define CONFIGOSICS_T100_H

#include <QMainWindow>
#include <QSettings>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "constants.h"

namespace Ui {
class ConfigOSICS_T100;
}

class ConfigOSICS_T100 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigOSICS_T100(QVariant &device, QWidget *parent = nullptr);
    ~ConfigOSICS_T100();

    void populateLaserOutputPowerUnit();
    void populateLaserOutputPower();
    void populateLaserMinPower();
    void populateLaserMaxPower();
    void populateLaserState();

    void populateLaserWavelength();
    void populateLaserMinWavelength();
    void populateLaserMaxWavelength();

    void populateLaserFrequencyUnit();
    void populateLaserFrequency();
    void populateLaserMinFrequency();
    void populateLaserMaxFrequency();

signals:
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);

public slots:
    void slotUpdateWindow();

private slots:

    void on_powerUnitComboBox_currentIndexChanged(int index);

    void on_wavelengthUnitComboBox_currentIndexChanged(int index);

    void on_frequencyUnitComboBox_currentIndexChanged(int index);

    void on_laserOutputPowerEdit_editingFinished();

    void on_laserWavelengthEdit_editingFinished();

    void on_laserFrequencyEdit_editingFinished();

    void on_togglePowerButton_clicked();

    void on_loadSettingsButton_clicked();

    void on_saveSettingsButton_clicked();

    void on_saveChangesButton_clicked();

private:
    Ui::ConfigOSICS_T100 *ui;

    QVariant device;
    QSettings *settings;
    QString settingsFileName;
    bool windowConfigured = false;


    int slotNum;

    QByteArray powerSetting;
    QByteArray minPower;
    QByteArray maxPower;
    QByteArray laserState;

    QByteArray wavelengthSetting;
    QByteArray minWavelength;
    QByteArray maxWavelength;

    QByteArray frequencySetting;
    QByteArray minFrequency;
    QByteArray maxFrequency;

    void showEvent(QShowEvent* event);
    void getValuesFromConfig();
    void populateAllValues();
    bool isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue);

    bool loadSettings();
    bool saveSettings();

    void colorText(QLineEdit *textField, bool colored);
    void colorDisplayFieldText();
    void resetDisplayFieldColoredStatus();

    bool powerSettingColored = false;
    bool laserStateColored = false;
    bool wavelengthSettingColored = false;
    bool frequencySettingColored = false;



};

#endif // CONFIGOSICS_T100_H
