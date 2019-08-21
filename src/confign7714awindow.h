#ifndef CONFIGN7714AWINDOW_H
#define CONFIGN7714AWINDOW_H

#include <QMainWindow>
#include "N7714A.h"

namespace Ui {
class ConfigN7714AWindow;
}

class ConfigN7714AWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigN7714AWindow(N7714A *device, QWidget *parent = nullptr);
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

    void on_testEdit_editingFinished();

private:
    Ui::ConfigN7714AWindow *ui;

    N7714A *device;

    int slotNum;

    int wavelengthExponentIndex;
    int frequencyExponentIndex;

    QList<QByteArray> powerUnits;
    QList<double> powerSettings;
    QList<double> minPowers;
    QList<double> maxPowers;

    QList<QByteArray> laserState;

    QList<double> wavelengthSettings;
    QList<double> minWavelengths;
    QList<double> maxWavelengths;

    QList<double> frequencySettings;
    QList<double> minFrequencies;
    QList<double> maxFrequencies;

    double convertWavelengthFromMeter(double wavelengthInMeter);
    double convertWavelengthToMeter(double wavelengthInOtherUnit);
    double convertFrequencyFromHz(double frequencyInHz);
    double convertFrequencyToHz(double frequencyInOtherUnit);
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
};

#endif // CONFIGN7714AWINDOW_H
