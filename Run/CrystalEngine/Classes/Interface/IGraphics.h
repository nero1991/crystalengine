//
//  IGraphics.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__IGraphics__
#define __CrystalEngine__IGraphics__

#include "../Utils/Public.h"
#include "../Interface/IShaderProgram.h"

START_CRYSTALENGINE

class IGraphics : public IInterface
{
public:
    //使用当前图形数据
    virtual bool use() = 0;
    
    //清除现有的图形数据
    virtual void clear() = 0;
    
    //初始化图形所有数据组的绑定点(vao)
    virtual void initGraphicsHandle() = 0;
    
    //初始化顶点位置数据的gpu缓冲
    virtual void initPositionHandle() = 0;
    
    //获取图形顶点数量
    virtual CEsizei getVertercisCount() const = 0;
    
    //设置坐标数据维度
    virtual void setPositionDimension(CEint dimension) = 0;
    
    //重新分配gpu缓冲，并上传顶点位置数据
    //param @data : 顶点数据的内存地址
    //param @size : 缓冲区内存大小(字节数)
    virtual bool updatePositionData(const CEfloat* data,const CEsizei size) = 0;
    
    //绑定顶点特性到shader的指定位置
    virtual bool bindPositionAttribute(iShaderProgram shader,const CEchar* attributName) = 0;
};

typedef AutoReleasePtr<IGraphics> iGraphics;

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__IGraphics__) */
