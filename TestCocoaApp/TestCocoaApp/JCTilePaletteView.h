//
//  JCTilePaletteView.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-15.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "JCImageResource.h"

@interface JCTilePaletteView : NSView

- (void)initWithImageResource:(JCImageResource*)imageResource;
- (void)setScaleFactor:(float)scaleFactor;

@end
