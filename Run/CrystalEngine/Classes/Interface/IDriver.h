//
//  IDriverFactory.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_IDriverFactory_h
#define CrystalEngine_IDriverFactory_h

#include "../Utils/Public.h"
#include "../Interface/IGraphics.h"
#include "../Interface/IShaderProgram.h"
#include "../Interface/IRenderCommand.h"

START_CRYSTALENGINE

class IDriver : public IInterface
{
public:
    
    //初始化Driver
    virtual void init() = 0;
    
    //执行绘制
    virtual void executeCommands() = 0;
    
    //获取背景清除色
    virtual iColor clearColor() const = 0;
        
    //创建一个图形对象
    virtual iGraphics createGraphics() = 0;
    
    //创建一个shader对象
    virtual iShaderProgram createShaderProgram() = 0;
    
    //添加一个绘制命令
    virtual void addCommand(iRenderCommand command) = 0;
    
    //设置背景清除色
    virtual void setClearColor(CEfloat r,CEfloat g,CEfloat b,CEfloat a) = 0;
};

typedef AutoReleasePtr<IDriver> iDriver;

ENDED_CRYSTALENGINE

#endif
