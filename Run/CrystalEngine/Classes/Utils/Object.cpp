//
//  Object.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "Object.h"
#include "Printer.h"

START_CRYSTALENGINE

Object::Object() : m_referenceCount(0)
{
    
}

void Object::retain()
{
    ++m_referenceCount;
}

void Object::release()
{
    ENGINE_ASSERT(m_referenceCount > 0, "releasing too much time!");
    if (--m_referenceCount ==0 )
    {
        delete this;
    }
}

inline long Object::getReferenceCount() const
{
    return m_referenceCount;
}


ENDED_CRYSTALENGINE