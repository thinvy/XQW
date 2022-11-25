/****************************************************************************
** Meta object code from reading C++ file 'MainTask.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainTask.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainTask.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TransVideoTask_t {
    QByteArrayData data[5];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransVideoTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransVideoTask_t qt_meta_stringdata_TransVideoTask = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TransVideoTask"
QT_MOC_LITERAL(1, 15, 9), // "setFailed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "std::string&"
QT_MOC_LITERAL(4, 39, 9) // "error_msg"

    },
    "TransVideoTask\0setFailed\0\0std::string&\0"
    "error_msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransVideoTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void TransVideoTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransVideoTask *_t = static_cast<TransVideoTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFailed((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TransVideoTask::*_t)(std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransVideoTask::setFailed)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TransVideoTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TransVideoTask.data,
      qt_meta_data_TransVideoTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TransVideoTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransVideoTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TransVideoTask.stringdata0))
        return static_cast<void*>(const_cast< TransVideoTask*>(this));
    return QObject::qt_metacast(_clname);
}

int TransVideoTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TransVideoTask::setFailed(std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CameraTask_t {
    QByteArrayData data[14];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraTask_t qt_meta_stringdata_CameraTask = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CameraTask"
QT_MOC_LITERAL(1, 11, 11), // "toTransport"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "cv::Mat&"
QT_MOC_LITERAL(4, 33, 5), // "frame"
QT_MOC_LITERAL(5, 39, 9), // "videoLost"
QT_MOC_LITERAL(6, 49, 12), // "std::string&"
QT_MOC_LITERAL(7, 62, 9), // "error_msg"
QT_MOC_LITERAL(8, 72, 9), // "toDisplay"
QT_MOC_LITERAL(9, 82, 25), // "std::vector<TrackingBox>&"
QT_MOC_LITERAL(10, 108, 5), // "boxes"
QT_MOC_LITERAL(11, 114, 8), // "toDetect"
QT_MOC_LITERAL(12, 123, 14), // "if_direct_show"
QT_MOC_LITERAL(13, 138, 12) // "directDislay"

    },
    "CameraTask\0toTransport\0\0cv::Mat&\0frame\0"
    "videoLost\0std::string&\0error_msg\0"
    "toDisplay\0std::vector<TrackingBox>&\0"
    "boxes\0toDetect\0if_direct_show\0"
    "directDislay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       8,    2,   45,    2, 0x06 /* Public */,
      11,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,    4,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   12,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CameraTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraTask *_t = static_cast<CameraTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toTransport((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 1: _t->videoLost((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->toDisplay((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< std::vector<TrackingBox>(*)>(_a[2]))); break;
        case 3: _t->toDetect((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->directDislay(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CameraTask::*_t)(cv::Mat & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraTask::toTransport)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CameraTask::*_t)(std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraTask::videoLost)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CameraTask::*_t)(cv::Mat & , std::vector<TrackingBox> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraTask::toDisplay)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CameraTask::*_t)(cv::Mat & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraTask::toDetect)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject CameraTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CameraTask.data,
      qt_meta_data_CameraTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraTask.stringdata0))
        return static_cast<void*>(const_cast< CameraTask*>(this));
    return QObject::qt_metacast(_clname);
}

int CameraTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CameraTask::toTransport(cv::Mat & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraTask::videoLost(std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraTask::toDisplay(cv::Mat & _t1, std::vector<TrackingBox> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraTask::toDetect(cv::Mat & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_DetectTask_t {
    QByteArrayData data[18];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DetectTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DetectTask_t qt_meta_stringdata_DetectTask = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DetectTask"
QT_MOC_LITERAL(1, 11, 9), // "setFailed"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "std::string&"
QT_MOC_LITERAL(4, 35, 9), // "error_msg"
QT_MOC_LITERAL(5, 45, 9), // "toDisplay"
QT_MOC_LITERAL(6, 55, 8), // "cv::Mat&"
QT_MOC_LITERAL(7, 64, 5), // "frame"
QT_MOC_LITERAL(8, 70, 25), // "std::vector<TrackingBox>&"
QT_MOC_LITERAL(9, 96, 5), // "rects"
QT_MOC_LITERAL(10, 102, 6), // "toSent"
QT_MOC_LITERAL(11, 109, 6), // "float*"
QT_MOC_LITERAL(12, 116, 9), // "id_vector"
QT_MOC_LITERAL(13, 126, 11), // "cv::Rect2d&"
QT_MOC_LITERAL(14, 138, 4), // "rect"
QT_MOC_LITERAL(15, 143, 7), // "uint8_t"
QT_MOC_LITERAL(16, 151, 9), // "camera_id"
QT_MOC_LITERAL(17, 161, 9) // "person_id"

    },
    "DetectTask\0setFailed\0\0std::string&\0"
    "error_msg\0toDisplay\0cv::Mat&\0frame\0"
    "std::vector<TrackingBox>&\0rects\0toSent\0"
    "float*\0id_vector\0cv::Rect2d&\0rect\0"
    "uint8_t\0camera_id\0person_id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DetectTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    2,   32,    2, 0x06 /* Public */,
      10,    4,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 15,   12,   14,   16,   17,

       0        // eod
};

void DetectTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DetectTask *_t = static_cast<DetectTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFailed((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->toDisplay((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< std::vector<TrackingBox>(*)>(_a[2]))); break;
        case 2: _t->toSent((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< cv::Rect2d(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DetectTask::*_t)(std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectTask::setFailed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DetectTask::*_t)(cv::Mat & , std::vector<TrackingBox> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectTask::toDisplay)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DetectTask::*_t)(float * , cv::Rect2d & , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectTask::toSent)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DetectTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DetectTask.data,
      qt_meta_data_DetectTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DetectTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DetectTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DetectTask.stringdata0))
        return static_cast<void*>(const_cast< DetectTask*>(this));
    return QObject::qt_metacast(_clname);
}

int DetectTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DetectTask::setFailed(std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetectTask::toDisplay(cv::Mat & _t1, std::vector<TrackingBox> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DetectTask::toSent(float * _t1, cv::Rect2d & _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_TransDataTask_t {
    QByteArrayData data[13];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransDataTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransDataTask_t qt_meta_stringdata_TransDataTask = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TransDataTask"
QT_MOC_LITERAL(1, 14, 10), // "sentFailed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "std::string&"
QT_MOC_LITERAL(4, 39, 9), // "error_msg"
QT_MOC_LITERAL(5, 49, 10), // "toReDetect"
QT_MOC_LITERAL(6, 60, 6), // "float*"
QT_MOC_LITERAL(7, 67, 9), // "id_vector"
QT_MOC_LITERAL(8, 77, 11), // "cv::Rect2d&"
QT_MOC_LITERAL(9, 89, 4), // "rect"
QT_MOC_LITERAL(10, 94, 7), // "uint8_t"
QT_MOC_LITERAL(11, 102, 9), // "camera_id"
QT_MOC_LITERAL(12, 112, 9) // "person_id"

    },
    "TransDataTask\0sentFailed\0\0std::string&\0"
    "error_msg\0toReDetect\0float*\0id_vector\0"
    "cv::Rect2d&\0rect\0uint8_t\0camera_id\0"
    "person_id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransDataTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    4,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 10,    7,    9,   11,   12,

       0        // eod
};

void TransDataTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransDataTask *_t = static_cast<TransDataTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sentFailed((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->toReDetect((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< cv::Rect2d(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TransDataTask::*_t)(std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransDataTask::sentFailed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TransDataTask::*_t)(float * , cv::Rect2d & , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransDataTask::toReDetect)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TransDataTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TransDataTask.data,
      qt_meta_data_TransDataTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TransDataTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransDataTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TransDataTask.stringdata0))
        return static_cast<void*>(const_cast< TransDataTask*>(this));
    return QObject::qt_metacast(_clname);
}

int TransDataTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TransDataTask::sentFailed(std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TransDataTask::toReDetect(float * _t1, cv::Rect2d & _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
