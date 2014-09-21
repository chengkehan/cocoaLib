//
//  JCNewSceneWindowController.m
//  TestCocoaApp
//
//  Created by jimCheng on 14-9-10.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#import "JCNewSceneWindowController.h"
#import "JCDataManager.h"
#import "JCNotificationName.h"
#import "IsometricModel.h"

@interface JCNewSceneWindowController ()

@property (weak) IBOutlet NSTextField *floorsInput;
@property (weak) IBOutlet NSTextField *rowsInput;
@property (weak) IBOutlet NSTextField *colsInput;
@property (weak) IBOutlet NSTextField *cellSizeInput;

@end

@implementation JCNewSceneWindowController

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

- (IBAction)onCreate:(id)sender
{
    if ([JCDataManager sharedManager].isometricModel != nil)
    {
        NSLog(@"error isometricModel");
        return;
    }
    
    NSString* floorsStr = self.floorsInput.stringValue;
    NSString* rowsStr = self.rowsInput.stringValue;
    NSString* colsStr = self.colsInput.stringValue;
    NSString* cellSizeStr = self.cellSizeInput.stringValue;
    
    if ([floorsStr isEqual:@""])
    {
        NSLog(@"Empty floors");
        return;
    }
    
    if ([rowsStr isEqual:@""])
    {
        NSLog(@"Empty rows");
        return;
    }
    
    if ([colsStr isEqual:@""])
    {
        NSLog(@"Empty cols");
        return;
    }
    
    if ([cellSizeStr isEqual:@""])
    {
        NSLog(@"error cellSize");
        return;
    }
    
    int floors = floorsStr.intValue;
    int rows = rowsStr.intValue;
    int cols = colsStr.intValue;
    int cellSize = cellSizeStr.intValue;
    
    if (floors < 1)
    {
        NSLog(@"Illegal floors");
        return;
    }
    
    if (rows < 1)
    {
        NSLog(@"Illegal rows");
        return;
    }
    
    if (cols < 1)
    {
        NSLog(@"Illegal cols");
        return;
    }
    
    if (cellSize < 1)
    {
        NSLog(@"Illegal cellSize");
        return;
    }
    
    [[JCDataManager sharedManager]destroyIsometric];
    [[JCDataManager sharedManager]initIsometricModel];
    [JCDataManager sharedManager].isometricModel->init(floors, rows, cols);
    [JCDataManager sharedManager].isometricModel->setCellSize(cellSize);
    [[NSNotificationCenter defaultCenter] postNotificationName:[JCNotificationName newScene] object:nil userInfo:nil];
    [self.window close];
}

@end
