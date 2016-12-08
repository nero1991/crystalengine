//
//  Frame.cpp
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#include "Frame.h"

USING_NS_CC;

const std::string Frame::FrameShaderName = "FrameShader";

Frame::Frame() :
_program(nullptr),
_maxR(0.0f),
_minR(0.0f),
_startAngle(0.0f),
_endAngle(0.0f),
_lineNumber(0.0f)
{
    loadShader();
}

void Frame::loadShader()
{
    if (nullptr == GLProgramCache::getInstance()->getGLProgram(FrameShaderName)) {
        GLProgram* program = GLProgram::createWithFilenames("shader/frame.vsh",
                                                            "shader/frame.fsh");
        
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION,
                                    GLProgram::VERTEX_ATTRIB_POSITION);
        program->link();
        program->updateUniforms();
        GLProgramCache::getInstance()->addGLProgram(program, FrameShaderName);
    }
}

GLProgram* Frame::getProgram()
{
    return _program;
}

void Frame::set(const float startAngle,const float endAngle,const float maxR,const float minR)
{
    _startAngle = startAngle;
    _endAngle   = endAngle;
    _maxR = maxR;
    _minR = minR;
}

void Frame::draw(cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform)
{
    //绘制 弧形
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(FrameShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _arcVertices.data());
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_LINE_STRIP, 0, (GLint)_arcVertices.size());
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_arcVertices.size());
    }
    
    //绘制 刻度
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(FrameShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _lineVertices.data());
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_LINES, 0, (GLint)_lineVertices.size());
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_lineVertices.size());
    }
}

void Frame::resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z)
{
    //弧形线顶点
    _arcVertices.clear();
    for (auto angle = _startAngle;angle < _endAngle;angle += M_PI / 180.0f) {
        Vec4 point(cos(angle) * _maxR + anPoint.x * size.width, sin(angle) * _maxR + anPoint.y * size.height, z,1.0f);
        transform.transformVector(&point);
        _arcVertices.push_back(Vec3(point.x,point.y,point.z));
    }
    for (auto angle = _endAngle;angle > _startAngle;angle -= M_PI / 180.0f) {
        Vec4 point(cos(angle) * _minR + anPoint.x * size.width, sin(angle) * _minR + anPoint.y * size.height, z,1.0f);
        transform.transformVector(&point);
        _arcVertices.push_back(Vec3(point.x,point.y,point.z));
    }
    //刻度尺顶点
    _lineVertices.clear();
    for (auto angle = _startAngle; angle < _endAngle; angle += (_endAngle - _startAngle) / _lineNumber) {
        float x = cos(angle),y = sin(angle);
        Vec4 upper(x * _maxR + anPoint.x * size.width,y * _maxR + anPoint.y * size.height,z,1.0f);
        transform.transformVector(&upper);
        _lineVertices.push_back(Vec3(upper.x,upper.y,upper.z));
        
        Vec4 down(x * _minR + anPoint.x * size.width,y * _minR + anPoint.y * size.height,z,1.0f);
        transform.transformVector(&down);
        _lineVertices.push_back(Vec3(down.x,down.y,down.z));
    }
}