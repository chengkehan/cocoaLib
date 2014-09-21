//
//  JCAddResourceInformation.h
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-8.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCInformation.h"
#import "JCImageResource.h"

@interface JCAddImageResourceInformation : JCInformation

@property (nonatomic, readwrite) JCImageResource* imageResource;

- (id)initWithImageResource:(JCImageResource*)imageResource;

@end
