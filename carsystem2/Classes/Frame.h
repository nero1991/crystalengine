//
//  Frame.h
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#ifndef __carsystem__Frame__
#define __carsystem__Frame__

#include <cocos2d.h>

class Frame : public cocos2d::Ref
{
    static const std::string FrameShaderName;
public:
    Frame();
    void loadShader();
    cocos2d::GLProgram* getProgram();
    
    inline void setLineNumber(const float number)
    {
        _lineNumber = number;
    }
    
    void set(const float startAngle,const float endAngle,const float maxR,const float minR);
    
    void draw(cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform);
    
    void resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z);
private:
    cocos2d::GLProgram* _program;
    float _startAngle;
    float _endAngle;
    float _maxR;
    float _minR;
    float _lineNumber;
    std::vector<cocos2d::Vec3> _arcVertices;
    std::vector<cocos2d::Vec3> _lineVertices;
};

#endif /* defined(__carsystem__Frame__) */
