//
//  JCTilePaletteView.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-15.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCTilePaletteView.h"
#import "IsometricTileConfig.h"
#import "JCDataManager.h"

using namespace jcgame;

@interface JCTilePaletteView()

@property (nonatomic, readwrite) JCImageResource* imageResource;
@property (nonatomic, readwrite) float m_scaleFactor;
@property (nonatomic, readwrite) NSPoint mousePosition;
@property (nonatomic, readwrite) NSMutableArray* allFrames;

@end

@implementation JCTilePaletteView

- (NSMutableArray*)allFrames
{
    if (_allFrames == nil)
    {
        _allFrames = [[NSMutableArray alloc] init];
    }
    return _allFrames;
}

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    [self.allFrames removeAllObjects];
    
    // Get context
    CGContextRef context = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
    // Fill background
    CGContextSetRGBFillColor(context, 0, 0, 0, 0.8);
    CGContextFillRect(context, NSMakeRect(0, 0, self.bounds.size.width, self.bounds.size.height));
    
    // Draw tiles
    if (self.imageResource != nil)
    {
        NSRect selfBounds = self.bounds;
        NSPoint point = NSMakePoint(0, selfBounds.size.height);
        int lineHeight = 0;
        
        IsometricTileConfig* config = self.imageResource.config;
        const IsometricTileConfig_Metadata* metadata = config->getMetadata();
        
        int numFrames = config->getNumFrames();
        float scaleFactor = self.m_scaleFactor;
        for (int i = 0; i < numFrames; ++i)
        {
            const IsometricTileConfig_Frame* frame = config->getFrame(i);
            const IsometricTileConfig_Bounds* bounds = &frame->frame;
            
            // newline
            if (point.x + bounds->size.width * scaleFactor > selfBounds.size.width)
            {
                point.x = 0;
                point.y -= lineHeight * scaleFactor;
                lineHeight = 0;
            }
            
            NSRect drawFrame = NSMakeRect(point.x, point.y, bounds->size.width * scaleFactor, -bounds->size.height * scaleFactor);
            point.x += bounds->size.width * scaleFactor;
            
            // line height
            if (bounds->size.height > lineHeight)
            {
                lineHeight = bounds->size.height;
            }
            
            NSValue* drawFrameValue = [NSValue valueWithRect:drawFrame];
            [self.allFrames addObject:drawFrameValue];
            
            [self.imageResource.image drawInRect:drawFrame fromRect:NSMakeRect(bounds->point.x, metadata->size.height - bounds->point.y - bounds->size.height, bounds->size.width, bounds->size.height) operation:NSCompositeSourceOver fraction:1];
        }
        
        // Draw selection
        if ([[JCDataManager sharedManager].strokeImageResource.imageResourceName isEqual:self.imageResource.name])
        {
            // by index
            for (int i = 0; i < numFrames; ++i)
            {
                if ([JCDataManager sharedManager].strokeImageResource.frameIndex == i)
                {
                    NSValue* drawFrameValue = [self.allFrames objectAtIndex:i];
                    NSRect drawFrame = drawFrameValue.rectValue;
                    
                    // Draw selection box
                    CGContextSetRGBFillColor(context, 1, 0, 0, 0.5);
                    CGContextFillRect(context, drawFrame);
                    
                    break;
                }
            }
        }
        else
        {
            // by mousePosition
            for (int i = 0; i < numFrames; ++i)
            {
                NSValue* drawFrameValue = [self.allFrames objectAtIndex:i];
                NSRect drawFrame = drawFrameValue.rectValue;
                // In frame area
                if (self.mousePosition.x > drawFrame.origin.x &&
                    self.mousePosition.x < drawFrame.origin.x + drawFrame.size.width &&
                    self.mousePosition.y < drawFrame.origin.y &&
                    self.mousePosition.y > drawFrame.origin.y + drawFrame.size.height)
                {
                    // Draw selection box
                    CGContextSetRGBFillColor(context, 1, 0, 0, 0.5);
                    CGContextFillRect(context, drawFrame);
                    
                    // Set stroke
                    [JCDataManager sharedManager].strokeImageResource.imageResourceName = self.imageResource.name;
                    [JCDataManager sharedManager].strokeImageResource.frameIndex = i;
                    
                    break;
                }
            }
        }
    }
}

- (void)initWithImageResource:(JCImageResource *)imageResource
{
    self.imageResource = imageResource;
    [self setNeedsDisplay:YES];
    
}

- (void)setScaleFactor:(float)scaleFactor
{
    self.m_scaleFactor = scaleFactor;
    [self setNeedsDisplay:YES];
}

- (void)mouseDown:(NSEvent *)theEvent
{
    self.mousePosition = theEvent.locationInWindow;
    [[JCDataManager sharedManager] resetStrokeImageResource];
    [self setNeedsDisplay:YES];
}

@end
