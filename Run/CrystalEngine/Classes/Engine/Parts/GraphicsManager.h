//
//  GraphicsManager.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__GraphicsManager__
#define __CrystalEngine__GraphicsManager__

#include <map>
#include "IGraphicsManager.h"

START_CRYSTALENGINE

class GraphicsManager : public IGraphicsManager
{
    typedef std::map<std::string, iGraphics> GraphicsMap;
    typedef GraphicsMap::iterator Graphics;
public:
    //设置shader驱动
    virtual void setDriver(iDriver driver) override;
    
    //移除指定的graphics(完整释放在所有使用到这个graphics节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(iGraphics program) override;
    
    //移除指定的graphics(完整释放在所有使用到这个graphics节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(const std::string& name) override;
    
    //创建指定名称的图形，若图形已存在着返回无效指针
    virtual iGraphics create(const std::string& name) override;
    
    //查找指定名称的shader
    virtual iGraphics findByName(const std::string& name) override;
private:
    iDriver m_driver;
    GraphicsMap m_graphicsMap;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__GraphicsManager__) */
