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
    floor(floor), row(row), col(col)
{
    // Do nothing
}

IsometricCell::~IsometricCell()
{
    // Do nothing
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

void IsometricCell::setData(void* data)
{
    this->data = data;
}

void* IsometricCell::getData() const
{
    return this->data;
}

/* PRIVATE */
