//
//  IsometricCell.h
//  IsometricModel
//
//  Created by jimCheng on 14-8-11.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricCell__
#define __IsometricModel__IsometricCell__

#include "IsometricCellType.h"
#include "IsometricCellBevelDirection.h"

namespace jcgame
{
    class IsometricCell
    {
    public:
        IsometricCell(int floor, int row, int col);
        ~IsometricCell();
        
        void setType(enum ISOMETRIC_CELL_TYPE);
        enum ISOMETRIC_CELL_TYPE getType() const;
        
        void setDirection(enum ISOMETRIC_CELL_BEVEL_DIRECTION);
        enum ISOMETRIC_CELL_BEVEL_DIRECTION getDirection() const;
        
        int getFloor() const;
        int getRow() const;
        int getCol() const;
        
        void setFloorHeight(int floorHeight);
        int getFloorHeight() const;
        
        void setStartHeight(int startHeight);
        int getStartHeight() const;
        
        void setEndHeight(int endHeight);
        int getEndHeight() const;
        
        void setData(void*);
        void* getData() const;
        
        void setAtlasName(const char* atlasName);
        const char* getAtlasName() const;
        
        void setSpriteName(const char* spriteName);
        const char* getSpriteName() const;
        
    private:
        IsometricCell(const IsometricCell&);
        const IsometricCell& operator=(const IsometricCell&);
        
    private:
        enum ISOMETRIC_CELL_TYPE type;
        enum ISOMETRIC_CELL_BEVEL_DIRECTION direction;
        int floor;
        int row;
        int col;
        int floorHeight;
        int startHeight;
        int endHeight;
        void* data;
        char* atlasName;
        char* spriteName;
    };
}

#endif /* defined(__IsometricModel__IsometricCell__) */
