/****************************************************************************
** Meta object code from reading C++ file 'Orchestrator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../shared/Orchestrator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Orchestrator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Orchestrator_t {
    QByteArrayData data[35];
    char stringdata0[582];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Orchestrator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Orchestrator_t qt_meta_stringdata_Orchestrator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Orchestrator"
QT_MOC_LITERAL(1, 13, 24), // "signalReturnDevicesFound"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "FoundInstr"
QT_MOC_LITERAL(4, 50, 21), // "signalSettingsUpdated"
QT_MOC_LITERAL(5, 72, 22), // "signalSetupEXFOModules"
QT_MOC_LITERAL(6, 95, 26), // "signalSendDecisionErrorMsg"
QT_MOC_LITERAL(7, 122, 8), // "errorMsg"
QT_MOC_LITERAL(8, 131, 24), // "signalSendSimpleErrorMsg"
QT_MOC_LITERAL(9, 156, 18), // "slotLookForDevices"
QT_MOC_LITERAL(10, 175, 16), // "slotCreateDevice"
QT_MOC_LITERAL(11, 192, 4), // "type"
QT_MOC_LITERAL(12, 197, 17), // "instrumentAddress"
QT_MOC_LITERAL(13, 215, 18), // "instrumentIdentity"
QT_MOC_LITERAL(14, 234, 26), // "slotGetEXFOModuleQVariants"
QT_MOC_LITERAL(15, 261, 19), // "QMap<int,QVariant>&"
QT_MOC_LITERAL(16, 281, 7), // "modules"
QT_MOC_LITERAL(17, 289, 9), // "QVariant&"
QT_MOC_LITERAL(18, 299, 6), // "device"
QT_MOC_LITERAL(19, 306, 13), // "slotBeginTest"
QT_MOC_LITERAL(20, 320, 12), // "testTypeName"
QT_MOC_LITERAL(21, 333, 24), // "slotClearSelectedDevices"
QT_MOC_LITERAL(22, 358, 28), // "slotGetEXFOModuleConfigPairs"
QT_MOC_LITERAL(23, 387, 27), // "QMap<int,ModuleConfigPair>&"
QT_MOC_LITERAL(24, 415, 17), // "moduleConfigPairs"
QT_MOC_LITERAL(25, 433, 14), // "slotSendCmdRsp"
QT_MOC_LITERAL(26, 448, 12), // "instrAddress"
QT_MOC_LITERAL(27, 461, 7), // "command"
QT_MOC_LITERAL(28, 469, 11), // "QByteArray*"
QT_MOC_LITERAL(29, 481, 8), // "response"
QT_MOC_LITERAL(30, 490, 16), // "slotSendCmdNoRsp"
QT_MOC_LITERAL(31, 507, 24), // "slotUpdateConfigSettings"
QT_MOC_LITERAL(32, 532, 10), // "QSettings&"
QT_MOC_LITERAL(33, 543, 14), // "configSettings"
QT_MOC_LITERAL(34, 558, 23) // "slotApplyConfigSettings"

    },
    "Orchestrator\0signalReturnDevicesFound\0"
    "\0FoundInstr\0signalSettingsUpdated\0"
    "signalSetupEXFOModules\0"
    "signalSendDecisionErrorMsg\0errorMsg\0"
    "signalSendSimpleErrorMsg\0slotLookForDevices\0"
    "slotCreateDevice\0type\0instrumentAddress\0"
    "instrumentIdentity\0slotGetEXFOModuleQVariants\0"
    "QMap<int,QVariant>&\0modules\0QVariant&\0"
    "device\0slotBeginTest\0testTypeName\0"
    "slotClearSelectedDevices\0"
    "slotGetEXFOModuleConfigPairs\0"
    "QMap<int,ModuleConfigPair>&\0"
    "moduleConfigPairs\0slotSendCmdRsp\0"
    "instrAddress\0command\0QByteArray*\0"
    "response\0slotSendCmdNoRsp\0"
    "slotUpdateConfigSettings\0QSettings&\0"
    "configSettings\0slotApplyConfigSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Orchestrator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    0,   92,    2, 0x06 /* Public */,
       5,    0,   93,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       8,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  100,    2, 0x0a /* Public */,
      10,    3,  101,    2, 0x0a /* Public */,
      14,    2,  108,    2, 0x0a /* Public */,
      19,    1,  113,    2, 0x0a /* Public */,
      21,    0,  116,    2, 0x0a /* Public */,
      22,    2,  117,    2, 0x0a /* Public */,
      25,    3,  122,    2, 0x08 /* Private */,
      30,    2,  129,    2, 0x08 /* Private */,
      31,    2,  134,    2, 0x08 /* Private */,
      34,    2,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QByteArray,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   16,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 23,   18,   24,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray, 0x80000000 | 28,   26,   27,   29,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,   26,   27,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 32,   18,   33,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 32,   18,   33,

       0        // eod
};

void Orchestrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Orchestrator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalReturnDevicesFound((*reinterpret_cast< FoundInstr(*)>(_a[1]))); break;
        case 1: _t->signalSettingsUpdated(); break;
        case 2: _t->signalSetupEXFOModules(); break;
        case 3: _t->signalSendDecisionErrorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->signalSendSimpleErrorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slotLookForDevices(); break;
        case 6: _t->slotCreateDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 7: _t->slotGetEXFOModuleQVariants((*reinterpret_cast< QMap<int,QVariant>(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 8: _t->slotBeginTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slotClearSelectedDevices(); break;
        case 10: _t->slotGetEXFOModuleConfigPairs((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QMap<int,ModuleConfigPair>(*)>(_a[2]))); break;
        case 11: _t->slotSendCmdRsp((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QByteArray*(*)>(_a[3]))); break;
        case 12: _t->slotSendCmdNoRsp((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 13: _t->slotUpdateConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings(*)>(_a[2]))); break;
        case 14: _t->slotApplyConfigSettings((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QSettings(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QByteArray* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Orchestrator::*)(FoundInstr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Orchestrator::signalReturnDevicesFound)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Orchestrator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Orchestrator::signalSettingsUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Orchestrator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Orchestrator::signalSetupEXFOModules)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Orchestrator::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Orchestrator::signalSendDecisionErrorMsg)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Orchestrator::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Orchestrator::signalSendSimpleErrorMsg)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Orchestrator::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Orchestrator.data,
    qt_meta_data_Orchestrator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Orchestrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Orchestrator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Orchestrator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Orchestrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Orchestrator::signalReturnDevicesFound(FoundInstr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Orchestrator::signalSettingsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Orchestrator::signalSetupEXFOModules()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Orchestrator::signalSendDecisionErrorMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Orchestrator::signalSendSimpleErrorMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
