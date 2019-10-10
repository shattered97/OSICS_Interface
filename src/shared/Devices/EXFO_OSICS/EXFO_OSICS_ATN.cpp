#include "EXFO_OSICS_ATN.h"

EXFO_OSICS_ATN::EXFO_OSICS_ATN(QByteArray theIdentity, QByteArray theInstrLoc) : EXFO_OSICS_MAINFRAME(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void EXFO_OSICS_ATN::setModuleAttenuationCmd(int slotNum, QByteArray attenuation){
    // Command: "CH#:ATN\n"
    // Params: 0 < slotnum <= 8
    // Response: None
     QByteArray baseCmd = "CH#:ATN\n";
     baseCmd = insertSlotNum(baseCmd, slotNum);
     baseCmd = appendParamToCmdWithSpace(baseCmd, attenuation);

     emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray EXFO_OSICS_ATN::moduleAttenuationQuery(int slotNum){
    // Command: "CH#:ATN?\n";
    // Params: 0 < slotnum <= 8
    // Response: CH#:ATN=xx.xx

    QByteArray baseCmd = "CH#:ATN?\n";

     baseCmd = insertSlotNum(baseCmd, slotNum);
     QByteArray response = "";
     emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);

     return response;
}

QByteArray EXFO_OSICS_ATN::moduleAttenuationMinMaxQuery(int slotNum, QByteArray wavelengthNum){
    // Command: "CH#:ATN_MIN_MAX?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:ATN_MIN_MAX=+<minimum value>+<maximum value>

    QByteArray baseCmd = "CH#:ATN_MIN_MAX?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    QByteArray response = "";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);

    return response;
}

QByteArray EXFO_OSICS_ATN::moduleWavelengthNMQuery(int slotNum, QByteArray wavelengthNum){
    // Command: "CH#:LREF?\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:L(1|2)=<wavelength value>

    QByteArray baseCmd = "CH#:LREF?\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, wavelengthNum);

    QByteArray response = "";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);

    return response;
}

