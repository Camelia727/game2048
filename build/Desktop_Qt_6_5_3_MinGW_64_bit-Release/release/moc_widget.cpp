/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWidgetENDCLASS = QtMocHelpers::stringData(
    "Widget",
    "playBgm",
    "",
    "QMediaPlayer::MediaStatus",
    "status",
    "acceptMove",
    "recall",
    "openMenu",
    "changeTheme",
    "reset",
    "closeMenu",
    "exit",
    "changeVolumn",
    "volumn"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWidgetENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[7];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[7];
    char stringdata5[11];
    char stringdata6[7];
    char stringdata7[9];
    char stringdata8[12];
    char stringdata9[6];
    char stringdata10[10];
    char stringdata11[5];
    char stringdata12[13];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWidgetENDCLASS_t qt_meta_stringdata_CLASSWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Widget"
        QT_MOC_LITERAL(7, 7),  // "playBgm"
        QT_MOC_LITERAL(15, 0),  // ""
        QT_MOC_LITERAL(16, 25),  // "QMediaPlayer::MediaStatus"
        QT_MOC_LITERAL(42, 6),  // "status"
        QT_MOC_LITERAL(49, 10),  // "acceptMove"
        QT_MOC_LITERAL(60, 6),  // "recall"
        QT_MOC_LITERAL(67, 8),  // "openMenu"
        QT_MOC_LITERAL(76, 11),  // "changeTheme"
        QT_MOC_LITERAL(88, 5),  // "reset"
        QT_MOC_LITERAL(94, 9),  // "closeMenu"
        QT_MOC_LITERAL(104, 4),  // "exit"
        QT_MOC_LITERAL(109, 12),  // "changeVolumn"
        QT_MOC_LITERAL(122, 6)   // "volumn"
    },
    "Widget",
    "playBgm",
    "",
    "QMediaPlayer::MediaStatus",
    "status",
    "acceptMove",
    "recall",
    "openMenu",
    "changeTheme",
    "reset",
    "closeMenu",
    "exit",
    "changeVolumn",
    "volumn"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x0a,    1 /* Public */,
       5,    0,   71,    2, 0x0a,    3 /* Public */,
       6,    0,   72,    2, 0x0a,    4 /* Public */,
       7,    0,   73,    2, 0x0a,    5 /* Public */,
       8,    0,   74,    2, 0x0a,    6 /* Public */,
       9,    0,   75,    2, 0x0a,    7 /* Public */,
      10,    0,   76,    2, 0x0a,    8 /* Public */,
      11,    0,   77,    2, 0x0a,    9 /* Public */,
      12,    1,   78,    2, 0x0a,   10 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Widget, std::true_type>,
        // method 'playBgm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'acceptMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeVolumn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->playBgm((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 1: _t->acceptMove(); break;
        case 2: _t->recall(); break;
        case 3: _t->openMenu(); break;
        case 4: _t->changeTheme(); break;
        case 5: _t->reset(); break;
        case 6: _t->closeMenu(); break;
        case 7: _t->exit(); break;
        case 8: _t->changeVolumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
