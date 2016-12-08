//
//  Director.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Director__
#define __CrystalEngine__Director__

#include "../Utils/Public.h"
#include "../Interface/INode.h"
#include "../Interface/IDriver.h"
#include "../Interface/IShaderManager.h"
#include "../Interface/IGraphicsManager.h"

START_CRYSTALENGINE

class Director : public Object
{
public:
    SINGLETON_INSTANCE(Director)
    
    //进行绘制
    void draw();
    
    //进行绘制准备
    void prepare();
    
    //获取根节点
    iNode root();
    
    //获取图形绘制驱动
    iDriver getDriver() const;
    
    //获取shader管理器
    iShaderManager& getShaderManager();
    
    //获取graphics管理器
    iGraphicsManager& getGraphicsManager();
    
    //创建指定图形的绘制驱动
    bool initDriver(ENUM_DRIVER_TYPE type);
    
    //创建一个空绘制节点
    iNode createNode(const ENUM_NODE_TYPE type);
private:
    iNode   m_root;
    iDriver m_Driver;
    iShaderManager m_shaderManager;
    iGraphicsManager m_graphicsManager;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__Director__) */
