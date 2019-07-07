#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QMap>

//QPair<Instrument Address, Instrument Identity>
typedef QPair<QByteArray, QByteArray> InstrData;

//QMap<Index, Instrument Data>
typedef QMap<int, InstrData> FoundInstr;


//Logging Constansts
const QString LOG_FILE_PATH  = QDir::currentPath();  //Same dir as exe
const QString LOG_FILE       = "OSICS_LOG.txt";

const QString TIMESTAMP_FORMAT = "dd_MMM_yy_hh_mm:ss:zzz";

//VISA Resource Queries
const QString GPIB          =  "GPIB[0-9]*::?*INSTR";
const QString VXI           =  "VXI?*INSTR";
const QString GPIB_VXI      =  "GPIB-VXI?*INSTR";
const QString ANY_VXI       =  "?*VXI[0-9]*::?*INSTR";
const QString SERIAL        =  "ASRL[0-9]*::?*INSTR";
const QString PXI           =  "PXI?*INSTR";
const QString ALL_INSTR     =  "?*INSTR";
const QString ALL_RESOURCES =  "?*";

//VISA read buffer max size
const qint32 VISA_MAX_BUFFER_READ_SIZE = 100;
const qint32 VISA_MAX_BUFFER_SEND_SIZE = 512;

//SCPI Command*/

const QByteArray IDENTITY = "*IDN?\n";



#endif // CONSTANTS_H
