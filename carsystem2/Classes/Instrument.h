//
//  Instrument.h
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#ifndef __carsystem__Instrument__
#define __carsystem__Instrument__

#include <cocos2d.h>
#include "Dial.h"

class Instrument : public cocos2d::LayerColor
{
    enum CHILD_TAG
    {
        TAG_BEGIN,
        TAG_POINTER,
    };
public:
    Instrument();
    CREATE_FUNC(Instrument);
    void reflush();
    
    inline void setFirstCircle(const float percent)
    {
        _dial.setFirstCirlceShowPercent(percent);
    }
    
    inline void setSecondCircle(const float percent)
    {
        _dial.setSecondCirlceShowPercent(percent);
    }
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void update(float delta) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
private:
    
    void initEventTouch();
    bool createPointerLayer();
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
    Dial _dial;
    
    float _showPercent;
    float _zOrderBefore;
    
    cocos2d::Vec2 _positionBefore;
    cocos2d::Vec2 _anchorPointBefore;
    cocos2d::Size _contentSizeBefore;
    
    cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__carsystem__Instrument__) */
