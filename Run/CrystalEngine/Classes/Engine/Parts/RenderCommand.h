//
//  RenderCommand.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__RenderCommand__
#define __CrystalEngine__RenderCommand__

#include <map>
#include <string>
#include "IRenderCommand.h"

START_CRYSTALENGINE

class RenderCommand : public IRenderCommand
{
    typedef std::map<std::string, Martix4x4> UniformMat4x4Map;
    typedef UniformMat4x4Map::iterator UniformMat4x4;
public:
    RenderCommand();
    virtual ~RenderCommand();
    
    //执行绘制命令
    virtual void execute() override;
    
    //获取顶点绘制数量
    virtual CEsizei vertercisCount() override;
    
    //获取绘制图形
    virtual ENUM_DRIVER_DRAW_TYPE drawType() const override;
    
    //设置绘制图形类型
    virtual void setDrawType(const ENUM_DRIVER_DRAW_TYPE type) override;
    
    //设置绘制资源
    virtual void init(iShaderProgram shader,iGraphics graphics) override;
    
    //添加mat4x4统一值
    virtual void addUniformMat4(const char* name,const Martix4x4& data) override;
protected:
    //上载所有的mat4统一值
    void uploadAllUniformMat4();
    
    iGraphics m_graphics;
    iShaderProgram m_shader;
    ENUM_DRIVER_DRAW_TYPE m_type;
    //shader data;
    UniformMat4x4Map m_uniformMat4x4Map;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__RenderCommand__) */
