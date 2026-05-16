//
//  ns_interoperability.mm
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on May 2026.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "macos_app.h"
#include "ns_acme_form_impact_controller.h"
#include "ns_interoperability.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"
#include "acme/platform/application_menu.h"
#include "acme/handler/command_handler.h"
#include <Foundation/Foundation.h>



::uptr ns_show_dialog(const char * pszDialog)
{
   
   // 1. Get the delegate and cast it to your custom class
     macos_app *pmacosapp = (macos_app *)[NSApp delegate];
   
   NSString * strName = [[NSString alloc]initWithUTF8String:pszDialog];
   
   auto u = [pmacosapp showDialog:strName];
   
   return u;
}

NSWindow *ns_window_from_cg_window_id(CGWindowID windowID)
{
    for (NSWindow *window in NSApp.windows)
    {
        if ((CGWindowID)window.windowNumber == windowID)
        {
            return window;
        }
    }

    return nil;
}

NSView *ns_window_get_impact_by_tag(NSWindow * pnswindow, int iTag)
{
   if (pnswindow == nil)
       {
           return nil;
       }

       return [pnswindow.contentView viewWithTag:iTag];
}


NSView *ns_get_impact(::uptr u, ::uptr uChild)
{
   
   auto cgwindowid = (CGWindowID) u;
   
   auto pnswindow = ns_window_from_cg_window_id(cgwindowid);

   auto pnsimpact = ns_window_get_impact_by_tag(pnswindow, uChild);
   
   return pnsimpact;
   
}


template < typename NS_CLASS >
NS_CLASS * ns_typed_impact(::uptr u, ::uptr uChild)
{
   
   auto pnsimpact = ns_get_impact(u, uChild);
   
   if (![pnsimpact isKindOfClass:[NS_CLASS class]])
   {
      
      return nil;
      
   }

   auto p = (NS_CLASS *) pnsimpact;
   
   return p;

}

//
//::uptr ns_get_dlg_item(::uptr u, int iDlgItem)
//{
//
//   NSWindow * pwindowDialog = ns_window_from_cg_window_id(u);
//
//   if(pwindowDialog == nil)
//   {
//
//      NSLog(@"ns_get_dlg_item: window not found");
//
//      return 0;
//
//   }
//
//
//
//}

NSString * ns_get_impact_text(NSView * pnsview)
{
    if (pnsview == nil)
    {
        return nil;
    }

    if ([pnsview isKindOfClass:[NSTextField class]])
    {
        return [(NSTextField *) pnsview stringValue];
    }

    if ([pnsview isKindOfClass:[NSTextView class]])
    {
        return [(NSTextView *) pnsview string];
    }
   
   

    return nil;
}
char * ns_get_impact_text(::uptr u, ::uptr uChild)
{
   
   auto cgwindowid = (CGWindowID) u;
   auto pnswindow = ns_window_from_cg_window_id(cgwindowid);
   
   if(pnswindow == nil)
   {
      
      return nullptr;
      
   }
   
   auto iTag = (int)uChild;
   
   auto pnsimpact = ns_window_get_impact_by_tag(pnswindow, iTag);
   
   if(pnsimpact == nil)
   {
      
      return nullptr;
      
   }
   
   auto str = ns_get_impact_text(pnsimpact);
   
   if(str == nil)
   {
      return nullptr;
      
   }
   
   auto p = ::strdup([str UTF8String]);
   
   return p;

}
char * ns_get_window_text(::uptr u)
{
   auto cgwindowid = (CGWindowID) u;
   auto pnswindow = ns_window_from_cg_window_id(cgwindowid);
   
   if(pnswindow == nil)
   {
      
      return nullptr;
      
   }
   auto p = ::strdup([ pnswindow.title UTF8String]);
   return p;
   
}

::collection::index ns_combo_box_insert_string(::uptr u, ::uptr uChild, ::collection::index i, const char * psz)
{
   
   auto pcombobox = ns_typed_impact<NSComboBox>(u, uChild);
   
   if(!pcombobox)
   {
      
      throw_wrong_ns_type();
      
   }
   auto str = [[NSString alloc] initWithUTF8String:psz];
   [pcombobox insertItemWithObjectValue:str atIndex:i];
}

void ns_combo_box_reset_content(::uptr u, ::uptr uChild)
{
   
   auto pcombobox = ns_typed_impact<NSComboBox>(u, uChild);
   
   if(!pcombobox)
   {
      
      throw_wrong_ns_type();
      
   }
   [pcombobox removeAllItems];
}



