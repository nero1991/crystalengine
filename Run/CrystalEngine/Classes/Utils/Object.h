//
//  Object.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Object__
#define __CrystalEngine__Object__

#include "Enum.h"
#include "Marco.h"
#include "Types.h"

START_CRYSTALENGINE

//所有类的公共父类
//用于引用计数管理
class Object
{
public:
    Object();
    virtual ~Object() = default;
    
    void retain();
    void release();
    long getReferenceCount() const;
private:
    CEsizei m_referenceCount;
};

//所有接口的公共父类
class IInterface : public Object
{
public:
    
};


ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__Object__) */
