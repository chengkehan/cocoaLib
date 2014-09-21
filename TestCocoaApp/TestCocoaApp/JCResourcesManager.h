//
//  JCResourcesManager.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCImageResource.h"

@interface JCResourcesManager : NSObject

+ (JCResourcesManager*)sharedManager;

- (JCImageResource*)addImageResource:(NSImage*)image config:(jcgame::IsometricTileConfig*)config name:(NSString*)name;
- (NSInteger)getNumImageResources;
- (JCImageResource*)getImageResourceAt:(NSUInteger)index;
- (JCImageResource*)getImageResourceWithName:(NSString*)name;
- (BOOL)containsImageResourceWithName:(NSString*)name;

@end
