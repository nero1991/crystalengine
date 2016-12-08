//
//  log.h
//  CrystalEngine
//
//  Created by Nero on 8/18/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__log__
#define __CrystalEngine__log__

#include "marcos.h"

START_CE_SPACE

class log
{
public:
    STATIC_CLASS(log);
    
    static void error(const char* msg,...);
    static void print(const char* msg,...);
};

//TODO::error write to file
#ifdef DEBUG
#define DEBUG_LOG(msg,args...) log::print(msg,##args)
#define ERROR_LOG(msg,args...) log::error(msg,##args)
#else
#define DEBUG_LOG(msg,args...)
#define ERROR_LOG(msg,args...) log::error(msg,##args)
#endif

ENDED_CE_SPACE

#endif /* defined(__CrystalEngine__log__) */
