//
//  GLESLog.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_GLESLog_h
#define CrystalEngine_GLESLog_h

#include "Public.h"

#ifdef  NDEBUG
#define GLES_ERRORLOG()
#else
#define GLES_ERRORLOG()       {                     \
        GLenum error = glGetError();                \
        if (GL_NO_ERROR != error) {                 \
            ENGINE_LOGOUT("GL error 0x%x",error);   \
        }                                           \
    }
#endif

#endif
