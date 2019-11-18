#include "ConversionUtilities.h"

ConversionUtilities::ConversionUtilities()
{

}

double ConversionUtilities::convertWattToDBm(double powerInWatt){
    // 10 ⋅ log10(1000⋅W)
    double converted = 10 * log10(1000 * powerInWatt);
    return converted;
}

double ConversionUtilities::convertDBmToWatt(double powerInDBm){
    // 10(43dBm/ 10) / 1000
    double converted = qPow(10, (powerInDBm / 10)) / 1000;
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

double ConversionUtilities::convertWavelengthToFrequency(double wavelength){
    double frequency = SPEED_OF_LIGHT / wavelength;
    return frequency;
}

double ConversionUtilities::convertFrequencyToWavelength(double frequency){
    double wavelength = SPEED_OF_LIGHT / frequency;
    return wavelength;
}

double ConversionUtilities::convertTimeFromSeconds(double time, QByteArray unit){
    double convertedTime = time;

    if(unit == "hr"){
        convertedTime = time / 60 / 60;
    }
    else if(unit == "min"){
        convertedTime = time / 60;
    }
    else if(unit == "ms"){
        convertedTime = time * 1000;
    }
    else if(unit == "us"){
        convertedTime = time / qPow(10, -6);
    }

    return convertedTime;
}

double ConversionUtilities::convertTimeToSeconds(double time, QByteArray unit){
    double convertedTime = time;

    if(unit == "hr"){
        convertedTime = time * 60 * 60;
    }
    else if(unit == "min"){
        convertedTime = time * 60;
    }
    else if(unit == "ms"){
        convertedTime = time / 1000;
    }
    else if(unit == "us"){
        convertedTime = time * qPow(10, -6);
    }

    return convertedTime;
}
