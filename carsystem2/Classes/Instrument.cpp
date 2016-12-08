//
//  Instrument.cpp
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#include "Instrument.h"
#include "PointerLayer.h"

USING_NS_CC;

Instrument::Instrument() :
_showPercent(0.0f),
_zOrderBefore(0.0f)
{
    
}

bool Instrument::init()
{
    bool result = LayerColor::init();
    _dial.loadShader();
    //initEventTouch();
    scheduleUpdate();
    return result;
}

void Instrument::reflush()
{
//    if (getLocalZOrder() != _zOrderBefore || getAnchorPoint() != _anchorPointBefore ||
//        getPosition() != _positionBefore || !getContentSize().equals(_contentSizeBefore)) {
//        updateTransform();
    //由于cocos机制的不合理，必须每次在cpu计算变换后的坐标
        //_dial.setFirstCirlceShowPercent(0.8f);
        _dial.resize(getAnchorPoint(), getContentSize(), _modelViewTransform, getLocalZOrder());
//        
//        //reflush
//        _zOrderBefore = getLocalZOrder();
//        _positionBefore = getPosition();
//        _anchorPointBefore = getAnchorPoint();
//        _contentSizeBefore = getContentSize();
//    }
}

void Instrument::onEnter()
{
    setColor(Color3B(0, 255, 0));
    setOpacity(255);
    createPointerLayer();
    LayerColor::onEnter();
}

void Instrument::update(float delta)
{
    _dial.addFirstCirlceShowPercent(_showPercent);
    auto pointer = dynamic_cast<Node*>(getChildByTag(TAG_POINTER));
    if (nullptr != pointer) {
        pointer->setRotation(_dial.getFirstCircleRotateAngle());
    }
}

void Instrument::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    //LayerColor::draw(renderer, transform, flags);
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(Instrument::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Instrument::initEventTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch *touch, Event *event)
    {
        bool result = false;
        Rect rect(0,0,this->getContentSize().width,this->getContentSize().height);
        //if (rect.containsPoint(this->convertToNodeSpace(touch->getLocation()))) {
            this->_showPercent = 0.02f;
            result = true;
        //}
        return result;
    };
    
    listener->onTouchMoved = [this](Touch *touch, Event *event)
    {
    };
    
    listener->onTouchEnded = [this](Touch *touch, Event *event)
    {
        this->_showPercent = -0.01f;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Instrument::createPointerLayer()
{
    removeChildByTag(TAG_POINTER);
    auto pointerLayer = PointerLayer::create();
    pointerLayer->setContentSize(getContentSize());
    pointerLayer->ignoreAnchorPointForPosition(false);
    pointerLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
    pointerLayer->setPosition(Vec2(pointerLayer->getContentSize().width * 0.5f,
                                   pointerLayer->getContentSize().height * 0.5f));
    addChild(pointerLayer, 0, TAG_POINTER);
    return true;
}

void Instrument::onDraw(const cocos2d::Mat4& transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins();
    reflush();
    _dial.draw(1.0f, _blendFunc, _modelViewTransform);
}