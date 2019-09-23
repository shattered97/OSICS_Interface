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

void Ando_AQ6331::setCenterWavelength(QByteArray &wavelength)
{
    QByteArray baseCmd = "CTRWL\n";
    baseCmd.insert(baseCmd.indexOf('\n'), wavelength);
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}
\
void Ando_AQ6331::setSpan(QByteArray &span)
{
    QByteArray baseCmd = "SPAN\n";
    baseCmd.insert(baseCmd.indexOf('\n'), span);
    emit signalSendCmdNoRsp(theInstrLoc, baseCmd);
}

void Ando_AQ6331::setResolution(QByteArray &resolution)
{
    QByteArray baseCmd = "RESLN\n";
    baseCmd.insert(baseCmd.indexOf('\n'), resolution);
}

void Ando_AQ6331::getCenterWavelength(QByteArray &wavelength)
{
    QByteArray baseCmd = "CTRWL?\n";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, wavelength);
}

void Ando_AQ6331::getSpan(QByteArray &span)
{
    QByteArray baseCmd = "SPAN?\n";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, span);
}

void Ando_AQ6331::getPeakDataFromTrace(QByteArray &wavelength, QByteArray &power){
    QByteArray wavTraceCmd = "WDATA\n";
    QByteArray wavTraceDataRaw;
    emit signalSendCmdRsp(theInstrLoc, wavTraceCmd, wavTraceDataRaw);
    // parse raw data into list

    QList<QByteArray> wavDataList = wavTraceDataRaw.trimmed().split(',');
    int numWavDataPoints = wavDataList[0].toInt();
    qDebug() << numWavDataPoints;
    wavDataList.removeFirst();
    qDebug() << wavDataList.size();

    QByteArray powTraceCmd = "LDATA\n";
    QByteArray powerTraceDataRaw;
    emit signalSendCmdRsp(theInstrLoc, powTraceCmd, powerTraceDataRaw);

    QList<QByteArray> powDataList = powerTraceDataRaw.trimmed().split(',');
    int numPowDataPoints = powDataList[0].toInt();
    qDebug() << numPowDataPoints;
    powDataList.removeFirst();
    qDebug() << powDataList.size();

    // get index of highest power level
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

}

void Ando_AQ6331::getResolution(QByteArray &resolution)
{
    QByteArray baseCmd = "RESLN?\n";
    emit signalSendCmdRsp(theInstrLoc, baseCmd, resolution);
}


