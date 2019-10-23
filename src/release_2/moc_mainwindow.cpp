/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[496];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "signalDeviceTypeSelected"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "deviceType"
QT_MOC_LITERAL(4, 48, 36), // "signalRequestDevicesFromOrche..."
QT_MOC_LITERAL(5, 85, 24), // "signalCreateN7714ADevice"
QT_MOC_LITERAL(6, 110, 4), // "type"
QT_MOC_LITERAL(7, 115, 17), // "instrumentAddress"
QT_MOC_LITERAL(8, 133, 18), // "instrumentIdentity"
QT_MOC_LITERAL(9, 152, 24), // "signalCreateN7745ADevice"
QT_MOC_LITERAL(10, 177, 18), // "signalCreateDevice"
QT_MOC_LITERAL(11, 196, 15), // "signalBeginTest"
QT_MOC_LITERAL(12, 212, 21), // "slotCreateErrorDialog"
QT_MOC_LITERAL(13, 234, 8), // "errorMsg"
QT_MOC_LITERAL(14, 243, 30), // "on_searchForDevTypeBtn_clicked"
QT_MOC_LITERAL(15, 274, 18), // "slotReceiveDevices"
QT_MOC_LITERAL(16, 293, 10), // "FoundInstr"
QT_MOC_LITERAL(17, 304, 13), // "listOfDevices"
QT_MOC_LITERAL(18, 318, 39), // "on_testTypeComboBox_currentIn..."
QT_MOC_LITERAL(19, 358, 5), // "index"
QT_MOC_LITERAL(20, 364, 31), // "on_addSelectedDeviceBtn_clicked"
QT_MOC_LITERAL(21, 396, 30), // "on_startTestPushButton_clicked"
QT_MOC_LITERAL(22, 427, 46), // "on_selectedDevicesListWidget_..."
QT_MOC_LITERAL(23, 474, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(24, 491, 4) // "item"

    },
    "MainWindow\0signalDeviceTypeSelected\0"
    "\0deviceType\0signalRequestDevicesFromOrchestrator\0"
    "signalCreateN7714ADevice\0type\0"
    "instrumentAddress\0instrumentIdentity\0"
    "signalCreateN7745ADevice\0signalCreateDevice\0"
    "signalBeginTest\0slotCreateErrorDialog\0"
    "errorMsg\0on_searchForDevTypeBtn_clicked\0"
    "slotReceiveDevices\0FoundInstr\0"
    "listOfDevices\0on_testTypeComboBox_currentIndexChanged\0"
    "index\0on_addSelectedDeviceBtn_clicked\0"
    "on_startTestPushButton_clicked\0"
    "on_selectedDevicesListWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    0,   82,    2, 0x06 /* Public */,
       5,    3,   83,    2, 0x06 /* Public */,
       9,    3,   90,    2, 0x06 /* Public */,
      10,    3,   97,    2, 0x06 /* Public */,
      11,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  107,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x08 /* Private */,
      15,    1,  111,    2, 0x08 /* Private */,
      18,    1,  114,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x08 /* Private */,
      21,    0,  118,    2, 0x08 /* Private */,
      22,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QByteArray,    6,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QByteArray,    6,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QByteArray,    6,    7,    8,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDeviceTypeSelected((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signalRequestDevicesFromOrchestrator(); break;
        case 2: _t->signalCreateN7714ADevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 3: _t->signalCreateN7745ADevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 4: _t->signalCreateDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 5: _t->signalBeginTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slotCreateErrorDialog((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->on_searchForDevTypeBtn_clicked(); break;
        case 8: _t->slotReceiveDevices((*reinterpret_cast< FoundInstr(*)>(_a[1]))); break;
        case 9: _t->on_testTypeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_addSelectedDeviceBtn_clicked(); break;
        case 11: _t->on_startTestPushButton_clicked(); break;
        case 12: _t->on_selectedDevicesListWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalDeviceTypeSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalRequestDevicesFromOrchestrator)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalCreateN7714ADevice)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalCreateN7745ADevice)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalCreateDevice)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalBeginTest)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MainWindow::signalDeviceTypeSelected(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::signalRequestDevicesFromOrchestrator()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::signalCreateN7714ADevice(QString _t1, QByteArray _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::signalCreateN7745ADevice(QString _t1, QByteArray _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::signalCreateDevice(QString _t1, QByteArray _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::signalBeginTest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
