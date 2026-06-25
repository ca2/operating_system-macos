//
//  ns_interoperability.mm
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on May 2026.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "macos_app.h"
#include "ns_acme_impact.h"
#include "ns_acme_window.h"
#include "ns_acme_form_impact_controller.h"
#include "interoperability.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"
#include "acme/platform/application_menu.h"
#include "acme/handler/command_handler.h"
#include <Foundation/Foundation.h>
#include "interoperability_ns.h"
#include "operating_system-apple/core_graphics/_struct.h"
#import <objc/runtime.h>

char * øget_resource_name_strdup(int iResource);

#define WINDOW_WIDTH_USE_DEFAULT       ((int)0x80000000)

//static char g_nsEmbeddedPageAssociationKey;
//static char g_nsEmbeddedTabItemAssociationKey;
static char g_nsEmbeddedTabItemImpact;
static char g_nsEmbeddedImpactTabItem;
static char g_nsEmbeddedImpactController2;


void * impact_controller_association_id()
{
   
   return &g_nsEmbeddedImpactController2;
   
}


::uptr as_ns_window_uptr(NSWindow * pnswindow);
::uptr as_ns_impact_uptr(NSView * pnsview);
NSView *ns_window_get_impact_by_tag(NSWindow * pnswindow, int iTag);
NSView *ns_get_impact(::appkit::ns_impact_t nsimpact);



NSInteger ns_view_find_free_tag(
    NSView * prootview,
    NSInteger minimumTag)
{
    NSInteger tag = minimumTag;

    for(;;)
    {
        NSView * pfound =
            [prootview viewWithTag:tag];

        if(pfound == nil)
        {
            return tag;
        }

        tag++;
    }
}

NSInteger ns_window_find_free_tag(
    NSWindow * pwindow,
    NSInteger minimumTag)
{
    if(pwindow == nil)
    {
        return minimumTag;
    }

    return ns_view_find_free_tag(
        pwindow.contentView,
        minimumTag);
}


NSWindow * as_ns_window(const ::operating_system::window & operatingsystemwindow)
{

   if(operatingsystemwindow.m_eoperatingambient != ::windowing::e_operating_ambient_macos_impact2)
      {
         
         auto pnsimpact = (__bridge NSView *)(void *) operatingsystemwindow.m_window.m_ulla[0];
         
         
         return [pnsimpact window];

         
      }
   else if(operatingsystemwindow.m_eoperatingambient != ::windowing::e_operating_ambient_macos
      && operatingsystemwindow.m_eoperatingambient != ::windowing::e_operating_ambient_macos_impact_by_tag)
   {
      
      return nil;
      
   }
   
   auto pnswindow = (__bridge NSWindow *)(void *) operatingsystemwindow.m_window.m_ulla[0];
   
   return pnswindow;
   
}


namespace cross_windows
{


::operating_system::window create_window(::i32 xPos, ::i32 yPos, ::i32 width, ::i32 height, const ::operating_system::window & operatingsystemwindowParent,
                                         ::acme::windowing::window * pacmewindowingwindow,
                                         ::appkit::acme_window_bridge * pacmewindowbridge)
{
   
   ::operating_system::window operatingsystemwindow{};
   
   NSRect r;
   
   r.origin.x = xPos == WINDOW_WIDTH_USE_DEFAULT ? 200 : xPos;
   r.origin.y = yPos == WINDOW_WIDTH_USE_DEFAULT ? 200 : yPos;
   r.size.width = width == WINDOW_WIDTH_USE_DEFAULT ? 1024 : width;
   r.size.height = height == WINDOW_WIDTH_USE_DEFAULT ? 768 : height;
   
   if(operatingsystemwindowParent.is_null())
   {
      
      macos_app *pmacosapp = (macos_app *)[NSApp delegate];

      auto pnsacmewindow = [ pmacosapp createMainFrame : r styleMask : 0 withAcmeWindowingWindow:pacmewindowingwindow withAcmeWindowBridge:pacmewindowbridge];
      
      NSWindow * pnswindow = pnsacmewindow;
      
      operatingsystemwindow = ::as_operating_system_window(::as_ns_window_uptr(pnswindow));
      
   }
   else
   {
      
      NSWindow * pnswindow = ::as_ns_window(operatingsystemwindowParent);
      
      NSView * pnsimpactParent = nullptr;
      
      if(operatingsystemwindowParent.m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact_by_tag)
      {
         
         pnsimpactParent = ns_window_get_impact_by_tag(pnswindow, operatingsystemwindowParent.m_window.m_ulla[1]);
         
      }
      else if(operatingsystemwindowParent.m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact2)
      {
         
         pnsimpactParent = ns_window_get_impact_by_tag(pnswindow, operatingsystemwindowParent.m_window.m_ulla[1]);
         
      }

      NSView * pnsimpactChild = nullptr;
      
      if(pnsimpactParent)
      {
         
         throw "";
         
      }
      else
      {
         
         ns_acme_window * pnsacmewindow = pnswindow;
         
         NSRect bounds = [ pnswindow frame ];
         
         bounds.origin = NSZeroPoint;
         
         auto pnsacmeimpact = [ [ ns_acme_impact alloc ] initWithFrame: bounds andBridge: pacmewindowbridge ];
         
         pnsimpactChild = pnsacmeimpact;
         
         [ pnsacmewindow setContentView: pnsimpactChild ];
         
         [ pnsimpactChild setFrame: bounds ];
         
         [ pnsimpactChild setAutoresizingMask: 0 ];
         
//         int uMinimumTag = 2000;
//         
//         auto uTagNew = ns_view_find_free_tag(pnsimpactChild, uMinimumTag);
//         
//         pnsacmeimpact.tag = uTagNew;
         
         operatingsystemwindow = ::operating_system::window(
                                                            ::windowing::e_operating_ambient_macos_impact2, ::as_ns_impact_uptr(pnsimpactChild), 0);
         
         //return operatingsystemwindow;
         
      }
      
   }
   
   return operatingsystemwindow;
   
}


} // namespace cross_windows


