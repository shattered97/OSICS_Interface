#ifndef CONFIGPOWERMETER_H
#define CONFIGPOWERMETER_H

#include <QMainWindow>
#include "Orchestrator.h"
#include "KeysightPowerMeter.h"
#include <QtMath>
#include <QFileDialog>
#include <QSettings>
#include <QRadioButton>
#include <QHBoxLayout>

namespace Ui {
class ConfigPowerMeter;
}

class ConfigPowerMeter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigPowerMeter(Orchestrator &orchestrator, PowerMeter *device, QWidget *parent = nullptr);
    ~ConfigPowerMeter();

private slots:
    void slot_radio_button_clicked();

    void on_powerUnitComboBox_currentIndexChanged(const QString &unit);

    void on_wavelengthComboBox_currentIndexChanged();

    void on_wavelengthEdit_editingFinished();

    void on_testEdit_editingFinished();

    void on_loadSettingsButton_pressed();

    void on_saveSettingsButton_pressed();

private:
    Ui::ConfigPowerMeter *ui;

    PowerMeter *device;
    Orchestrator *orchestrator;
    ViSession *defaultSession;
    QList<QRadioButton*> buttons;
    QString settingsFileName;

    int numSlots;
    int slotNum;
    int wavelengthExponentIndex;

    QList<QByteArray> powerUnits;
    QList<double> powerReadings;
    QList<double> wavelengthReadings;
    QList<double> minWavelengths;
    QList<double> maxWavelengths;

    void setupWindow();
    void initWavelengthReadings();
    void initMinWavelengths();
    void initMaxWavelengths();
    void initChannelRadioButtons();

    void populateAllValues();
    void populatePowerUnit();
    void populatePower();
    void populateWavelengthUnit();
    void populateWavelength();
    void populateMinWavelength();
    void populateMaxWavelength();
    double convertWavelengthFromMeter(double wavelength);

    bool saveSettings();
    bool loadSettings();

};

#endif // CONFIGPOWERMETER_H
