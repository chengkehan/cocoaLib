//
//  JCDataManager.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-12.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCStrokeImageResource.h"

namespace jcgame
{
    class IsometricModel;
}

@interface JCDataManager : NSObject

@property (nonatomic, readonly) JCStrokeImageResource* strokeImageResource;
@property (nonatomic, readonly) jcgame::IsometricModel* isometricModel;

+ (JCDataManager*)sharedManager;

- (void)initIsometricModel;
- (void)destroyIsometric;

- (void)resetStrokeImageResource;

@end
