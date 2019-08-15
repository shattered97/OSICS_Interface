#ifndef LOGGING_H
#define LOGGING_H

#include "constants.h"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QMutexLocker>
#include <QDateTime>
#include <QMessageBox>

//Singleton

class Logging
{
public:

    ~Logging();

    /**
     * @brief getInstance static access method to the singleton
     */
    static Logging *getInstance();

    /**
     * @brief logEntry used to format the log entry so the logs are uniform
     * @param msg what message that needs to be logged
     * @return TRUE if log entry was entered / FALSE if log entry failed to write
     */
    bool logEntry(QString msg, int lineNum);

    /**
     * @brief logInstrSendCmd Formats a log entry for sending a command
     * @param instrAddr Device being accessed
     * @param statusCode Status returned from sending command
     * @param cmd command Sent
     */
    void logInstrSendCmd(QByteArray instrAddr, qint32 statusCode, QByteArray cmd, int lineNum);

    /**
     * @brief logInstrReadCmd Formats a log entry for reading a device response
     * @param instrAddr Device being accessed
     * @param statusCode Status returned from reading from device
     * @param response Response from device
     */
    void logInstrReadCmd(QByteArray instrAddr, qint32 statusCode, QByteArray response, int lineNum);

private:

    /**
     * @brief Logging - constructor is private to prevent instancing
     */
    Logging();

    // pointer to logging instance
    static Logging *theLoggerPtr;

    // Log File object
    QFile theLogFile;

    // Mutex to lock the log file while writing to it
    QMutex lockLogMutex;

};

#endif // LOGGING_H
