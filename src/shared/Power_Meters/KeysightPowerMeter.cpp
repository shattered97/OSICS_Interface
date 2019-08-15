#include "KeysightPowerMeter.h"

KeysightPowerMeter::KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc) : PowerMeter(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

KeysightPowerMeter::~KeysightPowerMeter()
{
}

void KeysightPowerMeter::measurePower(int window, QByteArray &response){

    QByteArray baseCmd = "read:pow?";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
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

void KeysightPowerMeter::getPowerUnit(int window, QByteArray &response){
    QByteArray baseCmd = "sens:pow:unit?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void KeysightPowerMeter::testCommand(QByteArray cmd, QByteArray &response){
    emit signalSendCmdRsp(theInstrLoc, cmd, response);
    qDebug() << "Response from test command: " << response;
}

void KeysightPowerMeter::queryWavelength(int window, QByteArray &response, QByteArray value){
    QByteArray baseCmd = "sens:pow:wav?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    baseCmd.insert(baseCmd.indexOf('\n'), " " + value);

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

void KeysightPowerMeter::setWavelength(int window, QByteArray &value, QByteArray &unit){
    QByteArray baseCmd = "sens:pow:wav\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));
    baseCmd.insert(baseCmd.indexOf('\n'), " " + value + unit);

    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void KeysightPowerMeter::getAllPowerUnits(QByteArray & response){
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";

    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);
}

int KeysightPowerMeter::getNumPowerMeterChannels(){
    // use the command to read all power units (response is easy to parse)
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";

    QByteArray response;
    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);

    // Response format: "1,1,1,1,1,1,1,1,\x00\n"
    // Count the number of tokens separated by ',' minus 1 for <END>\n
    int numChannels = response.split(',').size() - 1;

    return numChannels;
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

QList<double> KeysightPowerMeter::parseBinaryBlockPowerReadings(QByteArray binaryBlock, int numBytesPerValue){
    // FORMAT:
    // #<H><LEN><BLOCK><END>
    // # specifies that this is a binary block
    // <H> states the number of ascii characters in next field
    // <LEN> states how many bytes of binary data will follow

    QList<double> powerReadings;
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
        qDebug() << val;

        powerReadings.append(static_cast<double>(val));
    }

    return powerReadings;
}


