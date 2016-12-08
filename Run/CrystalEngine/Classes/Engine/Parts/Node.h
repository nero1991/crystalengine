//
//  Node.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Node__
#define __CrystalEngine__Node__

#include "INode.h"

START_CRYSTALENGINE

class Node : public INode
{
public:
    Node();
    virtual ~Node();
    
    //获取和更改坐标
    virtual CEfloat& x() override;
    virtual CEfloat& y() override;
    virtual CEfloat& z() override;
    
    virtual CEfloat rotationX() const override;
    virtual CEfloat rotationY() const override;
    virtual CEfloat rotationZ() const override;
    
    virtual void setRotationX(const CEfloat x) override;
    virtual void setRotationY(const CEfloat y) override;
    virtual void setRotationZ(const CEfloat z) override;
    
    //获取节点标记
    virtual CEsizei tag() const override;
    
    //设置节点标记
    virtual void setTag(const CEsizei tag) override;
    
    //获取父节点
    virtual iNode& parent() override;
    
    //设置父节点
    virtual void setParent(iNode parent) override;
    
    //获取所有的子节点
    virtual Childen& childen() override;
    
    //获取子节点
    virtual iNode child(const CEsizei tag) override;
    
    //从父节点移除自己
    virtual void remove() override;
    
    //移除子节点
    virtual bool removeChild(iNode child) override;
    
    //设置节点绘制模式
    virtual void setDrawType(const ENUM_DRIVER_DRAW_TYPE type) override;
        
    //添加子节点
    virtual void addChild(iNode child,const CEsizei tag = nops) override;
    
    //访问节点
    virtual void visit(iDriver driver,const Martix4x4& modelViewMartix) override;
    
    //初始化绘制数据
    virtual void init(iRenderCommand command,iShaderProgram program,iGraphics graphics) override;
private:
    CEsizei m_tag;
    iNode m_parent;
    Childen m_childen;
    
    iGraphics m_graphics;
    iShaderProgram m_program;
    iRenderCommand m_command;
    ENUM_DRIVER_DRAW_TYPE m_type;
    
    Position m_position;
    Rotation m_rotation;
};

ENDED_CRYSTALENGINE


#endif /* defined(__CrystalEngine__Node__) */
