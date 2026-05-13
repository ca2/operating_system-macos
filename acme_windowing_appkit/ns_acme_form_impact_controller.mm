//
//  ns_acme_form_impact_controller.mm
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/05/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//

#import "ns_acme_form_impact_controller.h"

void user_on_command(::uptr u, ::uptr uControl);

@implementation ns_acme_form_impact_controller

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Automatically find and attach an event hook to every button in this scene
    [self attachCentralActionToButtonsInView:self.view];
}

// Helper method to recursively search the view tree for buttons
- (void)attachCentralActionToButtonsInView:(NSView *)parentView {
    for (NSView *subview in parentView.subviews) {
        
        // 1. Check if the element is an NSButton
        if ([subview isKindOfClass:[NSButton class]]) {
            NSButton *button = (NSButton *)subview;
            
           NSString *cellClassName = NSStringFromClass([[button cell] class]);

           // Filter out internal system-level Checkbox and Radio implementations
           if (![cellClassName containsString:@"CheckBox"] &&
               ![cellClassName containsString:@"Radio"] &&
               button.isBordered == YES) {
                
                // 3. Point the button's action targeting mechanism to this view controller
                button.target = self;
                button.action = @selector(anyButtonWasPressed:);
            }
        }
        
        // 2. Recursively crawl subviews (in case buttons are inside box wrappers or stack views)
        if (subview.subviews.count > 0) {
            [self attachCentralActionToButtonsInView:subview];
        }
    }
}

// The Central Catch-All Interceptor Method
- (void)anyButtonWasPressed:(id)sender {
    NSButton *clickedButton = (NSButton *)sender;
    
    // Identify which button was pressed using its Title string or its assigned tag ID number
    NSString *buttonTitle = clickedButton.title;
    NSInteger buttonTag = clickedButton.tag;
    
    NSLog(@"[Central Hook] Button Pressed! Title: '%@' | Tag ID: %ld", buttonTitle, (long)buttonTag);
    
   NSWindow *myWindow = self.view.window;
   auto cgwindowid = myWindow.windowNumber;
   user_on_command(cgwindowid, buttonTag);
    // Route logic based on title or tag
    if ([buttonTitle isEqualToString:@"Submit"]) {
        NSLog(@"Processing form submission data...");
    } else if ([buttonTitle isEqualToString:@"Cancel"]) {
        NSLog(@"Closing the dialog window.");
        [self.view.window close];
    }
}

@end
