//
//  IGraphicsManager.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_IGraphicsManager_h
#define CrystalEngine_IGraphicsManager_h

#include <string>
#include "IDriver.h"

START_CRYSTALENGINE

class IGraphicsManager : public IInterface
{
public:
    //设置shader驱动
    virtual void setDriver(iDriver driver) = 0;
    
    //移除指定的graphics(完整释放在所有使用到这个graphics节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(iGraphics program) = 0;
    
    //移除指定的graphics(完整释放在所有使用到这个graphics节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(const std::string& name) = 0;
    
    //创建指定名称的图形，若图形已存在着返回无效指针
    virtual iGraphics create(const std::string& name) = 0;
    
    //查找指定名称的shader
    virtual iGraphics findByName(const std::string& name) = 0;
};

typedef AutoReleasePtr<IGraphicsManager> iGraphicsManager;

ENDED_CRYSTALENGINE

#endif
