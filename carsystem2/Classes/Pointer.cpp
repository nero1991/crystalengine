//
//  Pointer.cpp
//  carsystem
//
//  Created by Nero on 8/10/15.
//
//

#include "Pointer.h"
USING_NS_CC;

const std::string Pointer::PointerShaderName = "PointerShader";

Pointer::Pointer()
{
    loadShader();
}

void Pointer::loadShader()
{
    if (nullptr == GLProgramCache::getInstance()->getGLProgram(PointerShaderName)) {
        GLProgram* program = GLProgram::createWithFilenames("shader/frame.vsh",
                                                            "shader/frame.fsh");
        
        program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION,
                                    GLProgram::VERTEX_ATTRIB_POSITION);
        program->link();
        program->updateUniforms();
        GLProgramCache::getInstance()->addGLProgram(program, PointerShaderName);
    }
}

GLProgram* Pointer::getProgram()
{
    return _program;
}

void Pointer::draw(cocos2d::BlendFunc& blendFunc,const cocos2d::Mat4& transform)
{
    //绘制 三角形
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(PointerShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _triangleVertices.data());
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLES, 0, (GLint)_triangleVertices.size());
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_triangleVertices.size());
    }
    //绘制 弧形
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(PointerShaderName);
        if (nullptr != program ) {
            program->use();
            program->setUniformsForBuiltins();
        }
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION |
                                GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0,
                              _circleVertices.data());
        
        GL::blendFunc( blendFunc.src, blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)_circleVertices.size());
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_circleVertices.size());
    }
}

void Pointer::resize(const cocos2d::Vec2& anPoint,const cocos2d::Size& size,const cocos2d::Mat4& transform,const float z)
{
    const float r = size.width * 0.02f;
    _triangleVertices.clear();
    std::vector<Vec4> points;
    points.push_back(Vec4(size.width * 0.5f,size.height,z,1.0f));
    points.push_back(Vec4(size.width * 0.5f + r,size.height * 0.5f ,z,1.0f));
    points.push_back(Vec4(size.width * 0.5f - r,size.height * 0.5f,z,1.0f));
    for(auto it = points.begin();it != points.end();++it) {
        transform.transformVector(&*it);
        _triangleVertices.push_back(Vec3(it->x, it->y, it->z));
    }
    
    _circleVertices.clear();
    Vec4 origin(size.width * 0.5f,size.height *0.5f,z,1.0f);
    transform.transformVector(&origin);
    _circleVertices.push_back(Vec3(origin.x, origin.y, origin.z));
    for (auto angle = M_PI;angle < M_PI * 2.0f;angle += M_PI / 180.0f) {
        Vec4 point(cos(angle) * r + anPoint.x * size.width, sin(angle) * r + anPoint.y * size.height, z, 1.0f);
        transform.transformVector(&point);
        _circleVertices.push_back(Vec3(point.x, point.y, point.z));
    }
}