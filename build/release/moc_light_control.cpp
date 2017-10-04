/****************************************************************************
** Meta object code from reading C++ file 'light_control.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../light_control.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'light_control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlLight_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlLight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlLight_t qt_meta_stringdata_ControlLight = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ControlLight"
QT_MOC_LITERAL(1, 13, 11), // "openShutter"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "closeShutter"
QT_MOC_LITERAL(4, 39, 10), // "turnBulbOn"
QT_MOC_LITERAL(5, 50, 11), // "turnBulbOff"
QT_MOC_LITERAL(6, 62, 15), // "enableHighPower"
QT_MOC_LITERAL(7, 78, 16), // "disableHighPower"
QT_MOC_LITERAL(8, 95, 13), // "connectButton"
QT_MOC_LITERAL(9, 109, 10) // "updateData"

    },
    "ControlLight\0openShutter\0\0closeShutter\0"
    "turnBulbOn\0turnBulbOff\0enableHighPower\0"
    "disableHighPower\0connectButton\0"
    "updateData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlLight[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void ControlLight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlLight *_t = static_cast<ControlLight *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openShutter(); break;
        case 1: _t->closeShutter(); break;
        case 2: _t->turnBulbOn(); break;
        case 3: _t->turnBulbOff(); break;
        case 4: _t->enableHighPower(); break;
        case 5: _t->disableHighPower(); break;
        case 6: _t->connectButton(); break;
        case 7: _t->updateData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ControlLight::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ControlLight.data,
      qt_meta_data_ControlLight,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ControlLight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlLight::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlLight.stringdata0))
        return static_cast<void*>(const_cast< ControlLight*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ControlLight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
