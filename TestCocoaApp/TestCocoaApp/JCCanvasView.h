//
//  JCCanvasView.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-17.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface JCCanvasView : NSView

- (void)showGrid;
- (void)hideGrid;

- (void)floorGridVisibleAt:(int)index;

@end
