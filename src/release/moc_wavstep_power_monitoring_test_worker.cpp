/****************************************************************************
** Meta object code from reading C++ file 'wavstep_power_monitoring_test_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Tests/wavstep_power_monitoring_test_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wavstep_power_monitoring_test_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker_t {
    QByteArrayData data[10];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker_t qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker = {
    {
QT_MOC_LITERAL(0, 0, 36), // "WavStep_Power_Monitoring_Test..."
QT_MOC_LITERAL(1, 37, 8), // "finished"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 23), // "signalWriteBufferToFile"
QT_MOC_LITERAL(4, 71, 42), // "QList<WavStep_Power_Monitorin..."
QT_MOC_LITERAL(5, 114, 10), // "dataPoints"
QT_MOC_LITERAL(6, 125, 24), // "signalAddReadingsToGraph"
QT_MOC_LITERAL(7, 150, 22), // "signalStopWorkerThread"
QT_MOC_LITERAL(8, 173, 7), // "runTest"
QT_MOC_LITERAL(9, 181, 21) // "slotStopWorkerThreads"

    },
    "WavStep_Power_Monitoring_Test_Worker\0"
    "finished\0\0signalWriteBufferToFile\0"
    "QList<WavStep_Power_Monitoring_Data_Point>\0"
    "dataPoints\0signalAddReadingsToGraph\0"
    "signalStopWorkerThread\0runTest\0"
    "slotStopWorkerThreads"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WavStep_Power_Monitoring_Test_Worker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       6,    1,   48,    2, 0x06 /* Public */,
       7,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WavStep_Power_Monitoring_Test_Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WavStep_Power_Monitoring_Test_Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->signalWriteBufferToFile((*reinterpret_cast< QList<WavStep_Power_Monitoring_Data_Point>(*)>(_a[1]))); break;
        case 2: _t->signalAddReadingsToGraph((*reinterpret_cast< QList<WavStep_Power_Monitoring_Data_Point>(*)>(_a[1]))); break;
        case 3: _t->signalStopWorkerThread(); break;
        case 4: _t->runTest(); break;
        case 5: _t->slotStopWorkerThreads(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WavStep_Power_Monitoring_Test_Worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Worker::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Worker::*)(QList<WavStep_Power_Monitoring_Data_Point> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Worker::signalWriteBufferToFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Worker::*)(QList<WavStep_Power_Monitoring_Data_Point> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Worker::signalAddReadingsToGraph)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WavStep_Power_Monitoring_Test_Worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WavStep_Power_Monitoring_Test_Worker::signalStopWorkerThread)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WavStep_Power_Monitoring_Test_Worker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker.data,
    qt_meta_data_WavStep_Power_Monitoring_Test_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WavStep_Power_Monitoring_Test_Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WavStep_Power_Monitoring_Test_Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WavStep_Power_Monitoring_Test_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WavStep_Power_Monitoring_Test_Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WavStep_Power_Monitoring_Test_Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WavStep_Power_Monitoring_Test_Worker::signalWriteBufferToFile(QList<WavStep_Power_Monitoring_Data_Point> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WavStep_Power_Monitoring_Test_Worker::signalAddReadingsToGraph(QList<WavStep_Power_Monitoring_Data_Point> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WavStep_Power_Monitoring_Test_Worker::signalStopWorkerThread()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
