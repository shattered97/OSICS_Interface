/****************************************************************************
** Meta object code from reading C++ file 'snapshotgraphdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Device_Tests/snapshotgraphdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'snapshotgraphdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SnapshotGraphDialog_t {
    QByteArrayData data[12];
    char stringdata0[353];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SnapshotGraphDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SnapshotGraphDialog_t qt_meta_stringdata_SnapshotGraphDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SnapshotGraphDialog"
QT_MOC_LITERAL(1, 20, 20), // "signalInputValidated"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 32), // "on_graphPastTimeRadioBtn_clicked"
QT_MOC_LITERAL(4, 75, 38), // "on_graphCustomStartEndRadioBt..."
QT_MOC_LITERAL(5, 114, 41), // "on_snapshotGoBackTimeEdit_edi..."
QT_MOC_LITERAL(6, 156, 41), // "on_goBackUnitComboBox_current..."
QT_MOC_LITERAL(7, 198, 4), // "arg1"
QT_MOC_LITERAL(8, 203, 40), // "on_snapshotStartTimeEdit_edit..."
QT_MOC_LITERAL(9, 244, 49), // "on_startAndEndTimeUnitComboBo..."
QT_MOC_LITERAL(10, 294, 38), // "on_snapshotEndTimeEdit_editin..."
QT_MOC_LITERAL(11, 333, 19) // "on_okButton_clicked"

    },
    "SnapshotGraphDialog\0signalInputValidated\0"
    "\0on_graphPastTimeRadioBtn_clicked\0"
    "on_graphCustomStartEndRadioBtn_clicked\0"
    "on_snapshotGoBackTimeEdit_editingFinished\0"
    "on_goBackUnitComboBox_currentIndexChanged\0"
    "arg1\0on_snapshotStartTimeEdit_editingFinished\0"
    "on_startAndEndTimeUnitComboBox_currentTextChanged\0"
    "on_snapshotEndTimeEdit_editingFinished\0"
    "on_okButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SnapshotGraphDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SnapshotGraphDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SnapshotGraphDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalInputValidated(); break;
        case 1: _t->on_graphPastTimeRadioBtn_clicked(); break;
        case 2: _t->on_graphCustomStartEndRadioBtn_clicked(); break;
        case 3: _t->on_snapshotGoBackTimeEdit_editingFinished(); break;
        case 4: _t->on_goBackUnitComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_snapshotStartTimeEdit_editingFinished(); break;
        case 6: _t->on_startAndEndTimeUnitComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_snapshotEndTimeEdit_editingFinished(); break;
        case 8: _t->on_okButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SnapshotGraphDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SnapshotGraphDialog::signalInputValidated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SnapshotGraphDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SnapshotGraphDialog.data,
    qt_meta_data_SnapshotGraphDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SnapshotGraphDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SnapshotGraphDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SnapshotGraphDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SnapshotGraphDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SnapshotGraphDialog::signalInputValidated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
