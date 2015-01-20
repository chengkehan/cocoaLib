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

/* PUBLIC STATIC */

const char* TinyString::C_EMPTY_STRING = "\0";

const TinyString TinyString::EMPTY_STRING(TinyString::C_EMPTY_STRING);

const TinyString TinyString::NULL_STRING(nullptr);


/* PRIVATE STATIC */

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

TinyString::TinyString(const TinyString& str) :
    handle(nullptr)
{
    TinyString::initTinyMemory();
    *this = str;
}

TinyString::TinyString(const char* str) :
    handle(nullptr)
{
    TinyString::initTinyMemory();
    *this = str;
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
        if (this->isNull())
        {
            return *this;
        }
        ++this->handle->refCount;
        return *this;
    }
}

const TinyString& TinyString::operator=(const char* str)
{
    if (str == nullptr)
    {
        releaseHandle();
        return *this;
    }
    
    if (this->handle != nullptr && this->handle->str != nullptr && strcmp(this->handle->str, str) == 0)
    {
        return *this;
    }
    
    this->releaseHandle();
    this->initHandle();
    assert(this->handle != nullptr);
    
    size_t strLength = strlen(str);
    if (strLength == 0)
    {
        ++this->handle->refCount;
        return *this;
    }
    else
    {
        char* newStr = (char*)TinyString::tinyMemory.allocateMemory((unsigned int)strLength + 1);
        // Allocate memory fail
        if (newStr == nullptr)
        {
            return *this;
        }
        this->initSubString();
        assert(this->handle->subString != nullptr);
        this->handle->str = newStr;
        memcpy(this->handle->str, str, strLength);
        this->handle->str[strLength] = '\0';
        this->handle->subString->startIndex = 0;
        this->handle->subString->length = (unsigned int)strLength;
        ++this->handle->refCount;
        return *this;
    }
}

bool TinyString::operator==(const TinyString &str) const
{
    if (this == &str)
    {
        return true;
    }
    if (this->handle == str.handle)
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
        return this->stringCompare(str0, str1,
                                   this->handle->subString->startIndex, this->handle->subString->length,
                                   str.handle->subString->startIndex, str.handle->subString->length);
    }
}

bool TinyString::operator==(const char *str) const
{
    if (this->isNull() && str == nullptr)
    {
        return true;
    }
    size_t strLength = strlen(str);
    if (this->isEmpty() && (str != nullptr && strLength == 0))
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
        return this->stringCompare(str0, str1,
                                   this->handle->subString->startIndex, this->handle->subString->length,
                                   0, (unsigned int)strLength);
    }
}

TinyString TinyString::operator+(const TinyString &str)
{
    if (str.isNullOrEmpty())
    {
        return *this;
    }
    return TinyString(this->isNull() ? nullptr : this->isEmpty() ? "" : this->handle->str, str.handle->str,
                      this->handle->subString->startIndex, this->handle->subString->length,
                      str.handle->subString->startIndex, str.handle->subString->length);
}

TinyString TinyString::operator+(const char *str)
{
    if (str == nullptr)
    {
        return *this;
    }
    size_t strLength = strlen(str);
    if (strLength == 0)
    {
        return *this;
    }
    return TinyString(this->isNull() ? nullptr : this->isEmpty() ? "" : this->handle->str, str,
                      this->handle->subString->startIndex, this->handle->subString->length,
                      0, (unsigned int)strLength);
}

namespace jcgame
{
    TinyString operator+(const TinyString& strLH, const TinyString& strRH)
    {
        return TinyString(strLH.isNull() ? nullptr : strLH.isEmpty() ? TinyString::C_EMPTY_STRING : strLH.handle->str,
                          strRH.isNull() ? nullptr : strRH.isEmpty() ? TinyString::C_EMPTY_STRING : strRH.handle->str,
                          strLH.isNullOrEmpty() ? 0 : strLH.handle->subString->startIndex, strLH.isNullOrEmpty() ? 0 : strLH.handle->subString->length,
                          strRH.isNullOrEmpty() ? 0 : strRH.handle->subString->startIndex, strRH.isNullOrEmpty() ? 0 : strRH.handle->subString->length);
    }
    
