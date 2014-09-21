//
//  JCInformation.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-8.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JCInformation : NSDictionary

- (void)setInformation:(NSString*)key value:(id)value;
- (id)getInformation:(NSString*)key;

@end
