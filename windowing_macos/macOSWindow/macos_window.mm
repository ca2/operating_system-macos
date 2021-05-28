//
//  macos_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"



void * new_macos_window(macos_window * pmacoswindow, CGRect rect, unsigned int uStyle)
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
   
   macOSWindow * pmacOSWindow = [macOSWindow alloc];
   
   NSWindow * pNSWindow = pmacOSWindow;
   
   pmacoswindow->m_pmacoswindow = pmacOSWindow;
   
   pmacoswindow->m_pmacoswindow->m_pmacoswindow = pmacoswindow;
   
   //__block RoundWindow * proundwindow;
   
   ns_main_sync(^()
   {
                   
      auto id = [pmacoswindow->m_pmacoswindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
      
      if(!id)
      {
         
         NSLog(@"window wasn't created");
      
      }
                   
   });
   
   return (__bridge_retained void *) pNSWindow;
   
}


macos_window::macos_window()
{
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
}


macos_window::~macos_window()
{
   
   m_pmacoswindow = nullptr;
   
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
   
   [m_pmacoswindow setTitle:str];
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
                   
                  NSString * str = [m_pmacoswindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void macos_window::macos_window_destroy()
{
   
   if(m_pmacoswindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_pmacoswindow];

   [m_pmacoswindow setReleasedWhenClosed: YES];
   
   m_pmacoswindow->m_pmacoswindow = NULL;
   
   [m_pmacoswindow close];

}


void macos_window::macos_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_pmacoswindow->m_pwindowcontroller showWindow : m_pmacoswindow];
      
      [m_pmacoswindow windowDidExpose];

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
      
      if(![m_pmacoswindow isVisible])
      {
      
         [m_pmacoswindow->m_pwindowcontroller showWindow : m_pmacoswindow];
      
         [m_pmacoswindow windowDidExpose];
         
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
                 
                 if(m_pmacoswindow)
                 {
                 
                    [m_pmacoswindow orderOut : nil];
                    
                 }
                 
                 if(m_pmacoswindow)
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
                    
                    if([m_pmacoswindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [m_pmacoswindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [m_pmacoswindow orderOut : nil];
                       
                       macos_window_iconified();
                       
                    }
                    
                    if(m_pmacoswindow->m_pmacoswindow == NULL)
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
                 
                 [m_pmacoswindow orderFront : m_pmacoswindow];
                 
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
                 
                 [m_pmacoswindow makeFirstResponder:nullptr];
                 
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
                 
                 [m_pmacoswindow makeKeyWindow];
                 
              });
   
}


void macos_window::macos_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_pmacoswindow makeKeyAndOrderFront: m_pmacoswindow];
                 
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
                 
                 [m_pmacoswindow makeMainWindow];
                 
              });
   
}


void macos_window::macos_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   auto proundwindow = m_pmacoswindow;
   
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
                    
                    [m_pmacoswindow display];
                    
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
      
      [m_pmacoswindow setFrame : rect display: TRUE];

   });
   
}

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
      
      [m_pmacoswindow setFrame : rect display: TRUE];

      
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
      
      [m_pmacoswindow setViewsNeedDisplay : TRUE];
      
   });
   
}


//NSWindow * get_os_window_ns_window(oswindow hwnd)
//{
//   
//   return __nswindow(hwnd);
//   
//}



