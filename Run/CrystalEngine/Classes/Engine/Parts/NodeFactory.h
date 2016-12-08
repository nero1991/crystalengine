//
//  NodeFactory.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__NodeFactory__
#define __CrystalEngine__NodeFactory__

#include "INode.h"

START_CRYSTALENGINE

class NodeFactory
{
public:
    STATIC_CLASS(NodeFactory)
    
    //创建指定类型的Node
    static iNode create(const ENUM_NODE_TYPE type);
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__NodeFactory__) */