NSWindow *ns_window_from_ns_window_t(::appkit::ns_window_t nswindow)
{
   auto pnswindow = (__bridge NSWindow *)nswindow.m_p;

    return pnswindow;
}


void ns_window_destroy_window(::appkit::ns_window_t nswindow)
{
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   [pnswindow orderOut:nil];
   
   [pnswindow close];
   
}


void ns_window_show(::appkit::ns_window_t nswindow)
{
   auto pnswindow = ns_window_from_ns_window_t(nswindow);

//   NSTabViewItem * pnstabviewitem =
//      objc_getAssociatedObject(pnswindow, &g_nsEmbeddedTabItemAssociationKey);
//
//   if(pnstabviewitem != nil)
//   {
//
//      return;
//
//   }
//
//   NSView * pnsimpactEmbedded =
//      objc_getAssociatedObject(pnswindow, &g_nsEmbeddedPageAssociationKey);
//
//   if(pnsimpactEmbedded != nil)
//   {
//
//      [pnsimpactEmbedded setHidden:NO];
//      return;
//
//   }
//   
   [[pnswindow windowController] showWindow:nil];
   [pnswindow makeKeyAndOrderFront:nil];
   
}
void ns_window_hide(::appkit::ns_window_t nswindow)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);

//   NSTabViewItem * pnstabviewitem =
//      objc_getAssociatedObject(pnswindow, &g_nsEmbeddedTabItemAssociationKey);
//
//   if(pnstabviewitem != nil)
//   {
//
//      return;
//
//   }
//
//   NSView * pnsimpactEmbedded =
//      objc_getAssociatedObject(pnswindow, &g_nsEmbeddedPageAssociationKey);
//
//   if(pnsimpactEmbedded != nil)
//   {
//
//      [pnsimpactEmbedded setHidden:YES];
//      return;
//
//   }
   
   [pnswindow orderOut:nil];

}


void ns_window_enable_window(::appkit::ns_window_t nswindow, bool bEnable)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   if(pnswindow == nil)
   {
      
      return;
      
   }
   
}


bool ns_window_is_this_window_enabled(::appkit::ns_window_t nswindow)
{
   
   return true;
   
}


bool ns_window_is_window_enabled(::appkit::ns_window_t nswindow)
{
   
   return true;
   
}


bool ns_move_window_to_tab_control(::appkit::ns_impact_t nsimpactTabControl,
                                   ::appkit::ns_window_t nswindowPage)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);
   NSWindow * pnswindowPage = ns_window_from_ns_window_t(nswindowPage);

   if(pnsimpactTabControl == nil || pnswindowPage == nil)
   {

      return false;

   }

   NSView * pnsimpactContainer = pnsimpactTabControl;
   NSTabViewItem * pnstabviewitem = nil;

   if([pnsimpactTabControl isKindOfClass:[NSTabView class]])
   {

      pnstabviewitem = [[NSTabViewItem alloc] initWithIdentifier:nil];
      [(NSTabView *) pnsimpactTabControl addTabViewItem:pnstabviewitem];

   }
   else if([pnsimpactTabControl isKindOfClass:[NSBox class]])
   {

      pnsimpactContainer = [(NSBox *) pnsimpactTabControl contentView];

   }

   NSView * pnsimpactPage = [pnswindowPage contentView];

   if(pnsimpactContainer == nil || pnsimpactPage == nil)
   {

      return false;

   }

   [pnswindowPage orderOut:nil];
   [pnsimpactPage removeFromSuperview];
   [pnsimpactPage setTranslatesAutoresizingMaskIntoConstraints:YES];
   [pnsimpactPage setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
   if(pnstabviewitem != nil)
   {

      [pnstabviewitem setView:pnsimpactPage];

   }
   else
   {

      [pnsimpactPage setFrame:[pnsimpactContainer bounds]];
      [pnsimpactPage setHidden:YES];
      [pnsimpactContainer addSubview:pnsimpactPage];

   }

   return true;

}


bool ns_tab_control_set_page_caption(::appkit::ns_impact_t nsimpactTabControl,
                                     ::appkit::ns_window_t nswindowPage,
                                     const char * pszCaption)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);
   
   NSWindow * pnswindowPage = ns_window_from_ns_window_t(nswindowPage);
   
   NSTabViewItem * pnstabviewitem = objc_getAssociatedObject(pnswindowPage, &g_nsEmbeddedImpactTabItem);

   if(![pnsimpactTabControl isKindOfClass:[NSTabView class]] || pnstabviewitem == nil)
   {

      return false;

   }

   pnstabviewitem.label = [NSString stringWithUTF8String:pszCaption ? pszCaption : ""];
   
   return true;

}


