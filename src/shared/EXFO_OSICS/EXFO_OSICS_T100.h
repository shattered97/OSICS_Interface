#ifndef EXFO_OSICS_T100_H
#define EXFO_OSICS_T100_H

#include "EXFO_OSICS_MAINFRAME.h"

class EXFO_OSICS_T100 : EXFO_OSICS_MAINFRAME
{
public:
    EXFO_OSICS_T100(QByteArray theIdentity, QByteArray theInstrLoc);

    // ********* Diode-Current Setting Commands **********

    // CH#:I?
    bool diodeCurrentLevelModuleQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &response);

    // CH#:IMAX?
    bool diodeMaxCurrentModuleQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &response);

    // ********* Calibration Control Commands *********

    // CH#:MOD_F=
    bool setModFrequencyModuleCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &frequency);

    // CH#:MOD_F?
    bool modFrequencyModuleQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &response);

    // CH#:WAVEREF
    bool runWavelengthRefProcedureCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum);

    // CH#:LCAL1=
    bool setFirstCalibrationWavelengthCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &wavelength);

    // CH#:LCAL2=
    bool setSecondCalibrationWavelengthCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &wavelength);

    // CH#:LCAL1?
    bool firstCalibrationWavelengthQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &wavelength, QByteArray &response);

    // CH#:LCAL2?
    bool secondCalibrationWavelengthQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &wavelength, QByteArray &response);

    // CH#:PCAL1=
    bool setFirstCalibrationPowerCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &power);

    // CH#"PCAL2=
    bool setSecondCalibrationPowerCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &power);

    // CH#:PCAL1?
    bool firstCalibrationPowerQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &power, QByteArray &response);

    // CH#:PCAL2?
    bool secondCalibrationPowerQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &power, QByteArray &response);

    // ********* Module Parameter-Monitoring Commands *********

    // CH#:AOUT
    bool assignOutBNCPortToSignalCmd(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &signalType);

    // CH#:AOUT?
    bool outBNCPortSignalMonitoringQuery(ViSession &defaultSession, ViSession &instrSession, int moduleNum, QByteArray &response);

private:
    QByteArray theIdentity;
    QByteArray theInstrLoc;

};

#endif // EXFO_OSICS_T100_H
