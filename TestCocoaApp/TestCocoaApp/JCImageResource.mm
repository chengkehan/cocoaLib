//
//  JCImageResource.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCImageResource.h"
#import "IsometricTileConfig.h"

using namespace jcgame;

@interface JCImageResource()

@end

@implementation JCImageResource

- (id)initWidthImage:(NSImage *)image config:(IsometricTileConfig *)cfg name:(NSString *)name
{
    self = [super init];
    if (self)
    {
        _image = image;
        _name = name;
        _config = (IsometricTileConfig*)cfg;
    }
    return self;
}

@end