    TinyString operator+(const TinyString& strLH, const char* strRH)
    {
        return TinyString(strLH.isNull() ? nullptr : strLH.isEmpty() ? TinyString::C_EMPTY_STRING : strLH.handle->str,
                          strRH,
                          strLH.isNullOrEmpty() ? 0 : strLH.handle->subString->startIndex, strLH.isNullOrEmpty() ? 0 : strLH.handle->subString->length,
                          0, strRH == nullptr ? 0 : (unsigned int)strlen(strRH));
    }
    
    TinyString operator+(const char* strLH, const TinyString& strRH)
    {
        return TinyString(strLH,
                          strRH.isNull() ? nullptr : strRH.isEmpty() ? TinyString::C_EMPTY_STRING : strRH.handle->str,
                          0, strLH == nullptr ? 0 : (unsigned int)strlen(strLH),
                          strRH.isNullOrEmpty() ? 0 : strRH.handle->subString->startIndex, strRH.isNullOrEmpty() ? 0 : strRH.handle->subString->length);
    }
}// end of jcgame namespace

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
    return this->isNull() || this->isEmpty();
}

unsigned int TinyString::length() const
{
    if (this->isNullOrEmpty())
    {
        return 0;
    }
    
    return this->handle->subString->length;
}

bool TinyString::c_str(char* o_buffer, unsigned int* io_bufferLength) const
{
    if (o_buffer == nullptr)
    {
        *io_bufferLength = this->length() + 1;
        return true;
    }
    else
    {
        if(io_bufferLength == nullptr)
        {
            return false;
        }
        else
        {
            memset(o_buffer, '\0', *io_bufferLength);
            if (!this->isNullOrEmpty())
            {
                memcpy(o_buffer, this->handle->str + this->handle->subString->startIndex, this->length());
            }
            return true;
        }
    }
}

const TinyString TinyString::subStr(unsigned int startIndex, unsigned int length) const
{
    return TinyString::TinyString(*this, startIndex, length);
}

const TinyString TinyString::subString(unsigned int startIndex, unsigned int endIndex) const
{
    return TinyString::TinyString(*this, startIndex, endIndex - startIndex);
}

/* PRIVATE */

TinyString::TinyString(const TinyString& str, unsigned int subStrStartIndex, unsigned int subStrLength) :
    handle(nullptr)
{
    if (str.isNull())
    {
        *this = TinyString::NULL_STRING;
        return;
    }
    if (str.isEmpty())
    {
        *this = TinyString::EMPTY_STRING;
        return;
    }
    if (subStrLength == 0)
    {
        *this = TinyString::EMPTY_STRING;
        return;
    }
    if (subStrStartIndex >= str.handle->subString->startIndex + str.handle->subString->length)
    {
        *this = TinyString::EMPTY_STRING;
        return;
    }
    if (subStrStartIndex + subStrLength >= str.handle->subString->startIndex + str.handle->subString->length)
    {
        subStrLength = str.handle->subString->startIndex + str.handle->subString->length - subStrStartIndex;
    }
    
    this->handle = str.handle;
    initSubString();
    assert(this->handle->subString != nullptr);
    ++(this->handle->refCount);
    this->handle->subString->startIndex = subStrStartIndex;
    this->handle->subString->length = subStrLength;
}

