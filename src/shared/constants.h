#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QMap>

//QPair<Instrument Address, Instrument Identity>
typedef QPair<QByteArray, QByteArray> InstrData;

//QMap<Index, Instrument Data>
typedef QMap<int, InstrData> FoundInstr;

//QPair<int, QByteArray>
typedef QPair<int, QByteArray> UnitPair;

//QPair<channel/slot, power reading>
typedef QPair<QByteArray, QByteArray> PowerReading;

//QMap<Instrument Data, Power reading and channel>
typedef QMap<InstrData, PowerReading> PowerReadingData;

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
const QByteArray EXEC_CLS = "*CLS\n";
const QByteArray EXEC_ESE = "*ESE\n";
const QByteArray QUERY_ESE = "*ESE?\n";
const QByteArray QUERY_ESR = "*ESR?\n";
const QByteArray QUERY_IDN = "*IDN?\n";
const QByteArray EXEC_OPC = "*OPC\n";
const QByteArray QUERY_OPC = "*OPC?\n";
const QByteArray QUERY_OPT = "*OPT?\n";
const QByteArray EXEC_RST = "*RST\n";
const QByteArray QUERY_STB = "*STB?\n";
const QByteArray QUERY_TST = "*TST?\n";
const QByteArray EXEC_WAI = "*WAI\n";

const int DEFAULT_COMMAND_TIMEOUT_MS = 1000 * 5;
const int POWER_ON_TIMEOUT_MS = 1000 * 10;

// N7714A Commands
const QByteArray N7714A_POW_UNIT_QUERY = "sour:pow:unit?\n";
const QByteArray N7714A_POW_UNIT_CMD = "sour:pow:unit\n";
const QByteArray N7714A_POW_STAT_QUERY = "sour:pow:stat?\n";
const QByteArray N7714A_POW_ON_CMD = "sour:pow:stat on\n";
const QByteArray N7714A_POW_OFF_CMD = "sour:pow:stat off\n";
const QByteArray N7714A_POW_LEVEL_QUERY = "sour:pow?\n";
const QByteArray N7714A_POW_LEVEL_CMD = "sour:pow\n";
const QByteArray N7714A_WAV_QUERY = "sour:wav?\n";
const QByteArray N7714A_WAV_CMD = "sour:wav\n";
const QByteArray N7714A_FREQ_QUERY = "sour:freq?\n";
const QByteArray N7714A_FREQ_CMD = "sour:wav\n";

// N7714A Constants
const int N7714A_NUM_SLOTS = 4;

// Keysight Unit Pair List
const UnitPair PM_UNIT = {-12, "pm"};
const UnitPair NM_UNIT = {-9, "nm"};
const UnitPair UM_UNIT = {-6, "um"};
const UnitPair MM_UNIT = {-3, "mm"};
const UnitPair M_UNIT = {0, "m"};
const QList<UnitPair> WAV_EXPONENT_LIST = {PM_UNIT, NM_UNIT, UM_UNIT, MM_UNIT, M_UNIT};

const UnitPair HZ_UNIT = {0, "Hz"};
const UnitPair KHZ_UNIT = {3, "KHz"};
const UnitPair MHZ_UNIT = {6, "MHz"};
const UnitPair GHZ_UNIT = {9, "GHz"};
const UnitPair THZ_UNIT = {12, "THz"};
const QList<UnitPair> FREQ_EXPONENT_LIST = {HZ_UNIT, KHZ_UNIT, MHZ_UNIT, GHZ_UNIT, THZ_UNIT};

// Device type names
const QByteArray N7714A_DEVICE = "N7714A";
const QByteArray N7745A_POWER_METER = "N7745A";
const QByteArray EXFO_CHASSIS_DEVICE = "EXFO,OSICS";
const QByteArray DEVICE_TYPES[] = {N7714A_DEVICE, N7745A_POWER_METER, EXFO_CHASSIS_DEVICE};

// Test type names
const QByteArray N7714A_WAV_CYCLE_TEST = "N7714A Wavelength Cycle Test";
const QByteArray OSICS_WAV_CYCLE_TEST = "EXFO OSICS Wavelength Cycle Test";
const QByteArray TEST_TYPES[] = {N7714A_WAV_CYCLE_TEST, OSICS_WAV_CYCLE_TEST};


#endif // CONSTANTS_H
