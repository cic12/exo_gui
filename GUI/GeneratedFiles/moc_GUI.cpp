/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../GUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_t {
    QByteArrayData data[20];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 0, 3), // "GUI"
QT_MOC_LITERAL(1, 4, 20), // "on_btn_start_clicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 19), // "on_btn_stop_clicked"
QT_MOC_LITERAL(4, 46, 20), // "on_btn_reset_clicked"
QT_MOC_LITERAL(5, 67, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(6, 87, 21), // "on_checkBox_2_clicked"
QT_MOC_LITERAL(7, 109, 22), // "on_openClose_triggered"
QT_MOC_LITERAL(8, 132, 19), // "on_message_received"
QT_MOC_LITERAL(9, 152, 25), // "ximu::SerialPort::Message"
QT_MOC_LITERAL(10, 178, 1), // "m"
QT_MOC_LITERAL(11, 180, 22), // "on_quaternion_received"
QT_MOC_LITERAL(12, 203, 20), // "ximu::QuaternionData"
QT_MOC_LITERAL(13, 224, 1), // "q"
QT_MOC_LITERAL(14, 226, 15), // "on_text_changed"
QT_MOC_LITERAL(15, 242, 24), // "on_openClose_triggered_2"
QT_MOC_LITERAL(16, 267, 16), // "on_data_received"
QT_MOC_LITERAL(17, 284, 17), // "on_text_changed_2"
QT_MOC_LITERAL(18, 302, 10), // "onGUIComms"
QT_MOC_LITERAL(19, 313, 9) // "onTimeout"

    },
    "GUI\0on_btn_start_clicked\0\0on_btn_stop_clicked\0"
    "on_btn_reset_clicked\0on_checkBox_clicked\0"
    "on_checkBox_2_clicked\0on_openClose_triggered\0"
    "on_message_received\0ximu::SerialPort::Message\0"
    "m\0on_quaternion_received\0ximu::QuaternionData\0"
    "q\0on_text_changed\0on_openClose_triggered_2\0"
    "on_data_received\0on_text_changed_2\0"
    "onGUIComms\0onTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,
      16,    0,   98,    2, 0x08 /* Private */,
      17,    0,   99,    2, 0x08 /* Private */,
      18,    1,  100,    2, 0x0a /* Public */,
      19,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_start_clicked(); break;
        case 1: _t->on_btn_stop_clicked(); break;
        case 2: _t->on_btn_reset_clicked(); break;
        case 3: _t->on_checkBox_clicked(); break;
        case 4: _t->on_checkBox_2_clicked(); break;
        case 5: _t->on_openClose_triggered(); break;
        case 6: _t->on_message_received((*reinterpret_cast< ximu::SerialPort::Message(*)>(_a[1]))); break;
        case 7: _t->on_quaternion_received((*reinterpret_cast< const ximu::QuaternionData(*)>(_a[1]))); break;
        case 8: _t->on_text_changed(); break;
        case 9: _t->on_openClose_triggered_2(); break;
        case 10: _t->on_data_received(); break;
        case 11: _t->on_text_changed_2(); break;
        case 12: _t->onGUIComms((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ximu::SerialPort::Message >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ximu::QuaternionData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GUI.data,
    qt_meta_data_GUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
