//
//  Graphics.cpp
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "GLESLog.h"
#include "Graphics.h"
#include "IShaderProgram.h"

START_CRYSTALENGINE

Graphics::Graphics() :
    m_GraphicsVAO(nops),
    m_VertercisVBO(nops),
    m_VertercisCount(nops),
    m_dismension(4)
{
    
}

Graphics::~Graphics()
{
    clear();
}

bool Graphics::use()
{
    if (nops != m_GraphicsVAO) {
        glBindVertexArray(m_GraphicsVAO);
        GLES_ERRORLOG();
        return true;
    } else {
        return false;
    }
}

void Graphics::clear()
{
    if (nops != m_VertercisVBO) {
        glDeleteBuffers(1, &m_VertercisVBO);
        GLES_ERRORLOG();
        m_VertercisVBO = nops;
    }
    if (nops != m_GraphicsVAO) {
        glDeleteVertexArrays(1, &m_GraphicsVAO);
        GLES_ERRORLOG();
        m_GraphicsVAO = nops;
    }
}

void Graphics::initGraphicsHandle()
{
    glGenVertexArrays(1, &m_GraphicsVAO);
    GLES_ERRORLOG();
}

void Graphics::initPositionHandle()
{
    glGenBuffers(1, &m_VertercisVBO);
    GLES_ERRORLOG();
}

inline CEsizei Graphics::getVertercisCount() const
{
    return m_VertercisCount;
}

void Graphics::setPositionDimension(CEint dimension)
{
    m_dismension = dimension;
}

bool Graphics::updatePositionData(const CEfloat* data,const CEsizei size)
{
    bool result = false;
    if (nullptr != data && 0 != size && nops != m_VertercisVBO) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertercisVBO);
        GLES_ERRORLOG();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        GLES_ERRORLOG();
        glBindBuffer(GL_ARRAY_BUFFER, nops);
        GLES_ERRORLOG();//for safe
        result = true;
        m_VertercisCount = size / (sizeof(CEfloat) * m_dismension);
    }
    return result;
}

bool Graphics::bindPositionAttribute(iShaderProgram shader,const CEchar* attributName)
{
    bool result = false;
    if (nullptr != attributName && nops != m_GraphicsVAO) {
        glBindVertexArray(m_GraphicsVAO);
        GLES_ERRORLOG();
        CEint loaction = shader->getAttributeLoaction(attributName);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertercisVBO);
        GLES_ERRORLOG();
        glVertexAttribPointer(loaction, m_dismension, GL_FLOAT, GL_FALSE, 0, nullptr);
        GLES_ERRORLOG();
        glEnableVertexAttribArray(loaction);
        GLES_ERRORLOG();
        //for safe
        glBindBuffer(GL_ARRAY_BUFFER, nops);
        GLES_ERRORLOG();
        glBindVertexArray(nops);
        GLES_ERRORLOG();
        result = true;
    }
    return result;
}


ENDED_CRYSTALENGINE