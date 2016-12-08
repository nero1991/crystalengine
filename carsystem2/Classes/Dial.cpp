//
//  Dial.cpp
//  carsystem
//
//  Created by Nero on 8/4/15.
//
//

#include "Dial.h"
USING_NS_CC;

const std::string Dial::DialShaderName = "DialShader";
const std::string Dial::BGShaderName = "BGShader";


const float Dial::firstCirlceAngle = (4.0f / 3.0f) * M_PI;
const float Dial::secondCirlcerAngle = (8.0f / 18.0f) * M_PI;

enum BIND_POSITION
{
    BIND_POSITION_START = GLProgram::VERTEX_ATTRIB_TEX_COORDS,
    BIND_POSITION_FULLR,
    BIND_POSITION_ORIGIN,
    BINF_POSITION_DISCARDR,
};

Dial::Dial() :
_firstCirlceShowPercent(1.0f),
_secondCirlceShowPercent(1.0f),
_discardR(0.85f)
{
    
}

void Dial::loadShader()
{
    if (nullptr == GLProgramCache::getInstance()->getGLProgram(DialShaderName)) {
        GLProgram* program = GLProgram::createWithFilenames("shader/dial.vsh",
                                                            "shader/dial.fsh");
        
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION,
                                    GLProgram::VERTEX_ATTRIB_POSITION);
        program->bindAttribLocation("a_fullR", BIND_POSITION_FULLR);
        program->bindAttribLocation("a_cirlceOrigin",BIND_POSITION_ORIGIN);
        program->bindAttribLocation("a_discardR", BINF_POSITION_DISCARDR);
        program->link();
        program->updateUniforms();
        GLProgramCache::getInstance()->addGLProgram(program, DialShaderName);
    }
    
    if (nullptr == GLProgramCache::getInstance()->getGLProgram(BGShaderName)) {
        GLProgram* program = GLProgram::createWithFilenames("shader/background.vsh",
                                                            "shader/background.fsh");
        
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION,
                                    GLProgram::VERTEX_ATTRIB_POSITION);
        program->link();
        program->updateUniforms();
        GLProgramCache::getInstance()->addGLProgram(program, BGShaderName);
    }
}

float Dial::getFirstCircleRotateAngle() const
{
    return 90.0f -
    CC_RADIANS_TO_DEGREES((firstCirlceAngle - M_PI) * 0.5f + M_PI - _firstCirlceShowPercent * firstCirlceAngle);
}

GLProgram* Dial::getProgram()
{
    return GLProgramCache::getInstance()->getGLProgram(DialShaderName);
}

void Dial::resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z)
{
    Vec4 origin(anPoint.x * size.width,anPoint.y * size.height,z,1.0f);
    transform.transformVector(&origin);
    const float r = size.width > size.height ? size.height / 2.0f : size.width / 2.0f;
    
    {
        _firstCircularVertices.clear();
        const float startAngle = (firstCirlceAngle - M_PI) / 2.0f + M_PI;
        const float endAngle = (startAngle - M_PI) * -1.0f;
        _firstCircularVertices.push_back(Vec3(origin.x,origin.y,origin.z));
        for (float angle = startAngle;angle > endAngle;angle -= M_PI / 720.0f) {
            Vec4 point(cos(angle) * r + anPoint.x * size.width, sin(angle) * r + anPoint.y * size.height, z,1.0f);
            transform.transformVector(&point);
            _firstCircularVertices.push_back(Vec3(point.x,point.y,point.z));
        }
        _firstFram.setLineNumber(28.0f);
        _firstFram.set(endAngle,startAngle , r, r * _discardR);
        _firstFram.resize(anPoint, size, transform, z);
    }
    
    {
        _secondCircularVertices.clear();
        const float startAngle = M_PI + ((M_PI - secondCirlcerAngle) / 2.0f);
        const float endAngle = secondCirlcerAngle + startAngle;
        _secondCircularVertices.push_back(Vec3(origin.x,origin.y,origin.z));
        for (float angle = startAngle;angle < endAngle;angle += M_PI / 720.0f) {
            Vec4 point(cos(angle) * r + anPoint.x * size.width, sin(angle) * r + anPoint.y * size.height, z,1.0f);
            transform.transformVector(&point);
            _secondCircularVertices.push_back(Vec3(point.x,point.y,point.z));
        }
        _secondFram.setLineNumber(6.0f);
        _secondFram.set(startAngle, endAngle, r, r * _discardR);
        _secondFram.resize(anPoint, size, transform, z);
    }
    {
        _backgroundVertices.clear();
        for (float angle = 0.0f;angle < M_PI * 2.0f;angle += M_PI / 90.0f) {
            Vec4 point(cos(angle) * r + anPoint.x * size.width, sin(angle) * r + anPoint.y * size.height, z,1.0f);
            transform.transformVector(&point);
            _backgroundVertices.push_back(Vec3(point.x,point.y,point.z));
        }
    }
}

void Dial::draw(const float percent,cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform)
{
    //绘制 背景色
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(BGShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _backgroundVertices.data());
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)_backgroundVertices.size());
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_backgroundVertices.size());
    }

    //绘制 上弧形
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(DialShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                 GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _firstCircularVertices.data());
        
        glVertexAttrib3f(BIND_POSITION_ORIGIN,
                         _firstCircularVertices.front().x,
                         _firstCircularVertices.front().y,
                         _firstCircularVertices.front().z);
    
        glVertexAttrib1f(BINF_POSITION_DISCARDR, _discardR);
        
        glVertexAttrib1f(BIND_POSITION_FULLR, _firstCircularVertices.front().distance(_firstCircularVertices.back()));
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)_firstCircularVertices.size() * _firstCirlceShowPercent);
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_firstCircularVertices.size() * _firstCirlceShowPercent);
    }
    
    //绘制 下弧形
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(DialShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _secondCircularVertices.data());
        
        glVertexAttrib3f(BIND_POSITION_ORIGIN,
                         _secondCircularVertices.front().x,
                         _secondCircularVertices.front().y,
                         _secondCircularVertices.front().z);
        
        glVertexAttrib1f(BINF_POSITION_DISCARDR, _discardR);
        
        glVertexAttrib1f(BIND_POSITION_FULLR, _secondCircularVertices.front().distance(_secondCircularVertices.back()));
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)_secondCircularVertices.size() * _secondCirlceShowPercent);
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_secondCircularVertices.size() * _secondCirlceShowPercent);
    }
    
    _firstFram.draw(blendFunc, transform);
    _secondFram.draw(blendFunc,transform);
}