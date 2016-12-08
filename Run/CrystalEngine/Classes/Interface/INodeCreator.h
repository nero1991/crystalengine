//
//  INodeCreator.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_INodeCreator_h
#define CrystalEngine_INodeCreator_h

#include "INode.h"

START_CRYSTALENGINE

class INodeCreator : public IInterface
{
public:
    //创建节点
    virtual iNode create() = 0;
};

typedef AutoReleasePtr<INodeCreator> iNodeCreator;

ENDED_CRYSTALENGINE

#endif
