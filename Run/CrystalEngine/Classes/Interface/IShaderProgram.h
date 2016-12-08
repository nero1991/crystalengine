//
//  IShaderProgram.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_IShaderProgram_h
#define CrystalEngine_IShaderProgram_h

#include "../Utils/Public.h"

START_CRYSTALENGINE

class IShaderProgram : public IInterface
{
public:
    //使用这个shader程序来渲染
    virtual bool use()   = 0;
    
    //链接所有已经编译的源码
    virtual void link()  = 0;
    
    //清楚现有的shader程序
    virtual void clear() = 0;
    
    //编译制定的shader源码
    virtual bool build(ENUM_SHADER_TYPE type,const CEchar* source) = 0;
    
    //获取制定属性的位置
    virtual CEint getAttributeLoaction(const CEchar* attributeName) = 0;
    
    //上传Mat4x4统一值数据
    virtual void upLoadUniformMat4(const CEchar* uniformName,const CEfloat* data) = 0;
};

typedef AutoReleasePtr<IShaderProgram> iShaderProgram;

ENDED_CRYSTALENGINE

#endif
