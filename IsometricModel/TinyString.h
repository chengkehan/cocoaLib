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
        unsigned int* refCount;
        // The sub string start from the index which in the whole string
        // If current string is not a sub string of str, this value is 0
        unsigned int subStrStartIndex;
        // The length of sub stirng
        // If current string is not a sub stirng of str, this value is equal to length of the whole string
        unsigned int subStrLength;
    }
    TinyString_Handle;
    
    // TinyString
    class TinyString
    {
    public:
        static const char* C_EMPTY_STRING;
        static const TinyString EMPTY_STRING;
        static const TinyString NULL_STRING;
        
    public:
        TinyString();
        TinyString(const TinyString& str);
        TinyString(const char* str);
        ~TinyString();
        
        // Assign another tinyString object to this object
        const TinyString& operator=(const TinyString& str);
        // Assign a char string to this object
        const TinyString& operator=(const char* str);
        bool operator==(const TinyString& str) const;
        bool operator==(const char* str) const;
        
        // Whether current tinyString is null
        bool isNull() const;
        // Whether current tinyString is empty
        bool isEmpty() const;
        // Whether current tinyString is null or empty
        bool isNullOrEmpty() const;
    
        // The number characters of the string
        unsigned int length() const;
        
        // Get the duplicate c_string
        // If o_buffer is null, io_bufferLength is set as the size of buffer
        // If o_buffer isnot null, io_bufferLength is the size of o_buffer, and o_buffer will be filled with characters.
        bool c_str(char* o_buffer, unsigned int* io_bufferLength) const;
        // Sub string of current string
        const TinyString subStr(unsigned int startIndex, unsigned int length) const;
        // Sub string of current string
        // Pay attention, endIndex = startIndex + length of substring.
        const TinyString subString(unsigned int startIndex, unsigned int endIndex) const;
        
    private:
        // Allocate memory for handle and string
        static TinyMemory tinyMemory;
        
        // Initialize memory allocator
        static bool initTinyMemory();
    
    private:
        // Construct TinyString with a sub string
        TinyString(const TinyString& str, unsigned int subStrStartIndex, unsigned int subStrLength);
        
        // Init TinyString_Handle
        bool initHandle(bool initRefCount);
        
        // Release memory of current handle
        void releaseHandle();
        
        // Compare two string
        // You can use a sub stirng of strLH compare with a sub string of strRH
        // If strLH is equal to strRG, then reurn 0
        // If strLH is less than strRH, then return value is less than 0
        // If strLH is greater than strRH, then return value is greater than 0
        int stringCompare(const char* strLH, const char* strRH,
                          unsigned int subStrStartIndexLH, unsigned int subStrLengthLH,
                          unsigned int subStrStartIndexRH, unsigned int subStrLengthRH) const;
        
        // The handle of current tinyString
        TinyString_Handle* handle;
    };
}

#endif /* defined(__IsometricModel__TinyString__) */
