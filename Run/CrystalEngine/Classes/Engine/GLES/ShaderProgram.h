//
//  ShaderProgram.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__ShaderProgram__
#define __CrystalEngine__ShaderProgram__

#include <vector>
#include "IShaderProgram.h"

START_CRYSTALENGINE

class ShaderProgram final : public IShaderProgram
{
    typedef std::vector<CEuint> ShaderHandles;
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    
    //使用这个shader程序来渲染
    virtual bool use()   override;
    
    //链接所有已经编译的源码
    virtual void link()  override;
    
    //清除现有的shader程序
    virtual void clear() override;
    
    //编译制定的shader源码
    virtual bool build(ENUM_SHADER_TYPE type,const CEchar* source) override;
    
    //获取制定属性的位置
    virtual CEint getAttributeLoaction(const CEchar* attributeName) override;
    
    //上传Mat4x4统一值数据
    virtual void upLoadUniformMat4(const CEchar* uniformName,const CEfloat* data) override;
private:
    //打印链接信息
    void printLinkingLog();
    //打印编译信息
    void printCompileLog(CEuint handle);

    
    CEuint m_programHandle;
    ShaderHandles m_shaderHandles;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__ShaderProgram__) */
