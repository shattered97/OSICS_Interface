#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QMap>
#include <QMainWindow>

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

// QPair<module variant, configWindow>
typedef QPair<QVariant, QMainWindow*> ModuleConfigPair;

// series name, list of data points (time, power)
typedef QMap<QByteArray, QList<QPair<QByteArray, QByteArray>>*> WavStepPowerTestData;

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
const qint32 VISA_MAX_BUFFER_READ_SIZE = 8192;
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
const QByteArray N7714A_FREQ_CMD = "sour:freq\n";

// N7714A Constants
const int N7714A_NUM_SLOTS = 4;

// EXFO OSICS CONSTANTS
const int EXFO_OSICS_NUM_SLOTS = 8;

// Keysight Unit Pair List
const UnitPair PM_UNIT = {-12, "pm"};
const UnitPair NM_UNIT = {-9, "nm"};
const UnitPair UM_UNIT = {-6, "um"};
const UnitPair MM_UNIT = {-3, "mm"};
const UnitPair M_UNIT = {0, "m"};
const QMap<QByteArray, int> WAV_CONVERSION_MAP = {{"m", 0}, {"mm", -3}, {"um", -6}, {"nm", -9}, {"pm", -12}};
const QList<UnitPair> WAV_EXPONENT_LIST = {PM_UNIT, NM_UNIT, UM_UNIT, MM_UNIT, M_UNIT};

const UnitPair HZ_UNIT = {0, "Hz"};
const UnitPair KHZ_UNIT = {3, "KHz"};
const UnitPair MHZ_UNIT = {6, "MHz"};
const UnitPair GHZ_UNIT = {9, "GHz"};
const UnitPair THZ_UNIT = {12, "THz"};
const QMap<QByteArray, int> FREQ_CONVERSION_MAP = {{"Hz", 0}, {"KHz", 3}, {"MHz", 6}, {"GHz", 9}, {"THz", 12}};
const QList<UnitPair> FREQ_EXPONENT_LIST = {HZ_UNIT, KHZ_UNIT, MHZ_UNIT, GHZ_UNIT, THZ_UNIT};

// Device type names
const QByteArray N7714A_DEVICE = "N7714A";
const QByteArray N7745A_POWER_METER = "N7745A";
const QByteArray EXFO_CHASSIS_DEVICE = "EXFO,OSICS";
const QByteArray ANDO_AQ6331_DEVICE = "ANDO,AQ6331";
const QByteArray Bristol_428A_DEVICE = "Bristol Wavemeter, 428A";
const QByteArray DEVICE_TYPES[] = {N7714A_DEVICE, N7745A_POWER_METER, EXFO_CHASSIS_DEVICE, ANDO_AQ6331_DEVICE,
                                   Bristol_428A_DEVICE};

// Test type names
const QByteArray N7714A_WAV_CYCLE_TEST = "N7714A Wavelength Cycle Test";
const QByteArray OSICS_WAV_CYCLE_TEST = "EXFO OSICS Wavelength Cycle Test";
const QByteArray EXFO_T100_ANDO_OSA_WAV_CYCLE_TEST = "EXFO T100 / ANDO OSA Wavelength Cycle Test";
const QByteArray EXFO_T100_SWT_WAV_STEP_OSA_POWER_TEST = "EXFO T100 / SWT / OSA Wavelength Step Test";
const QByteArray EXFO_T100_BRISTOL_WAV_STEP_TEST = "EXFO / T100 / Bristol / Wavelength Step Test";
const QByteArray EXFO_T100_ATN_POWER_TEST = "EXFO / T100 / ATN / Power Meter / Power Test";
const QByteArray EXFO_T100_SWT_PM_WM_TEST = "EXFO / T100 / SWT / Bristol / Wavelength Step Test";
const QByteArray EXFO_T100_PM_POWER_STEP_TEST = "EXFO / T100 / Power Meter / Power Step Test";
const QByteArray EXFO_OPERATIONAL_TEST_T100_SWT_ATN = "EXFO SWT / T100 / ATN / Operational Test";
const QByteArray WAV_STEP_TEST_WITH_POWER_MONITORING_TEST = "Wavelength Step Test with Power Monitoring (EXFO T100)";

