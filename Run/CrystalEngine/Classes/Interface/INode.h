//
//  INode.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_INode_h
#define CrystalEngine_INode_h

#include <vector>
#include "../Utils/Public.h"
#include "../Interface/IDriver.h"
#include "../Interface/IGraphics.h"
#include "../Interface/IShaderProgram.h"
#include "../Interface/IRenderCommand.h"

START_CRYSTALENGINE

class INode : public IInterface
{
public:
    typedef AutoReleasePtr<INode> iNode;

    typedef std::vector<iNode> Childen;
    typedef Childen::iterator  Child;
    
    //获取和更改坐标
    virtual CEfloat& x() = 0;
    virtual CEfloat& y() = 0;
    virtual CEfloat& z() = 0;
    
    virtual CEfloat rotationX() const = 0;
    virtual CEfloat rotationY() const = 0;
    virtual CEfloat rotationZ() const = 0;
    
    virtual void setRotationX(const CEfloat x) = 0;
    virtual void setRotationY(const CEfloat x) = 0;
    virtual void setRotationZ(const CEfloat x) = 0;

    
    //获取节点标记
    virtual CEsizei tag() const = 0;
    
    //设置节点标记
    virtual void setTag(const CEsizei tag) = 0;
    
    //获取父节点
    virtual iNode& parent() = 0;
    
    //设置父节点
    virtual void setParent(iNode parent) = 0;
    
    //获取所有的子节点
    virtual Childen& childen() = 0;
    
    //获取子节点
    virtual iNode child(const CEsizei tag) = 0;
    
    //从父节点移除自己
    virtual void remove() = 0;
    
    //移除子节点
    virtual bool removeChild(iNode child) = 0;
    
    //设置绘制模式
    virtual void setDrawType(const ENUM_DRIVER_DRAW_TYPE type) = 0;
        
    //添加子节点
    virtual void addChild(iNode child,const CEsizei tag = nops) = 0;
    
    //访问节点
    virtual void visit(iDriver driver,const Martix4x4& modelViewMartix) = 0;
    
    //初始化绘制数据
    virtual void init(iRenderCommand command,iShaderProgram program,iGraphics graphics) = 0;
};

typedef INode::iNode iNode;

ENDED_CRYSTALENGINE

#endif
