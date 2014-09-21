//
//  JCResourcesManager.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCResourcesManager.h"
#import "JCImageResource.h"

using namespace jcgame;

@interface JCResourcesManager()

@property (nonatomic, readwrite) NSMutableArray* allImages;

@end

@implementation JCResourcesManager

- (NSMutableArray*)allImages
{
    if (_allImages == nil)
    {
        _allImages = [[NSMutableArray alloc] init];
    }
    return _allImages;
}

+ (JCResourcesManager*)sharedManager
{
    static JCResourcesManager* instance = nil;
    static dispatch_once_t dispatchOnce;
    dispatch_once(&dispatchOnce, ^{
        instance = [[JCResourcesManager alloc] init];
    });
    return instance;
}

- (JCImageResource*)addImageResource:(NSImage *)image config:(IsometricTileConfig*)config name:(NSString *)name
{
    if (image == nil || name == nil)
    {
        return nil;
    }
    
    JCImageResource* imageResource = [[JCImageResource alloc] initWidthImage:image config:config name:name];
    [[self allImages] addObject:imageResource];
    
    return imageResource;
}

- (NSInteger)getNumImageResources
{
    return [[self allImages] count];
}

- (JCImageResource*)getImageResourceAt:(NSUInteger)index
{
    if (index < [[NSNumber numberWithInt:0] unsignedIntegerValue] || index >= [[self allImages] count])
    {
        return nil;
    }
    return [[self allImages] objectAtIndex:index];
}

- (JCImageResource*)getImageResourceWithName:(NSString *)name
{
    NSInteger count = [self getNumImageResources];
    for (NSInteger i = 0; i < count; ++i)
    {
        JCImageResource* image = [self getImageResourceAt:i];
        if ([image.name isEqual:name])
        {
            return image;
        }
    }
    return nil;
}

- (BOOL)containsImageResourceWithName:(NSString *)name
{
    return [self getImageResourceWithName:name] != nil;
}

@end
