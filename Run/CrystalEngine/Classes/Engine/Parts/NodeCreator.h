//
//  NodeCreator.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__NodeCreator__
#define __CrystalEngine__NodeCreator__

#include "INodeCreator.h"

START_CRYSTALENGINE

///////////////// 空节点创建 /////////////////
class NodeCreator : public INodeCreator
{
public:
    //创建节点
    virtual iNode create() override;
};

//////////////// 测试节点创建 ////////////////
class TestNodeCreator : public NodeCreator
{
public:
    //创建节点
    virtual iNode create() override;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__NodeCreator__) */
