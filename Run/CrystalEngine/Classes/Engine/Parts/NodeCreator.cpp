//
//  NodeCreator.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "Node.h"
#include "Director.h"
#include "NodeCreator.h"
#include "RenderCommand.h"

START_CRYSTALENGINE

///////////////// 空节点创建 /////////////////
inline iNode NodeCreator::create()
{
    iNode node = new Node();
    ENGINE_ASSERT(node.isValid(), "node create faild!");
    return node;
}

//////////////// 测试节点创建 ////////////////
iNode TestNodeCreator::create()
{
    iNode node = NodeCreator::create();
    iShaderProgram program = Director::sharedInstance().getShaderManager()->findByName("test shader");
    if (!program.isValid()) {
        program = Director::sharedInstance().getShaderManager()->create("test shader");
        program->build(ENUM_SHADER_TYPE_VERTEX,
                       "attribute vec4 position;                           \
                        uniform mat4 transformMat4;                        \
                        void main(void)                                    \
                        {                                                  \
                            gl_Position = transformMat4 * position ;       \
                        }                                                  \
                       ");
        program->build(ENUM_SHADER_TYPE_FRAGMENT,
                       "void main(void)                             \
                       {                                            \
                            gl_FragColor = vec4(1.0,0.0,0.0,1.0);   \
                       }                                            \
                       ");
        program->link();
    }
    
    iGraphics graphics = Director::sharedInstance().getGraphicsManager()->findByName("test graphics");
    if (!graphics.isValid()) {
        graphics = Director::sharedInstance().getGraphicsManager()->create("test graphics");
        graphics->initGraphicsHandle();
        graphics->initPositionHandle();
        std::vector<CEfloat> positions;
        positions.push_back(-0.5f);positions.push_back( 0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        positions.push_back(-0.5f);positions.push_back(-0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        positions.push_back( 0.5f);positions.push_back(-0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        positions.push_back( 0.5f);positions.push_back(-0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        positions.push_back( 0.5f);positions.push_back( 0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        positions.push_back(-0.5f);positions.push_back( 0.5f);positions.push_back( 0.0f);positions.push_back( 1.0f);
        graphics->updatePositionData(positions.data(),static_cast<CEsizei>(positions.size() * sizeof(CEfloat)));
        graphics->bindPositionAttribute(program, "position");
    }
    node->init(new RenderCommand(), program, graphics);
    return node;
}

ENDED_CRYSTALENGINE