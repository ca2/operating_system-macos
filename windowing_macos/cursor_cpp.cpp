//
//  cursor_cpp.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/04/22 19:38.
//
#include "framework.h"
#include "cursor.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/parallelization/synchronous_lock.h"

//::mutex  g_mutexCursor;
bool     g_bCursorHidden;
::pointer < ::windowing::cursor >   g_pwindowingcursor;

void __ns_cursor_hide();
void __ns_cursor_unhide();
void __ns_set_cursor(void * pNSCursor);
void __ns_cursor_free(void * pNSCursor);
void * __nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);
void * __ns_get_default_system_cursor(enum_cursor ecursor);


void _locked_ns_cursor_hide();
void _locked_ns_cursor_show();

void main_asynchronous(const ::procedure & procedure);


void ns_set_cursor(::windowing::cursor * pcursorParam)
{
   
   ::pointer < ::windowing::cursor > pcursor(pcursorParam);
   
   main_asynchronous([pcursor]()
   {

      {
         
         _synchronous_lock lock(pcursor->system()->synchronization());
         
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
         
      }

      g_pwindowingcursor = pcursor;
      
   });
   
}


::windowing::cursor * ns_get_cached_cursor()
{
   
   _synchronous_lock lock(platform::get()->system()->synchronization());
   
   return g_pwindowingcursor;
   
}


void ns_cursor_show()
{
   
   _synchronous_lock lock(platform::get()->system()->synchronization());
   
   _locked_ns_cursor_show();
   
}


void ns_cursor_hide()
{
   
   _synchronous_lock lock(::platform::get()->system()->synchronization());
  
   _locked_ns_cursor_hide();
  
}


void ns_cursor_free(void * pNSCursor)
{
   
   _synchronous_lock lock(::platform::get()->system()->synchronization());
   
   __ns_cursor_free(pNSCursor);
   
}


void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
{
   
   _synchronous_lock lock(::platform::get()->system()->synchronization());
   
   return __nscursor_from_cgimageref(image, cx, cy, xHotSpot, yHotSpot);
   
}


void * ns_get_default_system_cursor(enum_cursor ecursor)
{
   
   _synchronous_lock lock(::platform::get()->system()->synchronization());
   
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



