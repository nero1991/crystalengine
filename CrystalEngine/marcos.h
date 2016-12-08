//
//  marcos.h
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_marcos_h
#define CrystalEngine_marcos_h

#define ENGILE_NAME crystal
#define START_CE_SPACE namespace ENGILE_NAME {
#define ENDED_CE_SPACE }
#define USING_CRYSTAL_ENGINE using namespace ENGILE_NAME

#define STATIC_CLASS(_class)  \
     _class() = delete;       \
    ~_class() = delete;

#define PROPERTY_SET(_T,_NAME)          \
    private:                            \
        _T _##_NAME;

#define _PROPERTY_READONLY(_T,_NAME)    \
    public:                             \
        const _T& _NAME() const         \
        {                               \
            return _##_NAME;            \
        }                               \

#define _PROPERTY_READWRITE(_T,_NAME)   \
    public:                             \
    void set##_NAME(const _T& value)    \
    {                                   \
        _##_NAME = value;               \
    }                                   \
    _PROPERTY_READONLY(_T,_NAME)        \

#define PROPERTY_READONLY(_T,_NAME)     \
    _PROPERTY_READONLY(_T,_NAME)        \
    PROPERTY_SET(_T,_NAME)

#define PROPERTY_READWRITE(_T,_NAME)    \
    _PROPERTY_READWRITE(_T,_NAME)       \
    PROPERTY_SET(_T,_NAME)

#endif
