#ifndef DEFAULTINSTRUMENT_H
#define DEFAULTINSTRUMENT_H

#include "VisaInterface.h"

#include <QThread>
#include <QString>

class DefaultInstrument
{
public:
    DefaultInstrument();
    DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc);

    QByteArray getInstrIdentity();

    void setInstrIdentity(QByteArray theIdentity);

    QByteArray getInstrLocation();

    void setInstrLocation(QByteArray theInstrLoc);

    VisaInterface getCommBus();

    void setCommBus(VisaInterface theCommBus);

    bool sendCmdNoRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command);

    bool sendCmdRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command, QByteArray &response);

    bool querySTB(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool execESE(ViSession &defaultSession, ViSession &instrSession, ViByte registerVal);

    bool queryESE(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool querySRE(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool queryESR(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool execOPC(ViSession &defaultSession, ViSession &instrSession);

    bool queryOPC(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool execCLS(ViSession &defaultSession, ViSession &instrSession);

    bool execRST(ViSession &defaultSession, ViSession &instrSession);

    bool queryTST(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool queryOPT(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool execWAI(ViSession &defaultSession, ViSession &instrSession);

    bool queryIDN(ViSession &defaultSession, ViSession &instrSession, QByteArray &response);

    bool checkOperationComplete(ViSession &instrSession, int timeout);

private:
    QByteArray theIdentity;
    QByteArray theInstrLoc;
    VisaInterface theCommBus;
};

#endif // DEFAULTINSTRUMENT_H