void ns_tab_control_add_page(::appkit::ns_impact_t nsimpactTabControl,
                             ::appkit::ns_impact_t nsimpactTab,
                                     const char * pszCaption)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);
   
   NSView * pnsimpactTab = ns_get_impact(nsimpactTab);
   
   if(![pnsimpactTabControl isKindOfClass:[NSTabView class]])
   {
      
      throw "ns_tab_control_add_page failed";
      
   }
   
   NSTabView * pnstabview = pnsimpactTabControl;
   
   NSTabViewItem * pnstabviewitem = [[NSTabViewItem alloc] initWithIdentifier:nil];

   if([pnsimpactTab isKindOfClass:[NSView class]])
   {
      
      objc_setAssociatedObject(
                               pnstabviewitem,
                               &g_nsEmbeddedTabItemImpact,
                               pnsimpactTab,
                               OBJC_ASSOCIATION_RETAIN_NONATOMIC);
      
      objc_setAssociatedObject(
                               pnsimpactTab,
                               &g_nsEmbeddedImpactTabItem,
                               pnstabviewitem,
                               OBJC_ASSOCIATION_RETAIN_NONATOMIC);
      
      [pnstabviewitem setView:pnsimpactTab];
      
   }

   pnstabviewitem.label = [NSString stringWithUTF8String:pszCaption ? pszCaption : ""];
   
   [pnstabview addTabViewItem:pnstabviewitem];
   
}


bool ns_tab_control_select_item(::appkit::ns_impact_t nsimpactTabControl, int iItem)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);

   if(![pnsimpactTabControl isKindOfClass:[NSTabView class]])
   {

      return false;

   }

   NSTabView * pnstabview = (NSTabView *) pnsimpactTabControl;

   if(iItem < 0 || iItem >= pnstabview.numberOfTabViewItems)
   {

      return false;

   }
   
   auto pnstabviewitem = [ pnstabview tabViewItemAtIndex: iItem ];
   
   if(pnstabviewitem)
   {
      
      NSView * pnsimpactTab = objc_getAssociatedObject(
                               pnstabviewitem,
                               &g_nsEmbeddedTabItemImpact);

      if(pnsimpactTab)
      {
         
         //[ pnstabview addSubview: pnsimpactTab ];
         
         NSViewController * pimpactcontroller = objc_getAssociatedObject(
                                  (NSView*) pnsimpactTab,
                                  impact_controller_association_id());
         
         [ pnstabview.window.contentViewController addChildViewController: pimpactcontroller ];
         
      }
      
   }

   [ pnstabview selectTabViewItemAtIndex:iItem ];
   
   return true;

}


int ns_tab_control_get_selected_item(::appkit::ns_impact_t nsimpactTabControl)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);

   if(![pnsimpactTabControl isKindOfClass:[NSTabView class]])
   {

      return -1;

   }

   NSTabView * pnstabview = (NSTabView *) pnsimpactTabControl;
   NSTabViewItem * pnstabviewitem = pnstabview.selectedTabViewItem;

   if(pnstabviewitem == nil)
   {

      return -1;

   }

   return (int) [pnstabview indexOfTabViewItem:pnstabviewitem];

}


void ns_tab_control_erase_page(::appkit::ns_impact_t nsimpactTabControl,
                                ::appkit::ns_impact_t nsimpactTab)
{

   NSView * pnsimpactTabControl = ns_get_impact(nsimpactTabControl);
   NSView * pnsimpactTab = ns_get_impact(nsimpactTab);
   NSTabViewItem * pnstabviewitem =
      objc_getAssociatedObject(pnsimpactTab, &g_nsEmbeddedImpactTabItem);

   if(![pnsimpactTabControl isKindOfClass:[NSTabView class]] || pnstabviewitem == nil)
   {

      throw "ns_tab_control_erase_page bad argument";

   }

   [(NSTabView *) pnsimpactTabControl removeTabViewItem:pnstabviewitem];
   
   

}


int ns_window_redraw(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect * pcgrect, bool bErase)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   if(pnswindow == nil)
   {
      
      return 0;
      
   }
   
   if(!pcgrect)
   {
      
      [[pnswindow contentView] setNeedsDisplay:(BOOL)true];
      
   }
   else{
      
      NSRect r;
      r.origin.x = pcgrect->origin.x;
      r.origin.y = pcgrect->origin.y;
      r.size.width = pcgrect->size.w;
      r.size.height = pcgrect->size.h;
      [[pnswindow contentView] setNeedsDisplayInRect:r];
      
   }

   return 1;
   
}


void ns_window_get_client_rect(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect * pcgrect)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   auto rBounds = [ [ pnswindow contentView ] bounds ];
   
   pcgrect->origin.x = rBounds.origin.x;
   pcgrect->origin.y = rBounds.origin.y;
   pcgrect->size.w = rBounds.size.width;
   pcgrect->size.h = rBounds.size.height;
   
}


