//
//  Enum.h
//  CrystalEngine
//
//  Created by Nero on 4/2/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_Enum_h
#define CrystalEngine_Enum_h

#include "Marco.h"

START_CRYSTALENGINE

enum ENUM_NODE_TYPE
{
    ENUM_NODE_TYPE_START,
    ENUM_NODE_TYPE_EMPTY,
    ENUM_NODE_TYPE_TEST,
    ENUM_NODE_TYPE_END,
};

enum ENUM_SHADER_TYPE
{
    ENUM_SHADER_TYPE_START,
    ENUM_SHADER_TYPE_VERTEX,
    ENUM_SHADER_TYPE_FRAGMENT,
    ENUM_SHADER_TYPE_END,
};

enum ENUM_DRIVER_TYPE
{
    ENUM_DRIVER_TYPE_STRAT,
    ENUM_DRIVER_TYPE_GLES,
    ENUM_DRIVER_TYPE_END,
};

enum ENUM_DRIVER_DRAW_TYPE
{
    ENUM_DRIVER_DRAW_TYPE_START,
    ENUM_DRIVER_DRAW_TYPE_LINES,
    ENUM_DRIVER_DRAW_TYPE_POINTS,
    ENUM_DRIVER_DRAW_TYPE_TRIANGLES,
    ENUM_DRIVER_DRAW_TYPE_END,
};

ENDED_CRYSTALENGINE

#endif
