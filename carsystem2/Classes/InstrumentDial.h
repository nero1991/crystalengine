//
//  InstrumentDial.h
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#ifndef __carsystem__InstrumentDial__
#define __carsystem__InstrumentDial__

#include <cocos2d.h>

class InstrumentDial : public cocos2d::Node
{
    enum TAG_CHILD
    {
        TAG_START,
        TAG_INSTRUMENT,
        TAG_VALUELAB,
    };
public:
    InstrumentDial();
    
    CREATE_FUNC(InstrumentDial);
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void update(float delta) override;
    
    //获取显示属性
    const float getValue() const
    {
        return _currentValue;
    }
    
    const cocos2d::Size getInstrumentSize() const;
    
    const cocos2d::Vec2 getInstrumentPosition() const;
    
    //显示属性设置
    void setValue(const float value);
    
    void setValueRange(const float min,const float max);
    
    void setInstrumentSize(const cocos2d::Size& size);
    
    void setInstrumentPosition(const cocos2d::Vec2& position);
private:
    void reset();
    void createValueLab();
    void createInstrument();
    
    float _minValue;
    float _maxValue;
    float _currentValue;
};

#endif /* defined(__carsystem__InstrumentDial__) */