int ns_window_set_window_pos(::appkit::ns_window_t nswindow,
                              ::appkit::ns_window_t nswindowOther,
                    int x, int y, int w, int h, int flags)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   if(pnswindow == nil)
   {
      
      return 0;
      
   }
   
   if(!(flags & ::user_interface::e_SWP_NOMOVE))
   {
      
      if(!(flags & ::user_interface::e_SWP_NOSIZE))
      {
       
         NSRect r = NSMakeRect(x, y, w, h);
         
         [pnswindow setFrame:r display:YES];
         
      }
      else
      {
         
         NSRect f = pnswindow.frame;
         f.size = NSMakeSize(w, h);
         [pnswindow setFrame:f display:YES];
         
      }
      
   }
   else if(!(flags & ::user_interface::e_SWP_NOSIZE))
   {
      
      [pnswindow setFrameTopLeftPoint:NSMakePoint(x, y)];
      //NSRect f = pnswindow.frame;
      //f.origin = NSMakePoint(x, y);
      //[pnswindow setFrameOrigin:f.origin];
   }
   
   // bring front
   // [window orderFront:nil];
   
   // send back
   // [window orderBack:nil];
   
   // hide
   // [window orderOut:nil];
   
   // without activating app
   // [window orderFront:nil];
   
   // activate app + window
   // [window makeKeyAndOrderFront:nil];
   // [NSApp activateIgnoringOtherApps:YES];
   
   return 1;
   
}



::core_graphics::cg_rect ns_window_monitor_rect(::appkit::ns_window_t nswindow)
{
   auto window = ns_window_from_ns_window_t(nswindow);
   
       NSScreen* screen = nil;

       if (window != nil)
       {
           screen = [window screen];
       }

       // Fallback
       if (screen == nil)
       {
           screen = [NSScreen mainScreen];
       }

       if (screen == nil)
       {
           return {};
       }

       NSRect frame = [screen frame];

       ::core_graphics::cg_rect rectangle;

       rectangle.origin.x   = (int)frame.origin.x;
       rectangle.origin.y    = (int)frame.origin.y;
       rectangle.size.w  = frame.size.width;
       rectangle.size.h =frame.size.height;

       return rectangle;
   //}
}


void ns_window_minimize(::appkit::ns_window_t nswindow)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   if(pnswindow == nil)
   {
      
      return;
      
   }
      
   ns_acme_window * pnsacmewindow = pnswindow;
      
   if(pnsacmewindow != nil)
   {
      
      if (pnsacmewindow.styleMask & NSWindowStyleMaskMiniaturizable) {
         
         [pnsacmewindow minimizeWindowInstantly];
      } else {
          NSLog(@"This window is not configured to allow minimization.");
      }

      
   }
   else
   {
      
      if (pnswindow.styleMask & NSWindowStyleMaskMiniaturizable) {
         [pnswindow miniaturize:nil];
      } else {
          NSLog(@"This window is not configured to allow minimization.");
      }
      
      
   }
   

}


void ns_window_enter_immersive_fullscreen(::appkit::ns_window_t nswindow)
{
   
   auto window = ns_window_from_ns_window_t(nswindow);
   
   ns_acme_window * pnsacmewindow = window;
   
   if(pnsacmewindow != nil)
   {
      
      [pnsacmewindow enterImmersiveFullscreen];
      
   }

   

}


void ns_window_exit_immersive_fullscreen(::appkit::ns_window_t nswindow)
{
   
   auto window = ns_window_from_ns_window_t(nswindow);
   
   ns_acme_window * pnsacmewindow = window;
   
   if(pnsacmewindow != nil)
   {
      
      [pnsacmewindow exitImmersiveFullscreen];
      
   }
   
}



::uptr ns_show_dialog(const char * pszDialog, ::acme::windowing::window * pacmewindowingwindow)
{
   
   // 1. Get the delegate and cast it to your custom class
     macos_app *pmacosapp = (macos_app *)[NSApp delegate];
   
   NSString * strName = [[NSString alloc]initWithUTF8String:pszDialog];
   
   auto u = [pmacosapp showDialog:strName withAcmeWindowingWindow: pacmewindowingwindow];
   
   return u;
}


::uptr ns_create_offscreen_child_dialog(const char * pszDialog, ::acme::windowing::window * pacmewindowingwindow)
{
   
   // 1. Get the delegate and cast it to your custom class
   macos_app *pmacosapp = (macos_app *)[NSApp delegate];
   
   NSString * strName = [[NSString alloc]initWithUTF8String:pszDialog];
   
   auto u = [pmacosapp createOffscreenChildDialog:strName withAcmeWindowingWindow: pacmewindowingwindow];
   
   return u;
   
}


int ns_do_modal_dialog(const char * pszDialog, ::acme::windowing::window * pacmewindowingwindow)
{
   
   // 1. Get the delegate and cast it to your custom class
     macos_app *pmacosapp = (macos_app *)[NSApp delegate];
   
   NSString * strName = [[NSString alloc]initWithUTF8String:pszDialog];
   
   auto i = [pmacosapp doModalDialog:strName withAcmeWindowingWindow: pacmewindowingwindow];
   
   return i;
}

