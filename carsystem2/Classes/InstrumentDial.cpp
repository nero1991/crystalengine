//
//  InstrumentDial.cpp
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#include "InstrumentDial.h"
#include "Instrument.h"

USING_NS_CC;

InstrumentDial::InstrumentDial() :
_minValue(0.0f),
_maxValue(0.0f),
_currentValue(0.0f)
{
    
}

bool InstrumentDial::init()
{
    bool result = Node::init();
    reset();
    scheduleUpdate();
    return result;
}

void InstrumentDial::onEnter()
{
    Node::onEnter();
}

void InstrumentDial::update(float delta)
{
    auto lab = dynamic_cast<Label*>(getChildByTag(TAG_VALUELAB));
    auto instrument = getChildByTag(TAG_INSTRUMENT);
    if (nullptr != lab && nullptr != instrument) {
        auto string = StringUtils::format("%d",(int)_currentValue);
        lab->setTextColor(Color4B::WHITE);
        lab->setString(string);
        
        lab->setPosition(Vec2(0,
                              instrument->getContentSize().height / -12.0f));
    }
}

//获取显示属性
const Size InstrumentDial::getInstrumentSize() const
{
    return getChildByTag(TAG_INSTRUMENT)->getContentSize();
}

const Vec2 InstrumentDial::getInstrumentPosition() const
{
    return getPosition();
}

//显示属性设置

void InstrumentDial::setValue(const float value)
{
    auto instrument = dynamic_cast<Instrument*>(getChildByTag(TAG_INSTRUMENT));
    if (nullptr != instrument && _minValue <= value && value <= _maxValue) {
        _currentValue = value;
        instrument->setFirstCircle(_currentValue / (_maxValue - _minValue));
    }
}

void InstrumentDial::setValueRange(const float min,const float max)
{
    _minValue = min;
    _maxValue = max;
}

void InstrumentDial::setInstrumentSize(const Size& size)
{
    auto instrument = getChildByTag(TAG_INSTRUMENT);
    instrument->setContentSize(size);
}

void InstrumentDial::setInstrumentPosition(const Vec2& position)
{
    setPosition(position);
}

void InstrumentDial::reset()
{
    createValueLab();
    createInstrument();
}

void InstrumentDial::createValueLab()
{
    removeChildByTag(TAG_VALUELAB);
    auto lab = Label::createWithTTF("N/A", "fonts/arial.ttf", 40);
    lab->ignoreAnchorPointForPosition(false);
    lab->setAnchorPoint(Vec2(0.5f, 1.0f));
    addChild(lab, TAG_VALUELAB, TAG_VALUELAB);
}

void InstrumentDial::createInstrument()
{
    removeChildByTag(TAG_INSTRUMENT);
    auto dial = Instrument::create();
    dial->setAnchorPoint(Vec2(0.5f,0.5f));
    dial->ignoreAnchorPointForPosition(false);
    addChild(dial,TAG_INSTRUMENT,TAG_INSTRUMENT);
}