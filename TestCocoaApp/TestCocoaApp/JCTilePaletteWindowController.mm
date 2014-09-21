//
//  JCTilePaletteWindowController.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-15.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCTilePaletteWindowController.h"
#import "JCResourcesManager.h"
#import "JCImageResource.h"
#import "JCTilePaletteView.h"

@interface JCTilePaletteWindowController ()

@property (nonatomic, readwrite) JCImageResource* imageResource;
@property (nonatomic, readwrite) JCTilePaletteView* view;

@end

@implementation JCTilePaletteWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (void)showTilePalette:(NSString *)name
{
    if (self.imageResource == nil)
    {
        self.window.title = name;
        self.imageResource = [[JCResourcesManager sharedManager] getImageResourceWithName:name];
        
        self.view = (JCTilePaletteView*)self.window.contentView;
        [self.view initWithImageResource:self.imageResource];
        [self.view setScaleFactor:1];
    }
}

- (IBAction)onScaleFactorChange:(NSSlider *)sender
{
    [self.view setScaleFactor:sender.floatValue];
}

@end
