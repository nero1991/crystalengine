//
//  GLESDriver.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__GLESDriver__
#define __CrystalEngine__GLESDriver__

#include <stack>
#include "IDriver.h"

START_CRYSTALENGINE

class GLESDriver final : public IDriver
{
    typedef std::stack<iRenderCommand> CommandsStack;
public:
    
    //初始化Driver
    virtual void init();
    
    //执行绘制
    virtual void executeCommands() override;
    
    //获取背景清除色
    virtual iColor clearColor() const override;
    
    //创建一个图形对象
    virtual iGraphics createGraphics() override;
    
    //创建一个shader对象
    virtual iShaderProgram createShaderProgram() override;
    
    //添加一个绘制命令
    virtual void addCommand(iRenderCommand command) override;
    
    //设置背景清除色
    virtual void setClearColor(CEfloat r,CEfloat g,CEfloat b,CEfloat a) override;
    
private:
    iColor m_clearColor;
    CommandsStack m_commandsStack;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__GLESDriver__) */
