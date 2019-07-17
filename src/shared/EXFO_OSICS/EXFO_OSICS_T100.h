#ifndef EXFO_OSICS_T100_H
#define EXFO_OSICS_T100_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_T100 : EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc);

    // ********************************* Diode-Current Setting Commands *********************************

    // CH#:I?
    bool diodeCurrentLevelModuleQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);

    // CH#:IMAX?
    bool diodeMaxCurrentModuleQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);


    // ********************************* Calibration Control Commands ********************************

    // CH#:MOD_F=
    bool setModFrequencyModuleCmd(ViSession &defaultSession, int moduleNum, QByteArray &frequency);

    // CH#:MOD_F?
    bool modFrequencyModuleQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);

    // CH#:WAVEREF
    bool runWavelengthRefProcedureCmd(ViSession &defaultSession, int moduleNum);

    // CH#:LCAL1=
    bool setFirstCalibrationWavelengthCmd(ViSession &defaultSession, int moduleNum, QByteArray &wavelength);

    // CH#:LCAL2=
    bool setSecondCalibrationWavelengthCmd(ViSession &defaultSession, int moduleNum, QByteArray &wavelength);

    // CH#:LCAL1?
    bool firstCalibrationWavelengthQuery(ViSession &defaultSession, int moduleNum,  QByteArray &response);

    // CH#:LCAL2?
    bool secondCalibrationWavelengthQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);

    // CH#:PCAL1=
    bool setFirstCalibrationPowerCmd(ViSession &defaultSession, int moduleNum, QByteArray &power);

    // CH#"PCAL2=
    bool setSecondCalibrationPowerCmd(ViSession &defaultSession, int moduleNum, QByteArray &power);

    // CH#:PCAL1?
    bool firstCalibrationPowerQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);

    // CH#:PCAL2?
    bool secondCalibrationPowerQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);


    // ********************************** Module Parameter-Monitoring Commands *********************************

    // CH#:AOUT
    bool assignOutBNCPortToSignalCmd(ViSession &defaultSession, int moduleNum, QByteArray &signalType);

    // CH#:AOUT?
    bool outBNCPortSignalMonitoringQuery(ViSession &defaultSession, int moduleNum, QByteArray &response);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

};

#endif // EXFO_OSICS_T100_H
