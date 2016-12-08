//
//  object.cpp
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "object.h"

START_CE_SPACE

Object::Object() : _referenceCount(int())
{
    
}

void Object::retain()
{
    ++_referenceCount;
}

void Object::release()
{
    --_referenceCount;
    if (int() == _referenceCount) {
        delete this;
        DEBUG_LOG("release memory at %lld", this);
    } else if (int() > _referenceCount) {
        ERROR_LOG("release count error at %lld", this);
    }
}

bool Object::init()
{
    return true;
}

ENDED_CE_SPACE