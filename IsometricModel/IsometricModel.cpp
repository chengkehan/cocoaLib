//
//  IsometricModel.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-8-11.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include <iostream>
#include "IsometricModel.h"
#include "IsometricCell.h"

using namespace jcgame;

/* PUBLIC */

IsometricModel::IsometricModel():
    cells(nullptr), rows(0), cols(0), floors(0), cellSize(0)
{
    // Do nothing
}

IsometricModel::~IsometricModel()
{
    releaseCells(true);
}

bool IsometricModel::init(int floors, int rows, int cols)
{
    if(cells != nullptr)
    {
        return false;
    }
    if (floors <= 0 || rows <= 0 || cols <= 0)
    {                               
        return false;
    }
    
    this->floors = floors;
    this->rows = rows;
    this->cols = cols;
    
    return initCells();
}

IsometricCell* IsometricModel::getCell(int floor, int row, int col)
{
    if (cells == nullptr)
    {
        return nullptr;
    }
    if (floor < 0 || floor >= floors || row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return nullptr;
    }
    
    int index;
    if(getIndexWithFloorRowCol(&index, floor, row, col))
    {
        return &cells[index];
    }
    else
    {
        return nullptr;
    }
}

int IsometricModel::getFloors() const
{
    return floors;
}

int IsometricModel::getRows() const
{
    return rows;
}

int IsometricModel::getCols() const
{
    return cols;
}

int IsometricModel::getCellSize() const
{
    return cellSize;
}

void IsometricModel::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
}

/* PRIVATE */

bool IsometricModel::initCells()
{
    void* memoryBlock = malloc(sizeof(IsometricCell) * floors * rows * cols);
    if(memoryBlock == nullptr)
    {
        return false;
    }
    
    cells = (IsometricCell*)memoryBlock;
    int totalCells = floors * rows * cols;
    for (int i = 0; i < totalCells; ++i)
    {
        IsometricCell* cell = &cells[i];
        int floor, row, col;
        if(getFloorRowColWithIndex(i, &floor, &row, &col))
        {
            new (cell)IsometricCell(floor, row, col);
        }
        else
        {
            releaseCells(false);
            return false;
        }
    }
    
    return true;
}

bool IsometricModel::getFloorRowColWithIndex(int index, int* floor, int *row, int *col)
{
    int totalCells = floors * rows * cols;
    if (index < 0 || index >= totalCells)
    {
        return false;
    }
    
    *floor = totalCells / (rows * cols);
    *row = (totalCells - (*floor * rows * cols)) / cols;
    *col = (totalCells - (*floor * rows * cols) - (*row * cols));
    
    return true;
}

bool IsometricModel::getIndexWithFloorRowCol(int *index, int floor, int row, int col)
{
    int totalCells = floors * rows * cols;
    int theIndex = rows * cols * floor + cols * row + col;
    if (index < 0 || theIndex >= totalCells)
    {
        return false;
    }
    *index = theIndex;
    return true;
}

void IsometricModel::releaseCells(bool runDestructor)
{
    if(cells != nullptr)
    {
        if (runDestructor)
        {
            int totalCells = floors * rows * cols;
            for (int i = 0; i < totalCells; ++i)
            {
                IsometricCell* cell = &cells[i];
                cell->~IsometricCell();
            }
        }
        
        free(cells);
        cells = nullptr;
    }
}