//
//  JCCanvasView.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-17.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCCanvasView.h"
#import "JCResourcesManager.h"
#import "JCImageResource.h"
#import "JCDataManager.h"
#import "JCNotificationName.h"
#import "IsometricModel.h"

using namespace jcgame;

@interface JCCanvasView()

@property (nonatomic, readwrite) BOOL gridVisible;
@property (nonatomic, readwrite) CGFloat originCrossOffsetX;
@property (nonatomic, readwrite) CGFloat originCrossOffsetY;
@property (nonatomic, readwrite) int floorVisibleIndex;

@end

@implementation JCCanvasView

- (void)showGrid
{
    self.gridVisible = YES;
    [self setNeedsDisplay:YES];
}

- (void)hideGrid
{
    self.gridVisible = NO;
    [self setNeedsDisplay:YES];
}

- (void)floorGridVisibleAt:(int)index
{
    self.floorVisibleIndex = index;
    [self setNeedsDisplay:YES];
}

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
        self.identifier = @"CanvasView";
        
        // Notification handler
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newSceneNotification:) name:[JCNotificationName newScene] object:nil];
        
        self.gridVisible = YES;
        self.floorVisibleIndex = -1;
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    CGSize boundsSize = self.bounds.size;
    
    // Drawing code here.
    // Fill in background Color
    CGContextRef context = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
    CGContextSetRGBFillColor(context, 0, 0, 0, 0.8);
    CGContextFillRect(context, NSMakeRect(0, 0, boundsSize.width, boundsSize.height));
    
    // setup stroke
    CGContextSetLineWidth(context, 1);
    CGContextSetRGBStrokeColor(context, 1, 0, 0, 1);
    
    // Draw origin cross
    NSPoint origin = NSMakePoint(boundsSize.width * 0.5, boundsSize.height * 0.5);
    // Drag offset
    origin.x += self.originCrossOffsetX;
    origin.y += self.originCrossOffsetY;
    // Limit in range
    int padding = 50;
    if (origin.x < padding)
    {
        origin.x = padding;
    }
    else if (origin.x > boundsSize.width - padding)
    {
        origin.x = boundsSize.width - padding;
    }
    if (origin.y < padding)
    {
        origin.y = padding;
    }
    else if (origin.y > boundsSize.height - padding)
    {
        origin.y = boundsSize.height - padding;
    }
    // Draw
    CGContextMoveToPoint(context, origin.x, origin.y + 10);
    CGContextAddLineToPoint(context, origin.x, origin.y - 10);
    CGContextMoveToPoint(context, origin.x - 10, origin.y);
    CGContextAddLineToPoint(context, origin.x + 10, origin.y);
    CGContextStrokePath(context);
    
    // Draw grid
    if (self.gridVisible)
    {
        IsometricModel* isometricModel = [JCDataManager sharedManager].isometricModel;
        if (isometricModel != nil)
        {
            int floors = isometricModel->getFloors();
            int rows = isometricModel->getRows();
            int cols = isometricModel->getCols();
            int cellSize = isometricModel->getCellSize();
            
            for (int floor = 0; floor < floors; ++floor)
            {
                if (self.floorVisibleIndex == -1 || floor == self.floorVisibleIndex)
                {
                    for (int row = 0; row <= rows; ++row)
                    {
                        NSPoint startPoint = NSMakePoint(0, row * cellSize);
                        NSPoint endPoint = NSMakePoint(cols * cellSize, row * cellSize);
                        startPoint = [self isoWorldToScreen:startPoint.x y:floor * cellSize z:startPoint.y];
                        endPoint = [self isoWorldToScreen:endPoint.x y:floor * cellSize z:endPoint.y];
                        CGContextMoveToPoint(context, origin.x + startPoint.x, origin.y - startPoint.y);
                        CGContextAddLineToPoint(context, origin.x + endPoint.x, origin.y - endPoint.y);
                    }
                    
                    for (int col = 0; col <= cols; ++col)
                    {
                        NSPoint startPoint = NSMakePoint(col * cellSize, 0);
                        NSPoint endPoint = NSMakePoint(col * cellSize, rows * cellSize);
                        startPoint = [self isoWorldToScreen:startPoint.x y:floor * cellSize z:startPoint.y];
                        endPoint = [self isoWorldToScreen:endPoint.x y:floor * cellSize z:endPoint.y];
                        CGContextMoveToPoint(context, origin.x + startPoint.x, origin.y - startPoint.y);
                        CGContextAddLineToPoint(context, origin.x + endPoint.x, origin.y - endPoint.y);
                    }
                }
            }

            CGContextStrokePath(context);
        }
    }
    
    // test draw tiles
//    if ([[JCResourcesManager sharedManager] getNumImageResources] == 1)
//    {
//        NSPoint origin = NSMakePoint(self.bounds.size.width * 0.5, self.bounds.size.height);
//        JCImageResource* imageResource = [[JCResourcesManager sharedManager] getImageResourceAt:0];
//        
//        // test draw line
//        CGContextSetLineWidth(context, 2);
//        CGContextSetRGBStrokeColor(context, 1, 0, 0, 1);
//        CGContextMoveToPoint(context, origin.x, origin.y);
//        CGContextAddLineToPoint(context, origin.x - 200, origin.y - 200);
//        CGContextStrokePath(context);
    
//        origin.x -= 64;
//        origin.y -= 128;
//        
//        for (int i = 0; i < 10; ++i)
//        {
//            for (int j = 0; j < 10; ++j)
//            {
//                NSPoint drawAtPoint = [self isoWorldToScreen:i * 60 y:0 z:j * 60];
//                drawAtPoint.x = origin.x - drawAtPoint.x;
//                drawAtPoint.y = origin.y - drawAtPoint.y;
//                
//                [imageResource.image drawAtPoint:drawAtPoint fromRect:NSMakeRect(0, imageResource.image.size.height - 128, 128, 128) operation:NSCompositeSourceOver fraction:1];
//            }
//        }
//        
//        for (int i = 5; i < 8; ++i)
//        {
//            for (int j = 5; j < 8; ++j)
//            {
//                NSPoint drawAtPoint = [self isoWorldToScreen:i * 60 y:2 * 60 z:j * 60];
//                drawAtPoint.x = origin.x - drawAtPoint.x;
//                drawAtPoint.y = origin.y - drawAtPoint.y;
//                
//                [imageResource.image drawAtPoint:drawAtPoint fromRect:NSMakeRect(0, imageResource.image.size.height - 128, 128, 128) operation:NSCompositeSourceOver fraction:1];
//            }
//        }
//    }
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    self.originCrossOffsetX += theEvent.deltaX;
    self.originCrossOffsetY -= theEvent.deltaY;
    [self setNeedsDisplay:YES];
}

- (void)resizeWithOldSuperviewSize:(NSSize)oldSize
{
    NSRect myBounds = self.superview.bounds;
    myBounds.size.width -= 200;
    myBounds.origin.x = 200;
    [self setFrame:myBounds];
}

- (void)viewDidMoveToSuperview
{
    NSRect myBounds = self.superview.bounds;
    myBounds.size.width -= 200;
    myBounds.origin.x = 200;
    [self setFrame:myBounds];
    [self setNeedsDisplay:YES];
}

- (NSPoint)isoWorldToScreen:(int)x y:(int)y z:(int)z
{
    NSPoint point;
    point.x = x - z;
    point.y = -y * 1.2247 + (x + z) * 0.5;
    return point;
}

- (void)newSceneNotification:(NSNotification*)notification
{
    [self setNeedsDisplay:YES];
}

@end
