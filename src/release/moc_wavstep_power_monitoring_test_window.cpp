/****************************************************************************
** Meta object code from reading C++ file 'wavstep_power_monitoring_test_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
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
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WavStep_Power_Monitoring_Test_Window_t {
    QByteArrayData data[38];
    char stringdata0[990];
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
QT_MOC_LITERAL(17, 363, 26), // "slotUpdateMinMaxWavelength"
QT_MOC_LITERAL(18, 390, 6), // "minWav"
QT_MOC_LITERAL(19, 397, 6), // "maxWav"
QT_MOC_LITERAL(20, 404, 24), // "slotDisplayPowerReadings"
QT_MOC_LITERAL(21, 429, 18), // "powerMeterIdentity"
QT_MOC_LITERAL(22, 448, 8), // "readings"
QT_MOC_LITERAL(23, 457, 22), // "on_beginTestPB_clicked"
QT_MOC_LITERAL(24, 480, 42), // "on_swtChannel1ComboBox_curren..."
QT_MOC_LITERAL(25, 523, 42), // "on_swtChannel2ComboBox_curren..."
QT_MOC_LITERAL(26, 566, 42), // "on_swtChannel3ComboBox_curren..."
QT_MOC_LITERAL(27, 609, 42), // "on_swtChannel4ComboBox_curren..."
QT_MOC_LITERAL(28, 652, 35), // "on_startWavLineEdit_editingFi..."
QT_MOC_LITERAL(29, 688, 33), // "on_endWavLineEdit_editingFini..."
QT_MOC_LITERAL(30, 722, 32), // "on_dwellLineEdit_editingFinished"
QT_MOC_LITERAL(31, 755, 35), // "on_stepSizeLineEdit_editingFi..."
QT_MOC_LITERAL(32, 791, 30), // "on_dwellMinRadioButton_clicked"
QT_MOC_LITERAL(33, 822, 28), // "on_dwellSRadioButton_clicked"
QT_MOC_LITERAL(34, 851, 31), // "on_dwellMsecRadioButton_clicked"
QT_MOC_LITERAL(35, 883, 32), // "on_openGraphWindowButton_clicked"
QT_MOC_LITERAL(36, 916, 29), // "on_selectCsvLocButton_clicked"
QT_MOC_LITERAL(37, 946, 43) // "on_pmReadingRefreshRateEdit_e..."

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
    "slotUpdateMinMaxWavelength\0minWav\0"
    "maxWav\0slotDisplayPowerReadings\0"
    "powerMeterIdentity\0readings\0"
    "on_beginTestPB_clicked\0"
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
    "on_pmReadingRefreshRateEdit_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WavStep_Power_Monitoring_Test_Window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,
       5,    1,  137,    2, 0x06 /* Public */,
       8,    1,  140,    2, 0x06 /* Public */,
      11,    1,  143,    2, 0x06 /* Public */,
      14,    0,  146,    2, 0x06 /* Public */,
      15,    0,  147,    2, 0x06 /* Public */,
      16,    0,  148,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    2,  149,    2, 0x0a /* Public */,
      20,    2,  154,    2, 0x0a /* Public */,
      23,    0,  159,    2, 0x08 /* Private */,
      24,    0,  160,    2, 0x08 /* Private */,
      25,    0,  161,    2, 0x08 /* Private */,
      26,    0,  162,    2, 0x08 /* Private */,
      27,    0,  163,    2, 0x08 /* Private */,
      28,    0,  164,    2, 0x08 /* Private */,
      29,    0,  165,    2, 0x08 /* Private */,
      30,    0,  166,    2, 0x08 /* Private */,
      31,    0,  167,    2, 0x08 /* Private */,
      32,    0,  168,    2, 0x08 /* Private */,
      33,    0,  169,    2, 0x08 /* Private */,
      34,    0,  170,    2, 0x08 /* Private */,
      35,    0,  171,    2, 0x08 /* Private */,
      36,    0,  172,    2, 0x08 /* Private */,
      37,    0,  173,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   18,   19,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArrayList,   21,   22,
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
        case 7: _t->slotUpdateMinMaxWavelength((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->slotDisplayPowerReadings((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QList<QByteArray>(*)>(_a[2]))); break;
        case 9: _t->on_beginTestPB_clicked(); break;
        case 10: _t->on_swtChannel1ComboBox_currentIndexChanged(); break;
        case 11: _t->on_swtChannel2ComboBox_currentIndexChanged(); break;
        case 12: _t->on_swtChannel3ComboBox_currentIndexChanged(); break;
        case 13: _t->on_swtChannel4ComboBox_currentIndexChanged(); break;
        case 14: _t->on_startWavLineEdit_editingFinished(); break;
        case 15: _t->on_endWavLineEdit_editingFinished(); break;
        case 16: _t->on_dwellLineEdit_editingFinished(); break;
        case 17: _t->on_stepSizeLineEdit_editingFinished(); break;
        case 18: _t->on_dwellMinRadioButton_clicked(); break;
        case 19: _t->on_dwellSRadioButton_clicked(); break;
        case 20: _t->on_dwellMsecRadioButton_clicked(); break;
        case 21: _t->on_openGraphWindowButton_clicked(); break;
        case 22: _t->on_selectCsvLocButton_clicked(); break;
        case 23: _t->on_pmReadingRefreshRateEdit_editingFinished(); break;
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
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
