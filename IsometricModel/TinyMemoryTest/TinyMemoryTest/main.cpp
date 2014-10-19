//
//  main.cpp
//  TinyMemoryTest
//
//  Created by jimCheng on 14-10-19.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include <iostream>
#include "TinyMemory.h"

using namespace jcgame;

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    
    TinyMemory tinyMemeory;
    
    bool initResult = tinyMemeory.init(16);
    tinyMemeory.debugPrint();
    
//    void* m0 = tinyMemeory.allocateMemory(2);
//    tinyMemeory.debugPrint();
//    void* m1 = tinyMemeory.allocateMemory(2);
//    tinyMemeory.debugPrint();
//    void* m2 = tinyMemeory.allocateMemory(2);
//    tinyMemeory.debugPrint();
//    void* m3 = tinyMemeory.allocateMemory(2);
//    tinyMemeory.freeMemory(m0);
//    tinyMemeory.freeMemory(m1);
//    tinyMemeory.freeMemory(m2);
//    m0 = tinyMemeory.allocateMemory(2);
//    tinyMemeory.debugPrint();
//    tinyMemeory.freeMemory(m0);
    
    return 0;
}

