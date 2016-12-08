//
//  Graphics.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Graphics__
#define __CrystalEngine__Graphics__

#include "IGraphics.h"

START_CRYSTALENGINE

class Graphics final : public IGraphics
{
public:
    Graphics();
    virtual ~Graphics();
    
    //使用当前图形数据
    virtual bool use() override;
    
    //清除现有的图形数据
    virtual void clear() override;
    
    //初始化图形所有数据组的绑定点(vao)
    virtual void initGraphicsHandle() override;
    
    //初始化顶点位置数据的gpu缓冲
    virtual void initPositionHandle() override;
    
    //获取图形顶点数量
    virtual CEsizei getVertercisCount() const override;
    
    //设置坐标数据维度(默认为4维数据)
    virtual void setPositionDimension(CEint dimension) override;
    
    //重新分配gpu缓冲，并上传顶点位置数据
    //param @data : 顶点数据的内存地址
    //param @size : 缓冲区内存大小(字节数)
    virtual bool updatePositionData(const CEfloat* data,const CEsizei size) override;
    
    //绑定顶点特性到shader的指定位置
    virtual bool bindPositionAttribute(iShaderProgram shader,const CEchar* attributName) override;
private:
    //GraphicsVAO
    CEuint m_GraphicsVAO;
    //顶点数据保存缓冲
    CEint   m_dismension;
    CEuint  m_VertercisVBO;
    CEsizei m_VertercisCount;
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__Graphics__) */
