//
//  IsometricCell.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-8-11.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "IsometricCell.h"

using namespace jcgame;

/* PUBLIC */

IsometricCell::IsometricCell(int floor, int row, int col):
    type(ISOMETRIC_CELL_TYPE_PLANE),
    direction(ISOMETRIC_CELL_BEVEL_DIRECTION_NONE),
    floor(floor), row(row), col(col),
    floorHeight(0), startHeight(0), endHeight(0),
    data(nullptr), atlasName(nullptr), spriteName(nullptr)
{
    // Do nothing
}

IsometricCell::~IsometricCell()
{
    data = nullptr;
}

void IsometricCell::setType(enum ISOMETRIC_CELL_TYPE type)
{
    this->type = type;
}

enum ISOMETRIC_CELL_TYPE IsometricCell::getType() const
{
    return type;
}

void IsometricCell::setDirection(enum ISOMETRIC_CELL_BEVEL_DIRECTION direction)
{
    this->direction = direction;
}

ISOMETRIC_CELL_BEVEL_DIRECTION IsometricCell::getDirection() const
{
    return direction;
}

int IsometricCell::getFloor() const
{
    return floor;
}

int IsometricCell::getRow() const
{
    return row;
}

int IsometricCell::getCol() const
{
    return col;
}

void IsometricCell::setFloorHeight(int floorHeight)
{
    this->floorHeight = floorHeight;
}

int IsometricCell::getFloorHeight() const
{
    return this->floorHeight;
}

void IsometricCell::setStartHeight(int startHeight)
{
    this->startHeight = startHeight;
}

int IsometricCell::getStartHeight() const
{
    return this->startHeight;
}

void IsometricCell::setEndHeight(int endHeight)
{
    this->endHeight = endHeight;
}

int IsometricCell::getEndHeight() const
{
    return this->endHeight;
}

void IsometricCell::setData(void* data)
{
    this->data = data;
}

void* IsometricCell::getData() const
{
    return this->data;
}

void IsometricCell::setAtlasName(const char *atlasName)
{
    
}

const char* IsometricCell::getAtlasName() const
{
    return this->atlasName;
}

void IsometricCell::setSpriteName(const char *spriteName)
{
    
}

const char* IsometricCell::getSpriteName() const
{
    return this->spriteName;
}

/* PRIVATE */
