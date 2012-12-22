/****************************************************************************
** Meta object code from reading C++ file 'QIrrControl.h'
**
** Created: Sat Sep 22 00:00:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QIrrControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QIrrControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QIrrControll[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QIrrControll[] = {
    "QIrrControll\0\0device\0"
    "UpdateIrrQuery(irr::IrrlichtDevice*)\0"
    "UpdateIrrlicht(irr::IrrlichtDevice*)\0"
};

void QIrrControll::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QIrrControll *_t = static_cast<QIrrControll *>(_o);
        switch (_id) {
        case 0: _t->UpdateIrrQuery((*reinterpret_cast< irr::IrrlichtDevice*(*)>(_a[1]))); break;
        case 1: _t->UpdateIrrlicht((*reinterpret_cast< irr::IrrlichtDevice*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QIrrControll::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QIrrControll::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QIrrControll,
      qt_meta_data_QIrrControll, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QIrrControll::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QIrrControll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QIrrControll::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QIrrControll))
        return static_cast<void*>(const_cast< QIrrControll*>(this));
    return QWidget::qt_metacast(_clname);
}

int QIrrControll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QIrrControll::UpdateIrrQuery(irr::IrrlichtDevice * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
