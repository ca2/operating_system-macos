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
#include "mouse_hook.h"
#import <Cocoa/Cocoa.h>

namespace input_appkit
{
   

   static ::input::mouse_hook * g_pmousehook = NULL;


   static id g_idEventMonitor;
   
   
   ::e_status install_mouse_hook(::input_appkit::mouse_hook * pmousehook)
   {
      

      pmousehook->m_typeref = (__bridge_retained CFTypeRef) [ NSEvent addGlobalMonitorForEventsMatchingMask:
                 
                          (NSEventMaskLeftMouseDown | NSEventMaskRightMouseDown | NSEventMaskOtherMouseDown)
                 
                          | (NSEventMaskLeftMouseUp | NSEventMaskRightMouseUp | NSEventMaskOtherMouseUp)                                     handler: ^(NSEvent *incomingEvent)
                 {
                                                         
                                             //NSEvent *result = incomingEvent;
                                                         
                                                         //NSWindow *targetWindowForEvent = //[incomingEvent window];
                                                         
         if ([incomingEvent type] == NSEventTypeLeftMouseDown) {
            
            if(!pmousehook->m_bLeftPressed)
            {
               pmousehook->m_bLeftPressed = true;
               pmousehook->mouse_proc(e_message_left_button_down);
               
            }
                                                            
                                                         }
         else if ([incomingEvent type] == NSEventTypeLeftMouseUp) {
            
            if(pmousehook->m_bLeftPressed)
            {
               pmousehook->m_bLeftPressed = false;
               pmousehook->mouse_proc(e_message_left_button_up);
               
            }
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeRightMouseDown) {
            pmousehook->mouse_proc(e_message_right_button_down);
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeRightMouseUp) {
            pmousehook->mouse_proc(e_message_right_button_up);
                       
                       
                    }
         else if ([incomingEvent type] == NSEventTypeOtherMouseDown) {
            pmousehook->mouse_proc(e_message_middle_button_down);
                       
                       
                    }
                    else if ([incomingEvent type] == NSEventTypeOtherMouseUp) {
                       pmousehook->mouse_proc(e_message_middle_button_up);
                       
                       
                    }
                                                         
                                                         
                                                      }];
      return ::success;
   
   }
   

   ::e_status uninstall_mouse_hook(::input_appkit::mouse_hook * pmousehook)
   {
      
      auto typeref = pmousehook->m_typeref;
      
      pmousehook->m_typeref = nil;
      
      if(typeref)
      {
         
         [ NSEvent removeMonitor : (__bridge_transfer id) pmousehook->m_typeref ];
         
      }
      
      return ::success;
      
   }


} // namespace input_appkit



