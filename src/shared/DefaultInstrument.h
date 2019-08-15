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

    bool querySTB(ViSession &defaultSession, QByteArray &response);

    bool execESE(ViSession &defaultSession, ViByte registerVal);

    bool queryESE(ViSession &defaultSession, QByteArray &response);

    bool querySRE(ViSession &defaultSession, QByteArray &response);

    bool queryESR(ViSession &defaultSession, QByteArray &response);

    bool execOPC(ViSession &defaultSession);

    bool queryOPC(ViSession &defaultSession, QByteArray &response);

    bool execCLS(ViSession &defaultSession);

    bool execRST(ViSession &defaultSession);

    bool queryTST(ViSession &defaultSession, QByteArray &response);

    bool queryOPT(ViSession &defaultSession, QByteArray &response);

    bool execWAI(ViSession &defaultSession);

    bool queryIDN(ViSession &defaultSession, QByteArray &response);


    void setConfigWindow(QMainWindow *configwindow);

    QMainWindow * getConfigWindow();

    void signalSendCmdRsp(QByteArray instrAddress, QByteArray &command, QByteArray &response);
    void signalSendCmdNoRsp(QByteArray instrAddress, QByteArray &command);

protected:

    // ************************************* Helper Functions ****************************************

    /**
     * @brief checkOperationComplete Continuously loops until the device's command buffer is empty or until timeout is reached.
     * @param instrSession Session to instrument
     * @param timeout Timeout in ms
     * @return The OPC status returned from the device at end of loop.
     */
    bool checkOperationComplete(ViSession &instrSession, int timeout);

    /**
     * @brief sendCmdNoRsp Sends a command to an instrument where no response is expected.
     * @param defaultSession Default communication session
     * @param instrSession Session to the instrument
     * @param command Command to send to instrument
     * @return
     */
    bool sendCmdNoRsp(ViSession &defaultSession, QByteArray &command);

    /**
     * @brief sendCmdRsp Sends a command to an instrument and returns the response from the instrument.
     * @param defaultSession Default communication session
     * @param instrSession Session to the instrument
     * @param command Command to send to instrument
     * @param response[out] Response returned by instrument
     * @return
     */
    bool sendCmdRsp(ViSession &defaultSession, QByteArray &command, QByteArray &response);



private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
    VisaInterface theCommBus;               // common methods for talking to VISA devices

    QMainWindow *configWindow;
};

#endif // DEFAULTINSTRUMENT_H