void ns_do_attached_modal_dialog(const char * pszResourceName,
                                 ::acme::windowing::window * pacmewindowingwindow,
                            const ::operating_system::window & operatingsystemwindowParent,
                                 const ::function < void(int) > & callback)
{
   
   macos_app *pmacosapp = (macos_app *)[NSApp delegate];
   
   auto pnswindowParent = ::as_ns_window(operatingsystemwindowParent);
 
   NSString * strName = [[NSString alloc]initWithUTF8String:pszResourceName];
 
   [ pmacosapp doAttachedModalDialog:strName withAcmeWindowingWindow: pacmewindowingwindow
 parentWindow: pnswindowParent andCallback: callback];
   
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




ns_acme_form_impact_controller *ns_form_controllerø(NSWindow * pnswindow)
{
   if(pnswindow == nil)
   {
      return nil;
   }
   auto pnsimpactcontrol = [pnswindow contentViewController];
   if(pnsimpactcontrol == nil)
   {
      return nil;
   }
   auto pformcontroller = (ns_acme_form_impact_controller *) pnsimpactcontrol;
   if(pformcontroller == nil)
   {
      return nil;
   }
   return pformcontroller;

}

ns_acme_form_impact_controller *ns_form_controllerø(::appkit::ns_window_t nswindow)
{
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   return ns_form_controllerø(pnswindow);
}


NSView * ns_impact_get_impact_by_tag(NSView * pnsimpactRoot, int iTag)
{
   
   if(pnsimpactRoot == nil)
   {
      
      return nil;;
      
   }

   auto pnsimpact = [ pnsimpactRoot viewWithTag: iTag ];

   if(pnsimpact == nil)
   {

      return nil;

   }

   return pnsimpact;

}


NSView *ns_window_get_impact_by_tag(NSWindow * pnswindow, int iTag)
{
   
   if (pnswindow == nil)
   {
      
      return nil;
      
   }
   
   auto pnsimpact = ns_impact_get_impact_by_tag([pnswindow contentView], iTag);
   
   if(pnsimpact != nil)
   {
      
      return pnsimpact;
      
   }
   
   if(iTag == 0 || iTag == 2000)
   {

      pnsimpact = pnswindow.contentView;

   }

   if(pnsimpact != nil)
   {
    
      return pnsimpact;
      
   }
   
   return pnsimpact;

}


static NSView *FindViewWithIdentifier(NSView *rootView, NSString *identifier)
{
   if ([rootView.identifier isEqualToString:identifier])
      return rootView;

   for (NSView *subview in rootView.subviews)
   {
      NSView *found = FindViewWithIdentifier(subview, identifier);

      if (found)
         return found;
   }

   return nil;
}

::operating_system::window ns_get_impact_operating_system_window_by_tag(const ::operating_system::window & operatingsystemwindow, int iDialogItem)
{
   
   if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos)
   {
      
      return ns_get_impact_operating_system_window_by_tag_from_window(operatingsystemwindow, iDialogItem);
      
   }
   else
   {
      
      return ns_get_impact_operating_system_window_by_tag_from_impact(operatingsystemwindow, iDialogItem);
      
   }
   
}


::operating_system::window ns_get_impact_operating_system_window_by_tag_from_window(::appkit::ns_window_t nswindow, int iDialogItem)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
  
   auto pnsimpact = ns_window_get_impact_by_tag(pnswindow, iDialogItem);
   
   if(pnsimpact)
   {
      
      return {::windowing::e_operating_ambient_macos_impact2, (::uptr)(__bridge void *) pnsimpact};
      
   }

   auto p = øget_resource_name_strdup(iDialogItem);
   
   if(p)
   {
      
      NSString * strId = [[NSString alloc] initWithUTF8String:p];
      
      if(strId)
      {
         
         pnsimpact =FindViewWithIdentifier([pnswindow contentView], strId);
         
      }
      
      free(p);
      
   }
   
   if(pnsimpact)
   {
      
      return {::windowing::e_operating_ambient_macos_impact2, (::uptr)(__bridge void *) pnsimpact};
   }
   
   return {};
   
}

::operating_system::window ns_get_impact_operating_system_window_by_tag_from_impact(::appkit::ns_impact_t nsimpact, int iDialogItem)
{
   
   auto pnsimpactRoot = ns_get_impact(nsimpact);

   auto pnsimpact = ns_impact_get_impact_by_tag(pnsimpactRoot, iDialogItem);
   
   if(pnsimpact)
   {
      
      return {::windowing::e_operating_ambient_macos_impact2, (::uptr)(__bridge void *) pnsimpact};
      
   }

   auto p = øget_resource_name_strdup(iDialogItem);
   
   if(p)
   {
      
      NSString * strId = [[NSString alloc] initWithUTF8String:p];
      
      if(strId)
      {
         
         pnsimpact = FindViewWithIdentifier(pnsimpactRoot, strId);
         
      }
      
      free(p);
      
   }
   
   if(pnsimpact)
   {
      
      return {::windowing::e_operating_ambient_macos_impact2, (::uptr)(__bridge void *) pnsimpact};
   }
   
   return {};
   
}


