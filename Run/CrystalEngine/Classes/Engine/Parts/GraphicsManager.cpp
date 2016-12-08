//
//  GraphicsManager.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "GraphicsManager.h"

START_CRYSTALENGINE

inline void GraphicsManager::setDriver(iDriver driver)
{
    m_driver = driver;
}

bool GraphicsManager::remove(iGraphics program)
{
    bool result = false;
    for (Graphics find = m_graphicsMap.begin();m_graphicsMap.end() != find;++find) {
        if (find->second == program) {
            m_graphicsMap.erase(find);
            result = true;
            break;
        }
    }
    return result;
}

inline bool GraphicsManager::remove(const std::string& name)
{
    bool result = false;
    Graphics find = m_graphicsMap.find(name);
    if (m_graphicsMap.end() != find) {
        m_graphicsMap.erase(find);
        result = true;
    }
    return result;
}

inline iGraphics GraphicsManager::create(const std::string& name)
{
    iGraphics result;
    if (m_driver.isValid() && m_graphicsMap.count(name) == nops) {
        result = m_driver->createGraphics();
        m_graphicsMap[name] = result;
    }
    return result;
}

inline iGraphics GraphicsManager::findByName(const std::string& name)
{
    iGraphics result;
    Graphics find = m_graphicsMap.find(name);
    if (m_graphicsMap.end() != find) {
        result = find->second;
    }
    return result;
}


ENDED_CRYSTALENGINE