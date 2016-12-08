//
//  Pointer.h
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#ifndef __carsystem__Pointer__
#define __carsystem__Pointer__

#include <cocos2d.h>

class Pointer : public cocos2d::Ref
{
    static const std::string PointerShaderName;
public:
    Pointer();
    
    void loadShader();
    cocos2d::GLProgram* getProgram();
    
    void draw(cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform);
    
    void resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z);
private:
    cocos2d::GLProgram* _program;
    std::vector<cocos2d::Vec3> _triangleVertices;
    std::vector<cocos2d::Vec3> _circleVertices;
};


#endif /* defined(__carsystem__Pointer__) */
