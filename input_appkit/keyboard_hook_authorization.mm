//
//  keyboard_hook_authorization.m
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/09/21.
//

#import <Cocoa/Cocoa.h>

namespace input_appkit
{


   ::e_status is_keyboard_hook_enabled(bool bPrompt)
   {
      
      NSDictionary * options;
      
      if(bPrompt)
      {
      
         options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @YES};
         
      }
      else
      {
         
         options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @NO};

      }
   //      if(true) // on install will run as root(admin) and will be trusted (wrongly) in the check?
   //      {
   //
      
      
      
      BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
      
      
      if (accessibilityEnabled)
      {
         
         return ::success;
         
      }
      
      
      //if(bPrompt)
      {
       
         return error_need_restart_application_to_activate_feature;
         
      }
      //else
      //{
         
        // return
         
      //}
      //[NSApp terminate];
   //      }
//
//      system("sudo sqlite3 /Library/Application\\ Support/com.apple.TCC/TCC.db \"INSERT INTO access VALUES('kTCCServiceAccessibility','com.ca2.app-core.auratype',1,1,1,NULL);\"");
//
//      system("sudo sqlite3 /Library/Application\\ Support/com.apple.TCC/TCC.db \"INSERT INTO access VALUES('kTCCServiceAccessibility','com.ca2.app-core.auratype',1,1,1,NULL, NULL);\"");
//
//      NSString *urlString = @"x-apple.systempreferences:com.apple.preference.security?Privacy_Accessibility";
//      [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];
   //
   //      //ns_main_sync(^{
//       SBSystemPreferencesApplication * systempreferences =
//        [SBApplication applicationWithBundleIdentifier:@"com.apple.systempreferences"];
//
//        [systempreferences activate];
//
//        SBElementArray * panes = [ systempreferences panes ];
//
//      NSUInteger paneCount = [panes count];
//
//        SBSystemPreferencesPane *securityPane = nil;
//
//        for (SBSystemPreferencesPane *pane in panes)
//        {
//
//           auto paneId = [pane id];
//
//           if ([paneId isEqualToString:@"com.apple.preference.security"])
//           {
//
//              securityPane = pane;
//
//              break;
//
//           }
//
//               }
//
//               [systempreferences setCurrentPane:securityPane];
//
//               SBElementArray *anchors = [securityPane anchors];
//
//               for (SBSystemPreferencesAnchor *anchor in anchors) {
//                  if ([anchor.name isEqualToString:@"Privacy_Accessibility"]) {
//                     [anchor reveal];
//                  }
//               }
//
//               {
//
//                  //[NSApp finishLaunching];
//      ns_main_sync(^{
//
//
//
//
//         //[NSApp finishLaunching];
//
//     BOOL             shouldKeepRunning = YES;
//                  do
//                  {
//
//
//                     NSEvent *event =
//                     [NSApp
//                      nextEventMatchingMask:NSAnyEventMask
//                      untilDate:[[NSDate date]dateByAddingTimeInterval: 1.0]
//                      inMode:NSDefaultRunLoopMode
//                      dequeue:YES];
//
//                     if(event)
//                     {
//                     [NSApp sendEvent:event];
//                     [NSApp updateWindows];
//
//                     }
//                     NSDictionary *options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @NO};
//                     BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
//                     if (accessibilityEnabled)
//                     {
//                        break;
//                     }
//                  } while (shouldKeepRunning);
//
//      });
               //}
   //
   //
   //      //});

      
      return ::success;

   }


} // namespace keyboard_hook
   
   
   
