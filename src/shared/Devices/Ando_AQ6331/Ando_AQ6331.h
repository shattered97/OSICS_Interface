#ifndef ANDO_AQ6331_H
#define ANDO_AQ6331_H

#include "DefaultInstrument.h"

class Ando_AQ6331: public DefaultInstrument
{
    Q_OBJECT

public:
    Ando_AQ6331(QByteArray theIdentity, QByteArray theInstrLoc);

    void updateConfig(QSettings &);
    void applyConfigSettings(QSettings &configSettings);

    void runSingleSweep();
    void setCenterWavelength(QByteArray wavelength);
    void setSpan(QByteArray span);
    void setResolution(QByteArray resolution);

    QByteArray getCenterWavelength();
    QByteArray getSpan();
    QPair <QByteArray, QByteArray> getPeakDataFromTrace(QByteArray wavelength, QByteArray power);
    QByteArray getResolution();

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

};


#endif // ANDO_AQ6331_H
