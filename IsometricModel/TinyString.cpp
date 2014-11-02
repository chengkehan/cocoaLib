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

bool TinyString::initTinyMemory()
{
    if (!TinyString::tinyMemory.isInitialized())
    {
        return TinyString::tinyMemory.init(4);
    }
    return true;
}

/* PUBLIC */

TinyString::TinyString() :
    handle(nullptr)
{
    TinyString::initTinyMemory();
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
    if (str == nullptr)
    {
        releaseHandle();
        return *this;
    }
    size_t strLen = strlen(str);
    if (str == 0)
    {
        TinyString_Handle* newHandle = (TinyString_Handle*)TinyString::tinyMemory.allocateMemory(sizeof(TinyString_Handle));
        // Allocate memory fail
        if (newHandle == nullptr)
        {
            return *this;
        }
        this->handle = newHandle;
        this->handle->str = nullptr;
        this->handle->refCount = 0;
        return *this;
    }
    char* newStr = (char*)TinyString::tinyMemory.allocateMemory(strLen + 1);
    // Allocate memory fail
    if (newStr == nullptr)
    {
        return *this;
    }
    this->handle->str = newStr;
    memcpy(this->handle->str, str, strLen);
    this->handle->str[strLen] = '\0';
    return *this;
}

bool TinyString::operator==(const TinyString &str)
{
    if (this == &str)
    {
        return true;
    }
    if (this->isNull() && str.isNull())
    {
        return true;
    }
    if (this->isEmpty() && str.isEmpty())
    {
        return true;
    }
    
    const char* str0 =
        this->handle == nullptr ? nullptr :
        this->handle->str == nullptr ? nullptr : this->handle->str;
    const char* str1 =
        str.handle == nullptr ? nullptr :
        str.handle->str == nullptr ? nullptr : str.handle->str;
    if (str0 == nullptr || str1 == nullptr)
    {
        return false;
    }
    else
    {
        return strcmp(str0, str1) == 0;
    }
}

bool TinyString::operator==(const char *str)
{
    if (this->isNull() && str == nullptr)
    {
        return true;
    }
    if (this->isEmpty() && (str != nullptr && strlen(str) == 0))
    {
        return true;
    }
    const char* str0 =
        this->handle == nullptr ? nullptr :
        this->handle->str == nullptr ? nullptr : this->handle->str;
    const char* str1 = str;
    if (str0 == nullptr || str1 == nullptr)
    {
        return false;
    }
    else
    {
        return strcmp(str0, str1) == 0;
    }

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
