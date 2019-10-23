#ifndef ANDO_AQ6331_H
#define ANDO_AQ6331_H

#include "DefaultInstrument.h"

class Ando_AQ6331: public DefaultInstrument
{
    Q_OBJECT

public:
    Ando_AQ6331(QByteArray theIdentity, QByteArray theInstrLoc);

    // ************************************ DEVICE SETTINGS *************************************

    void updateConfig(QSettings &configSettings);
    void applyConfigSettings(QSettings &configSettings);

    // ************************************ DEVICE COMMANDS *************************************

    /**
     * @brief runSingleSweep Command to run a single sweep on the OSA. No response expected from instrument.
     */
    void runSingleSweep();

    /**
     * @brief setCenterWavelength Command to set the center wavelength (in nanometers). No response expected
     *                            from instrument.
     * @param wavelength Center wavelength to set (nm).
     */
    void setCenterWavelength(QByteArray wavelength);

    /**
     * @brief setSpan Command to set the window span (distance between window min to window max with
     *                the center wavelength in the middle). No response expected from instrument.
     * @param span Span to set
     */
    void setSpan(QByteArray span);

    /**
     * @brief setResolution Command to set the wavelength resolution (in nanometers). No response expected
     *                      from instrument
     * @param resolution Wavelength resolution to set (nm).
     */
    void setResolution(QByteArray resolution);

    /**
     * @brief getCenterWavelength Command to query the instrument for the center wavelength (in nanometers).
     *                            Response Format: xxxx.xx (Example: 1500.01)
     * @return Center wavelength returned from instrument.
     */
    QByteArray getCenterWavelength();

    /**
     * @brief getSpan Command to query the instrument for the span (in nanometers).
     *                Response Format: xxxx.x (Example: 0.5 OR 1000.1)
     * @return Span returned from instrument.
     */
    QByteArray getSpan();

    /**
     * @brief getResolution Command to query the instrument for the wavelength resolution (in nanometers).
     *                      Response Format: x.xx (Example 0.05)
     * @return Resolution returned from instrument.
     */
    QByteArray getResolution();

    /**
     * @brief getPeakDataFromTrace
     * @param wavelength *********
     * @param power
     * @return
     */
    QPair <QByteArray, QByteArray> getPeakDataFromTrace(QByteArray wavelength, QByteArray power);



private:
    QByteArray theIdentity;      // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;      // the physical address of the instrument

};


#endif // ANDO_AQ6331_H
