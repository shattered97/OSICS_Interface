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
    QByteArray response = "";
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
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray KeysightPowerMeter::testCommand(QByteArray baseCmd)
{
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QByteArray KeysightPowerMeter::queryWavelength(int window, QByteArray value){
    QByteArray baseCmd = "sens:pow:wav?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    if(value != ""){
        baseCmd.insert(baseCmd.indexOf('\n'), " " + value);
    }

    QByteArray response = "";
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
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;
}

QByteArray KeysightPowerMeter::getAllPowerUnits(){
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

int KeysightPowerMeter::getNumPowerMeterChannels(){
    // use the command to read all power units (response is easy to parse)
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";

    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    // Response format: "1,1,1,1,1,1,1,1,\x00\n"
    // Count the number of tokens separated by ',' minus 1 for <END>\n
    int numChannels = response.split(',').size() - 1;

    return numChannels;
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

void KeysightPowerMeter::applyConfigSettings(QSettings &configSettings)
{
    QList<QByteArray> wavelengthSettings = configSettings.value(WAVELENGTH_SETTINGS).value<QList<QByteArray>>();
    for(int i = 0; i < numSlots; i++){
       int slot = i + 1;
       QByteArray unit = "m";
       setWavelength(slot, wavelengthSettings[i], unit);
    }
    // update values
    updateConfig(configSettings);
}

void KeysightPowerMeter::updateConfig(QSettings &configSettings)
{
    // get number of slots
    numSlots = getNumPowerMeterChannels();
    configSettings.setValue(NUM_CHANNELS, QVariant::fromValue(numSlots));

    // get device address/identity
    configSettings.setValue(DEVICE_ADDRESS, QVariant::fromValue(theInstrLoc));
    configSettings.setValue(DEVICE_IDENTITY, QVariant::fromValue(theIdentity));

    // get power/wavelength settings
    updatePowerSettings(configSettings);
    updateWavelengthSettings(configSettings);
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
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength = queryWavelength(i);
        wavelengthSettings.append(QByteArray::number(wavelength.toDouble()));
    }

    // save device wavelengths
    configSettings.setValue(WAVELENGTH_SETTINGS, QVariant::fromValue(wavelengthSettings));

    // query for min wavelengths
    QList<QByteArray> minWavelengths;
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength = queryWavelength(i, "MIN");
        minWavelengths.append(QByteArray::number(wavelength.toDouble()));
    }

    // save min wavelengths
    configSettings.setValue(MIN_WAVELENGTHS , QVariant::fromValue(minWavelengths));

    // query for max wavelengths
    QList<QByteArray> maxWavelengths;
    for(int i = 1; i <= numSlots; i++){
        QByteArray wavelength = queryWavelength(i, "MAX");
        maxWavelengths.append(QByteArray::number(wavelength.toDouble()));
    }

    // save max wavelengths
    configSettings.setValue(MAX_WAVELENGTHS, QVariant::fromValue(maxWavelengths));
}
