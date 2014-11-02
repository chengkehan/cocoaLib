//
//  TinyString.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-10-20.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "TinyString.h"
#include "TinyMemory.h"

using namespace jcgame;

/* PRIVATE STATIC */

TinyMemory TinyString::tinyMemory;

/* PUBLIC */

TinyString::TinyString() :
    handle(nullptr)
{
    // Do nothing
}

TinyString::~TinyString()
{
    releaseHandle();
}

const TinyString& TinyString::operator=(const TinyString& str)
{
    if (this == &str)
    {
        return *this;
    }
    else
    {
        releaseHandle();
        this->handle = str.handle;
        if (this->isNullOrEmpty())
        {
            return *this;
        }
        ++this->handle->refCount;
        return *this;
    }
}

const TinyString& TinyString::operator=(const char *str)
{
    releaseHandle();
    if (str == nullptr)
    {
        return *this;
    }
    size_t strLen = strlen(str);
    if (str == 0)
    {
        this->handle = (TinyString_Handle*)TinyString::tinyMemory.allocateMemory(sizeof(TinyString_Handle));
        this->handle->str = nullptr;
        this->handle->refCount = 0;
        return *this;
    }
    this->handle->str = (char*)TinyString::tinyMemory.allocateMemory(strLen + 1);
    memcpy(this->handle->str, str, strLen);
    this->handle->str[strLen] = '\0';
    return *this;
}

bool TinyString::isNull() const
{
    return this->handle == nullptr;
}

bool TinyString::isEmpty() const
{
    return this->handle != nullptr && this->handle->str == nullptr;
}

bool TinyString::isNullOrEmpty() const
{
    return this->handle == nullptr || this->handle->str == nullptr;
}

/* PRIVATE */

bool TinyString::initTinyMemory()
{
    if (!TinyString::tinyMemory.isInitialized())
    {
        return TinyString::tinyMemory.init(4);
    }
    return true;
}

void TinyString::releaseHandle()
{
    if (this->handle == nullptr)
    {
        return;
    }
    
    if (this->handle->refCount > 0)
    {
        assert(this->handle->str != nullptr);
        --this->handle->refCount;
        if (this->handle->refCount == 0)
        {
            TinyString::tinyMemory.freeMemory(this->handle->str);
            this->handle->str = nullptr;
            TinyString::tinyMemory.freeMemory(this->handle);
        }
        this->handle = nullptr;
    }
}
