//
//  ns_acme_form_impact_controller.mm
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/05/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//

#import "ns_acme_form_impact_controller.h"
#include "acme/constant/lightui.h"
#include "operating_system-macos/appkit/NSProgressIndicator+CppModel.h"

::appkit::ns_window_t as_ns_window_t(NSWindow * pnswindow)
{
   
   return {(__bridge void *) pnswindow};
   
}
::uptr as_ns_window_uptr(NSWindow * pnswindow)
{
   
   return (::uptr)((__bridge void *) pnswindow);
   
}
void user_on_command(::uptr u, ::lightui::enum_notification enotification, ::uptr uControl);
void ns_send_message(::appkit::ns_window_t nswindow, ::user::enum_message emessage, ::uptr wparam = 0, ::uptr lparam = 0);


@implementation ns_acme_form_impact_controller

- (void)viewDidLoad
{
   
    [super viewDidLoad];
   
    // Automatically find and attach an event hook to every button in this scene
    [self attachCentralActionToSubImpactsInImpact:self.view];
   
   
   ns_send_message(::as_ns_window_t(self.view.window), ::user::e_message_initialize_dialog);
   
}

// Helper method to recursively search the view tree for buttons
- (void)attachCentralActionToSubImpactsInImpact:(NSView *)parentView {
    for (NSView *psubimpact in parentView.subviews) {
        
        // 1. Check if the element is an NSButton
        if ([psubimpact isKindOfClass:[NSButton class]]) {
            NSButton *button = (NSButton *)psubimpact;
            
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
       else if([psubimpact isKindOfClass:[NSComboBox class]])
       {

           NSComboBox * combo =
           (NSComboBox *)psubimpact;

           combo.delegate = self;

       }
       else if([psubimpact isKindOfClass:[NSProgressIndicator class]])
       {
          NSProgressIndicator *progress = psubimpact;
//          NSProgressIndicator *progress = [[NSProgressIndicator alloc] init];
          //progress.customTag = 101;                // Solution 1: Identify in loops
          //progress.cppModelPointer = (void *)task;  // Solution 2: Map to C++ model
          NSLog(@"NSProgressIndicator customTag %d", (int) progress.tag);
          //[parentView addSubview:progress];
          
       }

        // 2. Recursively crawl psubimpacts (in case buttons are inside box wrappers or stack views)
        if (psubimpact.subviews.count > 0) {
            [self attachCentralActionToSubImpactsInImpact:psubimpact];
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
   user_on_command(::as_ns_window_uptr(myWindow), ::lightui::e_notification_default, buttonTag);
    // Route logic based on title or tag
    if ([buttonTitle isEqualToString:@"Submit"]) {
        NSLog(@"Processing form submission data...");
    } else if ([buttonTitle isEqualToString:@"Cancel"]) {
        NSLog(@"Closing the dialog window.");
        [self.view.window close];
    }
}

-(bool)isNotificationBlockedForTag:(::uptr)tag andID:(::lightui::enum_notification)enotification
{
   auto & controlhelper = self->m_mapControlHelper[tag];
   
   return controlhelper.is_notification_blocked(enotification);
   
   
}


- (void)comboBoxSelectionDidChange:
   (NSNotification *)notification
{
    NSComboBox * combo = notification.object;
   
   auto tag =combo.tag;
   
   if([self isNotificationBlockedForTag: tag andID: ::lightui::CBN_SELENDOK ])
   {
      
      return;
      
   }

    NSLog(@"Selection changed %@", combo);
   auto pnswindow = self.view.window;
   user_on_command(::as_ns_window_uptr(pnswindow),::lightui::CBN_SELENDOK,tag);
   
}


- (void)comboBoxWillPopUp:
   (NSNotification *)notification
{
    NSComboBox * combo = notification.object;

    NSLog(@"Popup opened %@", combo);
   auto pnswindow = self.view.window;
   user_on_command(::as_ns_window_uptr(pnswindow),::lightui::CBN_DROPDOWN,combo.tag);
}


- (void)comboBoxWillDismiss:
   (NSNotification *)notification
{
    NSComboBox * combo = notification.object;

    NSLog(@"Popup closed %@", combo);
}


@end
