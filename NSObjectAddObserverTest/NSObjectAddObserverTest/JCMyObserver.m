//
//  JCMyObserver.m
//  NSObjectAddObserverTest
//
//  Created by jimCheng on 14-8-23.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMyObserver.h"

@implementation JCMyObserver

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"age"])
    {
        NSLog(@"JCMyObserver");
        NSLog(@"old age is %@", [change objectForKey:@"old"]);
        NSLog(@"new age is %@", [change objectForKey:@"new"]);
    }
    else
    {
//        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

@end
