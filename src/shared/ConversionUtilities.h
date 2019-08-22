#ifndef CONVERSIONUTILITIES_H
#define CONVERSIONUTILITIES_H

#include <QByteArray>
#include <QtMath>
#include <constants.h>

class ConversionUtilities
{
public:
    ConversionUtilities();

    static double convertWattToDBm(double powerInWatt);
    static double convertWavelengthFromMeter(double wavelength, QByteArray unit);
    static double convertWavelengthToMeter(double wavelength, QByteArray unit);
    static double convertFrequencyFromHz(double frequency, QByteArray unit);
    static double convertFrequencyToHz(double freuqency, QByteArray unit);
};

#endif // CONVERSIONUTILITIES_H