NSView * ns_get_impact(::appkit::ns_impact_t nsimpact)
{
   
   if(nsimpact.m_pNSWindow)
   {
      
      auto pnswindow = ns_window_from_ns_window_t(nsimpact.ns_window());
      
      auto pnsimpact = ns_window_get_impact_by_tag(pnswindow, nsimpact.m_uTag);
      
      return pnsimpact;
      
   }
   else if(nsimpact.m_pNSImpact)
   {
      
      return (__bridge NSView *) nsimpact.m_pNSImpact;
      
   }
   else
   {
    
      return nullptr;
      
   }
   
}


NSView *ns_get_impact(ns_acme_form_impact_controller * pformcontroller, ::uptr uTag)
{
   
   auto pnswindow = pformcontroller.view.window;

   auto pnsimpact = ns_window_get_impact_by_tag(pnswindow, uTag);
   
   return pnsimpact;
   
}


void ns_impact_get_client_rect(::appkit::ns_impact_t nsimpact, ::core_graphics::cg_rect * pcgrect)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   auto rBounds = [ pnsimpact bounds ];
   
   pcgrect->origin.x = rBounds.origin.x;
   pcgrect->origin.y = rBounds.origin.y;
   pcgrect->size.w = rBounds.size.width;
   pcgrect->size.h = rBounds.size.height;
   
}


int ns_impact_set_window_pos(::appkit::ns_impact_t nsimpact,
                              ::appkit::ns_impact_t nsimpactOther,
                    int x, int y, int w, int h, int flags)
{
 
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
      
      return 0;
      
   }
   
   if(!(flags & ::user_interface::e_SWP_NOMOVE))
   {
      
      if(!(flags & ::user_interface::e_SWP_NOSIZE))
      {
       
         NSRect r = NSMakeRect(x, y, w, h);
         
         [pnsimpact setFrame:r];
         
      }
      else
      {
         
         NSRect f = pnsimpact.frame;
         f.size = NSMakeSize(w, h);
         [pnsimpact setFrame:f];
         
      }
      
   }
   else if(!(flags & ::user_interface::e_SWP_NOSIZE))
   {
      
      //[pnsimpact setFrameTopLeftPoint:NSMakePoint(x, y)];
      NSRect f = pnsimpact.frame;
      f.origin = NSMakePoint(x, y);
      [pnsimpact setFrame:f];
   }
   
   // bring to front
   // [[view superview] addSubview:view positioned:NSWindowAbove relativeTo:nil];
   
   // send behind
   // [[view superview] addSubview:view positioned:NSWindowBelow relativeTo:nil];
   // or
   // [view removeFromSuperview];
   // [parent addSubview:view];
   
   return 1;
   
}


template < typename NS_CLASS >
NS_CLASS * _ns_typed_impact(::appkit::ns_impact_t nsimpact)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if (![pnsimpact isKindOfClass:[NS_CLASS class]])
   {
      
      return nil;
      
   }

   auto p = (NS_CLASS *) pnsimpact;
   
   return p;

}
template < typename NS_CLASS >
NS_CLASS * _ns_typed_impact(ns_acme_form_impact_controller * pformcontroller, ::uptr uChild)
{
   
   auto pnsimpact = ns_get_impact(pformcontroller, uChild);
   
   if (![pnsimpact isKindOfClass:[NS_CLASS class]])
   {
      
      return nil;
      
   }

   auto p = (NS_CLASS *) pnsimpact;
   
   return p;

}

template < typename NS_CLASS >
NS_CLASS * ns_impactø(::appkit::ns_impact_t nsimpact)
{
   
   auto p = _ns_typed_impact<NS_CLASS>(nsimpact);
   
   if (p == nil)
   {
      
      throw_wrong_ns_type();
      
   }

   return p;

}
template < typename NS_CLASS >
NS_CLASS * ns_impactø(ns_acme_form_impact_controller * pformcontroller, ::uptr uChild)
{
   
   auto p = _ns_typed_impact<NS_CLASS>(pformcontroller, uChild);
   
   if (p == nil)
   {
      
      throw_wrong_ns_type();
      
   }

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


void ns_end_dialog(::appkit::ns_window_t nswindow, int iDialogResult)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);

   if (NSApp.modalWindow == pnswindow)
   {

      [NSApp stopModalWithCode:iDialogResult];

   }


}
void ns_end_attached_modal(::appkit::ns_window_t nswindow, int iDialogResult)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   [ NSApp endSheet:pnswindow returnCode: iDialogResult];
   
}

NSString * ns_get_impact_text(NSView * pnsimpact)
{
    if (pnsimpact == nil)
    {
        return nil;
    }

    if ([pnsimpact isKindOfClass:[NSTextField class]])
    {
        return [(NSTextField *) pnsimpact stringValue];
    }
else
    if ([pnsimpact isKindOfClass:[NSTextView class]])
    {
        return [(NSTextView *) pnsimpact string];
    }
    else
        if ([pnsimpact isKindOfClass:[NSComboBox class]])
        {
            return [(NSComboBox *) pnsimpact stringValue];
        }

   

    return nil;
}

