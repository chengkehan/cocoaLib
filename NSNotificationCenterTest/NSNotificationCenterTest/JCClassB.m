//
//  JCClassB.m
//  NSNotificationCenterTest
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCClassB.h"

@implementation JCClassB

- (id)init
{
    self = [super init];
    if (self) {
        NSLog(@"JCClassB init");
        [[NSNotificationCenter defaultCenter] postNotificationName:@"msgA" object:self userInfo:@{@"data": @"data of msgA"}];
    }
    return self;
}

@end
