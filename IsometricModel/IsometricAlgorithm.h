//
//  IsometricAlgorithm.h
//  IsometricModel
//
//  Created by jimCheng on 14-9-21.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricAlgorithm__
#define __IsometricModel__IsometricAlgorithm__

namespace jcgame
{
    typedef struct IsometricAlgorithm_Point
    {
        int x;
        int y;
    }
    IsometricAlgorithm_Point;
    
    class IsometricAlgorithm
    {
    public:
        static IsometricAlgorithm_Point isoWorldToScreen(int x, int y, int z);
        static IsometricAlgorithm_Point isoScreenToWorld(int x, int y);
        static int isoScreenFloorHeight(int cellSize);
    };
}

#endif /* defined(__IsometricModel__IsometricAlgorithm__) */
