//
//  windowing.mm
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-03-01.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//
#include<AppKit/AppKit.h>
void ns_main_post(dispatch_block_t block);

void ns_main_send(dispatch_block_t block);


NSAppleScript * ns_get_dark_mode_script()
{
   
   return [[NSAppleScript alloc] initWithSource :@"tell app \"System Events\" to tell appearance preferences to set dark mode to true"];
   
}


NSAppleScript * ns_get_lite_mode_script()
{
   
   return [[NSAppleScript alloc] initWithSource :@"tell app \"System Events\" to tell appearance preferences to set dark mode to false"];
}


// Don't forget to:
// add NSAppleEventsUsageDescription to Info.plist with System Events usage description
// add Apple Events Hardened Runtime entitlement

bool ns_set_dark_mode(bool bDark)
{
   
   NSAppleScript * pscript = nil;
   
   if(bDark)
   {
      
      pscript = ns_get_dark_mode_script();
      
   }
   else
   {
    
      pscript = ns_get_lite_mode_script();
      
   }
   
   NSDictionary *error = nil;
   
   [pscript executeAndReturnError:&error];
   
   return error == nil;
   
}


bool ns_get_dark_mode()
{
   
   __block BOOL dark = FALSE;
   
   ns_main_send(^()
                {
      
      NSAppearance* appearance = NSApp.effectiveAppearance;
      NSString* name = appearance.name;
      dark = [appearance bestMatchFromAppearancesWithNames:@[NSAppearanceNameAqua, NSAppearanceNameDarkAqua]] == NSAppearanceNameDarkAqua;
      
   });
   
   return !!dark;
   
}



