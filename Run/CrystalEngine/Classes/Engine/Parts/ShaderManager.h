//
//  ShaderManager.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__ShaderManager__
#define __CrystalEngine__ShaderManager__

#include <map>
#include "IShaderManager.h"

START_CRYSTALENGINE

class ShaderManager : public IShaderManager
{
    typedef std::map<std::string, iShaderProgram> Programes;
    typedef Programes::iterator Program;
public:
    //设置shader驱动
    virtual void setDriver(iDriver driver) override;
    
    //移除指定的shader(完整释放在所有使用到这个shader节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(iShaderProgram program) override;
    
    //移除指定的shader(完整释放在所有使用到这个shader节点释放之后)
    //这里仅仅是移除管理
    virtual bool remove(const std::string& name) override;
    
    //创建指定名称的shader，若shader已存在着返回无效指针
    virtual iShaderProgram create(const std::string& name) override;
    
    //查找指定名称的shader
    virtual iShaderProgram findByName(const std::string& name) override;
private:
    iDriver m_driver;
    Programes m_programes;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__ShaderManager__) */
