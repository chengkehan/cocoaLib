//
//  IsometricPairValue.h
//  IsometricModel
//
//  Created by jimCheng on 14-9-3.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricPairValue__
#define __IsometricModel__IsometricPairValue__

namespace jcgame
{
    class IsometricPairValue
    {
    public:
        IsometricPairValue();
        ~IsometricPairValue();
        
        bool set(const char* stringData);
        int getValue0() const;
        int getValue1() const;
        
    private:
        IsometricPairValue(const IsometricPairValue&);
        const IsometricPairValue& operator=(const IsometricPairValue&);
        
        int value0;
        int value1;
    };
}

#endif /* defined(__IsometricModel__IsometricPairValue__) */
