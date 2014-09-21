//
//  IsometricPairValueGroup.h
//  IsometricModel
//
//  Created by jimCheng on 14-9-3.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricPairValueGroup__
#define __IsometricModel__IsometricPairValueGroup__

#include "IsometricPairValue.h"

namespace jcgame
{
    class IsometricPairValueGroup
    {
    public:
        IsometricPairValueGroup();
        ~IsometricPairValueGroup();
        
        int getNumValues() const;
        const IsometricPairValue* getValue(int index) const;
        bool set(const char* stringData);
        
    private:
        IsometricPairValueGroup(const IsometricPairValueGroup&);
        const IsometricPairValueGroup& operator=(const IsometricPairValueGroup&);
        
        IsometricPairValue* values;
        int numValues;
        
        void releaseValues();
    };
}

#endif /* defined(__IsometricModel__IsometricPairValueGroup__) */
