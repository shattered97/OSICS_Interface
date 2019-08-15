#include "Logging.h"



Logging* Logging::theLoggerPtr = nullptr;

Logging::Logging()
{
    //Initialize with file path
    theLogFile.setFileName(LOG_FILE_PATH +  "/" + LOG_FILE);

    //Alert user if logging fails to create file at startup
    if(!logEntry("Logging started..................................................................", __LINE__))
    {
        QMessageBox alert;
        alert.setText("Failed to Create Log File");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }
}

Logging::~Logging()
{
    logEntry("Logging Closed Cleanly", __LINE__);
    delete theLoggerPtr;
}

Logging* Logging::getInstance()
{
    if(theLoggerPtr == nullptr)
    {
        theLoggerPtr = new Logging();
    }

    return theLoggerPtr;
}

bool Logging::logEntry(QString msg, int lineNum)
{
    bool success = false;

    if(theLogFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMutexLocker locker(&lockLogMutex);  //Lock the object until done writing
        QString timeStamp = QDateTime::currentDateTime().toString(TIMESTAMP_FORMAT);

        //%1:  Timestamp
        //%2:  Log entry
        QString logFormat = "%1 (%2): %3 \n";
        QString logEntry = logFormat.arg(timeStamp).arg(lineNum).arg(msg);

        theLogFile.write(logEntry.toLatin1());

        theLogFile.close();

        //We are done unlock the object
        locker.unlock();
        success = true;
    }

    return success;
}

void Logging::logInstrSendCmd(QByteArray instrAddr, qint32 statusCode, QByteArray cmd, int lineNum)
{
    //%1: instrument address
    //%2: status of command
    //%3: cmd sent

    QString command(cmd);
    command.chop(1);  //remove new line from command

    QString address(instrAddr);

    QString logFormat = "%1 (status code %2):  Sent: %3";
    logEntry(logFormat.arg(address).arg(statusCode).arg(command), lineNum);
}

void Logging::logInstrReadCmd(QByteArray instrAddr, qint32 statusCode, QByteArray response, int lineNum)
{
    //%1: instrument address
    //%2: status of command
    //%3: data received

    QString address(instrAddr);
    QString rspStr(response);

    QString logFormat = "%1 (status code %2): Received: %3";
    logEntry(logFormat.arg(address).arg(statusCode).arg(rspStr), lineNum);
}
