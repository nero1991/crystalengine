//
//  Memory.h
//  CrystalEngine
//
//  Created by Nero on 4/3/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#ifndef CrystalEngine_Memory_h
#define CrystalEngine_Memory_h

#include "Marco.h"
#include <utility>

START_CRYSTALENGINE

//自动释放指针
template <typename _Interface>
class AutoReleasePtr
{
    typedef _Interface* TypePtr;
public:
    
    AutoReleasePtr() : m_ptr(nullptr)
    {
        
    }
    
    ~AutoReleasePtr()
    {
        clear();
    }
    
    AutoReleasePtr(AutoReleasePtr&& right) : AutoReleasePtr()
    {
        self = std::move(right);
    }
    
    AutoReleasePtr(const AutoReleasePtr& right) : AutoReleasePtr()
    {
        self = right;
    }
    
    AutoReleasePtr(TypePtr ptr) : AutoReleasePtr()
    {
        keepPtr(ptr);
    }
    
    inline void clear()
    {
        keepPtr(nullptr);
    }
    
    inline TypePtr operator ->()
    {
        return m_ptr;
    }
    
    inline bool isValid() const
    {
        return nullptr != m_ptr;
    }
    
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;
    
    TypePtr operator *()
    {
        return m_ptr;
    }
    
    void operator =(AutoReleasePtr&& right)
    {
        keepPtr(right.m_ptr);
        right.keepPtr(nullptr);
    }
    
    void operator =(const AutoReleasePtr& right)
    {
        keepPtr(right.m_ptr);
    }
    
    bool operator == (const AutoReleasePtr& right) const
    {
        return m_ptr == right.m_ptr;
    }
    
private:
    
    void keepPtr(TypePtr ptr)
    {
        if (nullptr != ptr) {
            ptr->retain();
        }
        if (nullptr != m_ptr) {
            m_ptr->release();
        }
        m_ptr = ptr;
    }
    
    TypePtr m_ptr;
};

ENDED_CRYSTALENGINE

#endif