const QByteArray TEST_TYPES[] = {N7714A_WAV_CYCLE_TEST, OSICS_WAV_CYCLE_TEST, EXFO_T100_ANDO_OSA_WAV_CYCLE_TEST,
                                 EXFO_T100_SWT_WAV_STEP_OSA_POWER_TEST, EXFO_T100_BRISTOL_WAV_STEP_TEST,
                                 EXFO_T100_ATN_POWER_TEST, EXFO_T100_SWT_PM_WM_TEST, EXFO_T100_PM_POWER_STEP_TEST,
                                 EXFO_OPERATIONAL_TEST_T100_SWT_ATN, WAV_STEP_TEST_WITH_POWER_MONITORING_TEST};


// Wavelength Step Test With Power Monitoring Settings
const QByteArray WAV_STEP_TEST_CSV_FILENAME = "Wav Step Test .csv Filename";
const QByteArray WAV_STEP_TEST_GRAPH_FILENAME = "Wav Step Test Graph Filename";
const QByteArray WAV_STEP_TEST_START_WAVELENGTH = "Wav Step Test Start Wavelength";
const QByteArray WAV_STEP_TEST_END_WAVELENGTH = "Wav Step Test End Wavelength";
const QByteArray WAV_STEP_TEST_WAV_STEP_SIZE = "Wav Step Test Step Size";
const QByteArray WAV_STEP_TEST_DWELL_SECONDS = "Wav Step Test Dwell in Seconds";
const QByteArray WAV_STEP_TEST_SWT_CHANNELS_TO_T100 = "Wav Step Test SWT Channels to T100 Map";
const QByteArray WAV_STEP_TEST_CHANNELS_TO_GRAPH = "Wav Step Test Channels To Graph";

// EXFO_OSICS_ATN Values
const QByteArray EXFO_OSICS_ATN_MIN_OFFSET = "-10"; // defined in spec sheet/prog guide
const QByteArray EXFO_OSICS_ATN_MAX_OFFSET = "10"; // defined in spec sheet/prog guide

// EXFO_OSICS_SWT Values
const QByteArray EXFO_OSICS_SWT_MIN_WAV_NM = "1250";
const QByteArray EXFO_OSICS_SWT_MAX_WAV_NM = "1650";
const QByteArray EXFO_OSICS_SWT_MIN_POWER_DBM = "-6.99";
const QByteArray EXFO_OSICS_SWT_MAX_POWER_DBM = "3";
const QByteArray EXFO_OSICS_SWT_NUM_CHANNELS = "4";

// EXFO_OSICS_T100 Values
const QByteArray EXFO_OSICS_T100_MIN_POWER_DBM = "-6.99";
const QByteArray EXFO_OSICS_T100_MAX_POWER_DBM = "6";
const QByteArray EXFO_OSICS_T100_1310_MIN_WAV_NM = "1260";
const QByteArray EXFO_OSICS_T100_1310_MAX_WAV_NM = "1360";
const QByteArray EXFO_OSICS_T100_1415_MIN_WAV_NM = "1360";
const QByteArray EXFO_OSICS_T100_1415_MAX_WAV_NM = "1470";
const QByteArray EXFO_OSICS_T100_1520_MIN_WAV_NM = "1465";
const QByteArray EXFO_OSICS_T100_1520_MAX_WAV_NM = "1575";
const QByteArray EXFO_OSICS_T100_1550_MIN_WAV_NM = "1490";
const QByteArray EXFO_OSICS_T100_1550_MAX_WAV_NM = "1610";
const QByteArray EXFO_OSICS_T100_1575_MIN_WAV_NM = "1520";
const QByteArray EXFO_OSICS_T100_1575_MAX_WAV_NM = "1630";
const QByteArray EXFO_OSICS_T100_1620_MIN_WAV_NM = "1560";
const QByteArray EXFO_OSICS_T100_1620_MAX_WAV_NM = "1680";

// QSettings Key Values - General
const QByteArray DEVICE_LOCATION = "Device Location";
const QByteArray DEVICE_IDENTITY = "Device Identity";

// QSettings Key Values - Power Meter
const QByteArray NUM_CHANNELS = "PowerMeter Num Channels";
const QByteArray POWER_READINGS = "PowerMeter Power Readings";
const QByteArray WAVELENGTH_SETTINGS = "PowerMeter Wavelength Settings";
const QByteArray MIN_WAVELENGTHS = "PowerMeter Min Wavelength";
const QByteArray MAX_WAVELENGTHS = "PowerMeter Max Wavelength";

// QSettings Key Values - N7714A
const QByteArray N7714A_POWER_SETTINGS = "N7714A Power Settings";
const QByteArray N7714A_MIN_POWER = "N7714A Min Power";
const QByteArray N7714A_MAX_POWER = "N7714A Max Power";
const QByteArray N7714A_LASER_STATE = "N7714A Laser State";

