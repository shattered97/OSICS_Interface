#ifndef VISAINTERFACE_H
#define VISAINTERFACE_H

#include "visa.h"
#include "constants.h"
#include "Logging.h"

#include <QString>

// Wrapper to National Instruments visa.h library that was written in C
// See OSICS.pro to determine where the visa.h library must be installed.
// This is location is the default windows install when VISA drivers are installed


class VisaInterface
{
public:
    VisaInterface();
    ~VisaInterface();

//***********************************How to find resources*******************************************************
/*
 *  createDefaultRM(testA);
 *  findResources(testA, "?*INSTR");
 *  createInstrMap(testA, instrumentMap);
 *  closeDefaultSession(testA);
 *
 *  This is will result in a QMap with all the queried resources ordered by index (order found).
 *  QPair<Instrument Address, Instrument Identity> Instrument Data
 *  QMap<Index, Instrument Data>
 ****************************************************************************************************************/

    /**
     * @brief createDefaultRM - This function returns a session to the Default Resource Manager resource.
     *        This method must be run prior to any VISA operation.
     * @param[out] defualtSession Unique logical identifier to a Default Resource Manager session.
     * @return Completion code
     */
    ViStatus createDefaultRM(ViSession &defualtSession);

    /**
     * @brief findResources Find all the VISA resources in system and stores result in data member findList.
     * @param defaultRMSession Resource Manager session—should always be a session returned from viOpenDefaultRM().
     * @param query Query for the type of instrument to search for
     * @return true if finding resources was succesful
     */
    bool findResources(ViSession &defaultRMSession, QString query);

    /**
     * @brief createInstrMap Connect specified instrument
     * @param defaultRMSession Resource Manager session (should always be a session returned from viOpenDefaultRM()).
     * @param resultMap Map of found resources
     * @return Completion code
     */
    ViStatus createInstrMap(ViSession &defaultRMSession, FoundInstr &resultMap);

    /**
     * @brief displayResources Facilitates the process of searching for resources. Looks for resources then adds them to map if found.
     * @param defaultRMSession Resource Manager session
     * @param result Map of found resources
     */
    void displayResources(ViSession &defaultRMSession, FoundInstr &result);

    /**
     * @brief closeDefaultSession closes the default session
     * @param defaultSession[in] what session needs to be closed
     * @return Completion code
     */
    ViStatus closeDefaultSession(ViSession &defaultSession);

    /**
     * @brief sendCmd Send SCPI command to connected resource
     * @param instrSession[in] Unique logical identifier reference to a session.
     * @param instrAddr[in]  Unique symbolic name of a resource. Refer to the Description section of the VISA ICD for more information.
     * @param scpiCmd[in] SCPI Command to send to resource
     * @param writeCount[out] Number of bytes actually transferred
     * @return Completion code
     */
    ViStatus sendCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray scpiCmd);

    /**
     * @brief readCmd Reads response of SCPI command from connected resource
     * @param instrSession[in] instrument communication session
     * @param instrAddr[in] instrument address
     * @param response[out] Response read from instrument
     * @param retCount[out] Number of bytes actually transferred
     * @return Completion code
     */
    ViStatus readCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray *response);

    /**
     * @brief openInstrSession Opens a session to an instrument located at instrAddr.
     * @param defaultSession Resource Manager session
     * @param instrAddr instrument address
     * @param instrSess instrument communication session to open
     * @return Completion code
     */
    ViStatus openInstrSession(ViSession &defaultSession, QByteArray instrAddr, ViSession &instrSess);

    /**
     * @brief closeSession closes session to instrument or defualt session
     * @param sessionToClose[in] session to close
     * @return completion code
     */
    ViStatus closeSession(ViSession &sessionToClose);


//******************************************** End Find Resource *****************************************************

private:

    //*********************** Helper Functions ************************

    /**
     * @brief byteArrayToCharArray Converts QByteArray to C style char array
     * @param charArray[out] resulting char array from QByteArray
     * @param byteArray[in] QByteArray to convert to char array
     */
    void byteArrayToCharArray(char (*charArray)[VISA_MAX_BUFFER_SEND_SIZE], QByteArray *byteArray);

    /**
     * @brief charArrayToByteArray Converts C style char array to QByteArray
     * @param charArray[in] resulting char array from QByteArray
     * @param byteArray[out] QByteArray to convert to char array
     */
    void charArrayToByteArray(unsigned char (*charArray)[VISA_MAX_BUFFER_READ_SIZE], QByteArray *byteArray, ViUInt32 size);

    /**
     * @brief findNextResource Used to find the next resouce when multiple resources are connected to the system
     * @param defaultRMSession Resource Manager session
     * @param resultMap map of all found instruments
     * @return Completion code
     */
    ViStatus findNextResource(ViSession &defaultRMSession, FoundInstr &resultMap);

    /**
     * @brief queryInstrument Queries an individual instrument for its identity and inserts info into a resultMap.
     * @param instrAddr instrument address
     * @param instrSess instrument communication session
     * @param resultMap map of all found instruments
     * @return Completion code
     */
    ViStatus queryInstrument(QByteArray &instrAddr, ViSession &instrSess, FoundInstr &resultMap);


    // ******************** Private Data Members **********************

    //Status of last operation - Contains Completion Code
    ViStatus theStatus;

    // Logging instance
    Logging* logger = Logging::getInstance();

    // Handle identifying a search session from viFindRsrc
    ViFindList findList;

    // Session to an individual instrument
    ViSession instrSession;

    // Number of instruments found by viFindRsrc
    ViUInt32 numInstr;

    // Location of a device
    QByteArray instrAddr;

};

#endif // VISAINTERFACE_H
