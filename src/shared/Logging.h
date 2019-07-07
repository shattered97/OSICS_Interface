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
    bool logEntry(QString msg);

    void logInstrSendCmd(QByteArray instrAddr, qint32 statusCode, QByteArray cmd);

    void logInstrReadCmd(QByteArray instrAddr, qint32 statusCode, QByteArray response);

private:

    /**
     * @brief Logging - construstor is private to prevent instancing
     */
    Logging();

    static Logging *theLoggerPtr;

    ///Log File object
    QFile theLogFile;

    ///Mutex to lock the log file while writing to it
    QMutex lockLogMutex;

};

#endif // LOGGING_H