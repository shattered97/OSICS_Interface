#ifndef DEFAULTINSTRUMENT_H
#define DEFAULTINSTRUMENT_H

#include "VisaInterface.h"

#include <QThread>
#include <QString>
#include <QElapsedTimer>

class DefaultInstrument : public QObject
{
    Q_OBJECT

public:
    DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc, QObject *parent = 0);

    // ********************** Getters / Setters ************************

    /**
     * @brief getInstrIdentity Returns the instrument identity
     * @return instrument identity
     */
    QByteArray getInstrIdentity();

    /**
     * @brief getInstrLocation Returns the instrument location (address)
     * @return instrument location (address)
     */
    QByteArray getInstrLocation();


    // ********************** Common SCPI Commands **********************

    void querySTB(QByteArray &response);

    void execESE(ViByte registerVal);

    void queryESE(QByteArray &response);

    void querySRE(QByteArray &response);

    void queryESR(QByteArray &response);

    void execOPC();

    void queryOPC(QByteArray &response);

    void execCLS();

    void execRST();

    void queryTST(QByteArray &response);

    void queryOPT(QByteArray &response);

    void execWAI();

    void queryIDN(QByteArray &response);

    void setConfigWindow(QMainWindow *configwindow);

    QMainWindow * getConfigWindow();

signals:
    void signalSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);


private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
    VisaInterface theCommBus;               // common methods for talking to VISA devices

    QMainWindow *configWindow;
};

#endif // DEFAULTINSTRUMENT_H
