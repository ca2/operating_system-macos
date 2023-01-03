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
   

   static ::particle * g_pparticleListener = NULL;


   static id g_idEventMonitor;
   
   
   ::e_status install(::particle * pparticleListener)
   {
      
      g_pparticleListener = pparticleListener;

      g_idEventMonitor = [ NSEvent addGlobalMonitorForEventsMatchingMask:
                 
                          (NSEventMaskLeftMouseDown | NSEventMaskRightMouseDown | NSEventMaskOtherMouseDown)
                 
                          | (NSEventMaskLeftMouseUp | NSEventMaskRightMouseUp | NSEventMaskOtherMouseUp)                                     handler: ^(NSEvent *incomingEvent)
                 {
                                                         
                                             //NSEvent *result = incomingEvent;
                                                         
                                                         //NSWindow *targetWindowForEvent = //[incomingEvent window];
                                                         
         if ([incomingEvent type] == NSEventTypeLeftMouseDown) {
                                                            g_pparticleListener->call(e_message_left_button_down);
                                                            
                                                            
                                                         }
         else if ([incomingEvent type] == NSEventTypeLeftMouseUp) {
                                                            g_pparticleListener->call(e_message_left_button_up);
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeRightMouseDown) {
                       g_pparticleListener->call(e_message_right_button_down);
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeRightMouseUp) {
                       g_pparticleListener->call(e_message_right_button_up);
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeOtherMouseDown) {
                       g_pparticleListener->call(e_message_middle_button_down);
                       
                       
                    }
                    else if ([incomingEvent type] == NSEventTypeOtherMouseUp) {
                       g_pparticleListener->call(e_message_middle_button_up);
                       
                       
                    }
                                                         
                                                         
                                                      }];
      return true;
   
   }
   

   ::e_status uninstall(::particle * pparticleListener)
   {
      
      [NSEvent removeMonitor:g_idEventMonitor ];
      
      return true;
      
   }


} // namespace mouse_hook



