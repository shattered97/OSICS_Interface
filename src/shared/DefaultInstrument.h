#ifndef DEFAULTINSTRUMENT_H
#define DEFAULTINSTRUMENT_H

#include "VisaInterface.h"

#include <QThread>
#include <QString>
#include <QElapsedTimer>

class DefaultInstrument
{
public:
    DefaultInstrument();
    DefaultInstrument(QByteArray theIdentity, QByteArray theInstrLoc);

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
    bool sendCmdNoRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command);

    /**
     * @brief sendCmdRsp Sends a command to an instrument and returns the response from the instrument.
     * @param defaultSession Default communication session
     * @param instrSession Session to the instrument
     * @param command Command to send to instrument
     * @param response[out] Response returned by instrument
     * @return
     */
    bool sendCmdRsp(ViSession &defaultSession, ViSession &instrSession, QByteArray &command, QByteArray &response);

private:
    QByteArray theIdentity;                 // identity of instrument (manufacturer, model num, etc.)
    QByteArray theInstrLoc;                 // the physical address of the instrument
    VisaInterface theCommBus;               // common methods for talking to VISA devices
};

#endif // DEFAULTINSTRUMENT_H
