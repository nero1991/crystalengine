//
//  ShaderManager.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "ShaderManager.h"

START_CRYSTALENGINE

inline void ShaderManager::setDriver(iDriver driver)
{
    m_driver = driver;
}

bool ShaderManager::remove(iShaderProgram program)
{
    bool result = false;
    for (Program find = m_programes.begin();m_programes.end() != find;++find) {
        if (find->second == program) {
            m_programes.erase(find);
            result = true;
            break;
        }
    }
    return result;
}

inline bool ShaderManager::remove(const std::string& name)
{
    bool result = false;
    Program find = m_programes.find(name);
    if (m_programes.end() != find) {
        m_programes.erase(find);
        result = true;
    }
    return result;
}

inline iShaderProgram ShaderManager::create(const std::string& name)
{
    iShaderProgram result;
    if (m_driver.isValid() && m_programes.count(name) == nops) {
        result = m_driver->createShaderProgram();
        m_programes[name] = result;
    }
    return result;
}

inline iShaderProgram ShaderManager::findByName(const std::string& name)
{
    iShaderProgram result;
    Program find = m_programes.find(name);
    if (m_programes.end() != find) {
        result = find->second;
    }
    return result;
}


ENDED_CRYSTALENGINE