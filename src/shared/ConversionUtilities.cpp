#include "ConversionUtilities.h"

ConversionUtilities::ConversionUtilities()
{

}

double ConversionUtilities::convertWattToDBm(double powerInWatt){
    // 10 ⋅ log10(1000⋅W)
    double converted = 10 * log10(1000 * powerInWatt);
    return converted;
}

double ConversionUtilities::convertWavelengthFromMeter(double wavelength, QByteArray unit){
    int exp = WAV_CONVERSION_MAP.value(unit);
    double converted = wavelength * qPow(10, exp * -1);
    return converted;
}

double ConversionUtilities::convertWavelengthToMeter(double wavelength, QByteArray unit){
    int exp = WAV_CONVERSION_MAP.value(unit);
    double converted = wavelength * qPow(10, exp);
    return converted;
}

double ConversionUtilities::convertFrequencyFromHz(double frequency, QByteArray unit){
    int exp = FREQ_CONVERSION_MAP.value(unit);
    double converted = frequency * qPow(10, exp * -1);
    return converted;
}

double ConversionUtilities::convertFrequencyToHz(double frequency, QByteArray unit){
    int exp = FREQ_CONVERSION_MAP.value(unit);
    double converted = frequency * qPow(10, exp);
    return converted;
}
