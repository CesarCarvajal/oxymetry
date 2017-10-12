/****************************************************************************
** Meta object code from reading C++ file 'panel_polarimeter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../panel_polarimeter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panel_polarimeter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PanelPolarimeter_t {
    QByteArrayData data[17];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelPolarimeter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelPolarimeter_t qt_meta_stringdata_PanelPolarimeter = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PanelPolarimeter"
QT_MOC_LITERAL(1, 17, 16), // "handleClickEvent"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "QWidget*"
QT_MOC_LITERAL(4, 44, 6), // "widget"
QT_MOC_LITERAL(5, 51, 15), // "Load_Pol_Graphs"
QT_MOC_LITERAL(6, 67, 21), // "start_Pol_Measurement"
QT_MOC_LITERAL(7, 89, 20), // "stop_Pol_Measurement"
QT_MOC_LITERAL(8, 110, 22), // "toggle_Pol_Measurement"
QT_MOC_LITERAL(9, 133, 13), // "saveGraph_Pol"
QT_MOC_LITERAL(10, 147, 12), // "AutoSave_FFT"
QT_MOC_LITERAL(11, 160, 12), // "AutoSave_Raw"
QT_MOC_LITERAL(12, 173, 10), // "clearPlots"
QT_MOC_LITERAL(13, 184, 11), // "LoadFromFFT"
QT_MOC_LITERAL(14, 196, 15), // "LoadFromRawData"
QT_MOC_LITERAL(15, 212, 18), // "ConfSetup_Pol_Pump"
QT_MOC_LITERAL(16, 231, 13) // "ConfSetup_Pol"

    },
    "PanelPolarimeter\0handleClickEvent\0\0"
    "QWidget*\0widget\0Load_Pol_Graphs\0"
    "start_Pol_Measurement\0stop_Pol_Measurement\0"
    "toggle_Pol_Measurement\0saveGraph_Pol\0"
    "AutoSave_FFT\0AutoSave_Raw\0clearPlots\0"
    "LoadFromFFT\0LoadFromRawData\0"
    "ConfSetup_Pol_Pump\0ConfSetup_Pol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelPolarimeter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void PanelPolarimeter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelPolarimeter *_t = static_cast<PanelPolarimeter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->Load_Pol_Graphs(); break;
        case 2: _t->start_Pol_Measurement(); break;
        case 3: _t->stop_Pol_Measurement(); break;
        case 4: _t->toggle_Pol_Measurement(); break;
        case 5: _t->saveGraph_Pol(); break;
        case 6: _t->AutoSave_FFT(); break;
        case 7: _t->AutoSave_Raw(); break;
        case 8: _t->clearPlots(); break;
        case 9: _t->LoadFromFFT(); break;
        case 10: _t->LoadFromRawData(); break;
        case 11: _t->ConfSetup_Pol_Pump(); break;
        case 12: _t->ConfSetup_Pol(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject PanelPolarimeter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PanelPolarimeter.data,
      qt_meta_data_PanelPolarimeter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PanelPolarimeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelPolarimeter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PanelPolarimeter.stringdata0))
        return static_cast<void*>(const_cast< PanelPolarimeter*>(this));
    return QWidget::qt_metacast(_clname);
}

int PanelPolarimeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
