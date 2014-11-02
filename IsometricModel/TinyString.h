//
//  TinyString.h
//  IsometricModel
//
//  Created by jimCheng on 14-10-20.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__TinyString__
#define __IsometricModel__TinyString__

namespace jcgame
{
    class TinyMemory;
    
    typedef struct TinyString_Handle
    {
        char* str;
        unsigned int refCount;
    }
    TinyString_Handle;
    
    class TinyString
    {
    public:
        TinyString();
        ~TinyString();
        const TinyString& operator=(const TinyString& str);
        const TinyString& operator=(const char* str);
        
        bool isNull() const;
        bool isEmpty() const;
        bool isNullOrEmpty() const;
        
    private:
        static TinyMemory tinyMemory;
    
    private:
        TinyString_Handle* handle;
        
        bool initTinyMemory();
        void releaseHandle();
    };
}

#endif /* defined(__IsometricModel__TinyString__) */
