/****************************************************************************
** Meta object code from reading C++ file 'MappingToolWindow.h'
**
** Created: Sat 22. Dec 19:31:42 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EdPrec.h"
#include "Gui/MappingToolWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MappingToolWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MappingToolWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      40,   18,   18,   18, 0x08,
      53,   18,   18,   18, 0x08,
      83,   77,   18,   18, 0x08,
     112,   18,   18,   18, 0x08,
     131,   77,   18,   18, 0x08,
     167,  162,   18,   18, 0x08,
     205,  202,   18,   18, 0x08,
     234,  230,   18,   18, 0x08,
     261,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MappingToolWindow[] = {
    "MappingToolWindow\0\0OnOpenFileSelected()\0"
    "OnSaveFile()\0OnOpenTextureSelected()\0"
    "index\0OnFrameSelected(QModelIndex)\0"
    "OnShowAllChanged()\0OnTextureSelected(QModelIndex)\0"
    "item\0OnFrameDataChanged(QStandardItem*)\0"
    "ev\0closeEvent(QCloseEvent*)\0evt\0"
    "resizeEvent(QResizeEvent*)\0DelayedUpdate()\0"
};

void MappingToolWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MappingToolWindow *_t = static_cast<MappingToolWindow *>(_o);
        switch (_id) {
        case 0: _t->OnOpenFileSelected(); break;
        case 1: _t->OnSaveFile(); break;
        case 2: _t->OnOpenTextureSelected(); break;
        case 3: _t->OnFrameSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->OnShowAllChanged(); break;
        case 5: _t->OnTextureSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 6: _t->OnFrameDataChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 8: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 9: _t->DelayedUpdate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MappingToolWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MappingToolWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MappingToolWindow,
      qt_meta_data_MappingToolWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MappingToolWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MappingToolWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MappingToolWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MappingToolWindow))
        return static_cast<void*>(const_cast< MappingToolWindow*>(this));
    if (!strcmp(_clname, "IMappingToolWindow"))
        return static_cast< IMappingToolWindow*>(const_cast< MappingToolWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int MappingToolWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
