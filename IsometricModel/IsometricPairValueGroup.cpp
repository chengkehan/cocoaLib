//
//  IsometricPairValueGroup.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-9-3.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "IsometricPairValueGroup.h"

using namespace jcgame;
using namespace std;
using namespace boost;

/* PUBLIC */
IsometricPairValueGroup::IsometricPairValueGroup():
    values(nullptr), numValues(0)
{
    // Do nothing
}

IsometricPairValueGroup::~IsometricPairValueGroup()
{
    releaseValues();
}

int IsometricPairValueGroup::getNumValues() const
{
    return numValues;
}

const IsometricPairValue* IsometricPairValueGroup::getValue(int index) const
{
    if (index < 0 || index >= numValues)
    {
        return nullptr;
    }
    
    return &values[index];
}

bool IsometricPairValueGroup::set(const char *stringData)
{
    if (stringData == nullptr)
    {
        return false;
    }
    
    // minimuze {{0,0}}
    // or {{0,0},{0,0}}
    if (strlen(stringData) < 7)
    {
        return false;
    }
    
    string strData(stringData);
    if (strData[0] != '{' || strData[strData.size() - 1] != '}')
    {
        return false;
    }
    
    // {0,0}
    // or {0,0},{0,0}
    string realData = strData.substr(1, strData.size() - 2);
    
    // is {0,0}
    if (realData.find("},{") == string::npos)
    {
        if (numValues != 1)
        {
            releaseValues();
            numValues = 1;
            values = (IsometricPairValue*)malloc(sizeof(IsometricPairValue));
            // memory low
            if (values == nullptr)
            {
                return false;
            }
        }
        if(!values[0].set(realData.c_str()))
        {
            releaseValues();
            return false;
        }
    }
    // is {0,0},{0,0}
    else
    {
        vector<string> blocks;
        size_t headPos = 0;
        size_t tailPos = realData.find("}");
        while (tailPos != string::npos)
        {
            blocks.push_back(realData.substr(headPos, tailPos - headPos + 1));
            headPos = tailPos + 2;
            tailPos = realData.find("}", headPos, 1);
        }
        if (blocks.size() == 0)
        {
            return false;
        }
        int newNumValues = (int)blocks.size();
        if (numValues != newNumValues)
        {
            releaseValues();
            numValues = newNumValues;
            values = (IsometricPairValue*)malloc(sizeof(IsometricPairValue) * numValues);
            // memory low
            if (values == nullptr)
            {
                return false;
            }
        }
        for (int i = 0; i < numValues; ++i)
        {
            if (!values[i].set(blocks[i].c_str()))
            {
                releaseValues();
                return false;
            }
        }
    }
    
    return true;
}

/* PRIVATE */

void IsometricPairValueGroup::releaseValues()
{
    if (values != nullptr)
    {
        free(values);
        values = nullptr;
        numValues = 0;
    }
}