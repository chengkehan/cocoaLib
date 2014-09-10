//
//  JCMainWindow.m
//  XMLTest
//
//  Created by jimCheng on 14-8-24.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainWindow.h"

@implementation JCMainWindow

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    if (self)
    {
        NSError* error = nil;
        NSURL* url = [NSURL fileURLWithPath:@"/Users/jimCheng/projects/TileResources/testTiles/Untitled.plist"];
        NSXMLDocument* doc = [[NSXMLDocument alloc] initWithContentsOfURL:url options:NSXMLDocumentTidyXML error:&error];
    }
    return self;
}

@end
