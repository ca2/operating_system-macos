//
//  macos_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "macos_window.h"
#include "macos_nswindow.h"


void ns_set_main_window(NSWindow * pnswindow);
void ns_main_async(dispatch_block_t block);


void ns_main_sync(dispatch_block_t block);


void create_macos_nswindow(macos_window * pmacoswindow, CGRect rect, unsigned int uStyle)
{
   
   // rect.origin.x        = 0;
   
   rect.origin.y           = (int) [[NSScreen mainScreen]frame].size.height - (rect.origin.y + rect.size.height);
   
   // rect.size.width      = 0;
   // rect.size.height     = 0;
   
/* 
 
   rect.origin.x           = 100;
   rect.origin.y           = 100;
   rect.size.width         = 800;
   rect.size.height        = 500;
 
*/
   
   macos_nswindow * pnswindow = [macos_nswindow alloc];
   
   ns_set_main_window(pnswindow);
   
   pmacoswindow->m_pnswindow = pnswindow;
   
   pmacoswindow->m_pnswindow->m_pmacoswindow = pmacoswindow;
   
   ns_main_sync(^()
   {
                   
      auto id = [pmacoswindow->m_pnswindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
      
      if(!id)
      {
         
         NSLog(@"window wasn't created");
      
      }
      
      //pmacoswindow->macos_window_on_create();
                   
   });
   
   //return (__bridge_retained void *) pNSWindow;
   
}


macos_window::macos_window()
{
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
   m_bTest123 = false;
   
}


macos_window::~macos_window()
{
   
   m_pnswindow = nullptr;
   
}


void macos_window::macos_window_set_title(const char * pszTitle)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   char *pszText = strdup(pszTitle);
   
   ns_main_async(^
                 {
   
   NSString * str = [NSString stringWithUTF8String:pszText];
   
   [m_pnswindow setTitle:str];
                    ::free((void *)pszText);
                    
                 });
   
}


void macos_window::macos_window_get_title(char * pszTitle, int iSize)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                {
                   
                  NSString * str = [m_pnswindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void macos_window::macos_window_destroy()
{
   
   if(m_pnswindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_pnswindow];

   [m_pnswindow setReleasedWhenClosed: YES];
   
   m_pnswindow->m_pmacoswindow = NULL;
   
   [m_pnswindow close];
   
   m_pnswindow = nullptr;
   
   m_pnswindow = nullptr;

}


void macos_window::macos_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_pnswindow->m_pwindowcontroller showWindow : m_pnswindow];
      
      [m_pnswindow windowDidExpose:nil];

   });
   
}


void macos_window::macos_window_defer_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      if(![m_pnswindow isVisible])
      {
      
         [m_pnswindow->m_pwindowcontroller showWindow : m_pnswindow];
      
         [m_pnswindow windowDidExpose:nil];
         
      }

   });
   
}


void macos_window::macos_window_hide()
{
   
//   if(m_bDestroying)
//   {
//      
//      return;
//      
//   }

   ns_main_async(^
              {
                 
                 if(m_pnswindow)
                 {
                 
                    [m_pnswindow orderOut : nil];
                    
                 }
                 
                 if(m_pnswindow)
                 {
                    
                    macos_window_on_hide();
                    
                 }
                 
              });
   
}


void macos_window::macos_window_miniaturize()
{
 
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
                 {
                    
                    if([m_pnswindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [m_pnswindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [m_pnswindow orderOut : nil];
                       
                       macos_window_iconified();
                       
                    }
                    
                    if(m_pnswindow->m_pmacoswindow == NULL)
                    {
                       
                       return;
                       
                    }
                    
                    //macos_window_on_miniaturize();
                    
                 });
   
}



void macos_window::macos_window_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow orderFront : m_pnswindow];
                 
              });
   
}


void macos_window::macos_window_make_first_responder()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow makeFirstResponder:nullptr];
                 
              });
   
}


void macos_window::macos_window_resign_key()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow resignKeyWindow];
                 
              });
   
}



void macos_window::macos_window_make_key_window()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow makeKeyWindow];
                 
              });
   
}


bool macos_window::macos_window_is_key_window() const
{

   if(m_bDestroying)
   {
      
      return false;
      
   }
   
   __block bool bKeyWindow = false;
   
   ns_main_sync(^
   {
                 
      bKeyWindow =  [m_pnswindow isKeyWindow];
                 
   });
   
   return bKeyWindow;
   
}


void macos_window::macos_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow makeKeyAndOrderFront: m_pnswindow];
                 
              });
   
}


void macos_window::macos_window_make_main_window()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pnswindow makeMainWindow];
                 
              });
   
}


void macos_window::macos_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   auto proundwindow = m_pnswindow;
   
   if(proundwindow)
   {

   ns_main_async(^
                 {
                    
                   // m_bDirty = true;
                    
                    if(proundwindow)
                    {
                    
                       [proundwindow->m_pviewChildContent setNeedsDisplay:TRUE];
                       
                    }
   
                 });
      
   }
   
}


void macos_window::macos_window_redraw_sync()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                 {
                    
                    [m_pnswindow display];
                    
                 });
   
}



void macos_window::macos_window_set_frame(CGRect r)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      rect.origin.x     = r.origin.x;
      rect.origin.y     = rectScreen.size.height    -     r.origin.y - r.size.height;
      rect.size   = r.size;
      
      [m_pnswindow setFrame : rect display: TRUE];

   });
   
}


//void * macos_window::macos_window_get_mouse_cursor()
//{
//   
//   auto pcursor =
//   
//}


void macos_window::macos_window_get_frame(CGRect *pr)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      rect = [m_pnswindow frame];

      
      pr->origin.x     = rect.origin.x;
      pr->origin.y     = rectScreen.size.height    -     rect.origin.y - rect.size.height;
      pr->size   = rect.size;
      

   });
   
}


void macos_window::macos_window_invalidate()
{
  
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_pnswindow setViewsNeedDisplay : TRUE];
      
   });
   
}


//NSWindow * get_os_window_ns_window(oswindow hwnd)
//{
//   
//   return __nswindow(hwnd);
//   
//}







CGWindowID ns_get_window_id(void * pNSWindow)
{
   
   NSWindow * pnswindow = (__bridge NSWindow *) pNSWindow;
   
   __block CGWindowID windowid = 0;
   
   ns_main_sync(^{
   
   windowid = (CGWindowID)[pnswindow windowNumber];
      
   });
   
   return windowid;
   
}


void * ns_get_key_window()
{
   
   __block void * pnswindowKey = nullptr;
   
   ns_main_sync(^{
      
      NSWindow * pwindowKey = [NSApp keyWindow];
      
      pnswindowKey = (__bridge void *) pwindowKey;
      
   });
   
   return pnswindowKey;
   
}
