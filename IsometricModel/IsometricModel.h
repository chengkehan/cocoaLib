//
//  IsometricModel.h
//  IsometricModel
//
//  Created by jimCheng on 14-8-11.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricModel__
#define __IsometricModel__IsometricModel__

#include "IsometricCell.h"

namespace jcgame
{
    class IsometricModel
    {
    public:
        IsometricModel();
        ~IsometricModel();
        
        bool init(int floors, int rows, int cols);
        IsometricCell* getCell(int floor, int row, int col);
        
        int getFloors() const;
        int getRows() const;
        int getCols() const;
        
        int getCellSize() const;
        void setCellSize(int cellSize);
        
    private:
        IsometricModel(const IsometricModel&);
        const IsometricModel& operator=(const IsometricModel&);
        
        bool initCells();
        
    private:
        // All cells are stored into the one-dimensional array
        IsometricCell* cells;
        int floors;
        int rows;
        int cols;
        int cellSize;
        
        bool getFloorRowColWithIndex(int index, int* floor, int* row, int* col);
        bool getIndexWithFloorRowCol(int* index, int floor, int row, int col);
        
        void releaseCells(bool runDestructor);
    };
}

#endif /* defined(__IsometricModel__IsometricModel__) */
