#ifndef CONFIGPOWERMETER_H
#define CONFIGPOWERMETER_H

#include <QMainWindow>
#include <QtMath>
#include <QFileDialog>
#include <QSettings>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>

#include "PowerMeter.h"
#include "ConversionUtilities.h"

namespace Ui {
class ConfigPowerMeter;
}

class ConfigPowerMeter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigPowerMeter(QVariant &device, QWidget *parent = nullptr);
    ~ConfigPowerMeter();

signals:
    void signalUpdateConfigSettings(QVariant &device, QSettings &configSettings);
    void signalApplyConfigSettings(QVariant &device, QSettings &configSettings);

public slots:
    void slotUpdateWindow();

private slots:
    void slot_radio_button_clicked();

    void on_powerUnitComboBox_currentIndexChanged(const QString &unit);

    void on_wavelengthComboBox_currentIndexChanged(int index);

    void on_wavelengthEdit_editingFinished();

    void on_loadSettingsButton_pressed();

    void on_saveSettingsButton_pressed();

    void on_saveChangesButton_clicked();

private:
    Ui::ConfigPowerMeter *ui;

    QVariant device;
    QList<QRadioButton*> buttons;

    QString settingsFileName;
    QSettings *settings;

    int slotNum;

    // values from device
    int numSlots;
    QList<QByteArray> powerReadings;
    QList<QByteArray> wavelengthSettings;
    QList<QByteArray> minWavelengths;
    QList<QByteArray> maxWavelengths;

    void setupWindow();
    void initWavelengthReadings();
    void initMinWavelengths();
    void initMaxWavelengths();
    void initChannelRadioButtons();


    void populatePowerUnit();
    void populatePower();
    void populateWavelengthUnit();
    void populateWavelength();
    void populateMinWavelength();
    void populateMaxWavelength();

    bool saveSettings();
    bool loadSettings();
    void populateAllValues();
    void getValuesFromConfig();
    void showEvent(QShowEvent* event);
    void convertAndDisplayWavelength(QList<QByteArray> wavelength, QLineEdit* displayField);

};

#endif // CONFIGPOWERMETER_H
