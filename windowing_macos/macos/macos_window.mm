//
//  macos_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "macos_window.h"
#include "macOSWindow.h"
#include "macOSImpact.h"


void ns_set_main_window(NSWindow * pnswindow);
void ns_main_post(dispatch_block_t block);


void ns_main_send(dispatch_block_t block);


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
   
   macOSWindow * pnsmacoswindow = [macOSWindow alloc];
   
   ns_set_main_window(pnsmacoswindow);
   
   auto pnsacmewindow = (ns_acme_window *) pnsmacoswindow;
   
   pmacoswindow->m_pnsacmewindow = (__bridge_retained CFTypeRef) pnsacmewindow;
   
   pnsmacoswindow->m_pacmewindowbridge = pmacoswindow;
   
   pnsmacoswindow->m_pmacoswindow = pmacoswindow;
   
   ns_main_send(^()
   {
                   
      auto id = [ pnsmacoswindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
      
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
    
    m_dOpacity = 1.;
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
   m_bTest123 = false;
   
}


macos_window::~macos_window()
{
   
   //pnsmacoswindow = nullptr;
   
}


void macos_window::macos_window_set_title(const char * pszTitle)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   char *pszText = strdup(pszTitle);
   
   ns_main_post(^
                 {
   
   NSString * str = [NSString stringWithUTF8String:pszText];
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;
   
   [pnsmacoswindow setTitle:str];
                    ::free((void *)pszText);
                    
                 });
   
}


void macos_window::macos_window_get_title(char * pszTitle, int iSize)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_send(^
                {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
                  NSString * str = [pnsmacoswindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void macos_window::macos_window_destroy()
{
   
   ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
   
   macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

   
   if(pnsmacoswindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: pnsmacoswindow];

   [pnsmacoswindow setReleasedWhenClosed: YES];
   
   pnsmacoswindow->m_pmacoswindow = NULL;
   
   [pnsmacoswindow close];
   
   pnsmacoswindow = nullptr;
   
   pnsmacoswindow = nullptr;

}


void macos_window::macos_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
   {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
      [pnsmacoswindow->m_pwindowcontroller showWindow : pnsmacoswindow];
      
      [pnsmacoswindow windowDidExpose:nil];

   });
   
}


void macos_window::macos_window_defer_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
   {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
      if(![pnsmacoswindow isVisible])
      {
      
         [pnsmacoswindow->m_pwindowcontroller showWindow : pnsmacoswindow];
      
         [pnsmacoswindow windowDidExpose:nil];
         
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

   ns_main_post(^
              {
                 
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 if(pnsmacoswindow)
                 {
                 
                    [pnsmacoswindow orderOut : nil];
                    
                 }
                 
                 if(pnsmacoswindow)
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
   
   ns_main_post(^
                 {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                    
                    if([pnsmacoswindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [pnsmacoswindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [pnsmacoswindow orderOut : nil];
                       
                       macos_window_iconified();
                       
                    }
                    
                    if(pnsmacoswindow->m_pmacoswindow == NULL)
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
   
   ns_main_post(^
              {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 
                 [pnsmacoswindow orderFront : pnsmacoswindow];
                 
              });
   
}


void macos_window::macos_window_make_first_responder()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
              {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 
                 [pnsmacoswindow makeFirstResponder:nullptr];
                 
              });
   
}


void macos_window::macos_window_resign_key()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
              {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 [pnsmacoswindow resignKeyWindow];
                 
              });
   
}



void macos_window::macos_window_make_key_window()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
              {
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 [pnsmacoswindow makeKeyWindow];
                 
              });
   
}


bool macos_window::macos_window_is_key_window() const
{

   if(m_bDestroying)
   {
      
      return false;
      
   }
   
   __block bool bKeyWindow = false;
   
   ns_main_send(^
   {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 
      bKeyWindow =  [pnsmacoswindow isKeyWindow];
                 
   });
   
   return bKeyWindow;
   
}


void macos_window::macos_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
              {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 [pnsmacoswindow makeKeyAndOrderFront: pnsmacoswindow];
                 
              });
   
}


void macos_window::macos_window_make_main_window()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
              {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                 
                 [pnsmacoswindow makeMainWindow];
                 
              });
   
}


void macos_window::macos_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
   
   macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

   
   auto proundwindow = pnsmacoswindow;
   
   if(proundwindow)
   {

   ns_main_post(^
                 {
                    
                   // m_bDirty = true;
                    
                    if(proundwindow)
                    {
                    
                       [proundwindow->m_pnsacmeimpact setNeedsDisplay:TRUE];
                       
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
   
   ns_main_send(^
                 {
                    
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

                    [pnsmacoswindow display];
                    
                 });
   
}



void macos_window::macos_window_set_frame(CGRect r)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_post(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      rect.origin.x     = r.origin.x;
      rect.origin.y     = rectScreen.size.height    -     r.origin.y - r.size.height;
      rect.size   = r.size;
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
      [pnsmacoswindow setFrame : rect display: TRUE];

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
   
   ns_main_send(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
      rect = [pnsmacoswindow frame];

      
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
   
   ns_main_post(^
   {
      
      ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) m_pnsacmewindow;
      
      macOSWindow * pnsmacoswindow = (macOSWindow *) pnsacmewindow;

      
      [pnsmacoswindow setViewsNeedDisplay : TRUE];
      
   });
   
}



void macos_window::macos_window_set_opacity(double dOpacity)
{
  
    if(dOpacity <= 0.)
    {
        
        m_dOpacity = 0.;
        
    }
    else if(dOpacity >= 1.)
    {
        
        m_dOpacity = 1.;
        
    }
    else
    {
        
        m_dOpacity = dOpacity;
        
    }
   
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
   
   ns_main_send(^{
   
   windowid = (CGWindowID)[pnswindow windowNumber];
      
   });
   
   return windowid;
   
}


void * ns_get_key_window()
{
   
   __block void * pnswindowKey = nullptr;
   
   ns_main_send(^{
      
      NSWindow * pwindowKey = [NSApp keyWindow];
      
      pnswindowKey = (__bridge void *) pwindowKey;
      
   });
   
   return pnswindowKey;
   
}
