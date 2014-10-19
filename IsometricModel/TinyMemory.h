//
//  TinyMemory.h
//  IsometricModel
//
//  Created by jimCheng on 14-10-6.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__TinyMemory__
#define __IsometricModel__TinyMemory__

namespace jcgame
{
    // A block of memory
    // The block will be divided into many same small size cells to use.
    typedef struct TinyMemory_Block
    {
        // Link to the next block
        struct TinyMemory_Block* nextBlock;
        // Memory data
        char* data;
        // The tail pointer of the memory data
        char* tail;
        // The number of unused cells
        unsigned int numFreeCells;
        // All indices of unused cells
        unsigned int freeList[1024]; // TinyMemory::NUM_CELLS_PER_BLOCK
    }
    TinyMemory_Block;
    
    // The manager for all TinyMemory_Blocks
    class TinyMemory
    {
    public:
        // Define the increment of each block's cell
        static const unsigned int BYTES_LEVELS[];
        // The size of BYTES_LEVELS
        static const unsigned int NUM_LEVELS;
        // Minimal memory alignment
        static const unsigned char MIN_ALIGNMENT;
        // Maximal memory aligment
        static const unsigned char MAX_ALIGNMENT;
        
    public:
        TinyMemory();
        ~TinyMemory();
        
        // Initialize with memory address alignment
        bool init(unsigned char alignment);
        
        // Allocate memory with how many bytes you want
        void* allocateMemory(unsigned int numBytes);
        // Free memory
        bool freeMemory(void* ptr);
        
    private:
        // The number of cells in one memory block
        static const unsigned int NUM_CELLS_PER_BLOCK;
        
    private:
        TinyMemory(const TinyMemory&);
        const TinyMemory& operator=(const TinyMemory&);
        
        // The number of bytes will map to which index of BYTES_LEVELS
        int getIndexOfLevel(unsigned int numBytes);
        // Get memory block with index of BYTES_LEVELS
        TinyMemory_Block* getBlock(unsigned int indexOfLevel);
        // Initialize memory block
        bool initBlock(TinyMemory_Block* block, unsigned int indexOfLevel);
        // Get a aligned memory address
        char* alignMemory(char* memory);
        
        TinyMemory_Block blocks[10]; // TinyMemory::NUM_LEVELS
        // The alignment of memory address that allocate from this manager
        unsigned char alignment;
    };
}

#endif /* defined(__IsometricModel__TinyMemory__) */
