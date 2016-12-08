//
//  Node.cpp
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "Node.h"

START_CRYSTALENGINE

Node::Node() :
 m_tag(nops),
 m_type(ENUM_DRIVER_DRAW_TYPE_TRIANGLES)
{
}

Node::~Node()
{
    
}

CEfloat& Node::x()
{
    return m_position.x;
}

CEfloat& Node::y()
{
    return m_position.y;
}

CEfloat& Node::z()
{
    return m_position.z;
}

CEfloat Node::rotationX() const
{
    return m_rotation.getRotationX();
}

CEfloat Node::rotationY() const
{
    return m_rotation.getRotationY();
}

CEfloat Node::rotationZ() const
{
    return m_rotation.getRotationZ();
}

void Node::setRotationX(const CEfloat x)
{
    m_rotation.setRotationX(x);
}

void Node::setRotationY(const CEfloat y)
{
    m_rotation.setRotationY(y);
}

void Node::setRotationZ(const CEfloat z)
{
    m_rotation.setRotationZ(z);
}

CEsizei Node::tag() const
{
    return m_tag;
}

inline void Node::setTag(const CEsizei tag)
{
    m_tag = tag;
}

inline iNode& Node::parent()
{
    return m_parent;
}

inline void Node::setParent(iNode parent)
{
    if (m_parent.isValid()) {
        m_parent->removeChild(this);
    }
    if (parent.isValid()) {
        parent->addChild(this);
    }
}

inline Node::Childen& Node::childen()
{
    return m_childen;
}

iNode Node::child(const CEsizei tag)
{
    iNode child;
    for (iNode& find : m_childen) {
        if (find->tag() == tag) {
            child = find;
            break;
        }
    }
    return child;
}

inline void Node::remove()
{
    if (m_parent.isValid()) {
        m_parent->removeChild(this);
    }
}

bool Node::removeChild(iNode child)
{
    bool result = false;
    for (Child it = m_childen.begin(); m_childen.end() != it; ++it) {
        if (*it == child) {
            (*it)->parent().clear();
            m_childen.erase(it);
            result = true;
            break;
        }
    }
    return result;
}

inline void Node::addChild(iNode child,const CEsizei tag)
{
    if (child.isValid()) {
        child->setTag(tag);
        m_childen.push_back(child);
    }
}

inline void Node::setDrawType(const ENUM_DRIVER_DRAW_TYPE type)
{
    m_type = type;
}

void Node::visit(iDriver driver,const Martix4x4& modelViewMartix)
{
    if (driver.isValid()) {
        //visit child first
        Martix4x4 transformMat4 = modelViewMartix *
                                  static_cast<Martix4x4>(m_rotation) *
                                  static_cast<Martix4x4>(m_position);
        for (iNode& child : m_childen) {
            child->visit(driver,transformMat4);
        }
        if (m_command.isValid()) {
            //draw self
            m_command->setDrawType(m_type);
            m_command->init(m_program, m_graphics);
            m_command->addUniformMat4("transformMat4",
                                      transformMat4);
            driver->addCommand(m_command);
        }
    }
}


inline void Node::init(iRenderCommand command,iShaderProgram program,iGraphics graphics)
{
    m_command = command;
    m_program = program;
    m_graphics = graphics;
}

ENDED_CRYSTALENGINE