void EXFO_OSICS_ATN::moduleAttenuationOffsetCmd(int slotNum, QByteArray wavelengthNum, QByteArray offsetVal){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    //         -10 dB <= offsetVal <= +10 dB (offset in dB, format: xx.xx)
    // Response: None

    QByteArray baseCmd = "CH#:OFFSET\n";
    baseCmd = insertSlotNum(baseCmd, slotNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, wavelengthNum);
    baseCmd = appendParamToCmdWithSpace(baseCmd, offsetVal);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray EXFO_OSICS_ATN::moduleAttenuationOffsetQuery(int slotNum, QByteArray wavelengthNum){
    // Command: "CH#:OFFSET\n"
    // Params: 0 < slotnum <= 8
    //         wavelengthNum = 1 (first wavelength of factory calibration) OR wavelengthNum = 2 (second wl of factory calibration)
    // Response: CH#:OFFSET(1:2)=+xx.xx

    QByteArray baseCmd = "CH#:OFFSET?\n";
     baseCmd = insertSlotNum(baseCmd, slotNum);
     baseCmd = appendParamToCmdWithSpace(baseCmd, wavelengthNum);

     QByteArray response = "";
     emit signalSendCmdRsp(theInstrLoc, baseCmd, &response);

     return response;
}

void EXFO_OSICS_ATN::setSlotNum(int slotNum){
    this->slotNum = slotNum;
}

void EXFO_OSICS_ATN::applyConfigSettings(QSettings &configSettings){
    qDebug() << "in applyConfigSettings() for ATN";

    // apply attenuation
    QByteArray attenuation = configSettings.value(EXFO_OSICS_ATN_ATTENUATION).value<QByteArray>();
    setModuleAttenuationCmd(slotNum, attenuation);

    // apply refwavelength number
    QByteArray refWavNumber = configSettings.value(EXFO_OSICS_ATN_REF_WAV_NUMBER).value<QByteArray>();
    setRefWavelengthModuleCmd(slotNum, refWavNumber);

    // apply attenuation offset
    QByteArray firstOffset = configSettings.value(EXFO_OSICS_ATN_OFFSET_1).value<QByteArray>();
    QByteArray secondOffset = configSettings.value(EXFO_OSICS_ATN_OFFSET_2).value<QByteArray>();
    moduleAttenuationOffsetCmd(slotNum, "1", firstOffset);
    moduleAttenuationOffsetCmd(slotNum, "2", secondOffset);

    updateConfig(configSettings);
}

void EXFO_OSICS_ATN::updateConfig(QSettings &configSettings){
    qDebug() << "atn updateConfig()";

    configSettings.setValue(DEVICE_IDENTITY, theIdentity);
    configSettings.setValue(DEVICE_LOCATION, theInstrLoc);

    updateAttenuationSettings(configSettings);
    updateOffsetSettings(configSettings);
    updateWavelengthSettings(configSettings);
}

void parseMinMaxReturnValue(QByteArray valueToParse, QByteArray &minValue, QByteArray &maxValue){
    // FORMAT (+ | -)xx.xx(+ | -)xx.xx

    char firstSign = '+';
    char secondSign = '+';

    // get sign of first value
    firstSign = valueToParse.at(0);
    qDebug() << "first sign: " << firstSign;

    // remove first sign then search for second sign
    QByteArray valueToParseCopy = valueToParse;
    valueToParseCopy = valueToParseCopy.remove(0, 1);

    // find second sign
    if(valueToParseCopy.contains('-')){
        // second sign is negative
        secondSign = '-';
    }
    else if(valueToParseCopy.contains('+')){
        // second sign is positive
        secondSign = '+';
    }

    minValue = firstSign + valueToParse.split(firstSign)[1];

    // get index of second sign
    int secondIndex = valueToParse.lastIndexOf(secondSign);
    minValue = valueToParse.mid(0, secondIndex);
    maxValue = valueToParse.mid(secondIndex);

    qDebug() << "minValue: " << minValue;
    qDebug() << "maxValue: " << maxValue;

}

void EXFO_OSICS_ATN::updateAttenuationSettings(QSettings &configSettings)
{
    qDebug() << "updateAttenuationSettings()";
    // get attenuation value / parse returned value
    QByteArray attenuation = moduleAttenuationQuery(slotNum);
    attenuation = attenuation.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_ATTENUATION, attenuation);

    // get reference wavelength number (1 | 2)
    QByteArray refWavelengthNumber = refWavelengthModuleQuery(slotNum);
    refWavelengthNumber = refWavelengthNumber.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_REF_WAV_NUMBER, refWavelengthNumber);

    // get min/max attenuation for wavelength number 1
    QByteArray minAndMaxAtten1 = moduleAttenuationMinMaxQuery(slotNum, "1");
    minAndMaxAtten1 = minAndMaxAtten1.split('=')[1];
    QByteArray minAttenuation1;
    QByteArray maxAttenuation1;
    parseMinMaxReturnValue(minAndMaxAtten1, minAttenuation1, maxAttenuation1);

    configSettings.setValue(EXFO_OSICS_ATN_MIN_ATTENUATION_1, minAttenuation1);
    configSettings.setValue(EXFO_OSICS_ATN_MAX_ATTENUATION_1, maxAttenuation1);

    // get min/max attenuation for wavelength number 2
    QByteArray minAndMaxAtten2 = moduleAttenuationMinMaxQuery(slotNum, "2");
    minAndMaxAtten2 = minAndMaxAtten2.split('=')[1];
    QByteArray minAttenuation2;
    QByteArray maxAttenuation2;
    parseMinMaxReturnValue(minAndMaxAtten2, minAttenuation2, maxAttenuation2);
    configSettings.setValue(EXFO_OSICS_ATN_MIN_ATTENUATION_2, minAttenuation2);
    configSettings.setValue(EXFO_OSICS_ATN_MAX_ATTENUATION_2, maxAttenuation2);
}

void EXFO_OSICS_ATN::updateOffsetSettings(QSettings &configSettings)
{
    qDebug() << "updateOffsetSettings()";
    // get offset for wavelength number 1
    QByteArray firstOffset = moduleAttenuationOffsetQuery(slotNum, "1");
    firstOffset = firstOffset.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_OFFSET_1, firstOffset);

    // get offset for wavelength number 2
    QByteArray secondOffset = moduleAttenuationOffsetQuery(slotNum, "2");
    secondOffset = secondOffset.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_OFFSET_2, secondOffset);
}

void EXFO_OSICS_ATN::updateWavelengthSettings(QSettings &configSettings)
{
    qDebug() << "updateWavelengthSettings()";

    // set reference wavelength number
    QByteArray refWavelength = refWavelengthModuleQuery(slotNum);
    refWavelength = refWavelength.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_REF_WAV_NUMBER, refWavelength);

    // get reference wavelength for wavelength number 1
    QByteArray firstWavelength = moduleWavelengthNMQuery(slotNum, "1");
    firstWavelength = firstWavelength.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_REF_WAVELENGTH_1, firstWavelength);

    // get reference wavelength for wavelength number 2
    QByteArray secondWavelength = moduleWavelengthNMQuery(slotNum, "2");
    secondWavelength = secondWavelength.split('=')[1];
    configSettings.setValue(EXFO_OSICS_ATN_REF_WAVELENGTH_2, secondWavelength);
}

