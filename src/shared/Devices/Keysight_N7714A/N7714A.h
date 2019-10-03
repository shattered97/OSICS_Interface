#ifndef N7714A_H
#define N7714A_H

#include "DefaultInstrument.h"

class N7714A : public DefaultInstrument
{
    Q_OBJECT

public:
    N7714A(QByteArray theIdentity, QByteArray theInstrLoc);

    void queryPowerUnit(int module, QByteArray &response);

    void execPowerUnit(int module, QByteArray unit="");

    void queryPowerStatus(int module, QByteArray &response);

    void execPowerOnModule(int module);

    void execPowerOffModule(int module);

    void queryPowerLevel(int module, QByteArray &response, QByteArray value="");

    void execPowerLevel(int module, QByteArray value, QByteArray unit="");

    void queryWavelength(int module, QByteArray &response, QByteArray value="");

    void execWavelength(int module, QByteArray value, QByteArray unit="");

    void queryFrequency(int module, QByteArray &response, QByteArray value="");

    void execFrequency(int module, QByteArray value, QByteArray unit="");

    void testCommand(QByteArray cmd, QByteArray &response);

    void queryAutoWavMode(int module, QByteArray &response);

    void turnOnAutoWavMode(int module);

    void updateConfig(QSettings &);

    void applyConfigSettings(QSettings &configSettings);


//signals:
//    void signalSendCmdRsp(QByteArray instrAddress, QByteArray *command, QByteArray *response);
//    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray *command);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

    void updatePowerSettings(QSettings &configSettings);
    void updateWavelengthSettings(QSettings &configSettings);
    void updateFrequencySettings(QSettings &configSettings);
};

#endif // N7714A_H


