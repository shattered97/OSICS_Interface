#ifndef CONFIGN7714AWINDOW_H
#define CONFIGN7714AWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QLineEdit>

#include "N7714A.h"
#include "ConversionUtilities.h"

namespace Ui {
class ConfigN7714AWindow;
}

class ConfigN7714AWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigN7714AWindow(QVariant &device, QWidget *parent = nullptr);
    ~ConfigN7714AWindow();

    void populateLaserOutputPowerUnit();
    void populateLaserOutputPower();
    void populateLaserMinPower();
    void populateLaserMaxPower();
    void populateLaserState();

    void populateLaserWavelengthUnit();
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
    void on_powerUnitComboBox_currentIndexChanged(const QString &arg1);

    void on_slot1RadioBtn_clicked();

    void on_slot2RadioBtn_clicked();

    void on_slot3RadioBtn_clicked();

    void on_slot4RadioBtn_clicked();

    void on_laserOutputPowerEdit_editingFinished();

    void on_togglePowerButton_clicked();

    void on_wavelengthUnitComboBox_currentIndexChanged();

    void on_frequencyUnitComboBox_currentIndexChanged();

    void on_laserWavelengthEdit_editingFinished();

    void on_laserFrequencyEdit_editingFinished();

    void on_saveChangesButton_clicked();

    void on_loadSettingsButton_clicked();

    void on_saveSettingsButton_clicked();

private:
    Ui::ConfigN7714AWindow *ui;

    QVariant device;
    QString settingsFileName;
    QSettings *settings;

    int slotNum;
    bool powerSettingDisplayTextColored[N7714A_NUM_SLOTS] = {false};
    bool powerStatusDisplayTextColored[N7714A_NUM_SLOTS] = {false};
    bool wavelengthDisplayTextColored[N7714A_NUM_SLOTS] = {false};
    bool frequencyDisplayTextColored[N7714A_NUM_SLOTS] = {false};

    QList<QByteArray> powerSettings;
    QList<QByteArray> minPowerSettings;
    QList<QByteArray> maxPowerSettings;
    QList<QByteArray> laserStates;

    QList<QByteArray> wavelengthSettings;
    QList<QByteArray> minWavelengths;
    QList<QByteArray> maxWavelengths;

    QList<QByteArray> frequencySettings;
    QList<QByteArray> minFrequencies;
    QList<QByteArray> maxFrequencies;

    void showEvent(QShowEvent* event);
    void populateAllValues();
    void getValuesFromConfig();
    bool loadSettings();
    bool saveSettings();

    void convertAndDisplayPower(QList<QByteArray> powerList, QLineEdit* displayField);
    void convertAndDisplayWavelength(QList<QByteArray> wavelengthList, QLineEdit* displayField);
    void convertAndDisplayFrequency(QList<QByteArray> wavelengthList, QLineEdit* displayField);
    bool isInputValueValid(QByteArray inputValue, QByteArray minValue, QByteArray maxValue);

    void resetDisplayFieldColoredStatus();
    void colorDisplayFieldText();
    void colorText(QLineEdit *textField, bool colored);
};

#endif // CONFIGN7714AWINDOW_H
