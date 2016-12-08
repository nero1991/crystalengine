//
//  Printer.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef __CrystalEngine__Printer__
#define __CrystalEngine__Printer__

#include "Public.h"

START_CRYSTALENGINE

class Printer
{
public:
    STATIC_CLASS(Printer)
    static void crash(bool e,const CEchar* file,CEint line);
    static void print(const CEchar* str,const CEchar* file,CEint line,...);
};

#ifdef NDEBUG
#define ENGINE_ASSERT(_e,_msg)
#define ENGINE_LOGOUT(_str,var...)
#else
#define ENGINE_ASSERT(_e,_msg)     Printer::crash(_e,__FILE__,__LINE__);
#define ENGINE_LOGOUT(_str,var...) Printer::print(_str,__FILE__,__LINE__,##var);
#endif

ENDED_CRYSTALENGINE

#endif /* defined(__CrystalEngine__Printer__) */
