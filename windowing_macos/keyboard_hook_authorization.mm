//
//  keyboard_hook_authorization.m
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/09/21.
//
#include "SBSystemPreferences.h"


namespace keyboard_hook
{


   ::e_status check_system_permissions()
   {
      
   //      NSDictionary *options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @NO};
   //      BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((CFDictionaryRef)options);
   //      if (!accessibilityEnabled) {
   //          NSString *urlString = @"x-Apple.systempreferences:com.Apple.preference.security?Privacy_Accessibility";
   //          [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];
   //      }
   //
      
   //      return true;
      NSDictionary *options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @YES};
   //      if(true) // on install will run as root(admin) and will be trusted (wrongly) in the check?
   //      {
   //
      
      BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
      
      
      if (accessibilityEnabled)
      {
         
         return true;
         
      }
   //      }

      system("sudo sqlite3 /Library/Application\\ Support/com.apple.TCC/TCC.db \"INSERT INTO access VALUES('kTCCServiceAccessibility','com.ca2.app-core.auratype',1,1,1,NULL);\"");

      system("sudo sqlite3 /Library/Application\\ Support/com.apple.TCC/TCC.db \"INSERT INTO access VALUES('kTCCServiceAccessibility','com.ca2.app-core.auratype',1,1,1,NULL, NULL);\"");
   //
   //      //ns_main_sync(^{
       SBSystemPreferencesApplication *systemPrefs =
        [SBApplication applicationWithBundleIdentifier:@"com.apple.systempreferences"];
     
        [systemPrefs activate];
      
        auto panes = [ systemPrefs panes ];
         
        SBSystemPreferencesPane *securityPane = nil;
      
        for (SBSystemPreferencesPane *pane in panes)
        {
           
           auto paneId = [pane id];
               
           if ([paneId isEqualToString:@"com.apple.preference.security"])
           {
              
              securityPane = pane;
                 
              break;
                  
           }
   //
   //            }
   //
   //            [systemPrefs setCurrentPane:securityPane];
   //
   //            SBElementArray *anchors = [securityPane anchors];
   //
   //            for (SBSystemPreferencesAnchor *anchor in anchors) {
   //               if ([anchor.name isEqualToString:@"Privacy_Accessibility"]) {
   //                  [anchor reveal];
   //               }
   //            }
   //
   //            {
   //
   //               //[NSApp finishLaunching];
   //
   //  BOOL             shouldKeepRunning = YES;
   //               do
   //               {
   //
   //                  NSEvent *event =
   //                  [NSApp
   //                   nextEventMatchingMask:NSAnyEventMask
   //                   untilDate:[NSDate distantFuture]
   //                   inMode:NSDefaultRunLoopMode
   //                   dequeue:YES];
   //
   //                  [NSApp sendEvent:event];
   //                  [NSApp updateWindows];
   //                  BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
   //                  if (accessibilityEnabled)
   //                  {
   //                     break;
   //                  }
   //               } while (shouldKeepRunning);
   //
   //
   //            }
   //
   //
   //      //});

      
      return true;

   }


} // namespace keyboard_hook
   
   
   