void ns_set_impact_text(NSView * pnsimpact, const char * pszText)
{
    if (pnsimpact == nil)
    {
        return nil;
    }
   
   auto str = [NSString alloc];
   
   if(::is_empty(pszText))
   {
      
      str = [str init];
      
   }
   else
   {
    
      str = [str initWithUTF8String:pszText];
      
   }

    if ([pnsimpact isKindOfClass:[NSTextField class]])
    {
        [(NSTextField *) pnsimpact setStringValue:str];
    }
    else
    if ([pnsimpact isKindOfClass:[NSTextView class]])
    {
        [(NSTextView *) pnsimpact setString:str];
    }
else if ([pnsimpact isKindOfClass:[NSComboBox class]])
{
    [(NSComboBox *) pnsimpact setStringValue:str];
}

   
}


void ns_impact_destroy_window(::appkit::ns_impact_t nsimpact)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
      
      return nullptr;
      
   }
   
   [pnsimpact removeFromSuperview];
   
}


void ns_impact_enable_window(::appkit::ns_impact_t nsimpact, bool bEnable)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
      
      return nullptr;
      
   }
   
   if([pnsimpact isKindOfClass:[NSControl class]])
   {
      
      NSControl * pnscontrol = pnsimpact;
      
      [ pnscontrol setEnabled:bEnable ];
      
   }
   
}


bool ns_impact_is_this_window_enabled(::appkit::ns_impact_t nsimpact)
{
   
   return ns_impact_is_window_enabled(nsimpact);
   
}


bool ns_impact_is_window_enabled(::appkit::ns_impact_t nsimpact)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
      
      return true;
      
   }
   
   if([pnsimpact isKindOfClass:[NSControl class]])
   {
      
      NSControl * pnscontrol = pnsimpact;
      
      bool bEnabled = [ pnscontrol isEnabled ] != FALSE;
      
      return bEnabled;
      
   }
   
   return true;
   
}


char * ns_get_impact_text(::appkit::ns_impact_t nsimpact)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
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



void ns_set_impact_text(::appkit::ns_impact_t nsimpact, const char * pszText)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
      
      return nullptr;
      
   }
   
   ns_set_impact_text(pnsimpact, pszText);

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
void ns_set_window_text(::uptr u, const char * pszText)
{
   auto cgwindowid = (CGWindowID) u;
   auto pnswindow = ns_window_from_cg_window_id(cgwindowid);
   
   if(pnswindow == nil)
   {
      
      return nullptr;
      
   }
   auto str = [[NSString alloc] initWithUTF8String:pszText];
   pnswindow.title = str;
   
   
}




// NSComboBox

@implementation ComboItem

- (instancetype)initWithTitle:(NSString *)title
                        payload:(uint64_t)value
{
    self = [super init];

    if (self)
    {
        _title = [title copy];
        _payload = value;
    }

    return self;
}

- (id)copyWithZone:(NSZone *)zone
{
    ComboItem *copy =
        [[[self class] allocWithZone:zone]
            initWithTitle:self.title
                    payload:self.payload];

    return copy;
}

- (NSString *)description
{
    return self.title;
}

@end


::collection::index ns_combo_box_insert_string(::appkit::ns_impact_t nsimpact, ::collection::index i, const char * psz)
{
   
   auto pcombobox = ns_impactø<NSComboBox>(nsimpact);
   
   auto str = [[NSString alloc] initWithUTF8String:psz];
   auto pitem = [[ComboItem alloc] initWithTitle:str
                                  payload:0];
   [pcombobox insertItemWithObjectValue:pitem atIndex:i];
}

void ns_combo_box_reset_content(::appkit::ns_impact_t nsimpact)
{
   
   [ ns_impactø<NSComboBox>(nsimpact) removeAllItems];
   
}


::collection::count ns_combo_box_get_count(::appkit::ns_impact_t nsimpact)
{
   
   return [ ns_impactø<NSComboBox>(nsimpact) numberOfItems] ;
   
}


::collection::index ns_combo_box_get_cur_sel(::appkit::ns_impact_t nsimpact)
   {
   
   return [ ns_impactø<NSComboBox>(nsimpact) indexOfSelectedItem];
   
}


void ns_combo_box_set_cur_sel(::appkit::ns_impact_t nsimpact, ::collection::index i)
{
   
   auto pformcontroller = ns_form_controllerø(nsimpact.ns_window());
   
   ::user_interface::block_control_notification blockcontrolnotification(pformcontroller, nsimpact.m_uTag, ::user_interface::e_CBN_SELENDOK);
   
   auto pcombo = ns_impactø<NSComboBox>(pformcontroller, nsimpact.m_uTag);

   [ pcombo selectItemAtIndex: i ];
   
}


void ns_combo_box_set_item_data(::appkit::ns_impact_t nsimpact, ::collection::index i, void * p)
{
  
   ComboItem * pitem = [ ns_impactø<NSComboBox>(nsimpact) itemObjectValueAtIndex:i];
   
   if(pitem == nil)
   {
      auto str = [[NSString alloc] init];
      pitem = [[ComboItem alloc] initWithTitle:str
                                     payload:(::uptr)p];
      
      [ns_impactø<NSComboBox>(nsimpact) insertItemWithObjectValue:pitem atIndex:i];
      
   }
   else
   {
      
      pitem.payload = (::uptr)p;
      
   }
}


