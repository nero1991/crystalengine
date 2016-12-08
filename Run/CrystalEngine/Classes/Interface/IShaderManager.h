//
//  IShaderManager.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_IShaderManager_h
#define CrystalEngine_IShaderManager_h

#include <string>
#include "IDriver.h"

START_CRYSTALENGINE

class IShaderManager : public IInterface
{
public:
    //设置shader驱动
    virtual void setDriver(iDriver driver) = 0;
    
    //移除指定的shader(完整释放在所有使用到这个shader节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(iShaderProgram program) = 0;
    
    //移除指定的shader(完整释放在所有使用到这个shader节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(const std::string& name) = 0;
    
    //创建指定名称的shader，若shader已存在着返回无效指针
    virtual iShaderProgram create(const std::string& name) = 0;
    
    //查找指定名称的shader
    virtual iShaderProgram findByName(const std::string& name) = 0;
};

typedef AutoReleasePtr<IShaderManager> iShaderManager;

ENDED_CRYSTALENGINE

#endif
