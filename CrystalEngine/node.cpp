//
//  node.cpp
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "node.h"

START_CE_SPACE

Node::Node() : _tag(int())
{
    
}

Node::~Node()
{
    
}

bool Node::init()
{
    return true;
}

bool Node::addChild(autoNode child)
{
    return addChild(child, _children.rbegin()->first + 1);
}

bool Node::addChild(autoNode child,int tag)
{
    bool result = false;
    if (_children.count(tag) == 0) {
        child->settag(tag);
        _children.insert(std::make_pair(child->tag(), child));
    } else {
        ERROR_LOG("child %d is already added", tag);
    }
    return result;
}

bool Node::removeChild(autoNode child)
{
    if (child.isNull()) {
        return false;
    } else {
        return removeChildByTag(child->tag());
    }
}

bool Node::removeChildByTag(const int tag)
{
    bool result = false;
    auto findChild = _children.find(tag);
    if (_children.end() != findChild) {
        result = true;
        _children.erase(findChild);
    }
    return result;
}

Node::autoNode Node::parent()
{
    return _parent;
}

Node::autoNode Node::FindChildByTag(const int tag)
{
    autoNode result;
    auto getChild = _children.find(tag);
    if (_children.end() != getChild) {
        result = getChild->second;
    }
    return result;
}

ENDED_CE_SPACE