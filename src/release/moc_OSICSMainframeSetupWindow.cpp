/****************************************************************************
** Meta object code from reading C++ file 'OSICSMainframeSetupWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Config_Windows/OSICSMainframeSetupWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OSICSMainframeSetupWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OSICSMainframeSetupWindow_t {
    QByteArrayData data[17];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OSICSMainframeSetupWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OSICSMainframeSetupWindow_t qt_meta_stringdata_OSICSMainframeSetupWindow = {
    {
QT_MOC_LITERAL(0, 0, 25), // "OSICSMainframeSetupWindow"
QT_MOC_LITERAL(1, 26, 26), // "signalUpdateConfigSettings"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 6), // "device"
QT_MOC_LITERAL(4, 61, 10), // "QSettings*"
QT_MOC_LITERAL(5, 72, 14), // "configSettings"
QT_MOC_LITERAL(6, 87, 25), // "signalApplyConfigSettings"
QT_MOC_LITERAL(7, 113, 30), // "signalGetEXFOModuleConfigPairs"
QT_MOC_LITERAL(8, 144, 27), // "QMap<int,ModuleConfigPair>*"
QT_MOC_LITERAL(9, 172, 17), // "moduleConfigPairs"
QT_MOC_LITERAL(10, 190, 16), // "slotUpdateWindow"
QT_MOC_LITERAL(11, 207, 30), // "slotForwardApplyConfigSettings"
QT_MOC_LITERAL(12, 238, 13), // "deviceVariant"
QT_MOC_LITERAL(13, 252, 31), // "slotForwardUpdateConfigSettings"
QT_MOC_LITERAL(14, 284, 23), // "on_configButton_clicked"
QT_MOC_LITERAL(15, 308, 5), // "index"
QT_MOC_LITERAL(16, 314, 25) // "on_setNicknameBtn_clicked"

    },
    "OSICSMainframeSetupWindow\0"
    "signalUpdateConfigSettings\0\0device\0"
    "QSettings*\0configSettings\0"
    "signalApplyConfigSettings\0"
    "signalGetEXFOModuleConfigPairs\0"
    "QMap<int,ModuleConfigPair>*\0"
    "moduleConfigPairs\0slotUpdateWindow\0"
    "slotForwardApplyConfigSettings\0"
    "deviceVariant\0slotForwardUpdateConfigSettings\0"
    "on_configButton_clicked\0index\0"
    "on_setNicknameBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OSICSMainframeSetupWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    2,   59,    2, 0x06 /* Public */,
       7,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   69,    2, 0x0a /* Public */,
      11,    2,   70,    2, 0x0a /* Public */,
      13,    2,   75,    2, 0x0a /* Public */,
      14,    1,   80,    2, 0x08 /* Private */,
      16,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 8,    3,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,   12,    5,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,   12,    5,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,

       0        // eod
};

void OSICSMainframeSetupWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OSICSMainframeSetupWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 1: _t->signalApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 2: _t->signalGetEXFOModuleConfigPairs((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QMap<int,ModuleConfigPair>*(*)>(_a[2]))); break;
        case 3: _t->slotUpdateWindow(); break;
        case 4: _t->slotForwardApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 5: _t->slotForwardUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings*(*)>(_a[2]))); break;
        case 6: _t->on_configButton_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_setNicknameBtn_clicked(); break;
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
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSettings* >(); break;
            }
            break;
        case 5:
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
            using _t = void (OSICSMainframeSetupWindow::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OSICSMainframeSetupWindow::signalUpdateConfigSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OSICSMainframeSetupWindow::*)(QVariant , QSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OSICSMainframeSetupWindow::signalApplyConfigSettings)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OSICSMainframeSetupWindow::*)(QVariant , QMap<int,ModuleConfigPair> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OSICSMainframeSetupWindow::signalGetEXFOModuleConfigPairs)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OSICSMainframeSetupWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_OSICSMainframeSetupWindow.data,
    qt_meta_data_OSICSMainframeSetupWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OSICSMainframeSetupWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OSICSMainframeSetupWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OSICSMainframeSetupWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int OSICSMainframeSetupWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void OSICSMainframeSetupWindow::signalUpdateConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OSICSMainframeSetupWindow::signalApplyConfigSettings(QVariant _t1, QSettings * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OSICSMainframeSetupWindow::signalGetEXFOModuleConfigPairs(QVariant _t1, QMap<int,ModuleConfigPair> * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
