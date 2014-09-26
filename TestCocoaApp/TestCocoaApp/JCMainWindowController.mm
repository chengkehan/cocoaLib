//
//  JCMainWindowController.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-7.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCMainWindowController.h"
#import "JCNotificationName.h"
#import "JCAddImageResourceInformation.h"
#import "JCWindowManager.h"
#import "JCDataManager.h"
#import "JCCanvasView.h"
#import "IsometricModel.h"

using namespace jcgame;

@interface JCMainWindowController ()

@property (weak) IBOutlet NSTableView *resourcesTableView;
@property (nonatomic, readwrite) NSMutableArray* resourcesListOfTableView;
@property (weak) IBOutlet NSComboBox *floorsOption;
@property (nonatomic, readwrite) JCCanvasView* canvas;

@end

@implementation JCMainWindowController

- (NSMutableArray*)resourcesListOfTableView
{
    if (_resourcesListOfTableView == nil)
    {
        _resourcesListOfTableView = [[NSMutableArray alloc] init];
    }
    return _resourcesListOfTableView;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    
    // notification
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(addImageResourceNotification:) name:[JCNotificationName addImageResource] object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newSceneNotification:) name:[JCNotificationName newScene] object:nil];
    
    // NSTableView init
    self.resourcesTableView.dataSource = self;
    self.resourcesTableView.delegate = self;
    
    // Find Canvas
    NSArray* subViews = [self.window.contentView subviews];
    for(NSView* subView in subViews)
    {
        if ([subView.identifier isEqual:@"CanvasView"])
        {
            self.canvas = (JCCanvasView*)subView;
            break;
        }
    }
    if (self.canvas == nil)
    {
        NSLog(@"Missing CanvasView!");
    }    
}

// Receive a notification of AddImageResource
- (void)addImageResourceNotification:(NSNotification*)notification
{
    JCAddImageResourceInformation* information = (JCAddImageResourceInformation*)notification.userInfo;
    [self.resourcesListOfTableView addObject:information.imageResource.name];
    [self.resourcesTableView reloadData];
}

// Receive a notification of NewScene
- (void)newSceneNotification:(NSNotification*)notification
{
    [self.floorsOption removeAllItems];
    
    IsometricModel* isometricModel = [JCDataManager sharedManager].isometricModel;
    int floors = isometricModel->getFloors();
    for (int i = 0; i < floors; ++i)
    {
        NSString* label = [NSString stringWithFormat:@"%d", i];
        [self.floorsOption addItemWithObjectValue:label];
    }
    [self.floorsOption addItemWithObjectValue:@"-1"];
    [self.floorsOption selectItemAtIndex:floors];
}

// Click AddResource button
- (IBAction)onClickAddResource:(id)sender
{
    [[JCWindowManager sharedManager]showAddResourceWindow];
}

// Click NewScene button
- (IBAction)onClickNewScene:(id)sender
{
    [[JCWindowManager sharedManager]showNewSceneWindow];
}

// Grid Visible changed
- (IBAction)onChangeGridVisible:(NSButton *)sender
{
    if (sender.state == NSOnState)
    {
        [self.canvas showGrid];
    }
    else
    {
        [self.canvas hideGrid];
    }
}

// Switch to show one floor or all
- (IBAction)onChangeFloorVisible:(NSComboBox *)sender
{
    id selectedItem = sender.objectValueOfSelectedItem;
    if (selectedItem != nil)
    {
        NSString* label = selectedItem;
        int floor = label.intValue;
        [self.canvas floorGridVisibleAt:floor];
    }
}

// Use pen to draw tile
- (IBAction)usePenHandler:(id)sender
{
    self.canvas.strokeType = STROKE_TYPE_PEN;
}

// Use hand to drag canvas
- (IBAction)useHandHandler:(id)sender
{
    self.canvas.strokeType = STROKE_TYPE_HAND;
}

// Implements NSTableViewDelegate
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    return self.resourcesListOfTableView.count;
}

// Implements NSTableViewDataSource
- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    // Create cell
    NSString* label = [self.resourcesListOfTableView objectAtIndex:row];
    NSString *identifier = [tableColumn identifier];
    NSTextField *textField = [tableView makeViewWithIdentifier:identifier owner:self];
    if (textField == nil)
    {
        textField = [[NSTextField alloc] init];
        textField.drawsBackground = NO;
        [textField setBordered:NO];
    }
    textField.stringValue = label;
    return textField;
}

// Implements NSTableViewDataSource
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row
{
    if (row < 0 || row >= self.resourcesListOfTableView.count)
    {
        return NO;
    }
    else
    {
        NSString* resourceName = [self.resourcesListOfTableView objectAtIndex:row];
        [[JCWindowManager sharedManager] showTilePalette:resourceName];
        return YES;
    }
}

@end
