//
//  IsometricPairValue.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-9-3.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "IsometricPairValue.h"

using namespace jcgame;
using namespace std;
using namespace boost;

/* PUBLIC */

IsometricPairValue::IsometricPairValue():
    value0(0), value1(0)
{
    // Do nothing
}

IsometricPairValue::~IsometricPairValue()
{
    // Do nothing
}

bool IsometricPairValue::set(const char *stringData)
{
    if (stringData == nullptr)
    {
        return false;
    }
    
    // minimize {0,0}
    if(strlen(stringData) < 5)
    {
        return false;
    }
    
    string strData(stringData);
    if (strData[0] != '{' || strData[strData.size() - 1] != '}')
    {
        return false;
    }
    
    // 0,0
    string realData = strData.substr(1, strData.size() - 2);
    size_t index = realData.find(',');
    if (index == string::npos)
    {
        return false;
    }
    
    string value0Str = realData.substr(0, index);
    string value1Str = realData.substr(index + 1, realData.size() - (index + 1));
    try
    {
        value0 = lexical_cast<int>(value0Str.c_str());
        value1 = lexical_cast<int>(value1Str.c_str());
    }
    catch (bad_lexical_cast error)
    {
        printf("error:%s\n", error.what());
        return false;
    }
    
    return true;
}

int IsometricPairValue::getValue0() const
{
    return value0;
}

int IsometricPairValue::getValue1() const
{
    return value1;
}

/* PRIVATE */


