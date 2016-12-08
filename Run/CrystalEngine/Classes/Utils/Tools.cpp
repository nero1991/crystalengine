//
//  Math.cpp
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include <math.h>
#include "Tools.h"
#include "Printer.h"

START_CRYSTALENGINE

//////////// Color

Color::Color() :
    red(0.0f),
    green(0.0f),
    blue(0.0f),
    alpha(0.0f)
{
    
}

Color::Color(CEfloat r,CEfloat g,CEfloat b,CEfloat a) :
    red(r),
    green(g),
    blue(b),
    alpha(a)
{
    
}

//////////// Martix4x4

Martix4x4::Martix4x4()
{
    for (CEfloat& data : m_data) {
        data = CEfloat();
    }
}

Martix4x4::Martix4x4(const Martix4x4& right)
{
    self = right;
}

CEfloat* Martix4x4::data()
{
    return m_data;
}

Martix4x4& Martix4x4::operator=  (const Martix4x4& right)
{
    for (CEsizei index = 0; index < MARTIX_ELEMENT_COUNT; ++index) {
        m_data[index] = right.m_data[index];
    }
    return self;
}

Martix4x4& Martix4x4::operator*= (const Martix4x4& right)
{
    for (CEsizei row = 0; row < 4; ++row) {
        for (CEsizei column = 0; column < 4; ++column) {
            self[row][column] = multiplyBy(right, row, column);
        }
    }
    return self;
}

Martix4x4  Martix4x4::operator*  (const Martix4x4& right) const
{
    Martix4x4 result = self;
    return result *= right;
}

CEfloat* Martix4x4::operator[] (const size_t index)
{
    ENGINE_ASSERT(0 <= index && index < 4, "out of range");
    return &m_data[index * 4];
}

const CEfloat* Martix4x4::operator[] (const size_t index) const
{
    ENGINE_ASSERT(0 <= index && index < 4, "out of range");
    return &m_data[index * 4];
}

CEfloat Martix4x4::multiplyBy(const Martix4x4& right,CEsizei row,CEsizei column)
{
    return self[row][0] * right[0][column] +
           self[row][1] * right[1][column] +
           self[row][2] * right[2][column] +
           self[row][3] * right[3][column];
}

//////////////////////////// Position ////////////////////

Position::Position() :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
    
}

Position::Position(const Position& right)
{
    self = right;
}

Position::operator Martix4x4() const
{
    Martix4x4 result;
    result[0][0] = 1.0f;result[0][1] = 0.0f;result[0][2] = 0.0f;result[0][3] = 0.0f;
    result[1][0] = 0.0f;result[1][1] = 1.0f;result[1][2] = 0.0f;result[1][3] = 0.0f;
    result[2][0] = 0.0f;result[2][1] = 0.0f;result[2][2] = 1.0f;result[2][3] = 0.0f;
    result[3][0] =    x;result[3][1] =    y;result[3][2] =    z;result[3][3] = 1.0f;
    return result;
}

Position& Position::operator =(const Position& right)
{
    x = right.x;
    y = right.y;
    z = right.z;
    return self;
}

//////////////////////////// Rotation ////////////////////

Rotation::Rotation() :
m_rotationX(0.0f),
m_rotationY(0.0f),
m_rotationZ(0.0f)
{
    updateMatrix();
}

Rotation::Rotation(const Rotation& right)
{
    self = right;
}

Rotation::operator Martix4x4() const
{
    return m_rotationMartix;
}

Rotation& Rotation::operator = (const Rotation& right)
{
    m_rotationX = right.m_rotationX;
    m_rotationY = right.m_rotationY;
    m_rotationZ = right.m_rotationZ;
    m_rotationMartix = right.m_rotationMartix;
    return self;
}

void Rotation::setRotationX(CEfloat angle)
{
    m_rotationX = angle;
    updateMatrix();
}

void Rotation::setRotationY(CEfloat angle)
{
    m_rotationY = angle;
    updateMatrix();
}

void Rotation::setRotationZ(CEfloat angle)
{
    m_rotationZ = angle;
    updateMatrix();
}

CEfloat Rotation::getRotationX() const
{
    return m_rotationX;
}

CEfloat Rotation::getRotationY() const
{
    return m_rotationY;
}

CEfloat Rotation::getRotationZ() const
{
    return m_rotationZ;
}

void Rotation::updateMatrix()
{
    Martix4x4 x,y,z;
    CEfloat cos = 0,sin = 0.0f;
    cos = cosf(m_rotationX);sin = sinf(m_rotationX);
    x[0][0] = 1.0f;x[0][1] = 0.0f;x[0][2] = 0.0f;x[0][3] = 0.0f;
    x[1][0] = 0.0f;x[1][1] =  cos;x[1][2] =  sin;x[1][3] = 0.0f;
    x[2][0] = 0.0f;x[2][1] = -sin;x[2][2] =  cos;x[2][3] = 0.0f;
    x[3][0] = 0.0f;x[3][1] = 0.0f;x[3][2] = 0.0f;x[3][3] = 1.0f;
    
    cos = cosf(m_rotationY);sin = sinf(m_rotationY);
    y[0][0] =  cos;y[0][1] = 0.0f;y[0][2] = -sin;y[0][3] = 0.0f;
    y[1][0] = 0.0f;y[1][1] = 1.0f;y[1][2] = 0.0f;y[1][3] = 0.0f;
    y[2][0] =  sin;y[2][1] = 0.0f;y[2][2] =  cos;y[2][3] = 0.0f;
    y[3][0] = 0.0f;y[3][1] = 0.0f;y[3][2] = 0.0f;y[3][3] = 1.0f;
    
    cos = cosf(m_rotationZ);sin = sinf(m_rotationZ);
    z[0][0] =  cos;z[0][1] =  sin;z[0][2] = 0.0f;z[0][3] = 0.0f;
    z[1][0] = -sin;z[1][1] =  cos;z[1][2] = 0.0f;z[1][3] = 0.0f;
    z[2][0] = 0.0f;z[2][1] = 0.0f;z[2][2] = 1.0f;z[2][3] = 0.0f;
    z[3][0] = 0.0f;z[3][1] = 0.0f;z[3][2] = 0.0f;z[3][3] = 1.0f;
    m_rotationMartix = x * y * z;
}

//////////// Math Helper

iColor Math::MakeColor(CEfloat r,CEfloat g,CEfloat b,CEfloat a)
{
    return new Color(r,g,b,a);
}

ENDED_CRYSTALENGINE