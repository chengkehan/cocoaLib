//
//  JCWindowManager.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-10.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JCWindowManager : NSObject

+ (JCWindowManager*)sharedManager;

- (void)showMainWindow;
- (void)showAddResourceWindow;
- (void)showNewSceneWindow;
- (void)showTilePalette:(NSString*)name;

@end
