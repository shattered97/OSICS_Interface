#include "KeysightPowerMeter.h"

KeysightPowerMeter::KeysightPowerMeter(QByteArray theIdentity, QByteArray theInstrLoc) : PowerMeter(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

KeysightPowerMeter::~KeysightPowerMeter()
{
}

// Instead of returning sendCmdRsp/sendCmdNoRsp (which needs default session as param),
// send signal to orchestrator passing along the command and/or response.
// in orchestrator a signal will be sent back for

bool KeysightPowerMeter::measurePower(ViSession &defaultSession, int window, QByteArray &response){

    QByteArray baseCmd = "read:pow?";
    baseCmd.insert(baseCmd.indexOf(':'),  QByteArray::number(window));

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool KeysightPowerMeter::setPowerUnit(ViSession &defaultSession, int window, QByteArray unit){

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
    return sendCmdNoRsp(defaultSession, baseCmd);
}

bool KeysightPowerMeter::getPowerUnit(ViSession &defaultSession, int window, QByteArray &response){
    QByteArray baseCmd = "sens:pow:unit?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    return sendCmdRsp(defaultSession, baseCmd, response);
}

bool KeysightPowerMeter::testCommand(ViSession &defaultSession, QByteArray cmd, QByteArray &response){
    return sendCmdRsp(defaultSession, cmd, response);
}

bool KeysightPowerMeter::queryWavelength(ViSession &defaultSession, int window, QByteArray &response, QByteArray value){
    QByteArray baseCmd = "sens:pow:wav?\n";
    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));

    baseCmd.insert(baseCmd.indexOf('\n'), " " + value);

    // ******************* TEST SIGNAL TO ORCHESTRATOR **********************
    qDebug() << "EMITTING SIGNAL signalSendCmdRsp";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, response);


    // **********************************************************************
    return true;
}

bool KeysightPowerMeter::setWavelength(ViSession &defaultSession, int window, QByteArray &value, QByteArray &unit){
    QByteArray baseCmd = "sens:pow:wav\n";

    baseCmd.insert(baseCmd.indexOf(':'), QByteArray::number(window));
    baseCmd.insert(baseCmd.indexOf('\n'), " " + value + unit);

    return sendCmdNoRsp(defaultSession, baseCmd);
}

bool KeysightPowerMeter::getAllPowerUnits(ViSession &defaultSession, QByteArray & response){
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";
    return sendCmdRsp(defaultSession, baseCmd, response);
}

int KeysightPowerMeter::getNumPowerMeterChannels(ViSession &defaultSession){
    // use the command to read all power units (response is easy to parse)
    QByteArray baseCmd = "sens:pow:unit:all:csv?\n";

    QByteArray response;
    sendCmdRsp(defaultSession, baseCmd, response);

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


