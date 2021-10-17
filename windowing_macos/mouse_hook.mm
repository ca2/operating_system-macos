//
//  mouse_hook.mm
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:17 BRT
//
//  auraclick.m
//  app_core_auraclick
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


#include "acme/constant/message.h"


namespace mouse_hook
{
   

   static ::element * g_pelementListener = NULL;


   static id g_idEventMonitor;
   
   
   ::e_status install(::element * pelementListener)
   {
      
      g_pelementListener = pelementListener;

      g_idEventMonitor = [ NSEvent addGlobalMonitorForEventsMatchingMask:
                 
                 (NSLeftMouseDownMask | NSRightMouseDownMask | NSOtherMouseDownMask)
                 
                 | (NSLeftMouseUpMask | NSRightMouseUpMask | NSOtherMouseUpMask)                                     handler: ^(NSEvent *incomingEvent)
                 {
                                                         
                                             //NSEvent *result = incomingEvent;
                                                         
                                                         //NSWindow *targetWindowForEvent = //[incomingEvent window];
                                                         
                                                         if ([incomingEvent type] == NSLeftMouseDown) {
                                                            g_pelementListener->call(e_message_left_button_down);
                                                            
                                                            
                                                         }
                                                         else if ([incomingEvent type] == NSLeftMouseUp) {
                                                  g_pelementListener->call(e_message_left_button_up);
                       
                       
                    }
                    else if ([incomingEvent type] == NSRightMouseDown) {
                       g_pelementListener->call(e_message_right_button_down);
                       
                       
                    }
                    else if ([incomingEvent type] == NSRightMouseUp) {
                       g_pelementListener->call(e_message_right_button_up);
                       
                       
                    }
                    else if ([incomingEvent type] == NSOtherMouseDown) {
                       g_pelementListener->call(e_message_middle_button_down);
                       
                       
                    }
                    else if ([incomingEvent type] == NSOtherMouseUp) {
                       g_pelementListener->call(e_message_middle_button_up);
                       
                       
                    }
                                                         
                                                         
                                                      }];
      return true;
   
   }
   

   ::e_status uninstall(::element * pelementListener)
   {
      
      [NSEvent removeMonitor:g_idEventMonitor ];
      
      return true;
      
   }


} // namespace mouse_hook



