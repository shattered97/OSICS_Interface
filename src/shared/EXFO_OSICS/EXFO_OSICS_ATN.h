#ifndef EXFO_OSICS_ATN_H
#define EXFO_OSICS_ATN_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_ATN : EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc);

    // CH#:ATN
    bool setModuleAttenuationCmd(ViSession &defaultSession, int moduleNum, QByteArray &attenuation);

    // CH#:ATN?
    bool moduleAttenuationQuery(ViSession &defaultSession, int slotNum, QByteArray &response);

    // CH#:ATN_MIN_MAX?
    bool moduleAttenuationMinMaxQuery(ViSession &defaultSession, int moduleNum, QByteArray wavelengthNum, QByteArray &response);

    // CH#:LREF?
    bool moduleWavelengthNMQuery(ViSession &defaultSession, int moduleNum, QByteArray wavelengthNum, QByteArray &response);

    // CH#:OFFSET
    bool moduleAttenuationOffsetCmd(ViSession &defaultSession, int moduleNum, QByteArray wavelengthNum, QByteArray offsetVal);

    // CH#:OFFSET?
    bool moduleAttenuationOffsetQuery(ViSession &defaultSession, int moduleNum, QByteArray wavelengthNum, QByteArray &response);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
};

#endif // EXFO_OSICS_ATN_H
