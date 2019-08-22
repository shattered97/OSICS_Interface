#ifndef CONFIGN7714AWINDOW_H
#define CONFIGN7714AWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

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

    void on_wavelngthUnitComboBox_currentIndexChanged();

    void on_frequencyUnitComboBox_currentIndexChanged();

    void on_laserWavelengthEdit_editingFinished();

    void on_laserFrequencyEdit_editingFinished();

private:
    Ui::ConfigN7714AWindow *ui;

    QVariant device;
    QString settingsFileName;
    QSettings *settings;

    int slotNum;

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

    void setupAutoMode();
    void setupWindow();
    void populateAllValues();

    // initialize power displays on all channels/slots
    void initPowerUnits();
    void initPowerSettings();
    void initMinPower();
    void initMaxPower();
    void initPowerState();

    // initialize wavelength displays on all channels/slots
    void initWavelengthSettings();
    void initMinWavelengths();
    void initMaxWavelengths();

    // initialize frequency displays on all channels/slots
    void initFrequencySettings();
    void initMinFrequencies();
    void initMaxFrequencies();

    void getValuesFromConfig();
};

#endif // CONFIGN7714AWINDOW_H
