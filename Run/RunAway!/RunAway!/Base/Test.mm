//
//  Test.m
//  RunAway!
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "Test.h"
#import "Crystal.h"

USING_CRYSTALENGINE;

static iNode node;

@implementation Test

+ (void) init
{
    Director::sharedInstance().initDriver(ENUM_DRIVER_TYPE_GLES);
    Director::sharedInstance().prepare();
    Director::sharedInstance().getDriver()->setClearColor(1.0f,1.0f,1.0f,1.0f);
    iNode root = Director::sharedInstance().root();
    node = Director::sharedInstance().createNode(ENUM_NODE_TYPE_TEST);
    //node->setDrawType(ENUM_DRIVER_DRAW_TYPE_LINES);
    root->addChild(node,1);
}

+ (void) draw
{
    Director::sharedInstance().draw();
}

+(void) update
{
    static CEfloat move = 0.01f;
    //node->x() += move;
    if (node->x() < -1.0f) {
        node->x() = -1.0f;
        move *= -1.0f;
    } else if (node->x() > 1.0f) {
        node->x() = 1.0f;
        move *= -1.0f;
    }
    
    //node->setRotationX(node->rotationX() + 0.05f);
    //node->setRotationY(node->rotationY() + 0.05f);
    node->setRotationZ(node->rotationZ() + 0.05f);
}

@end
