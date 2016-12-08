//
//  Math.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Math__
#define __CrystalEngine__Math__

#include "Object.h"
#include "Memory.h"

START_CRYSTALENGINE

//////////////////////////// Color ////////////////////////

class Color : public Object
{
public:
    Color();
    Color(CEfloat r,CEfloat g,CEfloat b,CEfloat a);
    
    CEfloat red;
    CEfloat green;
    CEfloat blue;
    CEfloat alpha;
};

typedef AutoReleasePtr<Color> iColor;

//////////////////////////// Martix ////////////////////////

class Martix4x4 : public Object
{
    static const CEsizei MARTIX_ELEMENT_COUNT = 16;
public:
    Martix4x4();
    Martix4x4(const Martix4x4& right);

    CEfloat* data();
    
    Martix4x4& operator=  (const Martix4x4& right);
    Martix4x4& operator*= (const Martix4x4& right);
    Martix4x4  operator*  (const Martix4x4& right) const;
    //取出矩阵的第index行
    //ex: [0][3] 为第0行的第3个数据
    CEfloat*         operator[] (const size_t index);
    const CEfloat*   operator[] (const size_t index) const;
private:
    CEfloat multiplyBy(const Martix4x4& right,CEsizei row,CEsizei column);
    
    CEfloat m_data[MARTIX_ELEMENT_COUNT];//4*4
};

//////////////////////////// Position ////////////////////

class Position : public Object
{
public:
    Position();
    Position(const Position& right);
    
    operator Martix4x4() const;
    Position& operator =(const Position& right);
    
    CEfloat x;    CEfloat y;    CEfloat z;
};

class Rotation : public Object
{
public:
    Rotation();
    Rotation(const Rotation& right);
    
    operator Martix4x4() const;
    Rotation& operator = (const Rotation& right);
    
    void setRotationX(CEfloat angle);
    void setRotationY(CEfloat angle);
    void setRotationZ(CEfloat angle);
    
    CEfloat getRotationX() const;
    CEfloat getRotationY() const;
    CEfloat getRotationZ() const;
private:
    void updateMatrix();
    
    CEfloat m_rotationX;
    CEfloat m_rotationY;
    CEfloat m_rotationZ;
    Martix4x4 m_rotationMartix;
};

//////////////////////////// Math ////////////////////////

class Math
{
public:
    STATIC_CLASS(Math)
    
    static iColor MakeColor(CEfloat r,CEfloat g,CEfloat b,CEfloat a);
};

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__Math__) */