void * ns_combo_box_get_item_data(::appkit::ns_impact_t nsimpact, ::collection::index i)
            {
   ComboItem * pitem = [ ns_impactø<NSComboBox>(nsimpact) itemObjectValueAtIndex:i];
   
   if(pitem == nil)
   {
      return nullptr;
   }
   
   
   return (void *) (::uptr) [ pitem payload];

   
}


::string ns_combo_box_get_lb_text(::appkit::ns_impact_t nsimpact, ::collection::index i)
               {
   
   ComboItem * pitem = [ ns_impactø<NSComboBox>(nsimpact) itemObjectValueAtIndex:i];
   
   if(pitem == nil)
   {
      return {};
   }
   return [[pitem title] UTF8String];
}


void ns_combo_box_delete_string(::appkit::ns_impact_t nsimpact, ::collection::index i)
                  {
   
   [ns_impactø<NSComboBox>(nsimpact) removeItemAtIndex:i];
}



bool ns_window_is_in_immersive_fullscreen(::appkit::ns_window_t nswindow)
{
   
   auto window = ns_window_from_ns_window_t(nswindow);
   
   ns_acme_window * pnsacmewindow = window;
   
   if(pnsacmewindow != nil)
   {
      
      return [pnsacmewindow isInImmersiveFullscreen];
      
   }

   return false;

}

void ns_window_toggle_immersive_fullscreen(::appkit::ns_window_t nswindow)
{
   
   auto window = ns_window_from_ns_window_t(nswindow);
   
   ns_acme_window * pnsacmewindow = window;
   
   if(pnsacmewindow != nil)
   {
      
      [pnsacmewindow toggleImmersiveFullscreen];
      
   }
  

}

void ns_window_set_mouse_cursor(::appkit::ns_window_t nswindow, ::enum_cursor ecursor)
{
   
   auto pnswindow = ns_window_from_ns_window_t(nswindow);
   
   ns_acme_window * pnsacmewindow = pnswindow;
   
   if(pnsacmewindow == nil)
   {
      
      return;
      
   }
      
   ns_acme_impact * pnsacmeimpact = pnsacmewindow->m_pnsacmeimpact;
   
   if(pnsacmeimpact == nil)
   {
      
      return;
      
   }
         
   [ pnsacmeimpact setMouseCursor : ecursor ];
   
}


void ns_impact_set_mouse_cursor(::appkit::ns_impact_t nsimpact, ::enum_cursor ecursor)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
    
      return;
      
   }
   
   ns_acme_impact * pnsacmeimpact = pnsimpact;
   
   if(pnsacmeimpact == nil)
   {
      
      return;
      
   }
      
   [ pnsacmeimpact setMouseCursor : ecursor ];
   
}

void ns_progress_bar_set_range(::appkit::ns_impact_t nsimpact, int iMinimum, int iMaximum)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
    
      return;
      
   }
   
   NSProgressIndicator * pnsprogressindicator = pnsimpact;
   
   if(pnsprogressindicator == nil)
   {
      
      return;
      
   }
   
   [ pnsprogressindicator setIndeterminate: NO ];
   [ pnsprogressindicator setMinValue: iMinimum ];
   [ pnsprogressindicator setMaxValue: iMaximum ];
   
}


void ns_progress_bar_set_position(::appkit::ns_impact_t nsimpact, int iPosition)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
    
      return;
      
   }
   
   NSProgressIndicator * pnsprogressindicator = pnsimpact;
   
   if(pnsprogressindicator == nil)
   {
      
      return;
      
   }
      
   [ pnsprogressindicator setDoubleValue: iPosition ];
   
}


bool ns_check_box_is_checked(::appkit::ns_impact_t nsimpact)
{
   
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
    
      return;
      
   }
   
   NSButton * pnsbutton = pnsimpact;
   
   if(pnsbutton == nil)
   {
      
      return;
      
   }

   if (pnsbutton.state == NSControlStateValueOn)
   {
      
      return true;
      
   }
   else
   {
      
      return false;
      
   }
   
}


void ns_check_box_set_checked(::appkit::ns_impact_t nsimpact, bool checked)
{
   
   auto pnsimpact = ns_get_impact(nsimpact);
   
   if(pnsimpact == nil)
   {
    
      return;
      
   }
   
   NSButton * pnsbutton = pnsimpact;
   
   if(pnsbutton == nil)
   {
      
      return;
      
   }
   
   if(checked)
   {
      
      [ pnsbutton setState : NSControlStateValueOn ];
      
   }
   else
   {
      
      [ pnsbutton setState : NSControlStateValueOff ];
      
   }
   
}



//void ns_window_add_cursor_rectangle(::appkit::ns_window_t nswindow, ::core_graphics::cg_rect cgrect, ::enum_cursor ecursor)
//{
//   
//   auto window = ns_window_from_ns_window_t(nswindow);
//   
//   ns_acme_window * pnsacmewindow = window;
//   
//   if(pnsacmewindow != nil)
//   {
//      
//      NSRect r;
//      r.origin.x = cgrect.origin.x;
//      r.origin.y = cgrect.origin.y;
//      r.size.width = cgrect.size.w;
//      r.size.height = cgrect.size.h;
//      
//      [pnsacmewindow add_cursor_rectangle:r withCursor:ecursor];
//      
//   }
//   
//
//}