TinyString::TinyString(const char* strLH, const char* strRH,
                       unsigned int subStrStartIndexLH, unsigned int subStrLengthLH,
                       unsigned int subStrStartIndexRH, unsigned int subStrLengthRH) :
    handle(nullptr)
{
    if (strLH == nullptr && strRH == nullptr)
    {
        *this = TinyString::NULL_STRING;
        return;
    }
    
    size_t lhLength = strLH == nullptr ? 0 : subStrLengthLH;
    size_t rhLength = strRH == nullptr ? 0 : subStrLengthRH;
    
    if (lhLength + rhLength == 0)
    {
        *this = TinyString::EMPTY_STRING;
        return;
    }
    
    this->constructReservedTinyString((unsigned int)lhLength + (unsigned int)rhLength + 1);
    assert(this->handle != nullptr);
    if(strLH != nullptr)
    {
        memcpy(this->handle->str, strLH + subStrStartIndexLH, subStrLengthLH);
    }
    if(strRH != nullptr)
    {
        memcpy(this->handle->str + lhLength, strRH + subStrStartIndexRH, subStrLengthRH);
    }
}

bool TinyString::constructReservedTinyString(unsigned int reservedChars)
{
    if (reservedChars == 0)
    {
        *this = TinyString::EMPTY_STRING;
        return true;
    }
    
    initHandle();
    assert(this->handle != nullptr);
    
    char* reservedStr = (char*)TinyString::tinyMemory.allocateMemory(reservedChars);
    // Allocate memory fail
    if (reservedStr == nullptr)
    {
        releaseHandle();
        return false;
    }
    memset(reservedStr, '\0', reservedChars);
    this->handle->str = reservedStr;
    ++this->handle->refCount;
    
    initSubString();
    assert(this->handle->subString != nullptr);
    this->handle->subString->startIndex = 0;
    this->handle->subString->length = reservedChars;
    
    return true;
}

bool TinyString::initHandle()
{
    assert(this->handle == nullptr);
    
    TinyString_Handle* handle = (TinyString_Handle*)TinyString::tinyMemory.allocateMemory(sizeof(TinyString_Handle));
    // Allocate memory fail
    if (handle == nullptr)
    {
        this->handle = nullptr;
        return false;
    }
    this->handle = handle;
    this->handle->str = nullptr;
    this->handle->refCount = 0;
    this->handle->subString = nullptr;
    
    return true;
}

bool TinyString::initSubString()
{
    assert(this->handle != nullptr);
    assert(this->handle->subString == nullptr);
    
    TinyString_SubString* subString = (TinyString_SubString*)TinyString::tinyMemory.allocateMemory(sizeof(TinyString_SubString));
    // Allocate memory fail
    if (subString == nullptr)
    {
        this->handle->subString = nullptr;
        return false;
    }
    this->handle->subString = subString;
    this->handle->subString->startIndex = 0;
    this->handle->subString->length = 0;

    return true;
}

void TinyString::releaseHandle()
{
    if (this->handle == nullptr)
    {
        return;
    }
    
    assert(this->handle->refCount > 0);
    --this->handle->refCount;
    
    TinyString::tinyMemory.freeMemory(this->handle->subString);
    this->handle->subString = nullptr;
    
    if (this->handle->refCount == 0)
    {
        TinyString::tinyMemory.freeMemory(this->handle->str);
        this->handle->str = nullptr;
        TinyString::tinyMemory.freeMemory(this->handle);
    }
    this->handle = nullptr;
}

int TinyString::stringCompare(const char *strLH, const char *strRH,
                              unsigned int subStrStartIndexLH, unsigned int subStrLengthLH,
                              unsigned int subStrStartIndexRH, unsigned int subStrLengthRH) const
{
    if (strLH == nullptr && strRH == nullptr)
    {
        return 0;
    }
    if (strLH == nullptr && strRH != nullptr)
    {
        return -1;
    }
    if (strLH != nullptr && strRH == nullptr)
    {
        return 1;
    }
    if (subStrLengthLH < subStrLengthRH)
    {
        return -1;
    }
    if (subStrLengthLH > subStrLengthRH)
    {
        return 1;
    }
    
    assert(subStrLengthLH == subStrLengthRH);
    const char* lh = strLH + subStrStartIndexLH;
    const char* rh = strRH + subStrStartIndexRH;
    for (int i = 0; i < subStrLengthLH; ++i)
    {
        if (*lh != *rh)
        {
            return *lh - *rh;
        }
    }
    
    return 0;
}