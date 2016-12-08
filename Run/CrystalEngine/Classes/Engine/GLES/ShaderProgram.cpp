//
//  ShaderProgram.cpp
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include <string>
#include "GLESLog.h"
#include "ShaderProgram.h"

START_CRYSTALENGINE

ShaderProgram::ShaderProgram() : m_programHandle(nops)
{
    
}

ShaderProgram::~ShaderProgram()
{
    clear();
}

bool ShaderProgram::use()
{
    if (nops != m_programHandle) {
        glUseProgram(m_programHandle);
        GLES_ERRORLOG();
        return true;
    } else {
        return false;
    }
}

void ShaderProgram::link()
{
    if (nops == m_programHandle && !m_shaderHandles.empty()) {
        m_programHandle = glCreateProgram();
        GLES_ERRORLOG();
        for (auto handle : m_shaderHandles) {
            glAttachShader(m_programHandle, handle);
            GLES_ERRORLOG();
        }
        glLinkProgram(m_programHandle);
        GLES_ERRORLOG();
        printLinkingLog();
        for (auto handle : m_shaderHandles) {
            glDeleteShader(handle);
            GLES_ERRORLOG();
        }
        m_shaderHandles.clear();
    } else {
        ENGINE_LOGOUT("progam is not clean!");
    }
}

void ShaderProgram::clear()
{
    if (nops != m_programHandle) {
        glDeleteProgram(m_programHandle);
        GLES_ERRORLOG();
        m_programHandle = nops;
    }
    for (CEuint handle : m_shaderHandles) {
        glDeleteShader(handle);
        GLES_ERRORLOG();
    }
    m_shaderHandles.clear();
}

bool ShaderProgram::build(ENUM_SHADER_TYPE type,const CEchar* source)
{
    CEuint shaderHandle = nops;
    switch (type) {
        case ENUM_SHADER_TYPE_VERTEX:
        {
            shaderHandle = glCreateShader(GL_VERTEX_SHADER);
            GLES_ERRORLOG();
        }break;
        case ENUM_SHADER_TYPE_FRAGMENT:
        {
            shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
            GLES_ERRORLOG();
        }break;
        default:
        {
            ENGINE_LOGOUT("GLES 3 not surport this shader %d", type);
        }break;
    }
    if (nops != shaderHandle) {
        const CEchar * const sources [] = {source};
        glShaderSource(shaderHandle, 1, sources, nullptr);
        GLES_ERRORLOG();
        glCompileShader(shaderHandle);
        GLES_ERRORLOG();
        printCompileLog(shaderHandle);
        m_shaderHandles.push_back(shaderHandle);
        return true;
    } else {
        return false;
    }
}

CEint ShaderProgram::getAttributeLoaction(const CEchar* attributeName)
{
    return glGetAttribLocation(m_programHandle, attributeName);
}

inline void ShaderProgram::upLoadUniformMat4(const CEchar* uniformName,const CEfloat* data)
{
    CEint location = glGetUniformLocation(m_programHandle, uniformName);
    GLES_ERRORLOG();
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
    GLES_ERRORLOG();
}

void ShaderProgram::printLinkingLog()
{
    CEint log_length = 0,state = 0;
    glGetProgramiv(m_programHandle,GL_LINK_STATUS, &state);
    glGetProgramiv(m_programHandle,GL_INFO_LOG_LENGTH,&log_length);
    if (nops != log_length) {
        std::string logInfo;
        logInfo.reserve(log_length);
        glGetProgramInfoLog(m_programHandle, log_length,nullptr,const_cast<CEchar*>(logInfo.data()));
        ENGINE_LOGOUT("shader progam link log : %s", logInfo.c_str());
    }
}

void ShaderProgram::printCompileLog(CEuint handle)
{
    CEint log_length = 0,type = 0;
    glGetShaderiv(handle, GL_SHADER_TYPE, &type);
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if (nops != log_length) {
        std::string logInfo;
        logInfo.reserve(log_length);
        glGetShaderInfoLog(handle, log_length, nullptr, const_cast<GLchar*>(logInfo.data()));
        if (GL_VERTEX_SHADER == type) {
            ENGINE_LOGOUT("vertex shader comilpe log : %s", logInfo.c_str());
        } else if (GL_FRAGMENT_SHADER == type) {
            ENGINE_LOGOUT("fragment shader comilpe log : %s", logInfo.c_str());
        }
    }
}



ENDED_CRYSTALENGINE