//
//  node.h
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__node__
#define __CrystalEngine__node__

#include "object.h"
#include <map>

START_CE_SPACE

class Node : public Object
{
    AUTO_REFERENCE(Node);
    typedef std::map<int, autoNode> Children;
public:
    Node();
   ~Node();
    
    virtual bool init() override;
    
    bool addChild(autoNode child);
    
    bool addChild(autoNode child,int tag);
    
    bool removeChild(autoNode child);
    
    bool removeChildByTag(const int tag);
    
    autoNode parent();
    
    autoNode FindChildByTag(const int tag);
private:
    autoNode _parent;
    Children _children;
    PROPERTY_READWRITE(int, tag);
};

ENDED_CE_SPACE

#endif /* defined(__CrystalEngine__node__) */
