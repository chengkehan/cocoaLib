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
    
    // A handle of TinyString object
    typedef struct TinyString_Handle
    {
        // The pointer of string
        char* str;
        // Reference count
        unsigned int refCount;
    }
    TinyString_Handle;
    
    // TinyString
    class TinyString
    {
    public:
        TinyString();
        ~TinyString();
        
        // Assign another tinyString object to this object
        const TinyString& operator=(const TinyString& str);
        // Assign a char string to this object
        const TinyString& operator=(const char* str);
        bool operator==(const TinyString& str);
        bool operator==(const char* str);
        
        // Whether current tinyString is null
        bool isNull() const;
        // Whether current tinyString is empty
        bool isEmpty() const;
        // Whether current tinyString is null or empty
        bool isNullOrEmpty() const;
        
    private:
        // Allocate memory for handle and string
        static TinyMemory tinyMemory;
        
        // Initialize memory allocator
        static bool initTinyMemory();
    
    private:
        TinyString(const TinyString&);
        
        // Release memory of current handle
        void releaseHandle();
        
        // The handle of current tinyString
        TinyString_Handle* handle;
    };
}

#endif /* defined(__IsometricModel__TinyString__) */
