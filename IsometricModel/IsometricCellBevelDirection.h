//
//  IsometricCellBevelDirection.h
//  IsometricModel
//
//  Created by jimCheng on 14-8-11.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef IsometricModel_IsometricCellBevelDirection_h
#define IsometricModel_IsometricCellBevelDirection_h

namespace jcgame
{
    enum ISOMETRIC_CELL_BEVEL_DIRECTION
    {
        ISOMETRIC_CELL_BEVEL_DIRECTION_NONE, 
        ISOMETRIC_CELL_BEVEL_DIRECTION_NORTH,
        ISOMETRIC_CELL_BEVEL_DIRECTION_SOUTH,
        ISOMETRIC_CELL_BEVEL_DIRECTION_WEST,
        ISOMETRIC_CELL_BEVEL_DIRECTION_EAST,
        ISOMETRIC_CELL_BEVEL_DIRECTION_NORTH_WEST,
        ISOMETRIC_CELL_BEVEL_DIRECTION_NORTH_EAST,
        ISOMETRIC_CELL_BEVEL_DIRECTION_SOUTH_WEST,
        ISOMETRIC_CELL_BEVEL_DIRECTION_SOUTH_EAST
    };
}

#endif
