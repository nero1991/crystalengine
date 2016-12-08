//
//  Config.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CRYSTAL_ENGINE_TYPES_H
#define CRYSTAL_ENGINE_TYPES_H

//#ifdef USING_GL_ES
#include "Marco.h"
#include <OpenGLES/ES3/glext.h>

START_CRYSTALENGINE

typedef GLbitfield CEbitfield;
typedef GLboolean  CEboolean;
typedef GLbyte     CEbyte;
typedef GLclampf   CEclampf;
typedef GLenum     CEenum;
typedef GLfloat    CEfloat;
typedef GLint      CEint;
typedef GLshort    CEshort;
typedef GLsizei    CEsizei;
typedef GLubyte    CEubyte;
typedef GLuint     CEuint;
typedef GLushort   CEushort;
typedef GLvoid     CEvoid;

//#if !defined(GL_ES_VERSION_2_0)
typedef GLchar     CEchar;

typedef GLclampx   CEclampx;
typedef GLfixed    CEfixed;
//#if !defined(GL_ES_VERSION_3_0)
typedef GLhalf     CEhalf;

ENDED_CRYSTALENGINE

#endif
