//
//  JCWindowManager.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-10.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCWindowManager.h"
#import "JCMainWindowController.h"
#import "JCAddResourceWindowController.h"
#import "JCNewSceneWindowController.h"
#import "JCTilePaletteWindowController.h"

@interface JCWindowManager()

@property (nonatomic, readwrite) JCMainWindowController* mainWindow;
@property (nonatomic, readwrite) JCAddResourceWindowController* addResourceWindow;
@property (nonatomic, readwrite) JCNewSceneWindowController* createSceneWindow;
@property (nonatomic, readwrite) NSMutableDictionary* tilePaletteMap;

@end

@implementation JCWindowManager

+ (JCWindowManager*)sharedManager
{
    static JCWindowManager* instance = nil;
    static dispatch_once_t dispatchOnce;
    dispatch_once(&dispatchOnce, ^{
        instance = [[JCWindowManager alloc] init];
    });
    return instance;
}

- (void)showMainWindow
{
    if(self.mainWindow == nil)
    {
        self.mainWindow = [[JCMainWindowController alloc] initWithWindowNibName:@"Main"];
    }
    [self.mainWindow showWindow:self];
    [self.mainWindow.window center];
}

- (void)showAddResourceWindow
{
    if (self.addResourceWindow == nil)
    {
        self.addResourceWindow = [[JCAddResourceWindowController alloc] initWithWindowNibName:@"AddResource"];
    }
    [self.addResourceWindow showWindow:self];
    [self.addResourceWindow.window center];
    [self.mainWindow.window addChildWindow:self.addResourceWindow.window ordered:NSWindowAbove];
}

- (void)showNewSceneWindow
{
    if (self.createSceneWindow == nil)
    {
        self.createSceneWindow = [[JCNewSceneWindowController alloc] initWithWindowNibName:@"NewSceneWindow"];
    }
    [self.createSceneWindow showWindow:self];
    [self.createSceneWindow.window center];
    [self.mainWindow.window addChildWindow:self.createSceneWindow.window ordered:NSWindowAbove];
}

- (void)showTilePalette:(NSString *)name
{
    JCTilePaletteWindowController* windowController = [self.tilePaletteMap objectForKey:name];
    if (windowController == nil)
    {
        windowController = [[JCTilePaletteWindowController alloc] initWithWindowNibName:@"TilePalette"];
        [self.tilePaletteMap setObject:windowController forKey:name];
    }
    [windowController showWindow:self];
//    [windowController.window center];
    [self.mainWindow.window addChildWindow:windowController.window ordered:NSWindowAbove];
    [windowController showTilePalette:name];
}

- (NSDictionary*)tilePaletteMap
{
    if (_tilePaletteMap == nil)
    {
        _tilePaletteMap = [[NSMutableDictionary alloc] init];
    }
    return _tilePaletteMap;
}

@end
