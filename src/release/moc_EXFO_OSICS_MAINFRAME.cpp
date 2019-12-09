/****************************************************************************
** Meta object code from reading C++ file 'EXFO_OSICS_MAINFRAME.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../shared/Devices/EXFO_OSICS/EXFO_OSICS_MAINFRAME.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EXFO_OSICS_MAINFRAME.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EXFO_OSICS_MAINFRAME_t {
    QByteArrayData data[10];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EXFO_OSICS_MAINFRAME_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EXFO_OSICS_MAINFRAME_t qt_meta_stringdata_EXFO_OSICS_MAINFRAME = {
    {
QT_MOC_LITERAL(0, 0, 20), // "EXFO_OSICS_MAINFRAME"
QT_MOC_LITERAL(1, 21, 28), // "signalGetEXFOModuleQVariants"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 19), // "QMap<int,QVariant>&"
QT_MOC_LITERAL(4, 71, 7), // "modules"
QT_MOC_LITERAL(5, 79, 9), // "QVariant&"
QT_MOC_LITERAL(6, 89, 6), // "device"
QT_MOC_LITERAL(7, 96, 20), // "slotSetupEXFOModules"
QT_MOC_LITERAL(8, 117, 20), // "enableModuleLaserCmd"
QT_MOC_LITERAL(9, 138, 7) // "slotNum"

    },
    "EXFO_OSICS_MAINFRAME\0signalGetEXFOModuleQVariants\0"
    "\0QMap<int,QVariant>&\0modules\0QVariant&\0"
    "device\0slotSetupEXFOModules\0"
    "enableModuleLaserCmd\0slotNum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EXFO_OSICS_MAINFRAME[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   34,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    1,   35,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void EXFO_OSICS_MAINFRAME::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EXFO_OSICS_MAINFRAME *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalGetEXFOModuleQVariants((*reinterpret_cast< QMap<int,QVariant>(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->slotSetupEXFOModules(); break;
        case 2: _t->enableModuleLaserCmd((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EXFO_OSICS_MAINFRAME::*)(QMap<int,QVariant> & , QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EXFO_OSICS_MAINFRAME::signalGetEXFOModuleQVariants)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EXFO_OSICS_MAINFRAME::staticMetaObject = { {
    &DefaultInstrument::staticMetaObject,
    qt_meta_stringdata_EXFO_OSICS_MAINFRAME.data,
    qt_meta_data_EXFO_OSICS_MAINFRAME,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EXFO_OSICS_MAINFRAME::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EXFO_OSICS_MAINFRAME::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EXFO_OSICS_MAINFRAME.stringdata0))
        return static_cast<void*>(this);
    return DefaultInstrument::qt_metacast(_clname);
}

int EXFO_OSICS_MAINFRAME::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DefaultInstrument::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EXFO_OSICS_MAINFRAME::signalGetEXFOModuleQVariants(QMap<int,QVariant> & _t1, QVariant & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
