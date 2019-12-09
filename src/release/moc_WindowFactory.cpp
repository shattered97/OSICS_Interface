/****************************************************************************
** Meta object code from reading C++ file 'WindowFactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../shared/WindowFactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WindowFactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowFactory_t {
    QByteArrayData data[7];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowFactory_t qt_meta_stringdata_WindowFactory = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WindowFactory"
QT_MOC_LITERAL(1, 14, 10), // "makeWindow"
QT_MOC_LITERAL(2, 25, 12), // "QMainWindow*"
QT_MOC_LITERAL(3, 38, 0), // ""
QT_MOC_LITERAL(4, 39, 10), // "windowType"
QT_MOC_LITERAL(5, 50, 9), // "QVariant*"
QT_MOC_LITERAL(6, 60, 13) // "deviceVariant"

    },
    "WindowFactory\0makeWindow\0QMainWindow*\0"
    "\0windowType\0QVariant*\0deviceVariant"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2, QMetaType::QString, 0x80000000 | 5,    4,    6,

       0        // eod
};

void WindowFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QMainWindow* _r = _t->makeWindow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QMainWindow**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowFactory::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WindowFactory.data,
    qt_meta_data_WindowFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowFactory.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WindowFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
