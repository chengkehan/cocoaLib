//
//  JCDataManager.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-12.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCDataManager.h"
#import "IsometricModel.h"

using namespace jcgame;

@interface JCDataManager()

@end

@implementation JCDataManager

@synthesize isometricModel = _isometricModel;
@synthesize strokeImageResource = _strokeImageResource;

+ (JCDataManager*)sharedManager
{
    static JCDataManager* instance = nil;
    static dispatch_once_t dispatchOnce;
    dispatch_once(&dispatchOnce, ^{
        instance = [[JCDataManager alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if (self)
    {
        _strokeImageResource = [[JCStrokeImageResource alloc] init];
    }
    return self;
}

- (IsometricModel*)isometricModel
{
    return _isometricModel;
}

- (void)initIsometricModel
{
    if (_isometricModel == nil)
    {
        _isometricModel = new IsometricModel();
    }
}

- (void)destroyIsometric
{
    if (_isometricModel != nil)
    {
        delete _isometricModel;
        _isometricModel = nil;
    }
}

- (void)resetStrokeImageResource
{
    _strokeImageResource.imageResourceName = nil;
}

@end
