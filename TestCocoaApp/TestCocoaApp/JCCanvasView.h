//
//  JCCanvasView.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-17.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Cocoa/Cocoa.h>

enum StrokeType
{
    STROKE_TYPE_HAND,
    STROKE_TYPE_PEN
};

@interface JCCanvasView : NSView

@property (nonatomic, readwrite) enum StrokeType strokeType;

- (void)showGrid;
- (void)hideGrid;

- (void)floorGridVisibleAt:(int)index;

@end
