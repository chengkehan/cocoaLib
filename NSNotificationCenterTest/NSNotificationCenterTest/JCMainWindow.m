//
//  JCMainWindow.m
//  NSNotificationCenterTest
//
//  Created by jimCheng on 14-8-23.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainWindow.h"
#import "JCClassA.h"
#import "JCClassB.h"

@implementation JCMainWindow

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    if (self)
    {
        JCClassA* classA = [[JCClassA alloc] init];
        JCClassB* classB = [[JCClassB alloc]init];
    }
    return self;
}

@end
