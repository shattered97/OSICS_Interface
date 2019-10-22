/****************************************************************************
** Meta object code from reading C++ file 'ConfigOSICS_T100.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Config_Windows/ConfigOSICS_T100.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigOSICS_T100.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigOSICS_T100_t {
    QByteArrayData data[20];
    char stringdata0[504];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigOSICS_T100_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigOSICS_T100_t qt_meta_stringdata_ConfigOSICS_T100 = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConfigOSICS_T100"
QT_MOC_LITERAL(1, 17, 26), // "signalUpdateConfigSettings"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "QVariant&"
QT_MOC_LITERAL(4, 55, 6), // "device"
QT_MOC_LITERAL(5, 62, 10), // "QSettings&"
QT_MOC_LITERAL(6, 73, 14), // "configSettings"
QT_MOC_LITERAL(7, 88, 25), // "signalApplyConfigSettings"
QT_MOC_LITERAL(8, 114, 16), // "slotUpdateWindow"
QT_MOC_LITERAL(9, 131, 40), // "on_powerUnitComboBox_currentI..."
QT_MOC_LITERAL(10, 172, 5), // "index"
QT_MOC_LITERAL(11, 178, 45), // "on_wavelengthUnitComboBox_cur..."
QT_MOC_LITERAL(12, 224, 44), // "on_frequencyUnitComboBox_curr..."
QT_MOC_LITERAL(13, 269, 39), // "on_laserOutputPowerEdit_editi..."
QT_MOC_LITERAL(14, 309, 38), // "on_laserWavelengthEdit_editin..."
QT_MOC_LITERAL(15, 348, 37), // "on_laserFrequencyEdit_editing..."
QT_MOC_LITERAL(16, 386, 28), // "on_togglePowerButton_clicked"
QT_MOC_LITERAL(17, 415, 29), // "on_loadSettingsButton_clicked"
QT_MOC_LITERAL(18, 445, 29), // "on_saveSettingsButton_clicked"
QT_MOC_LITERAL(19, 475, 28) // "on_saveChangesButton_clicked"

    },
    "ConfigOSICS_T100\0signalUpdateConfigSettings\0"
    "\0QVariant&\0device\0QSettings&\0"
    "configSettings\0signalApplyConfigSettings\0"
    "slotUpdateWindow\0"
    "on_powerUnitComboBox_currentIndexChanged\0"
    "index\0on_wavelengthUnitComboBox_currentIndexChanged\0"
    "on_frequencyUnitComboBox_currentIndexChanged\0"
    "on_laserOutputPowerEdit_editingFinished\0"
    "on_laserWavelengthEdit_editingFinished\0"
    "on_laserFrequencyEdit_editingFinished\0"
    "on_togglePowerButton_clicked\0"
    "on_loadSettingsButton_clicked\0"
    "on_saveSettingsButton_clicked\0"
    "on_saveChangesButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigOSICS_T100[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       7,    2,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   89,    2, 0x0a /* Public */,
       9,    1,   90,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,
      16,    0,  102,    2, 0x08 /* Private */,
      17,    0,  103,    2, 0x08 /* Private */,
      18,    0,  104,    2, 0x08 /* Private */,
      19,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConfigOSICS_T100::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigOSICS_T100 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings(*)>(_a[2]))); break;
        case 1: _t->signalApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings(*)>(_a[2]))); break;
        case 2: _t->slotUpdateWindow(); break;
        case 3: _t->on_powerUnitComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_wavelengthUnitComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_frequencyUnitComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_laserOutputPowerEdit_editingFinished(); break;
        case 7: _t->on_laserWavelengthEdit_editingFinished(); break;
        case 8: _t->on_laserFrequencyEdit_editingFinished(); break;
        case 9: _t->on_togglePowerButton_clicked(); break;
        case 10: _t->on_loadSettingsButton_clicked(); break;
        case 11: _t->on_saveSettingsButton_clicked(); break;
        case 12: _t->on_saveChangesButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigOSICS_T100::*)(QVariant & , QSettings & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigOSICS_T100::signalUpdateConfigSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigOSICS_T100::*)(QVariant & , QSettings & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigOSICS_T100::signalApplyConfigSettings)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConfigOSICS_T100::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ConfigOSICS_T100.data,
    qt_meta_data_ConfigOSICS_T100,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigOSICS_T100::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigOSICS_T100::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigOSICS_T100.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ConfigOSICS_T100::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ConfigOSICS_T100::signalUpdateConfigSettings(QVariant & _t1, QSettings & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigOSICS_T100::signalApplyConfigSettings(QVariant & _t1, QSettings & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
