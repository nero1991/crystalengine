//
//  NodeFactory.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "NodeFactory.h"
#include "NodeCreator.h"

START_CRYSTALENGINE

iNode NodeFactory::create(const ENUM_NODE_TYPE type)
{
    iNodeCreator creator;
    switch (type) {
        case ENUM_NODE_TYPE_EMPTY:
        {
            creator = new NodeCreator();
        }break;
        case ENUM_NODE_TYPE_TEST:
        {
            creator = new TestNodeCreator();
        }break;
        default:
        {
            ENGINE_LOGOUT("not support this node type %d", type);
            creator = new NodeCreator();
        }break;
    }
    return creator->create();
}

ENDED_CRYSTALENGINE