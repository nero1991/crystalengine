//
//  GLESDriver.cpp
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "GLESLog.h"
#include "Graphics.h"
#include "GLESDriver.h"
#include "ShaderProgram.h"

START_CRYSTALENGINE

inline void GLESDriver::init()
{
    m_clearColor = new Color(0.0f,0.0f,0.0f,1.0f);
}

void GLESDriver::executeCommands()
{
    if (m_clearColor.isValid()) {
        glClearColor(m_clearColor->red, m_clearColor->green, m_clearColor->blue, m_clearColor->alpha);
    } else {
        ENGINE_LOGOUT("clear Color object is unvalid!");
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//default black background
    }
    GLES_ERRORLOG();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLES_ERRORLOG();
    
    while (!m_commandsStack.empty()) {
        iRenderCommand& command = m_commandsStack.top();
        if (command.isValid()) {
            CEuint driverType = 0;
            switch (command->drawType()) {
                case ENUM_DRIVER_DRAW_TYPE_LINES:
                {
                    driverType = GL_LINES;
                }break;
                case ENUM_DRIVER_DRAW_TYPE_POINTS:
                {
                    driverType = GL_POINTS;
                }break;
                case ENUM_DRIVER_DRAW_TYPE_TRIANGLES:
                {
                    driverType = GL_TRIANGLES;
                }break;
                default:
                {
                    ENGINE_LOGOUT("GLES 3.0 not support this graphics type %d", command->drawType());
                }break;
            }
            if (nops != driverType) {
                command->execute();
                glDrawArrays(driverType, 0, command->vertercisCount());
                GLES_ERRORLOG();
            }
        }
        m_commandsStack.pop();
    }
    glFlush();
    GLES_ERRORLOG();
}

//获取背景清除色
inline iColor GLESDriver::clearColor() const
{
    return m_clearColor;
}

inline iGraphics GLESDriver::createGraphics()
{
    return new Graphics();
}

inline iShaderProgram GLESDriver::createShaderProgram()
{
    return new ShaderProgram();
}

void GLESDriver::addCommand(iRenderCommand command)
{
    if (command.isValid()) {
        m_commandsStack.push(command);
    } else {
        ENGINE_LOGOUT("unvalid draw command");
    }
}

//设置背景清除色
inline void GLESDriver::setClearColor(CEfloat r,CEfloat g,CEfloat b,CEfloat a)
{
    if (m_clearColor.isValid()) {
        m_clearColor->red = r;
        m_clearColor->green = g;
        m_clearColor->blue = b;
        m_clearColor->alpha = a;
    }
}

ENDED_CRYSTALENGINE