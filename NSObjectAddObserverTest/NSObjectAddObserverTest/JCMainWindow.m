//
//  JCMainWindow.m
//  NSObjectAddObserverTest
//
//  Created by jimCheng on 14-8-23.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainWindow.h"
#import "JCMyObserver.h"
#import "JCMyObserver2.h"
#import "JCMySubject.h"

@implementation JCMainWindow

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    if (self)
    {
        JCMyObserver* observer = [[JCMyObserver alloc] init];
        JCMyObserver2* observer2 = [[JCMyObserver2 alloc] init];
        JCMySubject* subject = [[JCMySubject alloc] init];
        
        [subject addObserver:observer forKeyPath:@"age" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:nil];
        [subject addObserver:observer2 forKeyPath:@"age" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:nil];
        
        subject.age = 10;
        
        [subject removeObserver:observer forKeyPath:@"age"];
        [subject removeObserver:observer2 forKeyPath:@"age"];
    }
    return self;
}

@end
