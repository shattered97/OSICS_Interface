/****************************************************************************
** Meta object code from reading C++ file 'exfo_operationaltest_t100_swt_atn_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Tests/exfo_operationaltest_t100_swt_atn_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exfo_operationaltest_t100_swt_atn_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window_t {
    QByteArrayData data[10];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window_t qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window = {
    {
QT_MOC_LITERAL(0, 0, 40), // "EXFO_OperationalTest_T100_SWT..."
QT_MOC_LITERAL(1, 41, 23), // "signalBeginNextTestStep"
QT_MOC_LITERAL(2, 65, 0), // ""
QT_MOC_LITERAL(3, 66, 30), // "signalGetCurrentStepDirections"
QT_MOC_LITERAL(4, 97, 11), // "QByteArray&"
QT_MOC_LITERAL(5, 109, 12), // "resourcePath"
QT_MOC_LITERAL(6, 122, 10), // "directions"
QT_MOC_LITERAL(7, 133, 19), // "slotTestingComplete"
QT_MOC_LITERAL(8, 153, 27), // "on_outputFileButton_clicked"
QT_MOC_LITERAL(9, 181, 24) // "on_runTestButton_clicked"

    },
    "EXFO_OperationalTest_T100_SWT_ATN_Window\0"
    "signalBeginNextTestStep\0\0"
    "signalGetCurrentStepDirections\0"
    "QByteArray&\0resourcePath\0directions\0"
    "slotTestingComplete\0on_outputFileButton_clicked\0"
    "on_runTestButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EXFO_OperationalTest_T100_SWT_ATN_Window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    2,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   45,    2, 0x0a /* Public */,
       8,    0,   46,    2, 0x08 /* Private */,
       9,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EXFO_OperationalTest_T100_SWT_ATN_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EXFO_OperationalTest_T100_SWT_ATN_Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalBeginNextTestStep(); break;
        case 1: _t->signalGetCurrentStepDirections((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->slotTestingComplete(); break;
        case 3: _t->on_outputFileButton_clicked(); break;
        case 4: _t->on_runTestButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EXFO_OperationalTest_T100_SWT_ATN_Window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EXFO_OperationalTest_T100_SWT_ATN_Window::signalBeginNextTestStep)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EXFO_OperationalTest_T100_SWT_ATN_Window::*)(QByteArray & , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EXFO_OperationalTest_T100_SWT_ATN_Window::signalGetCurrentStepDirections)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EXFO_OperationalTest_T100_SWT_ATN_Window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window.data,
    qt_meta_data_EXFO_OperationalTest_T100_SWT_ATN_Window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EXFO_OperationalTest_T100_SWT_ATN_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EXFO_OperationalTest_T100_SWT_ATN_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EXFO_OperationalTest_T100_SWT_ATN_Window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int EXFO_OperationalTest_T100_SWT_ATN_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void EXFO_OperationalTest_T100_SWT_ATN_Window::signalBeginNextTestStep()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EXFO_OperationalTest_T100_SWT_ATN_Window::signalGetCurrentStepDirections(QByteArray & _t1, QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
