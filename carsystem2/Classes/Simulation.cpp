//
//  Simulation.cpp
//  carsystem
//
//  Created by Nero on 8/11/15.
//
//

#include "Simulation.h"
#include "InstrumentDial.h"

USING_NS_CC;

Simulation::Simulation() :
_speed(nullptr),
_rotate(nullptr),
_currentLv(1.0f),
_speedUp(false)
{
    
}

Simulation* Simulation::create(InstrumentDial* speed,InstrumentDial* rotate)
{
    if (nullptr != speed && nullptr != rotate) {
        auto sprite = Simulation::create();
        if (sprite && sprite->initWithFile("res/simulation.png"))
        {
            sprite->_speed = speed;
            sprite->_rotate = rotate;
            return sprite;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

bool Simulation::init()
{
    if (Sprite::init()) {
        scheduleUpdate();
        
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->onTouchBegan = [](Touch *touch, Event *event)
        {
            auto sprite = dynamic_cast<Simulation*>(event->getCurrentTarget());
            auto rect = Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height);
            if (rect.containsPoint(sprite->convertToNodeSpace(touch->getLocation()))) {
                sprite->_speedUp = true;
                return true;
            } else {
                return false;
            }
        };
        
        listener->onTouchMoved = [](Touch *touch, Event *event)
        {
        };
        
        listener->onTouchEnded = [](Touch *touch, Event *event)
        {
            auto sprite = dynamic_cast<Simulation*>(event->getCurrentTarget());
            sprite->_speedUp = false;
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        return true;
    } else {
        return false;
    }
    return Sprite::init();
}

void Simulation::update(float delta)
{
    if (_speedUp) {
        speedUp();
    } else {
        speedDown();
    }
}

void Simulation::speedUp()
{
    //提升后的转速
    float currentRotation = _rotate->getValue() + 27.64f + 8.9f * (_simulationLv.rbegin()->first - _currentLv);
    //提升后的速度
    float currentSpeed = currentRotation / _simulationLv[_currentLv];
    //计算下一个档位
    float nextLv = _simulationLv.count(_currentLv + 1.0f) != 0 ? _currentLv + 1.0f : _currentLv;
    
    //正常逻辑换挡
    if (currentRotation > 3500.0f && currentSpeed * _simulationLv[nextLv] > 800) {
        _currentLv = nextLv;
        currentRotation = currentSpeed * _simulationLv[nextLv];
    }
    _speed->setValue(currentSpeed);
    _rotate->setValue(currentRotation);
}

void Simulation::speedDown()
{
    //降低后的转速
    float currentRotation = _rotate->getValue() - 17.64f;
    if (currentRotation <= 0.0f) {
        currentRotation = 0.0f;
    }
    //降低后的速度
    float currentSpeed = currentRotation / _simulationLv[_currentLv];
    //计算下一个档位
    float beforeLv = _simulationLv.count(_currentLv - 1.0f) != 0 ? _currentLv - 1.0f : _currentLv;
    
    //正常逻辑换挡
    if (currentRotation < 1200.0f && currentSpeed * _simulationLv[beforeLv] > 800) {
        _currentLv = beforeLv;
        currentRotation = currentSpeed * _simulationLv[beforeLv];
    }
    _speed->setValue(currentSpeed);
    _rotate->setValue(currentRotation);
}

void Simulation::addSimulateLv(float lv,float ratio)
{
    _simulationLv[lv] = ratio;
}

void Simulation::setSimulateInfo(const float maxSpeed,const float maxRotate)
{
    if (nullptr != _speed) {
        _speed->setValue(0.0f);
        _speed->setValueRange(0.0f, maxSpeed);
    }
    if (nullptr != _rotate) {
        _rotate->setValue(0.0f);
        _rotate->setValueRange(0.0f, maxRotate);
    }
}
