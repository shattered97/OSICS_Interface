/****************************************************************************
** Meta object code from reading C++ file 'wavstep_power_monitoring_test_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Tests/wavstep_power_monitoring_test_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wavstep_power_monitoring_test_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window_t {
    QByteArrayData data[55];
    char stringdata0[1364];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window_t qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window = {
    {
QT_MOC_LITERAL(0, 0, 36), // "WavStep_Power_Monitoring_Test..."
QT_MOC_LITERAL(1, 37, 15), // "signalBeginTest"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 10), // "QSettings*"
QT_MOC_LITERAL(4, 65, 8), // "settings"
QT_MOC_LITERAL(5, 74, 25), // "signalGetT100DisplayNames"
QT_MOC_LITERAL(6, 100, 18), // "QList<QByteArray>&"
QT_MOC_LITERAL(7, 119, 12), // "displayNames"
QT_MOC_LITERAL(8, 132, 31), // "signalGetPowerMeterDisplayPairs"
QT_MOC_LITERAL(9, 164, 30), // "QList<QPair<QByteArray,int> >&"
QT_MOC_LITERAL(10, 195, 22), // "powerMeterDisplayPairs"
QT_MOC_LITERAL(11, 218, 22), // "signalSwitchMapChanged"
QT_MOC_LITERAL(12, 241, 20), // "QMap<int,QByteArray>"
QT_MOC_LITERAL(13, 262, 19), // "swtChannelToT100Map"
QT_MOC_LITERAL(14, 282, 31), // "signalPollForPowerMeterReadings"
QT_MOC_LITERAL(15, 314, 21), // "signalShowGraphWindow"
QT_MOC_LITERAL(16, 336, 26), // "signalStopAllWorkerThreads"
QT_MOC_LITERAL(17, 363, 22), // "signalTestWindowClosed"
QT_MOC_LITERAL(18, 386, 26), // "signalGetTestTimesFromFile"
QT_MOC_LITERAL(19, 413, 7), // "double&"
QT_MOC_LITERAL(20, 421, 13), // "testStartTime"
QT_MOC_LITERAL(21, 435, 15), // "currentTestTime"
QT_MOC_LITERAL(22, 451, 32), // "signalGetStaticGraphDataFromFile"
QT_MOC_LITERAL(23, 484, 34), // "QList<QPair<QByteArray,QPoint..."
QT_MOC_LITERAL(24, 519, 13), // "dataFromGraph"
QT_MOC_LITERAL(25, 533, 14), // "graphStartTime"
QT_MOC_LITERAL(26, 548, 12), // "graphEndtime"
QT_MOC_LITERAL(27, 561, 26), // "slotUpdateMinMaxWavelength"
QT_MOC_LITERAL(28, 588, 6), // "minWav"
QT_MOC_LITERAL(29, 595, 6), // "maxWav"
QT_MOC_LITERAL(30, 602, 24), // "slotDisplayPowerReadings"
QT_MOC_LITERAL(31, 627, 18), // "powerMeterIdentity"
QT_MOC_LITERAL(32, 646, 8), // "readings"
QT_MOC_LITERAL(33, 655, 17), // "slotTestCompleted"
QT_MOC_LITERAL(34, 673, 22), // "on_beginTestPB_clicked"
QT_MOC_LITERAL(35, 696, 42), // "on_swtChannel1ComboBox_curren..."
QT_MOC_LITERAL(36, 739, 42), // "on_swtChannel2ComboBox_curren..."
QT_MOC_LITERAL(37, 782, 42), // "on_swtChannel3ComboBox_curren..."
QT_MOC_LITERAL(38, 825, 42), // "on_swtChannel4ComboBox_curren..."
QT_MOC_LITERAL(39, 868, 35), // "on_startWavLineEdit_editingFi..."
QT_MOC_LITERAL(40, 904, 33), // "on_endWavLineEdit_editingFini..."
QT_MOC_LITERAL(41, 938, 32), // "on_dwellLineEdit_editingFinished"
QT_MOC_LITERAL(42, 971, 35), // "on_stepSizeLineEdit_editingFi..."
QT_MOC_LITERAL(43, 1007, 30), // "on_dwellMinRadioButton_clicked"
QT_MOC_LITERAL(44, 1038, 28), // "on_dwellSRadioButton_clicked"
QT_MOC_LITERAL(45, 1067, 31), // "on_dwellMsecRadioButton_clicked"
QT_MOC_LITERAL(46, 1099, 32), // "on_openGraphWindowButton_clicked"
QT_MOC_LITERAL(47, 1132, 29), // "on_selectCsvLocButton_clicked"
QT_MOC_LITERAL(48, 1162, 39), // "on_graphRefreshRateEdit_editi..."
QT_MOC_LITERAL(49, 1202, 28), // "slotDisplayCurrentWavelength"
QT_MOC_LITERAL(50, 1231, 10), // "wavelength"
QT_MOC_LITERAL(51, 1242, 24), // "on_saveConfigBtn_clicked"
QT_MOC_LITERAL(52, 1267, 24), // "on_loadConfigBtn_clicked"
QT_MOC_LITERAL(53, 1292, 39), // "on_seriesDataPointsEdit_editi..."
QT_MOC_LITERAL(54, 1332, 31) // "on_openSnapshotGraphBtn_clicked"

    },
    "WavStep_Power_Monitoring_Test_Window\0"
    "signalBeginTest\0\0QSettings*\0settings\0"
    "signalGetT100DisplayNames\0QList<QByteArray>&\0"
    "displayNames\0signalGetPowerMeterDisplayPairs\0"
    "QList<QPair<QByteArray,int> >&\0"
    "powerMeterDisplayPairs\0signalSwitchMapChanged\0"
    "QMap<int,QByteArray>\0swtChannelToT100Map\0"
    "signalPollForPowerMeterReadings\0"
    "signalShowGraphWindow\0signalStopAllWorkerThreads\0"
    "signalTestWindowClosed\0"
    "signalGetTestTimesFromFile\0double&\0"
    "testStartTime\0currentTestTime\0"
    "signalGetStaticGraphDataFromFile\0"
    "QList<QPair<QByteArray,QPointF> >&\0"
    "dataFromGraph\0graphStartTime\0graphEndtime\0"
    "slotUpdateMinMaxWavelength\0minWav\0"
    "maxWav\0slotDisplayPowerReadings\0"
    "powerMeterIdentity\0readings\0"
    "slotTestCompleted\0on_beginTestPB_clicked\0"
    "on_swtChannel1ComboBox_currentIndexChanged\0"
    "on_swtChannel2ComboBox_currentIndexChanged\0"
    "on_swtChannel3ComboBox_currentIndexChanged\0"
    "on_swtChannel4ComboBox_currentIndexChanged\0"
    "on_startWavLineEdit_editingFinished\0"
    "on_endWavLineEdit_editingFinished\0"
    "on_dwellLineEdit_editingFinished\0"
    "on_stepSizeLineEdit_editingFinished\0"
    "on_dwellMinRadioButton_clicked\0"
    "on_dwellSRadioButton_clicked\0"
    "on_dwellMsecRadioButton_clicked\0"
    "on_openGraphWindowButton_clicked\0"
    "on_selectCsvLocButton_clicked\0"
    "on_graphRefreshRateEdit_editingFinished\0"
    "slotDisplayCurrentWavelength\0wavelength\0"
    "on_saveConfigBtn_clicked\0"
    "on_loadConfigBtn_clicked\0"
    "on_seriesDataPointsEdit_editingFinished\0"
    "on_openSnapshotGraphBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WavStep_Power_Monitoring_Test_Window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  179,    2, 0x06 /* Public */,
       5,    1,  182,    2, 0x06 /* Public */,
       8,    1,  185,    2, 0x06 /* Public */,
      11,    1,  188,    2, 0x06 /* Public */,
      14,    0,  191,    2, 0x06 /* Public */,
      15,    0,  192,    2, 0x06 /* Public */,
      16,    0,  193,    2, 0x06 /* Public */,
      17,    0,  194,    2, 0x06 /* Public */,
      18,    2,  195,    2, 0x06 /* Public */,
      22,    3,  200,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    2,  207,    2, 0x0a /* Public */,
      30,    2,  212,    2, 0x0a /* Public */,
      33,    0,  217,    2, 0x0a /* Public */,
      34,    0,  218,    2, 0x08 /* Private */,
      35,    0,  219,    2, 0x08 /* Private */,
      36,    0,  220,    2, 0x08 /* Private */,
      37,    0,  221,    2, 0x08 /* Private */,
      38,    0,  222,    2, 0x08 /* Private */,
      39,    0,  223,    2, 0x08 /* Private */,
      40,    0,  224,    2, 0x08 /* Private */,
      41,    0,  225,    2, 0x08 /* Private */,
      42,    0,  226,    2, 0x08 /* Private */,
      43,    0,  227,    2, 0x08 /* Private */,
      44,    0,  228,    2, 0x08 /* Private */,
      45,    0,  229,    2, 0x08 /* Private */,
      46,    0,  230,    2, 0x08 /* Private */,
      47,    0,  231,    2, 0x08 /* Private */,
      48,    0,  232,    2, 0x08 /* Private */,
      49,    1,  233,    2, 0x08 /* Private */,
      51,    0,  236,    2, 0x08 /* Private */,
      52,    0,  237,    2, 0x08 /* Private */,
      53,    0,  238,    2, 0x08 /* Private */,
      54,    0,  239,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19, 0x80000000 | 19,   20,   21,
    QMetaType::Void, 0x80000000 | 23, QMetaType::Double, QMetaType::Double,   24,   25,   26,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   28,   29,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArrayList,   31,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WavStep_Power_Monitoring_Test_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WavStep_Power_Monitoring_Test_Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalBeginTest((*reinterpret_cast< QSettings*(*)>(_a[1]))); break;
        case 1: _t->signalGetT100DisplayNames((*reinterpret_cast< QList<QByteArray>(*)>(_a[1]))); break;
        case 2: _t->signalGetPowerMeterDisplayPairs((*reinterpret_cast< QList<QPair<QByteArray,int> >(*)>(_a[1]))); break;
        case 3: _t->signalSwitchMapChanged((*reinterpret_cast< QMap<int,QByteArray>(*)>(_a[1]))); break;
        case 4: _t->signalPollForPowerMeterReadings(); break;
        case 5: _t->signalShowGraphWindow(); break;
        case 6: _t->signalStopAllWorkerThreads(); break;
        case 7: _t->signalTestWindowClosed(); break;
        case 8: _t->signalGetTestTimesFromFile((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->signalGetStaticGraphDataFromFile((*reinterpret_cast< QList<QPair<QByteArray,QPointF> >(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 10: _t->slotUpdateMinMaxWavelength((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: _t->slotDisplayPowerReadings((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QList<QByteArray>(*)>(_a[2]))); break;
        case 12: _t->slotTestCompleted(); break;
        case 13: _t->on_beginTestPB_clicked(); break;
        case 14: _t->on_swtChannel1ComboBox_currentIndexChanged(); break;
        case 15: _t->on_swtChannel2ComboBox_currentIndexChanged(); break;
        case 16: _t->on_swtChannel3ComboBox_currentIndexChanged(); break;
        case 17: _t->on_swtChannel4ComboBox_currentIndexChanged(); break;
        case 18: _t->on_startWavLineEdit_editingFinished(); break;
        case 19: _t->on_endWavLineEdit_editingFinished(); break;
        case 20: _t->on_dwellLineEdit_editingFinished(); break;
        case 21: _t->on_stepSizeLineEdit_editingFinished(); break;
        case 22: _t->on_dwellMinRadioButton_clicked(); break;
        case 23: _t->on_dwellSRadioButton_clicked(); break;
        case 24: _t->on_dwellMsecRadioButton_clicked(); break;
        case 25: _t->on_openGraphWindowButton_clicked(); break;
        case 26: _t->on_selectCsvLocButton_clicked(); break;
        case 27: _t->on_graphRefreshRateEdit_editingFinished(); break;
        case 28: _t->slotDisplayCurrentWavelength((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 29: _t->on_saveConfigBtn_clicked(); break;
        case 30: _t->on_loadConfigBtn_clicked(); break;
        case 31: _t->on_seriesDataPointsEdit_editingFinished(); break;
        case 32: _t->on_openSnapshotGraphBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSettings* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalBeginTest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(QList<QByteArray> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalGetT100DisplayNames)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(QList<QPair<QByteArray,int>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalGetPowerMeterDisplayPairs)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(QMap<int,QByteArray> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalSwitchMapChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalPollForPowerMeterReadings)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalShowGraphWindow)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalStopAllWorkerThreads)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalTestWindowClosed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(double & , double & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalGetTestTimesFromFile)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Window::*)(QList<QPair<QByteArray,QPointF>> & , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Window::signalGetStaticGraphDataFromFile)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WavStep_Power_Monitoring_Test_Window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window.data,
    qt_meta_data_WavStep_Power_Monitoring_Test_Window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WavStep_Power_Monitoring_Test_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WavStep_Power_Monitoring_Test_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WavStep_Power_Monitoring_Test_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void WavStep_Power_Monitoring_Test_Window::signalBeginTest(QSettings * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WavStep_Power_Monitoring_Test_Window::signalGetT100DisplayNames(QList<QByteArray> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WavStep_Power_Monitoring_Test_Window::signalGetPowerMeterDisplayPairs(QList<QPair<QByteArray,int>> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WavStep_Power_Monitoring_Test_Window::signalSwitchMapChanged(QMap<int,QByteArray> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WavStep_Power_Monitoring_Test_Window::signalPollForPowerMeterReadings()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WavStep_Power_Monitoring_Test_Window::signalShowGraphWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void WavStep_Power_Monitoring_Test_Window::signalStopAllWorkerThreads()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void WavStep_Power_Monitoring_Test_Window::signalTestWindowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void WavStep_Power_Monitoring_Test_Window::signalGetTestTimesFromFile(double & _t1, double & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WavStep_Power_Monitoring_Test_Window::signalGetStaticGraphDataFromFile(QList<QPair<QByteArray,QPointF>> & _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
