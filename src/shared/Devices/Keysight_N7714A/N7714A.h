#ifndef N7714A_H
#define N7714A_H

#include "DefaultInstrument.h"

class N7714A : public DefaultInstrument
{
    Q_OBJECT

public:
    N7714A(QByteArray theIdentity, QByteArray theInstrLoc);

    QByteArray queryPowerUnit(int module);

    void execPowerUnit(int module, QByteArray unit="");

    QByteArray queryPowerStatus(int module);

    void execPowerOnModule(int module);

    void execPowerOffModule(int module);

    QByteArray queryPowerLevel(int module, QByteArray value="");

    void execPowerLevel(int module, QByteArray value, QByteArray unit="");

    QByteArray queryWavelength(int module, QByteArray value="");

    void execWavelength(int module, QByteArray value, QByteArray unit="");

    QByteArray queryFrequency(int module, QByteArray value="");

    void execFrequency(int module, QByteArray value, QByteArray unit="");

    QByteArray testCommand(QByteArray cmd);

    QByteArray queryAutoWavMode(int module);

    void turnOnAutoWavMode(int module);

    void updateConfig(QSettings *);

    void applyConfigSettings(QSettings *configSettings);


private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void updateFrequencySettings(QSettings &configSettings);
};

#endif // N7714A_H


