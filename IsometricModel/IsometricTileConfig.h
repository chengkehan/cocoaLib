//
//  IsometricTileConfig.h
//  IsometricModel
//
//  Created by jimCheng on 14-8-28.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#ifndef __IsometricModel__IsometricTileConfig__
#define __IsometricModel__IsometricTileConfig__

namespace jcgame
{
    typedef struct IsometricTileConfig_Size
    {
        int width;
        int height;
    }
    IsometricTileConfig_Size;
    
    typedef struct IsometricTileConfig_Point
    {
        int x;
        int y;
    }
    IsometricTileConfig_Point;
    
    typedef struct IsometricTileConfig_Bounds
    {
        IsometricTileConfig_Point point;
        IsometricTileConfig_Size size;
    }
    IsometricTileConfig_Bounds;
    
    struct IsometricTileConfig_Metadata
    {
        IsometricTileConfig_Size size;
    };
    
    struct IsometricTileConfig_Frame
    {
        IsometricTileConfig_Bounds frame;
        IsometricTileConfig_Point offset;
        IsometricTileConfig_Bounds sourceColorRect;
        IsometricTileConfig_Size sourceSize;
    };
    
    class IsometricTileConfig
    {
    public:
        IsometricTileConfig();
        ~IsometricTileConfig();
        
        bool init(const char* xmlString);
        
        const IsometricTileConfig_Metadata* getMetadata() const;
        int getNumFrames() const;
        const IsometricTileConfig_Frame* getFrame(int index) const;
        
    private:
        IsometricTileConfig(const IsometricTileConfig&);
        const IsometricTileConfig& operator=(const IsometricTileConfig&);
        
        IsometricTileConfig_Metadata metadata;
        IsometricTileConfig_Frame* frames;
        int numFrames;
        
        void releaseFrames();
    };
}

#endif /* defined(__IsometricModel__IsometricTileConfig__) */
