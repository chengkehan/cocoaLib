//
//  JCMainView.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-17.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainView.h"
#import "JCCanvasView.h"

@implementation JCMainView

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self)
    {
        JCCanvasView* canvas = [[JCCanvasView alloc] initWithFrame:self.bounds];
        [self addSubview:canvas];
//        [self setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
//        [self setAutoresizesSubviews:YES];
    }
    return self;
}

@end
