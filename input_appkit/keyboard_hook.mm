//
//  keyboard_hook.mm
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:18 BRT
//
//  auraclick.m
//  app_core_auraclick
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "keyboard_hook.h"
#include "acme/constant/message.h"
#include "apex/input/keyboard_hook.h"
//#import <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
//#import <ScriptingBridge/ScriptingBridge.h>

//#define VK_CLEAR          0x0C
//#define VK_RETURN         0x0D
//
//#define VK_SHIFT          0x10
//#define VK_CONTROL        0x11
//#define VK_MENU           0x12
//#define VK_PAUSE          0x13
//#define VK_CAPITAL        0x14
//
//#define VK_KANA           0x15
//#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
//#define VK_HANGUL         0x15
//#define VK_JUNJA          0x17
//#define VK_FINAL          0x18
//#define VK_HANJA          0x19
//#define VK_KANJI          0x19
//
//#define VK_ESCAPE         0x1B
//
//#define VK_CONVERT        0x1C
//#define VK_NONCONVERT     0x1D
//#define VK_ACCEPT         0x1E
//#define VK_MODECHANGE     0x1F
//
//#define VK_SPACE          0x20
//#define VK_PRIOR          0x21
//#define VK_NEXT           0x22
//#define VK_END            0x23
//#define VK_HOME           0x24
//#define VK_LEFT           0x25
//#define VK_UP             0x26
//#define VK_RIGHT          0x27
//#define VK_DOWN           0x28
//#define VK_SELECT         0x29
//#define VK_PRINT          0x2A
//#define VK_EXECUTE        0x2B
//#define VK_SNAPSHOT       0x2C
//#define VK_INSERT         0x2D
//#define VK_DELETE         0x2E
//#define VK_HELP           0x2F


namespace input_appkit
{


   ::e_status check_system_keyboard_hook_permissions();


   static ::input::keyboard_hook * g_pkeyboardhook = nullptr;


   static id g_idEventMonitor;


   ::e_status install_keyboard_hook(::input::keyboard_hook * pkeyboardhook)
   {
   
      auto estatus = is_enabled(false);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      g_pkeyboardhook = pkeyboardhook;
      
      //   NSDictionary *options = @{(__bridge NSString *)kAXTrustedCheckOptionPrompt: @NO};
      //   BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
      //   if (!accessibilityEnabled)
      //   {
      //      return false;
      //      for(int i = 0; i < 100; i++)
      //      {
      //         [NSThread sleepForTimeInterval: 0.084];
      //
      //      printf("::auratype::iview::install_auratype_monitor not authorized at Security > Accessibility\n");
      //      }
      //      on_install();
      //   }
      //
      //      [NSApp performSelector:@selector(terminate:) withObject:nil afterDelay:0.0];
      //      dwExitCode = System.process().elevated_synch(strPath + strParam,SW_HIDE,durationWait,&bTimedOut);
      
      //      NSString *urlString = @"x-apple.systempreferences:com.apple.preference.security?Privacy_Accessibility";
      //      [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];
      //      SBSystemPreferencesApplication *prefs = [SBApplication applicationWithBundleIdentifier:@"com.apple.systempreferences"];
      //      [prefs activate];
      
      
      //      SBSystemPreferencesApplication *systemPrefs =
      //      [SBApplication applicationWithBundleIdentifier:@"com.apple.systempreferences"];
      //
      //      [systemPrefs activate];
      //
      //      SBElementArray *panes = [systemPrefs panes];
      //      SBSystemPreferencesPane *speechPane = nil;
      //
      //      for (SBSystemPreferencesPane *pane in panes) {
      //         if ([[pane id] isEqualToString:@"com.apple.preference.security"]) {
      //            speechPane = pane;
      //            break;
      //         }
      //      }
      //      [systemPrefs setCurrentPane:speechPane];
      //
      //      SBElementArray *anchors = [speechPane anchors];
      //
      //      for (SBSystemPreferencesAnchor *anchor in anchors) {
      //         if ([anchor.name isEqualToString:@"Privacy_Accessibility"]) {
      //            [anchor reveal];
      //         }
      //      }
      //
      //      while(true)
      //      {
      //         [NSThread sleepForTimeInterval: 0.984];
      //         BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)options);
      //         if (accessibilityEnabled)
      //         {
      //            break;
      //         }
      //      }
      //}
      g_idEventMonitor = [NSEvent addGlobalMonitorForEventsMatchingMask:
                          
                          (NSEventMaskKeyDown | NSEventMaskKeyUp)                                    handler: ^(NSEvent *incomingEvent)
                          {
         
         //NSEvent *result = incomingEvent;
         
         //NSWindow *targetWindowForEvent = [incomingEvent window];
         
         if ([incomingEvent type] == NSEventTypeKeyDown)
         {
            
            if([incomingEvent keyCode] == kVK_Return)
            {
               
               g_pkeyboardhook->keyboard_proc(e_message_key_down, kVK_Return);
               
            }
            else if([incomingEvent keyCode] == kVK_Space)
            {
               
               g_pkeyboardhook->keyboard_proc((e_message_key_down, kVK_Space);
               
            }
            else
            {
               
               g_pkeyboardhook->keyboard_proc(e_message_key_down, kVK_ANSI_A);
               
            }
            
         }
         else if ([incomingEvent type] == NSEventTypeKeyUp)
         {
            
            if([incomingEvent keyCode] == kVK_Return)
            {
               
               g_pkeyboardhook->keyboard_proc(e_message_key_up, kVK_Return);
               
            }
            else if([incomingEvent keyCode] == kVK_Space)
            {
               
               g_pkeyboardhook->keyboard_proc(e_message_key_up, kVK_Space);
               
            }
            else
            {
               
               g_pkeyboardhook->keyboard_proc(e_message_key_up, kVK_ANSI_A);
               
            }
            
         }
         
      }];
      
      return ::success;
      
   }


   ::e_status uninstall_keyboard_hook(::input::keyboard_hook * pkeyboardhook)
   {
      
      [NSEvent removeMonitor: g_idEventMonitor ];
      
      return ::success;
      
   }


} // namespace keyboard_hook



