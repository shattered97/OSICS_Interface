/****************************************************************************
** Meta object code from reading C++ file 'ConfigOSICS_ATN.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Config_Windows/ConfigOSICS_ATN.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigOSICS_ATN.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigOSICS_ATN_t {
    QByteArrayData data[16];
    char stringdata0[385];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigOSICS_ATN_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigOSICS_ATN_t qt_meta_stringdata_ConfigOSICS_ATN = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ConfigOSICS_ATN"
QT_MOC_LITERAL(1, 16, 26), // "signalUpdateConfigSettings"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 6), // "device"
QT_MOC_LITERAL(4, 51, 10), // "QSettings*"
QT_MOC_LITERAL(5, 62, 14), // "configSettings"
QT_MOC_LITERAL(6, 77, 25), // "signalApplyConfigSettings"
QT_MOC_LITERAL(7, 103, 16), // "slotUpdateWindow"
QT_MOC_LITERAL(8, 120, 34), // "on_attenuationEdit_editingFin..."
QT_MOC_LITERAL(9, 155, 40), // "on_attenuationOffsetEdit_edit..."
QT_MOC_LITERAL(10, 196, 29), // "on_loadSettingsButton_clicked"
QT_MOC_LITERAL(11, 226, 29), // "on_saveSettingsButton_clicked"
QT_MOC_LITERAL(12, 256, 28), // "on_saveChangesButton_clicked"
QT_MOC_LITERAL(13, 285, 36), // "on_refWavelengthRadioButton1_..."
QT_MOC_LITERAL(14, 322, 36), // "on_refWavelengthRadioButton2_..."
QT_MOC_LITERAL(15, 359, 25) // "on_setNicknameBtn_clicked"

    },
    "ConfigOSICS_ATN\0signalUpdateConfigSettings\0"
    "\0device\0QSettings*\0configSettings\0"
    "signalApplyConfigSettings\0slotUpdateWindow\0"
    "on_attenuationEdit_editingFinished\0"
    "on_attenuationOffsetEdit_editingFinished\0"
    "on_loadSettingsButton_clicked\0"
    "on_saveSettingsButton_clicked\0"
    "on_saveChangesButton_clicked\0"
    "on_refWavelengthRadioButton1_clicked\0"
    "on_refWavelengthRadioButton2_clicked\0"
    "on_setNicknameBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigOSICS_ATN[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       6,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,

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

       0        // eod
};

void ConfigOSICS_ATN::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigOSICS_ATN *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 1: _t->signalApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 2: _t->slotUpdateWindow(); break;
        case 3: _t->on_attenuationEdit_editingFinished(); break;
        case 4: _t->on_attenuationOffsetEdit_editingFinished(); break;
        case 5: _t->on_loadSettingsButton_clicked(); break;
        case 6: _t->on_saveSettingsButton_clicked(); break;
        case 7: _t->on_saveChangesButton_clicked(); break;
        case 8: _t->on_refWavelengthRadioButton1_clicked(); break;
        case 9: _t->on_refWavelengthRadioButton2_clicked(); break;
        case 10: _t->on_setNicknameBtn_clicked(); break;
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
            using _t = void (ConfigOSICS_ATN::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigOSICS_ATN::signalUpdateConfigSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigOSICS_ATN::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigOSICS_ATN::signalApplyConfigSettings)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConfigOSICS_ATN::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ConfigOSICS_ATN.data,
    qt_meta_data_ConfigOSICS_ATN,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigOSICS_ATN::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigOSICS_ATN::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigOSICS_ATN.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ConfigOSICS_ATN::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ConfigOSICS_ATN::signalUpdateConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigOSICS_ATN::signalApplyConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
