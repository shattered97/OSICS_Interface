/****************************************************************************
** Meta object code from reading C++ file 'configpowermeter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Config_Windows/configpowermeter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configpowermeter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigPowerMeter_t {
    QByteArrayData data[24];
    char stringdata0[622];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigPowerMeter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigPowerMeter_t qt_meta_stringdata_ConfigPowerMeter = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConfigPowerMeter"
QT_MOC_LITERAL(1, 17, 26), // "signalUpdateConfigSettings"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 6), // "device"
QT_MOC_LITERAL(4, 52, 10), // "QSettings*"
QT_MOC_LITERAL(5, 63, 14), // "configSettings"
QT_MOC_LITERAL(6, 78, 25), // "signalApplyConfigSettings"
QT_MOC_LITERAL(7, 104, 16), // "slotUpdateWindow"
QT_MOC_LITERAL(8, 121, 25), // "slot_radio_button_clicked"
QT_MOC_LITERAL(9, 147, 40), // "on_powerUnitComboBox_currentI..."
QT_MOC_LITERAL(10, 188, 41), // "on_wavelengthComboBox_current..."
QT_MOC_LITERAL(11, 230, 33), // "on_wavelengthEdit_editingFini..."
QT_MOC_LITERAL(12, 264, 29), // "on_loadSettingsButton_pressed"
QT_MOC_LITERAL(13, 294, 29), // "on_saveSettingsButton_pressed"
QT_MOC_LITERAL(14, 324, 28), // "on_saveChangesButton_clicked"
QT_MOC_LITERAL(15, 353, 25), // "on_setNicknameBtn_clicked"
QT_MOC_LITERAL(16, 379, 35), // "on_totalTimeDisplay_editingFi..."
QT_MOC_LITERAL(17, 415, 36), // "on_periodTimeDisplay_editingF..."
QT_MOC_LITERAL(18, 452, 33), // "on_avgTimeDisplay_editingFini..."
QT_MOC_LITERAL(19, 486, 29), // "on_continuousRadioBtn_clicked"
QT_MOC_LITERAL(20, 516, 26), // "on_refreshRadioBtn_clicked"
QT_MOC_LITERAL(21, 543, 33), // "on_dataPointsEdit_editingFini..."
QT_MOC_LITERAL(22, 577, 39), // "on_timeUnitComboBox_currentIn..."
QT_MOC_LITERAL(23, 617, 4) // "unit"

    },
    "ConfigPowerMeter\0signalUpdateConfigSettings\0"
    "\0device\0QSettings*\0configSettings\0"
    "signalApplyConfigSettings\0slotUpdateWindow\0"
    "slot_radio_button_clicked\0"
    "on_powerUnitComboBox_currentIndexChanged\0"
    "on_wavelengthComboBox_currentIndexChanged\0"
    "on_wavelengthEdit_editingFinished\0"
    "on_loadSettingsButton_pressed\0"
    "on_saveSettingsButton_pressed\0"
    "on_saveChangesButton_clicked\0"
    "on_setNicknameBtn_clicked\0"
    "on_totalTimeDisplay_editingFinished\0"
    "on_periodTimeDisplay_editingFinished\0"
    "on_avgTimeDisplay_editingFinished\0"
    "on_continuousRadioBtn_clicked\0"
    "on_refreshRadioBtn_clicked\0"
    "on_dataPointsEdit_editingFinished\0"
    "on_timeUnitComboBox_currentIndexChanged\0"
    "unit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigPowerMeter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x06 /* Public */,
       6,    2,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  114,    2, 0x0a /* Public */,
       8,    0,  115,    2, 0x08 /* Private */,
       9,    0,  116,    2, 0x08 /* Private */,
      10,    0,  117,    2, 0x08 /* Private */,
      11,    0,  118,    2, 0x08 /* Private */,
      12,    0,  119,    2, 0x08 /* Private */,
      13,    0,  120,    2, 0x08 /* Private */,
      14,    0,  121,    2, 0x08 /* Private */,
      15,    0,  122,    2, 0x08 /* Private */,
      16,    0,  123,    2, 0x08 /* Private */,
      17,    0,  124,    2, 0x08 /* Private */,
      18,    0,  125,    2, 0x08 /* Private */,
      19,    0,  126,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,
      21,    0,  128,    2, 0x08 /* Private */,
      22,    1,  129,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,    3,    5,

 // slots: parameters
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
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void ConfigPowerMeter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigPowerMeter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 1: _t->signalApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 2: _t->slotUpdateWindow(); break;
        case 3: _t->slot_radio_button_clicked(); break;
        case 4: _t->on_powerUnitComboBox_currentIndexChanged(); break;
        case 5: _t->on_wavelengthComboBox_currentIndexChanged(); break;
        case 6: _t->on_wavelengthEdit_editingFinished(); break;
        case 7: _t->on_loadSettingsButton_pressed(); break;
        case 8: _t->on_saveSettingsButton_pressed(); break;
        case 9: _t->on_saveChangesButton_clicked(); break;
        case 10: _t->on_setNicknameBtn_clicked(); break;
        case 11: _t->on_totalTimeDisplay_editingFinished(); break;
        case 12: _t->on_periodTimeDisplay_editingFinished(); break;
        case 13: _t->on_avgTimeDisplay_editingFinished(); break;
        case 14: _t->on_continuousRadioBtn_clicked(); break;
        case 15: _t->on_refreshRadioBtn_clicked(); break;
        case 16: _t->on_dataPointsEdit_editingFinished(); break;
        case 17: _t->on_timeUnitComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSettings* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSettings* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigPowerMeter::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigPowerMeter::signalUpdateConfigSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigPowerMeter::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigPowerMeter::signalApplyConfigSettings)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConfigPowerMeter::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ConfigPowerMeter.data,
    qt_meta_data_ConfigPowerMeter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigPowerMeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigPowerMeter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigPowerMeter.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ConfigPowerMeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ConfigPowerMeter::signalUpdateConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigPowerMeter::signalApplyConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
