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
#import "IsometricAlgorithm.h"

using namespace jcgame;

@interface JCCanvasView()

@property (nonatomic, readwrite) BOOL gridVisible;
@property (nonatomic, readwrite) NSPoint origin;
@property (nonatomic, readwrite) CGFloat originCrossOffsetX;
@property (nonatomic, readwrite) CGFloat originCrossOffsetY;
@property (nonatomic, readwrite) int floorVisibleIndex;
@property (nonatomic, readwrite) int focusRow;
@property (nonatomic, readwrite) int focusCol;

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
        
        // Initialize trackingArea
        NSTrackingArea* trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:NSTrackingMouseMoved | NSTrackingActiveInKeyWindow | NSTrackingInVisibleRect owner:self userInfo:nil];
        [self addTrackingArea:trackingArea];
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
    self.origin = origin;
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
                        IsometricAlgorithm_Point isoStartPoint = IsometricAlgorithm::isoWorldToScreen(startPoint.x, -floor * cellSize, startPoint.y);
                        IsometricAlgorithm_Point isoEndPoint = IsometricAlgorithm::isoWorldToScreen(endPoint.x, -floor * cellSize, endPoint.y);
                        startPoint.x = isoStartPoint.x;
                        startPoint.y = isoStartPoint.y;
                        endPoint.x = isoEndPoint.x;
                        endPoint.y = isoEndPoint.y;
                        CGContextMoveToPoint(context, origin.x + startPoint.x, origin.y - startPoint.y);
                        CGContextAddLineToPoint(context, origin.x + endPoint.x, origin.y - endPoint.y);
                    }
                    
                    for (int col = 0; col <= cols; ++col)
                    {
                        NSPoint startPoint = NSMakePoint(col * cellSize, 0);
                        NSPoint endPoint = NSMakePoint(col * cellSize, rows * cellSize);
                        IsometricAlgorithm_Point isoStartPoint = IsometricAlgorithm::isoWorldToScreen(startPoint.x, -floor * cellSize, startPoint.y);
                        IsometricAlgorithm_Point isoEndPoint = IsometricAlgorithm::isoWorldToScreen(endPoint.x, -floor * cellSize, endPoint.y);
                        startPoint.x = isoStartPoint.x;
                        startPoint.y = isoStartPoint.y;
                        endPoint.x = isoEndPoint.x;
                        endPoint.y = isoEndPoint.y;
                        CGContextMoveToPoint(context, origin.x + startPoint.x, origin.y - startPoint.y);
                        CGContextAddLineToPoint(context, origin.x + endPoint.x, origin.y - endPoint.y);
                    }
                }
            }

            CGContextStrokePath(context);
        }
    }
    
    // Draw focus
    if (self.strokeType == STROKE_TYPE_PEN)
    {
        IsometricModel* isometricModel = [JCDataManager sharedManager].isometricModel;
        if (isometricModel != nil)
        {
            // setup focus stroke
            CGContextSetLineWidth(context, 2);
            CGContextSetRGBStrokeColor(context, 0, 2, 0, 1);
            
            int floor = self.floorVisibleIndex == -1 ? 0 : self.floorVisibleIndex;
            int cellSize = isometricModel->getCellSize();
            
            IsometricAlgorithm_Point isoP0 = IsometricAlgorithm::isoWorldToScreen(self.focusCol * cellSize, -floor * cellSize, self.focusRow * cellSize);
            CGContextMoveToPoint(context, origin.x + isoP0.x, origin.y - isoP0.y);
            
            IsometricAlgorithm_Point isoP1 = IsometricAlgorithm::isoWorldToScreen((self.focusCol + 1) * cellSize, -floor * cellSize, self.focusRow * cellSize);
            CGContextAddLineToPoint(context, origin.x + isoP1.x, origin.y - isoP1.y);
            
            IsometricAlgorithm_Point isoP2 = IsometricAlgorithm::isoWorldToScreen((self.focusCol + 1) * cellSize, -floor * cellSize, (self.focusRow + 1) * cellSize);
            CGContextAddLineToPoint(context, origin.x + isoP2.x, origin.y - isoP2.y);
            
            IsometricAlgorithm_Point isoP3 = IsometricAlgorithm::isoWorldToScreen(self.focusCol * cellSize, -floor * cellSize, (self.focusRow + 1) * cellSize);
            CGContextAddLineToPoint(context, origin.x + isoP3.x, origin.y - isoP3.y);
            
            CGContextAddLineToPoint(context, origin.x + isoP0.x, origin.y - isoP0.y);
            
            CGContextStrokePath(context);
        }
    }
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    // Store dragDelta
    if (self.strokeType == STROKE_TYPE_HAND)
    {
        self.originCrossOffsetX += theEvent.deltaX;
        self.originCrossOffsetY -= theEvent.deltaY;
        [self setNeedsDisplay:YES];
    }
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    // Store focus
    IsometricModel* isometricModel = [JCDataManager sharedManager].isometricModel;
    if (isometricModel != nil)
    {
        int floor = self.floorVisibleIndex == -1 ? 0 : self.floorVisibleIndex;
        NSPoint touchPoint = [self convertPoint:theEvent.locationInWindow fromView:self.window.contentView];
        NSPoint point = NSMakePoint(touchPoint.x - self.origin.x, -(self.origin.y - touchPoint.y));
        IsometricAlgorithm_Point isoPoint = IsometricAlgorithm::isoScreenToWorld(point.x, point.y - IsometricAlgorithm::isoScreenFloorHeight(floor * isometricModel->getCellSize()));
        int row = -isoPoint.x / isometricModel->getCellSize();
        int col = -isoPoint.y / isometricModel->getCellSize();
        if (row >= 0 && row < isometricModel->getRows() && col >= 0 && col < isometricModel->getCols())
        {
            self.focusRow = row;
            self.focusCol = col;
            [self setNeedsDisplay:YES];
        }
    }
}

- (void)mouseDown:(NSEvent *)theEvent
{
    // Store tile data
    if (self.strokeType == STROKE_TYPE_PEN)
    {
        IsometricModel* isometricModel = [JCDataManager sharedManager].isometricModel;
        if (isometricModel != nil)
        {
            NSString* imageResourceName = [JCDataManager sharedManager].strokeImageResource.imageResourceName;
        }
    }
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

- (void)newSceneNotification:(NSNotification*)notification
{
    [self setNeedsDisplay:YES];
}

@end
