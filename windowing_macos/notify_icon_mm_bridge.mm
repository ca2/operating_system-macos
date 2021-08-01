//
//  user_notify_icon_mm_bridge.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "framework.h"




void user_notify_icon_mm_bridge::notify_icon_mm_initialize(const char * strIconFile)
{

   NSString * str = [[NSString alloc] initWithCString:strIconFile encoding:NSUTF8StringEncoding];
   
   
   ns_main_sync(^()
                {

   m_pnotifyicon = (__bridge_retained void *) [[user_notify_icon alloc] initIconFile: str withBridge: m_pnotifyiconbridge];
      
   });

}


void user_notify_icon_mm_bridge::notify_icon_mm_finalize()
{
   
   ns_main_sync(^()
                {
      
            auto pnotifyicon = (__bridge_transfer user_notify_icon *) m_pnotifyicon;
      
      m_pnotifyicon = nullptr;
      
         [pnotifyicon close];
      
   });
   
}



