#ifndef DEFAULTINSTRUMENT_H
#define DEFAULTINSTRUMENT_H

#include <QThread>
#include <QString>
#include <QElapsedTimer>
#include <QMainWindow>
#include <QDebug>
#include <QSettings>

#include "constants.h"

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

    QByteArray querySTB();

    void execESE(char registerVal);

    QByteArray queryESE();

    QByteArray querySRE();

    QByteArray queryESR();

    void execOPC();

    QByteArray queryOPC();

    void execCLS();

    void execRST();

    QByteArray queryTST();

    QByteArray queryOPT();

    void execWAI();

    QByteArray queryIDN();

    void setConfigWindow(QMainWindow *configwindow);

    QMainWindow * getConfigWindow();

    void updateConfig(QSettings &configSettings);

signals:
    void signalSendCmdRsp(QByteArray instrAddress, QByteArray command, QByteArray *response);
    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray command);


private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument

    QMainWindow *configWindow;
};

#endif // DEFAULTINSTRUMENT_H
