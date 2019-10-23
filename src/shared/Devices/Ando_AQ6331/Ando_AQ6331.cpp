#include "Ando_AQ6331.h"

Ando_AQ6331::Ando_AQ6331(QByteArray theIdentity, QByteArray theInstrLoc) : DefaultInstrument(theIdentity, theInstrLoc)
{
    this->theIdentity = theIdentity;
    this->theInstrLoc = theInstrLoc;
}

void Ando_AQ6331::runSingleSweep()
{
    QByteArray baseCmd = "SGL\n";
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Ando_AQ6331::setCenterWavelength(QByteArray wavelength)
{
    QByteArray baseCmd = "CTRWL\n";
    baseCmd.insert(baseCmd.indexOf('\n'), wavelength);
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Ando_AQ6331::setSpan(QByteArray span)
{
    QByteArray baseCmd = "SPAN\n";
    baseCmd.insert(baseCmd.indexOf('\n'), span);
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Ando_AQ6331::setResolution(QByteArray resolution)
{
    QByteArray baseCmd = "RESLN\n";
    baseCmd.insert(baseCmd.indexOf('\n'), resolution);
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

QByteArray Ando_AQ6331::getCenterWavelength()
{
    QByteArray baseCmd = "CTRWL?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);

    return response;
}

QByteArray Ando_AQ6331::getSpan()
{
    QByteArray baseCmd = "SPAN?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}

QPair<QByteArray, QByteArray> Ando_AQ6331::getPeakDataFromTrace(QByteArray wavelength, QByteArray power){

    // send command to query for the wavelength data captured from trace
    QByteArray wavTraceCmd = "WDATA\n";
    QByteArray wavTraceDataRaw = "";
    sendCommandAndWaitForResponse(theInstrLoc, wavTraceCmd, &wavTraceDataRaw);

    // parse the raw data into a list
    QList<QByteArray> wavDataList = wavTraceDataRaw.trimmed().split(',');

    // remove first item in list because it's not part of following data
    wavDataList.removeFirst();

    // send command to query for the power data captured from trace
    QByteArray powTraceCmd = "LDATA\n";
    QByteArray powerTraceDataRaw = "";
    sendCommandAndWaitForResponse(theInstrLoc, powTraceCmd, &powerTraceDataRaw);

    // parse raw data into a list
    QList<QByteArray> powDataList = powerTraceDataRaw.trimmed().split(',');

    // same as wavelength data, first item is removed because it is not a data point
    powDataList.removeFirst();

    // get index of highest power level in the power data list
    double maxPow = powDataList[0].toDouble();
    int maxPowIndex = 0;
    for(int i = 0; i < powDataList.size(); i++){
        double power = powDataList[i].toDouble();
        if(power > maxPow){
            maxPow = power;
            maxPowIndex = i;
        }
    }


    power = powDataList[maxPowIndex];
    wavelength = wavDataList[maxPowIndex];
    return {wavelength, power};
}

QByteArray Ando_AQ6331::getResolution()
{
    QByteArray baseCmd = "RESLN?\n";
    QByteArray response = "";
    sendCommandAndWaitForResponse(theInstrLoc, baseCmd, &response);
    return response;
}



