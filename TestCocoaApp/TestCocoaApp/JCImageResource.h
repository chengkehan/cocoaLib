//
//  JCImageResource.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Foundation/Foundation.h>

namespace jcgame
{
    class IsometricTileConfig;
}

@interface JCImageResource : NSObject

@property (nonatomic, readonly) NSImage* image;
@property (nonatomic, readonly) NSString* name;
@property (nonatomic, readonly) jcgame::IsometricTileConfig* config;

- (id)initWidthImage:(NSImage*)image config:(jcgame::IsometricTileConfig*)cfg name:(NSString*)name;

@end
