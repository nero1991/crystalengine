//
//  object.h
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__object__
#define __CrystalEngine__object__

#include "marcos.h"
#include "log.h"
#include <utility>

START_CE_SPACE

class Object
{
public:
    Object();
    
    void retain();
    void release();
    
    virtual bool init();
private:
    int _referenceCount;
};

template <typename _T>
class AutoReleaseObject {
    typedef _T ClassType;
public:
    
    AutoReleaseObject() : _object(nullptr)
    {
        
    }
    
   ~AutoReleaseObject()
    {
        release();
    }
    
    AutoReleaseObject(ClassType* object) :
    AutoReleaseObject()
    {
        keep(object);
    }
    
    AutoReleaseObject(AutoReleaseObject&& right) :
    AutoReleaseObject()
    {
        *this = std::move(right);
    }
    
    AutoReleaseObject(const AutoReleaseObject& right) :
    AutoReleaseObject()
    {
        *this = right;
    }
    
    bool isNull() const
    {
        return nullptr == _object;
    }
    
    ClassType* operator*()
    {
        return _object;
    }
    
    ClassType* operator->()
    {
        return _object;
    }
    
    bool operator == (void* prt) const
    {
        return _object == prt;
    }
    
    bool operator != (void* ptr) const
    {
        return _object != ptr;
    }
    
    bool operator = (ClassType* object)
    {
        keep(object);
        
        return isNull();
    }
    
    bool operator = (AutoReleaseObject&& right)
    {
        keep(right._object);
        right.clear();
        
        return !isNull();
    }
    
    bool operator = (const AutoReleaseObject& right)
    {
        keep(right._object);
        
        return !isNull();
    }
    
    bool operator == (const AutoReleaseObject& right) const
    {
        return _object == right._object;
    }
    
    bool operator != (const AutoReleaseObject& right) const
    {
        return _object != right._object;
    }
    
private:
    void clear()
    {
        _object = nullptr;
    }
    
    void release()
    {
        if (nullptr != _object) {
            _object->release();
            _object= nullptr;
        }
    }
    
    void keep(ClassType* object)
    {
        if (nullptr != object) {
            object->retain();
        }
        if (nullptr != _object) {
            _object->release();
        }
        _object = object;
    }
    
    ClassType* _object;
};

#define AUTO_REFERENCE(_class)                          \
public:                                                 \
    typedef AutoReleaseObject<_class> auto##_class;     \
    static auto##_class create()                        \
    {                                                   \
        auto object = auto##_class(new _class());       \
        if (object == nullptr) {                        \
            ERROR_LOG("alloc object failed!");          \
        } else if (!object->init()){                    \
            DEBUG_LOG("init object failed!");           \
            object = nullptr;                           \
        }                                               \
        return object;                                  \
    }

ENDED_CE_SPACE

#endif /* defined(__CrystalEngine__object__) */
