//
//  JCAddResourceWindowController.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-8.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCAddResourceWindowController.h"
#import "JCResourcesManager.h"
#import "JCAddImageResourceInformation.h"
#import "JCNotificationName.h"
#import "IsometricTileConfig.h"
#import "IsometricPairValue.h"
#import "IsometricPairValueGroup.h"

using namespace jcgame;

@interface JCAddResourceWindowController ()

@property (weak) IBOutlet NSTextField *texturePathInput;
@property (weak) IBOutlet NSTextField *configPathInput;
@property (weak) IBOutlet NSTextField *nameInput;

@end

@implementation JCAddResourceWindowController

@synthesize texturePathInput;
@synthesize configPathInput;
@synthesize nameInput;

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (IBAction)cancelButtonClickHandler:(id)sender
{
    [self close];
}

- (IBAction)addButtonClickHandler:(id)sender
{
    NSString* name = [nameInput stringValue];
    // Illegal name
    if ([name isEqual:@""])
    {
        NSLog(@"Empty name");
        return;
    }
    if ([[JCResourcesManager sharedManager] containsImageResourceWithName:name])
    {
        NSLog(@"Repeated name");
        return;
    }
    
    
    NSString* imagePath = [texturePathInput stringValue];
    NSImage* image = [[NSImage alloc] initWithContentsOfFile:imagePath];
    // image init fail
    if (image == nil)
    {
        NSLog(@"Image error");
        return;
    }
    
    NSData* fileData = [[NSFileManager defaultManager] contentsAtPath:[configPathInput stringValue]];
    NSString* fileStr = [[NSString alloc] initWithData:fileData encoding:NSUTF8StringEncoding];
    IsometricTileConfig* config = new IsometricTileConfig();
    bool configInitSuccess = config->init([fileStr cStringUsingEncoding:NSUTF8StringEncoding]);
    // config init fail;
    if (!configInitSuccess)
    {
        NSLog(@"Config error");
        return;
    }
    
    // store into manager
    JCImageResource* imageResource = [[JCResourcesManager sharedManager] addImageResource:image config:config name:name];
    
    // notify
    JCAddImageResourceInformation* information = [[JCAddImageResourceInformation alloc] initWithImageResource:imageResource];
    [[NSNotificationCenter defaultCenter] postNotificationName:[JCNotificationName addImageResource] object:nil userInfo:information];
    
    // close window
    [self.window close];
    NSLog(@"Add Resource Success");
}

- (IBAction)browseTexture:(id)sender
{
    NSOpenPanel* nsOpenPanel = [NSOpenPanel openPanel];
    [nsOpenPanel setCanChooseFiles:YES];
    [nsOpenPanel setCanCreateDirectories:NO];
    if([nsOpenPanel runModal] == NSOKButton)
    {
        NSString* path = [[nsOpenPanel URL] path];
        [texturePathInput setStringValue:path];
    }
    
}

- (IBAction)browseConfig:(id)sender
{
    NSOpenPanel* nsOpenPanel = [NSOpenPanel openPanel];
    [nsOpenPanel setCanChooseFiles:YES];
    [nsOpenPanel setCanCreateDirectories:NO];
    if([nsOpenPanel runModal] == NSOKButton)
    {
        NSString* path = [[nsOpenPanel URL] path];
        [configPathInput setStringValue:path];
    }
}


@end
