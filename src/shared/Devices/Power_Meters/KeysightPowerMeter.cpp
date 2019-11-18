#include "KeysightPowerMeter.h"
#include <QMetaObject>
Q_DECLARE_METATYPE(QList<int>)
KeysightPowerMeter::KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc) : PowerMeter(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;


}

KeysightPowerMeter::~KeysightPowerMeter()
{
}

QByteArray KeysightPowerMeter::measurePower(int window){

    QByteArray baseCmd = "read:pow?";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

void KeysightPowerMeter::setPowerUnit(int window, QByteArray unit){

    QByteArray baseCmd = "sens:pow:unit\n";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    int unitCode = -1;

    if (unit == "dBm"){
        unitCode = 0;
    }
    else if (unit == "Watt"){
        unitCode = 1;
    }

    baseCmd.insert(baseCmd.indexOf('\n'), " " + QString::number(unitCode));

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray KeysightPowerMeter::getPowerUnit(int window){
    QByteArray baseCmd = "sens:pow:unit?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray KeysightPowerMeter::testCommand(QByteArray baseCmd)
{
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray KeysightPowerMeter::queryWavelength(int window, QByteArray value){
    QByteArray baseCmd = "sens:pow:wav?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    if(value != ""){
        baseCmd.insert(baseCmd.indexOf('\n'), " " + value);
    }

    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;
}

void KeysightPowerMeter::setWavelength(int window, QByteArray value, QByteArray unit){
    QByteArray baseCmd = "sens:pow:wav\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));
    baseCmd.insert(baseCmd.indexOf('\n'), " " + value + unit);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}


QByteArray KeysightPowerMeter::getAllPowerReadings(){
    QByteArray baseCmd = "read:pow:all?\n";
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;
}

QByteArray KeysightPowerMeter::getAllPowerUnits(){
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

int KeysightPowerMeter::getNumPowerMeterChannels(){
    // use the command to read all power units (response is easy to parse)
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";

    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    // Response format: "1,1,1,1,1,1,1,1,\x00\n"
    // Count the number of tokens separated by ',' minus 1 for <END>\n
    int numChannels = response.split(',').size() - 1;

    return numChannels;
}

QByteArray KeysightPowerMeter::getStabilityValues(int channel){
    QByteArray baseCmd = "sens:func:par:stab?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(channel));
    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;
}


void KeysightPowerMeter::setStabilityValues(int channel, double totalTime, double avgTime, double periodTime){
    QByteArray baseCmd = "sens:func:par:stab \n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(channel));

    // create comma-delimited list of times
    QStringList listOfTimes;
    listOfTimes.append(QByteArray::number(totalTime));
    listOfTimes.append(QByteArray::number(periodTime));
    listOfTimes.append(QByteArray::number(avgTime));

    // join with commas, and insert in to command string
    QString timesParam = listOfTimes.join("s,");
    baseCmd.insert(baseCmd.indexOf('\n'), timesParam);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray KeysightPowerMeter::getMinMaxModeValues(int channel){
    QByteArray baseCmd = "sens:func:par:minm?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(channel));

    response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;

}

void KeysightPowerMeter::setMinMaxModeValues(int channel, QByteArray mode, int dataPoints){
    QByteArray baseCmd = "sens:func:par:minm \n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(channel));

    // create single string from arguments
    QString param = mode + "," + QString::number(dataPoints);

    baseCmd.insert(baseCmd.indexOf('\n'), param);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QList<QByteArray> KeysightPowerMeter::getPowerReadingOnAllChannels(){

    // query for raw text block of readings
    QByteArray rawReadings = getAllPowerReadings();

    // format block and convert to list
    QList<QByteArray> readings = parseBinaryBlockPowerReadings(rawReadings, 4);

    return readings;
}

QList<QByteArray> KeysightPowerMeter::formatPowerUnits(QByteArray rawUnits, int numChannels){
    QList<QByteArray> formattedUnits;

    // turn each int from raw data into string (dBm or Watt)
    for(int i = 0; i < numChannels; i++){
        int unitIntValue = rawUnits.split(',')[i].toInt();

        if(unitIntValue == 0){
            formattedUnits.append("dBm");
        }
        else{
            formattedUnits.append("Watt");
        }
    }
    return formattedUnits;
}

QList<QByteArray> KeysightPowerMeter::parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue){
    // FORMAT:
    // #<H><LEN><BLOCK><END>
    // # specifies that this is a binary block
    // <H> states the number of ascii characters in next field
    // <LEN> states how many bytes of binary data will follow

    QList<QByteArray> powerReadings;
    // get value of <H>
    int numBytesInLength = binaryBlock.mid(1, 1).toInt();

    // get value of <LEN>
    int blockLength = binaryBlock.mid(2, numBytesInLength).toInt();

    // the rest of the data
    QByteArray dataBlock = binaryBlock.mid(2 + numBytesInLength, blockLength);

    for(int i = 0; i < dataBlock.size(); i += numBytesPerValue){
        QByteArray value = dataBlock.mid(i, numBytesPerValue);
        float val = 0;
        QDataStream stream(value);
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream >> val;

        powerReadings.append(QByteArray::number(static_cast<double>(val)));
    }

    return powerReadings;
}

void KeysightPowerMeter::applyConfigSettings(QSettings *configSettings)
{
    // apply nickname
    QByteArray nicknameToSet = configSettings->value(DEVICE_NICKNAME).value<QByteArray>();
    setNickname(nicknameToSet);

    // apply wavelength
    QList<QByteArray> wavelengthSettings = configSettings->value(WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i < numChannels; i++){
       int slot = i + 1;
       QByteArray unit = "m";
       setWavelength(slot, wavelengthSettings[i], unit);
    }

    // apply stability values
    QList<QByteArray> totalTimes = configSettings->value(PM_TOTAL_TIME).value<QList<QByteArray>>();
    QList<QByteArray> periodTimes = configSettings->value(PM_PERIOD_TIME).value<QList<QByteArray>>();
    QList<QByteArray> avgTimes = configSettings->value(PM_AVERAGING_TIME).value<QList<QByteArray>>();

    for(int i = 0; i < numChannels; i++){
        int channel = i + 1;
        setStabilityValues(channel, totalTimes[i].toDouble(), avgTimes[i].toDouble(), periodTimes[i].toDouble());
    }

    // apply minmax values
    QList<QByteArray> minMaxModes = configSettings->value(PM_MINMAX_MODE).value<QList<QByteArray>>();
    QList<QByteArray> minMaxDataPoints = configSettings->value(PM_MINMAX_DATA_POINTS).value<QList<QByteArray>>();

    for(int i = 0; i < numChannels; i++){
        int channel = i + 1;
        setMinMaxModeValues(channel, minMaxModes[i].mid(0, 4), minMaxDataPoints[i].toDouble());
    }

    // update values
    updateConfig(configSettings);
}

void KeysightPowerMeter::updateConfig(QSettings *configSettings)
{
    // get number of slots
    numChannels = getNumChannelsVar();
    configSettings->setValue(NUM_CHANNELS, QVariant::fromValue(numChannels));

    // get device address/identity
    configSettings->setValue(DEVICE_ADDRESS, QVariant::fromValue(theInstrLoc));
    configSettings->setValue(DEVICE_IDENTITY, QVariant::fromValue(theIdentity));
    configSettings->setValue(DEVICE_NICKNAME, QVariant::fromValue(getNickname()));

    // get power/wavelength settings
    updatePowerSettings(*configSettings);
    updateWavelengthSettings(*configSettings);

    // get stability settings
    updateStabilitySettings(*configSettings);

    // get minmax settings
    updateMinMaxSettings(*configSettings);
}

void KeysightPowerMeter::updateStabilitySettings(QSettings &configSettings){

    QList<QByteArray> totalTimes;
    QList<QByteArray> periodTimes;
    QList<QByteArray> avgTimes;

    for(int i = 0; i < numChannels; i++){
        int channel = i + 1;
        QByteArray stabilityValues = getStabilityValues(channel);
        QList<QByteArray> stabilityValuesList = stabilityValues.split(',');
        if(stabilityValuesList.size() == 3){
            // total time, period time, averaging time
            totalTimes.append(stabilityValuesList.at(0));
            periodTimes.append(stabilityValuesList.at(1));
            avgTimes.append(stabilityValuesList.at(2));
        }
    }

    configSettings.setValue(PM_TOTAL_TIME, QVariant::fromValue(totalTimes));
    configSettings.setValue(PM_PERIOD_TIME, QVariant::fromValue(periodTimes));
    configSettings.setValue(PM_AVERAGING_TIME, QVariant::fromValue(avgTimes));
}

void KeysightPowerMeter::updateMinMaxSettings(QSettings &configSettings){
    QList<QByteArray> minMaxModes;
    QList<QByteArray> minMaxDataPoints;

    for(int i = 0; i < numChannels; i++){
        int channel = i + 1;
        QByteArray minMaxModeAndPoints = getMinMaxModeValues(channel);
        QByteArray mode = minMaxModeAndPoints.split(',')[0];
        QByteArray points = minMaxModeAndPoints.split(',')[1].trimmed();
        minMaxModes.append(mode);
        minMaxDataPoints.append(points);
    }

    configSettings.setValue(PM_MINMAX_MODE, QVariant::fromValue(minMaxModes));
    configSettings.setValue(PM_MINMAX_DATA_POINTS, QVariant::fromValue(minMaxDataPoints));
}

void KeysightPowerMeter::updatePowerSettings(QSettings &configSettings)
{
    // query device for power readings
    QByteArray rawPowerReadings = getAllPowerReadings();
    QList<QByteArray> powerReadings = parseBinaryBlockPowerReadings(rawPowerReadings, 4);

    // save power readings to settings
    configSettings.setValue(POWER_READINGS, QVariant::fromValue(powerReadings));
    configSettings.sync();
}

void KeysightPowerMeter::updateWavelengthSettings(QSettings &configSettings){

    // query device for wavelengths
    QList<QByteArray> wavelengthSettings;
    for(int i = 1; i <= numChannels; i++){
        QByteArray wavelength = queryWavelength(i);
        wavelengthSettings.append(QByteArray::number(wavelength.toDouble()));
    }

    // save device wavelengths
    configSettings.setValue(WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));

    // query for min wavelengths
    QList<QByteArray> minWavelengths;
    for(int i = 1; i <= numChannels; i++){
        QByteArray wavelength = queryWavelength(i, "MIN");
        minWavelengths.append(QByteArray::number(wavelength.toDouble()));
    }

    // save min wavelengths
    configSettings.setValue(MIN_WAVELENGTHS , QVariant::fromValue(minWavelengths));

    // query for max wavelengths
    QList<QByteArray> maxWavelengths;
    for(int i = 1; i <= numChannels; i++){
        QByteArray wavelength = queryWavelength(i, "MAX");
        maxWavelengths.append(QByteArray::number(wavelength.toDouble()));
    }

    // save max wavelengths
    configSettings.setValue(MAX_WAVELENGTHS, QVariant::fromValue(maxWavelengths));
}
