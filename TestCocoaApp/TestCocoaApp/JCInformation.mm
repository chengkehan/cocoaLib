//
//  JCInformation.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-8.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCInformation.h"

@implementation JCInformation

- (void)setInformation:(NSString *)key value:(id)value
{
    [self setValue:value forKey:key];
}

- (id)getInformation:(NSString *)key
{
    return [self valueForKey:key];
}

@end
