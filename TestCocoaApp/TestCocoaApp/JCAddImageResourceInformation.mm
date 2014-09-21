//
//  JCAddResourceInformation.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-8.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCAddImageResourceInformation.h"

@implementation JCAddImageResourceInformation

- (id)initWithImageResource:(JCImageResource *)imageResource
{
    self = [super init];
    if (self)
    {
        self.imageResource = imageResource;
    }
    return self;
}

@end
