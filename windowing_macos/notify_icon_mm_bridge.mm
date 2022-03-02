//
//  user_notify_icon_mm_bridge.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "framework.h"


NSImage * nsimage_from_image_data(const void * pdata, int cx, int cy, int scan);

void user_notify_icon_mm_bridge::notify_icon_mm_initialize(const void * pdata, int size)
{
   
//   NSImage * pimage = nsimage_from_image_data(pdata, cx, cy, scan);

//   NSString * str = [[NSString alloc] initWithCString:strIconFile encoding:NSUTF8StringEncoding];
   
   
   ns_main_sync(^()
                {

   m_pnotifyicon = (__bridge_retained void *) [[user_notify_icon alloc] initIconImageFileData: pdata withSize: size withBridge: m_pnotifyiconbridge];
      
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



