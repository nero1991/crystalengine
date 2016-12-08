//
//  PointerLayer.cpp
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#include "PointerLayer.h"
USING_NS_CC;

PointerLayer::PointerLayer()
{
    
}

void PointerLayer::reflush()
{
    
}

bool PointerLayer::init()
{
    bool result = LayerColor::init();
    _pointer.loadShader();
    return result;
}

void PointerLayer::onEnter()
{
    setColor(Color3B(0, 255, 0));
    setOpacity(255);
    LayerColor::onEnter();
}

void PointerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(PointerLayer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void PointerLayer::onDraw(const cocos2d::Mat4& transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins();
    reflush();
    _pointer.resize(getAnchorPoint(), getContentSize(), transform, getLocalZOrder());
    _pointer.draw( _blendFunc, _modelViewTransform);
}