//
//  ns_window.mm
//  core_graphics
//
//  From early core_graphics/ns_bitmap.mm by
//  Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:53 <3ThomasBorregaardSørensen!!
//
#include <AppKit/AppKit.h>
#include "_mm.h"

void ns_window_release(ns_window_t & nswindow)
{
 
   if(nswindow.is_null())
   {
      
      return;
      
   }
   
   NSWindow * pns = (__bridge_transfer NSWindow *) nswindow.m_p;
   
   nswindow.clear();
      
}
