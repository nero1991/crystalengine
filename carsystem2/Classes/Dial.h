//
//  Dial.h
//  carsystem
//
//  Created by Nero on 8/4/15.
//
//

#ifndef __carsystem__Dial__
#define __carsystem__Dial__

#include <cocos2d.h>
#include "Frame.h"

class Dial : public cocos2d::Ref
{
    static const std::string DialShaderName;
    static const std::string BGShaderName;
    static const float firstCirlceAngle;
    static const float secondCirlcerAngle;
public:
    Dial();
    void loadShader();
    cocos2d::GLProgram* getProgram();
    
    float getFirstCircleRotateAngle() const;
    
    inline void addFirstCirlceShowPercent(const float percent)
    {
        auto final = _firstCirlceShowPercent + percent;
        if (final < 0.0f) {
            final = 0.0f;
        } else if (final > 1.0f) {
            final = 1.0f;
        }
        setFirstCirlceShowPercent(final);
    }
    
    inline void addSecindCirlceShowPercent(const float percent)
    {
        auto final = _secondCirlceShowPercent + percent;
        if (final < 0.0f) {
            final = 0.0f;
        } else if (final > 1.0f) {
            final = 1.0f;
        }
        setSecondCirlceShowPercent(final);
    }
    
    inline void setFirstCirlceShowPercent(const float percent)
    {
        if (0.0f <= percent && percent <= 1.0f) {
            _firstCirlceShowPercent = percent;
        }
    }
    
    inline void setSecondCirlceShowPercent(const float percent)
    {
        if (0.0f <= percent && percent <= 1.0f) {
            _secondCirlceShowPercent = percent;
        }

    }
    
    void draw(const float percent,cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform);
    
    void resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z);
private:
    Frame _firstFram;
    Frame _secondFram;
    float _discardR;
    cocos2d::GLProgram* _program;
    float _firstCirlceShowPercent;
    float _secondCirlceShowPercent;
    std::vector<cocos2d::Vec3> _backgroundVertices;
    std::vector<cocos2d::Vec3> _firstCircularVertices;
    std::vector<cocos2d::Vec3> _secondCircularVertices;
};


#endif /* defined(__carsystem__Dial__) */
