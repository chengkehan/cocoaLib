//
//  TinyMemory.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-10-6.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "TinyMemory.h"

using namespace jcgame;

/* PUBLIC STATIC */

const unsigned int TinyMemory::BYTES_LEVELS[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
const unsigned int TinyMemory::NUM_LEVELS = 10;
const unsigned char TinyMemory::MIN_ALIGNMENT = 2;
const unsigned char TinyMemory::MAX_ALIGNMENT = 64;

/* PRIVATE STATIC */

const unsigned int TinyMemory::NUM_CELLS_PER_BLOCK = 1024;

/* PUBLIC */

TinyMemory::TinyMemory() :
    alignment(0)
{
    // Do nothing
}

TinyMemory::~TinyMemory()
{
    // TODO free all memory, destruct object.
}

bool TinyMemory::init(unsigned char alignment)
{
    if (alignment == 0)
    {
        return false;
    }
    // Has been initialized
    if (this->alignment == 0)
    {
        return false;
    }
    if (alignment < TinyMemory::MIN_ALIGNMENT || alignment > TinyMemory::MAX_ALIGNMENT || alignment % 2 != 0)
    {
        return false;
    }
    
    this->alignment = alignment;
    memset(this->blocks, 0, sizeof(TinyMemory_Block) * TinyMemory::NUM_LEVELS);
    
    return true;
}

void* TinyMemory::allocateMemory(unsigned int numBytes)
{
    if (this->alignment == 0)
    {
        return nullptr;
    }
    // The size of bytes that you want is out of ability
    if (numBytes > TinyMemory::BYTES_LEVELS[TinyMemory::NUM_LEVELS - 1])
    {
        return nullptr;
    }
    
    int indexOfLevel = this->getIndexOfLevel(numBytes);
    if (indexOfLevel == -1)
    {
        return nullptr;
    }
    
    TinyMemory_Block* block = this->getBlock(indexOfLevel);
    if (block == nullptr)
    {
        return nullptr;
    }
    assert(block->numFreeCells > 0);
    
    --block->numFreeCells;
    unsigned int freeIndex = block->freeList[block->numFreeCells];
    block->freeList[block->numFreeCells] = UINT32_MAX;
    
    char* allocPtr = &block->data[(TinyMemory::BYTES_LEVELS[indexOfLevel] + this->alignment) * freeIndex];
    char* alignedPtr = this->alignMemory(allocPtr);

    return alignedPtr;
}

bool TinyMemory::freeMemory(void *ptr)
{
    if (this->alignment == 0)
    {
        return false;
    }
    if (ptr == nullptr)
    {
        return true;
    }
    
    char* offsetPtr = (char*)ptr - 1;
    char* rawPtr = (char*)ptr - *offsetPtr;
    for (int i = 0; i < TinyMemory::NUM_LEVELS; ++i)
    {
        TinyMemory_Block* block = &this->blocks[i];
        while (block != nullptr)
        {
            if (block->data != nullptr)
            {
                if (rawPtr >= block->data && rawPtr < block->tail)
                {
                    unsigned long offset = rawPtr - block->data;
                    unsigned int realCellSize = TinyMemory::BYTES_LEVELS[i] + this->alignment;
                    // Check the pointer is the header address of a cell
                    if (offset % realCellSize != 0)
                    {
                        return false;
                    }
                    unsigned long index = offset / realCellSize;
                    // Check if the index is in the freeList
                    for (int j = 0; j < block->numFreeCells; ++j)
                    {
                        if (block->freeList[j] == index)
                        {
                            return false;
                        }
                    }
                    // Append the index to freeList
                    block->freeList[block->numFreeCells] = (unsigned int)index;
                    ++block->numFreeCells;
                    return true;
                }
            }
            block = block->nextBlock;
        }
    }
    
    return false;
}

/* PRIVATE */

int TinyMemory::getIndexOfLevel(unsigned int numBytes)
{
    assert(numBytes <= TinyMemory::BYTES_LEVELS[TinyMemory::NUM_LEVELS - 1]);
    
    for (int i = 0; i < TinyMemory::NUM_LEVELS; ++i)
    {
        if (numBytes <= TinyMemory::BYTES_LEVELS[i])
        {
            return i;
        }
    }
    return -1;
}

TinyMemory_Block* TinyMemory::getBlock(unsigned int indexOfLevel)
{
    assert(indexOfLevel < TinyMemory::NUM_LEVELS);
    
    TinyMemory_Block* block = &this->blocks[indexOfLevel];
    if (block->data == nullptr)
    {
        if (initBlock(block, indexOfLevel))
        {
            return block;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        while (true)
        {
            if (block->numFreeCells > 0)
            {
                return block;
            }
            else
            {
                if (block->nextBlock == nullptr)
                {
                    TinyMemory_Block* nextBlock = (TinyMemory_Block*)malloc(sizeof(TinyMemory_Block));
                    if(nextBlock == nullptr)
                    {
                        return nullptr;
                    }
                    else
                    {
                        if (initBlock(nextBlock, indexOfLevel))
                        {
                            block->nextBlock = nextBlock;
                            return nextBlock;
                        }
                        else
                        {
                            free(nextBlock);
                            return nullptr;
                        }
                    }
                }
                else
                {
                    block = block->nextBlock;
                }
            }
        }
        return nullptr;
    }
}

bool TinyMemory::initBlock(TinyMemory_Block *block, unsigned int indexOfLevel)
{
    assert(block != nullptr);
    assert(block->data == nullptr);
    assert(indexOfLevel < TinyMemory::NUM_LEVELS);
    
    memset(block, 0, sizeof(TinyMemory_Block));
    
    size_t numBytes = (TinyMemory::BYTES_LEVELS[indexOfLevel] + this->alignment) * TinyMemory::NUM_CELLS_PER_BLOCK;
    block->data = (char*)malloc(numBytes);
    if (block->data == nullptr)
    {
        return false;
    }
    
    block->tail = block->data + numBytes;
    block->numFreeCells = TinyMemory::NUM_CELLS_PER_BLOCK;
    
    for (int i = 0; i < TinyMemory::NUM_CELLS_PER_BLOCK; ++i)
    {
        block->freeList[i] = i;
    }
    
    return true;
}

char* TinyMemory::alignMemory(char *memory)
{
    assert(memory != nullptr);
    
    unsigned long address = (unsigned long)memory;
    unsigned long mask = address & (this->alignment - 1);
    unsigned long offset = this->alignment - mask;
    char* alignedMemory = memory + offset;
    char* offsetPtr = alignedMemory - 1;
    *offsetPtr = offset;
    
    return alignedMemory;
}