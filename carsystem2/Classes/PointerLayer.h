//
//  PointerLayer.h
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#ifndef __carsystem__PointerLayer__
#define __carsystem__PointerLayer__

#include <cocos2d.h>
#include "Pointer.h"

class PointerLayer : public cocos2d::LayerColor
{
public:
    PointerLayer();
    CREATE_FUNC(PointerLayer);
    void reflush();
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
private:
    
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
    Pointer _pointer;
    
    cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__carsystem__PointerLayer__) */
