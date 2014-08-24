//
//  JCClassA.m
//  NSNotificationCenterTest
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCClassA.h"

@implementation JCClassA

- (id)init
{
    self = [super init];
    if (self) {
        NSLog(@"JCClassA init");
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(notificationHandler:) name:@"msgA" object:nil];
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    // The compiler will do this automatically
    //[super dealloc];
}

- (void)notificationHandler:(NSNotification*)notification
{
    NSLog(@"JCClassA notificationHandler");
    NSLog(@"notification name %@", [notification name]);
    NSLog(@"notification object %@", [notification object]);
    NSLog(@"notification userInfo %@", [notification userInfo]);
}

@end
