//
//  IRenderCommand.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_IRenderCommand_h
#define CrystalEngine_IRenderCommand_h

#include "../Utils/Public.h"
#include "../Interface/IGraphics.h"
#include "../Interface/IShaderProgram.h"

START_CRYSTALENGINE

class IRenderCommand : public IInterface
{
public:
    //执行绘制命令
    virtual void execute() = 0;
    
    //获取顶点绘制数量
    virtual CEsizei vertercisCount() = 0;
    
    //获取绘制图形
    virtual ENUM_DRIVER_DRAW_TYPE drawType() const = 0;
    
    //设置绘制图形类型
    virtual void setDrawType(const ENUM_DRIVER_DRAW_TYPE type) = 0;
    
    //设置绘制资源
    virtual void init(iShaderProgram shader,iGraphics graphics) = 0;
    
    //添加mat4x4统一值
    virtual void addUniformMat4(const char* name,const Martix4x4& data) = 0;
};

typedef AutoReleasePtr<IRenderCommand> iRenderCommand;

ENDED_CRYSTALENGINE

#endif
