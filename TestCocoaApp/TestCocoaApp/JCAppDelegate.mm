//
//  JCAppDelegate.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-8-16.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCAppDelegate.h"
#import "JCWindowManager.h"

@interface JCAppDelegate()

@end

@implementation JCAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSLog(@"Application did finish launching");
    [[JCWindowManager sharedManager]showMainWindow];
}

@end