const QByteArray N7714A_WAVELENGTH_SETTINGS = "N7714A Wavelength Settings";
const QByteArray N7714A_MIN_WAVELENGTH = "N7714A Min Wavelength";
const QByteArray N7714A_MAX_WAVELENGTH = "N7714A Max Wavelength";

const QByteArray N7714A_FREQUENCY_SETTINGS = "N7714A Frequency Settings";
const QByteArray N7714A_MIN_FREQUENCY = "N7714A Min Frequency";
const QByteArray N7714A_MAX_FREQUENCY = "N7714A Max Frequency";

// QSettings Key Values - EXFO OSICS MAINFRAME
const QByteArray EXFO_OSICS_MODULE_NAMES = "EXFO OSICS Module Names";

// QSettings Key Values - EXFO OSICS T100
const QByteArray EXFO_OSICS_T100_POWER = "EXFO OSICS T100 Power Setting";
const QByteArray EXFO_OSICS_T100_MIN_POWER = "EXFO OSICS T100 Min Power";
const QByteArray EXFO_OSICS_T100_MAX_POWER = "EXFO OSICS T100 Max Power";
const QByteArray EXFO_OSICS_T100_LASER_STATE = "EXFO OSICS T100 Laser State";

const QByteArray EXFO_OSICS_T100_WAVELENGTH = "EXFO OSICS T100 Wavelength Setting";
const QByteArray EXFO_OSICS_T100_MIN_WAVELENGTH = "EXFO OSICS T100 Min Wavelength";
const QByteArray EXFO_OSICS_T100_MAX_WAVELENGTH = "EXFO OSICS T100 Max Wavelength";

const QByteArray EXFO_OSICS_T100_FREQUENCY = "EXFO OSICS T100 Frequency Setting";
const QByteArray EXFO_OSICS_T100_MIN_FREQUENCY = "EXFO OSICS T100 Min Frequency";
const QByteArray EXFO_OSICS_T100_MAX_FREQUENCY = "EXFO OSICS T100 Max Frequency";

// QSettings Key Values - EXFO OSICS SWT
const QByteArray EXFO_OSICS_SWT_OUTPUT_STATUS = "EXFO OSICS SWT Output Status";
const QByteArray EXFO_OSICS_SWT_OPMODE = "EXFO OSICS SWT Operating Mode";
const QByteArray EXFO_OSICS_SWT_ACTIVE_CHANNEL = "EXFO OSICS SWT Active Channel";
const QByteArray EXFO_OSICS_SWT_POWER_SETTING = "EXFO OSICS SWT Power Setting";
const QByteArray EXFO_OSICS_SWT_WAVELENGTH_SETTING = "EXFO OSICS SWT Wavelength Setting";
const QByteArray EXFO_OSICS_SWT_FREQUENCY_SETTING = "EXFO OSICS SWT Frequency Setting";

// QSettings Key Values - EXFO OSICS ATN
const QByteArray EXFO_OSICS_ATN_ATTENUATION  = "EXFO OSICS ATN Attenuation";
const QByteArray EXFO_OSICS_ATN_MIN_ATTENUATION_1 = "EXFO OSICS ATN First Min Attenuation";
const QByteArray EXFO_OSICS_ATN_MAX_ATTENUATION_1 = "EXFO OSICS ATN First Max Attenuation";
const QByteArray EXFO_OSICS_ATN_MIN_ATTENUATION_2 = "EXFO OSICS ATN Second Min Attenuation";
const QByteArray EXFO_OSICS_ATN_MAX_ATTENUATION_2 = "EXFO OSICS ATN Second Max Attenuation";
const QByteArray EXFO_OSICS_ATN_REF_WAV_NUMBER = "EXFO OSICS ATN Reference Wavelength Number";
const QByteArray EXFO_OSICS_ATN_REF_WAVELENGTH_1 = "EXFO OSICS ATN First Reference Wavelength";
const QByteArray EXFO_OSICS_ATN_REF_WAVELENGTH_2 = "EXFO OSICS ATN Second Reference Wavelength";
const QByteArray EXFO_OSICS_ATN_OFFSET_1 = "EXFO OSICS ATN First Offset";
const QByteArray EXFO_OSICS_ATN_OFFSET_2 = "EXFO OSICS ATN Second Offset";

// Math Constants
const double SPEED_OF_LIGHT = 299792458;
#endif // CONSTANTS_H

