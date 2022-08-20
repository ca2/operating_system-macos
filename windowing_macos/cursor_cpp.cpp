//
//  cursor_cpp.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/04/22 19:38.
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif

::mutex  g_mutexCursor;
bool     g_bCursorHidden;
__pointer(::windowing::cursor)   g_pwindowingcursor;

void __ns_cursor_hide();
void __ns_cursor_unhide();
void __ns_set_cursor(void * pNSCursor);
void __ns_cursor_free(void * pNSCursor);
void * __nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);
void * __ns_get_default_system_cursor(enum_cursor ecursor);


void _locked_ns_cursor_hide();
void _locked_ns_cursor_show();


void ns_set_cursor(::windowing::cursor * pcursorParam)
{
   
   __pointer(::windowing::cursor) pcursor(pcursorParam);
   
   main_asynchronous([pcursor]()
   {

      synchronous_lock lock(&g_mutexCursor);
      
      auto pNSCursor = pcursor->get_os_data();
      
      if(is_null(pNSCursor))
      {
         
         //_locked_ns_cursor_hide();
         
      }
      else
      {

         __ns_set_cursor(pNSCursor);
         
         _locked_ns_cursor_show();
         
      }

      g_pwindowingcursor = pcursor;
      
   });
   
}


::windowing::cursor * ns_get_cached_cursor()
{
   
   synchronous_lock lock(&g_mutexCursor);
   
   return g_pwindowingcursor;
   
}


void ns_cursor_show()
{
   
   synchronous_lock lock(&g_mutexCursor);
   
   _locked_ns_cursor_show();
   
}


void ns_cursor_hide()
{
   
   synchronous_lock lock(&g_mutexCursor);
  
   _locked_ns_cursor_hide();
  
}


void ns_cursor_free(void * pNSCursor)
{
   
   synchronous_lock lock(&g_mutexCursor);
   
   __ns_cursor_free(pNSCursor);
   
}


void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
{
   
   synchronous_lock lock(&g_mutexCursor);
   
   return __nscursor_from_cgimageref(image, cx, cy, xHotSpot, yHotSpot);
   
}


void * ns_get_default_system_cursor(enum_cursor ecursor)
{
   
   synchronous_lock lock(&g_mutexCursor);
   
   return __ns_get_default_system_cursor(ecursor);

}
                                      


void _locked_ns_cursor_show()
{
   
   if(g_bCursorHidden)
   {
      
      __ns_cursor_unhide();
      
      g_bCursorHidden = false;
      
   }
   
}



void _locked_ns_cursor_hide()
{

   if(!g_bCursorHidden)
   {
      
      __ns_cursor_hide();
      
      g_bCursorHidden = true;
      
   }

}



