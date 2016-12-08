//
//  Director.cpp
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "Director.h"
#include "GLESDriver.h"
#include "NodeFactory.h"
#include "RenderCommand.h"
#include "ShaderManager.h"
#include "GraphicsManager.h"

START_CRYSTALENGINE

void Director::draw()
{
    if (m_Driver.isValid() && m_root.isValid()) {
        //TODO :: add model view martix
        m_root->visit(m_Driver,Position());
        m_Driver->executeCommands();
    } else {
        ENGINE_LOGOUT("no driver");
    }
}

void Director::prepare()
{
    if (m_Driver.isValid()) {
        m_shaderManager = new ShaderManager();
        ENGINE_ASSERT(m_shaderManager.isValid(),
                      "create shaderManager failed!");
        m_shaderManager->setDriver(m_Driver);
        
        m_graphicsManager = new GraphicsManager();
        ENGINE_ASSERT(m_graphicsManager.isValid(),
                      "create graphicsManager failed!");
        m_graphicsManager->setDriver(m_Driver);
        
        m_root = createNode(ENUM_NODE_TYPE_EMPTY);
    } else {
        ENGINE_LOGOUT("no driver");
    }
}

iNode Director::root()
{
    return m_root;
}

iDriver Director::getDriver() const
{
    return m_Driver;
}

iShaderManager& Director::getShaderManager()
{
    return m_shaderManager;
}

iGraphicsManager& Director::getGraphicsManager()
{
    return m_graphicsManager;
}

bool Director::initDriver(ENUM_DRIVER_TYPE type)
{
    bool result = true;
    switch (type) {
        case ENUM_DRIVER_TYPE_GLES:
        {
            m_Driver = new GLESDriver();
        }break;
        default:
        {
            result = false;
            ENGINE_ASSERT(false, "not support this driver!");
        }break;
    }
    if (m_Driver.isValid()) {
        m_Driver->init();
    } else {
        ENGINE_ASSERT(false,"create driver failed!");
    }
    return result;
}

iNode Director::createNode(const ENUM_NODE_TYPE type)
{
    return NodeFactory::create(type);
}

ENDED_CRYSTALENGINE