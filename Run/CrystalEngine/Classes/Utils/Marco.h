//
//  Marco.h
//  CrystalEngine
//
//  Created by Nero on 4/1/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CRYSTAL_ENGINE_MARCO_H
#define CRYSTAL_ENGINE_MARCO_H

#ifdef CRYSTAL_NAMESPACE
#undef CRYSTAL_NAMESPACE
#endif

#define CRYSTAL_NAMESPACE crystal

#ifdef START_CRYSTALENGINE
#undef START_CRYSTALENGINE
#endif


#define START_CRYSTALENGINE namespace CRYSTAL_NAMESPACE {

#ifdef ENDED_CRYSTALENGINE
#undef ENDED_CRYSTALENGINE
#endif

#define ENDED_CRYSTALENGINE }

#ifdef USING_CRYSTALENGINE
#undef USING_CRYSTALENGINE
#endif

#define USING_CRYSTALENGINE using namespace CRYSTAL_NAMESPACE

#ifdef nops
#undef nops
#endif

#define nops 0

#ifdef self
#undef self
#endif

#define self (*this)

#ifdef STATIC_CLASS
#undef STATIC_CLASS
#endif

#define STATIC_CLASS(_class)                            \
        public:                                         \
        _class() = delete;                              \
       ~_class() = delete;                              \

#ifdef SINGLETON_INSTANCE
#undef SINGLETON_INSTANCE
#endif

#define SINGLETON_INSTANCE(_class)                      \
        public:                                         \
            inline static _class& sharedInstance()      \
            {                                           \
                static _class sharedInstance;           \
                return sharedInstance;                  \
            }                                           \
        void *operator new(size_t) = delete;            \
        void *operator new[](size_t) = delete;

#endif
