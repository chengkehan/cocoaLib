//
//  JCMainWindow.m
//  GCDTest
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainWindow.h"

@implementation JCMainWindow

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    if (self) {
        // main queue
//        dispatch_get_main_queue();
        
        // global queue
//        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        
        // custom queue
//        dispatch_queue_create("com.jcgame.GCDTest", DISPATCH_QUEUE_CONCURRENT);
        
        // dispatch_async
        __block NSInteger myInt = 0;
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSLog(@"log from async global queue");
            myInt = 10;
        });
        NSLog(@"log after async dispatch_async");
        NSLog(@"%ld", myInt);
        
        // dispatch_sync
        dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSLog(@"log from sync global queue");
            myInt = 20;
        });
        NSLog(@"log after sync dispatch_async");
        NSLog(@"%ld", myInt);
        
        // dispatch_group
        {
            dispatch_queue_t groupQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
            dispatch_group_t group = dispatch_group_create();
            dispatch_group_async(group, groupQueue, ^{
                NSLog(@"async group maybe 1");
            });
            dispatch_group_async(group, groupQueue, ^{
                NSLog(@"async group maybe 2");
            });
            dispatch_group_async(group, groupQueue, ^{
                NSLog(@"async group maybe 3");
            });
            dispatch_group_notify(group, groupQueue, ^{
                NSLog(@"async group end");
            });
        }
        
        // semaphore
        {
            dispatch_group_t group = dispatch_group_create();
            dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
            dispatch_semaphore_t semaphore = dispatch_semaphore_create(10);
            for (int i = 0; i < 100; ++i) {
                dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
                dispatch_group_async(group, queue, ^{
                    NSLog(@"%d", i);
                    dispatch_semaphore_signal(semaphore);
//                    sleep(2);
                });
            }
            dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
            NSLog(@"semaphone tasks all complete");
        }
        
    }
    return self;
}

@end
