//
//  RenderCommand.cpp
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "RenderCommand.h"

START_CRYSTALENGINE

RenderCommand::RenderCommand() :
    m_type(ENUM_DRIVER_DRAW_TYPE_END)
{
    
}

RenderCommand::~RenderCommand()
{
    
}

inline void RenderCommand::execute()
{
    do {
        if (!m_shader.isValid()) {
            ENGINE_LOGOUT("command's shader is not valid");
            break;
        }
        if (!m_graphics.isValid()) {
            ENGINE_LOGOUT("command's graphics is not valid");
            break;
        }
        m_shader->use();m_graphics->use();
        uploadAllUniformMat4();
    } while (false);
}

inline CEsizei RenderCommand::vertercisCount()
{
    CEsizei result = nops;
    if (m_graphics.isValid()) {
        result = m_graphics->getVertercisCount();
    }
    return result;
}

inline ENUM_DRIVER_DRAW_TYPE RenderCommand::drawType() const
{
    return m_type;
}

inline void RenderCommand::setDrawType(const ENUM_DRIVER_DRAW_TYPE type)
{
    m_type = type;
}

inline void RenderCommand::init(iShaderProgram shader,iGraphics graphics)
{
    m_shader = shader;
    m_graphics = graphics;
}

inline void RenderCommand::addUniformMat4(const char* name,const Martix4x4& data)
{
    m_uniformMat4x4Map.insert(std::make_pair(name, data));
}

void RenderCommand::uploadAllUniformMat4()
{
    for (UniformMat4x4 uniform = m_uniformMat4x4Map.begin();
         m_uniformMat4x4Map.end() != uniform;++uniform) {
        Martix4x4& martix4x4 = uniform->second;
        m_shader->upLoadUniformMat4(uniform->first.c_str(), martix4x4.data());
    }
    m_uniformMat4x4Map.clear();
}

ENDED_CRYSTALENGINE
