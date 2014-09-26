//
//  IsometricAlgorithm.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-9-21.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "IsometricAlgorithm.h"

using namespace jcgame;

IsometricAlgorithm_Point IsometricAlgorithm::isoWorldToScreen(int x, int y, int z)
{
    IsometricAlgorithm_Point point;
    point.x = x - z;
    point.y = y * 1.2247 + (x + z) * 0.5;
    return point;
}

IsometricAlgorithm_Point IsometricAlgorithm::isoScreenToWorld(int x, int y)
{
    IsometricAlgorithm_Point point;
    point.x = y + x * 0.5;
    point.y = y - x * 0.5;
    return point;
}

int IsometricAlgorithm::isoScreenFloorHeight(int cellSize)
{
    return cellSize * 1.2247;
}
