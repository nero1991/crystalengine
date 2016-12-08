//
//  Printer.cpp
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#include "Printer.h"
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

START_CRYSTALENGINE

void Printer::crash(bool e,const CEchar* file,CEint line)
{
    if (!e) {
        print("engine assert at file %s line %d",file,line);
        assert(e);
    }
}

void Printer::print(const CEchar* str,const CEchar* file,CEint line,...)
{
    va_list params;
    va_start(params, line);
    printf("engine log at file %s line %d\r\n",file,line);
    vprintf(str, params);
    printf("\r\n");
}

ENDED_CRYSTALENGINE