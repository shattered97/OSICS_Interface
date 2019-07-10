#ifndef VISAINTERFACE_H
#define VISAINTERFACE_H

#include "visa.h"
#include "constants.h"
#include "Logging.h"

#include <QString>


//Wrapper to National Instruments visa.h library that was written in C
//See OSICS.pro to determine where the visa.h library must be installed.
//This is location is the default windows install when VISA drivers are installed


class VisaInterface
{
public:
    VisaInterface();
    ~VisaInterface();

//***********************************How to find resources*******************************************************
/*
 *  createDefaultRM(testA);
 *  findResources(testA, "?*INSTR", currentSession, numInstruments, instrAddr);
 *  createInstrMap(testA, instrAddr, currentSession, numInstruments, instrumentMap);
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
     * @return Retruns completion code
     */
    ViStatus createDefaultRM(ViSession &defualtSession);

    /**
     * @brief findResource Find all the VISA resources in our system and store the number of resources
     *        in the system in numInstrs.
     * @param defaultRMSession[in] Resource Manager session—should always be the session returned from viOpenDefaultRM().
     * @param query[in] This is a regular expression followed by an optional logical expression. See VISA ICD for more details
     * @param instrSession[out] Returns a handle identifying this search session. This handle will be used as an input in viFindNext().
     * @param numInstrs [out] Number of matches.
     * @param instrumentLoc[out] This string can then be passed to viOpen() to establish a session to the given device.
     *        viFindRsrc requires a char array.  We convert to QByteArray to makes things easier when passing around.
     * @return Returns true if VISA resources were found
     */
    bool findResources(ViSession &defaultRMSession,
                          QString query,
                          ViUInt32 *numInstrs,
                          ViFindList *findList,
                          QByteArray &instrumentLoc);

    /**
     * @brief createInstrSession Connect specified instrument
     * @param[in] defaultRMSession Resource Manager session—should always be a session returned from viOpenDefaultRM().
     * @param instrumentLoc[in] Unique symbolic name of a resource. Refer to the Description section of the VISA ICD for more information.
     * @param instrSession[out] Unique logical identifier reference to a session.
     * @return Returns completion code
     */
    ViStatus createInstrMap(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViUInt32 *numInstr, ViFindList *findList, FoundInstr &result);

    /**
     * @brief displayResources
     * @param defaultRMSession Ressource Manager session-should always be a session returned from viOpenDefaultRM().
     * @param instrumentLoc Unique symbolic name of a resource. Refer to the Description section of the VISA ICD for more information.
     * @param instrSess Unique logical identifier reference to a session.
     * @param numInstr Number of resources found.
     * @param mapping of int to QPair of instrument address and identity.
     * @return
     */
    void displayResources(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViUInt32 *numInstr, ViFindList *findList, FoundInstr &result);

    /**
     * @brief closeDefaultSession closes the default session
     * @param defaultSession[in] what session needs to be closed
     * @return Returns comnpletion code
     */
    ViStatus closeDefaultSession(ViSession &defaultSession);


    /**
     * @brief sendCmd Send SCPI command to connected resource
     * @param instrSession[in] Unique logical identifier reference to a session.
     * @param instrumentLoc[in]  Unique symbolic name of a resource. Refer to the Description section of the VISA ICD for more information.
     * @param scpiCmd[in] SCPI Command to send to resource
     * @param writeCount[out] Number of bytes actually transferred
     * @return
     */
    ViStatus sendCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray scpiCmd, ViUInt32 &writeCount);

    ViStatus readCmd(ViSession &instrSession, QByteArray instrAddr, QByteArray &response, ViUInt32 &retCount);

    ViStatus openInstrSession(ViSession &defaultSession, QByteArray instrAddr, ViSession &instrSess);

    /**
     * @brief closeSession closes session to instrument or defualt session
     * @param sessionToClose[in] session to close
     * @return returns completion code
     */
    ViStatus closeSession(ViSession &sessionToClose);

//********************************************End Find Resource*********************************************************************************

private:

    //Helper Functions

    /**
     * @brief byteArrayToCharArray Converts QByteArray to C style char array
     * @param charArray[out] resulting char array from QByteArray
     * @param byteArray[in] QByteArray to convert to char array
     */
    void byteArrayToCharArray(char (&charArray)[VISA_MAX_BUFFER_SEND_SIZE], QByteArray &byteArray);

    /**
     * @brief charArrayToByteArray Converts C style char array to QByteArray
     * @param charArray[in] resulting char array from QByteArray
     * @param byteArray[out] QByteArray to convert to char array
     */
    void charArrayToByteArray(unsigned char (&charArray)[VISA_MAX_BUFFER_READ_SIZE], QByteArray &byteArray, ViUInt32 size);



    /**
     * @brief findNextResource used to find the next resouce when multiple resources are connected to the system
     * @param instrumentLoc[in] instrument adddress
     * @param instrSess[in] instrument communication session
     * @param resultMap[out] map of all found instruments
     * @param indexOfInstr[in] index to store found instrument at in the map
     * @return
     */
    ViStatus findNextResource(ViSession &defaultRMSession, QByteArray &instrumentLoc, ViSession &instrSess, ViPFindList &findList, FoundInstr &resultMap);

    ViStatus queryInstrument(QByteArray &instrumentLoc, ViSession &instrSess, FoundInstr &resultMap);



    //Private Data Members

    ViStatus theStatus;  //Status of last operation - Contains Completion Code

};

#endif // VISAINTERFACE_H
