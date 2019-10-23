/****************************************************************************
** Meta object code from reading C++ file 'exfo_operationaltest_t100_swt_atn.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Tests/exfo_operationaltest_t100_swt_atn.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exfo_operationaltest_t100_swt_atn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_t {
    QByteArrayData data[9];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_t qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN = {
    {
QT_MOC_LITERAL(0, 0, 33), // "EXFO_OperationalTest_T100_SWT..."
QT_MOC_LITERAL(1, 34, 21), // "signalTestingComplete"
QT_MOC_LITERAL(2, 56, 0), // ""
QT_MOC_LITERAL(3, 57, 21), // "slotBeginNextTestStep"
QT_MOC_LITERAL(4, 79, 16), // "slotSkipTestStep"
QT_MOC_LITERAL(5, 96, 28), // "slotGetCurrentStepDirections"
QT_MOC_LITERAL(6, 125, 11), // "QByteArray&"
QT_MOC_LITERAL(7, 137, 12), // "resourcePath"
QT_MOC_LITERAL(8, 150, 10) // "directions"

    },
    "EXFO_OperationalTest_T100_SWT_ATN\0"
    "signalTestingComplete\0\0slotBeginNextTestStep\0"
    "slotSkipTestStep\0slotGetCurrentStepDirections\0"
    "QByteArray&\0resourcePath\0directions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EXFO_OperationalTest_T100_SWT_ATN[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,

       0        // eod
};

void EXFO_OperationalTest_T100_SWT_ATN::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EXFO_OperationalTest_T100_SWT_ATN *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalTestingComplete(); break;
        case 1: _t->slotBeginNextTestStep(); break;
        case 2: _t->slotSkipTestStep(); break;
        case 3: _t->slotGetCurrentStepDirections((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EXFO_OperationalTest_T100_SWT_ATN::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EXFO_OperationalTest_T100_SWT_ATN::signalTestingComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EXFO_OperationalTest_T100_SWT_ATN::staticMetaObject = { {
    &DeviceTest::staticMetaObject,
    qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN.data,
    qt_meta_data_EXFO_OperationalTest_T100_SWT_ATN,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EXFO_OperationalTest_T100_SWT_ATN::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EXFO_OperationalTest_T100_SWT_ATN::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN.stringdata0))
        return static_cast<void*>(this);
    return DeviceTest::qt_metacast(_clname);
}

int EXFO_OperationalTest_T100_SWT_ATN::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DeviceTest::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EXFO_OperationalTest_T100_SWT_ATN::signalTestingComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
