//
//  axuielement.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/05/23.
//
#include "framework.h"
#include "axuielement.h"

::string cf_get_string_value(CFTypeRef t);

void axuielement_post_close(AXUIElementRef axuielement)
{
   
   auto itemRef = axuielement_menu_bar_item_menu_item_with(axuielement, 0, "Quit ");
   
   AXError axerror = kAXErrorSuccess;
   
   try
   {
      
      axerror = AXUIElementPerformAction(itemRef, kAXPressAction);
      
   }
   catch (...)
   {
   
      
   }
   
   CFRelease(itemRef);
   
   return;

//   AXUIElementRef buttonRef = nil;
//
//   AXUIElementCopyAttributeValue(axuielement, kAXCloseButtonAttribute, (CFTypeRef*)&buttonRef);
//
//   auto axerror = AXUIElementPerformAction(buttonRef, kAXPressAction);
//
//   if(axerror != kAXErrorSuccess)
//   {
//
//      ::output_debug_string("AXUIElementPerformAction kAXPressAction failed");
//
//   }
//
//   CFRelease(buttonRef);
//
//   return;
//
//   CFArrayRef windowArray = nil;
//
//   AXUIElementCopyAttributeValue(axuielement, kAXWindowsAttribute, (CFTypeRef*)&windowArray);
//
//   if (windowArray == nil)
//   {
//
//      return;
//
//   }
//
//   CFIndex nItems = CFArrayGetCount(windowArray);
//
//   if (nItems < 1)
//   {
//
//      CFRelease(windowArray);
//
//      return;
//
//   }
//
//   for (int i = 0; i < nItems; i++)
//   {
//
//      AXUIElementRef itemRef = (AXUIElementRef) CFArrayGetValueAtIndex(windowArray, i);
//
//      AXUIElementRef buttonRef = nil;
//
//      AXUIElementCopyAttributeValue(itemRef, kAXCloseButtonAttribute, (CFTypeRef*)&buttonRef);
//
//      auto axerror = AXUIElementPerformAction(buttonRef, kAXPressAction);
//
//      if(axerror != kAXErrorSuccess)
//      {
//
//         ::output_debug_string("AXUIElementPerformAction kAXPressAction failed");
//
//      }
//
//      CFRelease(buttonRef);
//
//   }
//
//   CFRelease(windowArray);
   
}


AXUIElementRef axuielement_menu_bar(AXUIElementRef axuielement)
{
   
   AXUIElementRef menubar = nil;
   
   AXUIElementCopyAttributeValue(axuielement, kAXMenuBarAttribute, (CFTypeRef*)&menubar);
   
   if (menubar == nil)
   {
   
      return nil;
      
   }
   
   return menubar;
   
}


AXUIElementRef axuielement_menu_bar_item(AXUIElementRef axuielement, ::index i)
{
   
   AXUIElementRef menubar = axuielement_menu_bar(axuielement);
   
   CFArrayRef children = nil;
   
   AXUIElementCopyAttributeValue(menubar, kAXChildrenAttribute, (CFTypeRef*)&children);
   
   if (children == nil)
   {
      
      CFRelease(menubar);
   
      return nil;
      
   }
   
   CFIndex count = CFArrayGetCount(children);
   
   if(i >= count)
   {
      
      CFRelease(children);
      
      CFRelease(menubar);
    
      return nil;
      
   }
   
   AXUIElementRef menubaritem = (AXUIElementRef) CFArrayGetValueAtIndex(children, i);
   
   CFRetain(menubaritem);
   
   CFRelease(children);
   
   CFRelease(menubar);
   
   return menubaritem;
   
}


AXUIElementRef axuielement_menu_bar_item_menu(AXUIElementRef axuielement, ::index i)
{
   
   AXUIElementRef menubaritem = axuielement_menu_bar_item(axuielement, i);
   
   CFArrayRef children = nil;
   
   AXUIElementCopyAttributeValue(menubaritem, kAXChildrenAttribute, (CFTypeRef*)&children);
   
   if (children == nil)
   {
      
      CFRelease(menubaritem);
   
      return nil;
      
   }
   
   CFIndex count = CFArrayGetCount(children);
   
   if(i >= count)
   {
      
      CFRelease(children);
      
      CFRelease(menubaritem);
    
      return nil;
      
   }
   
   AXUIElementRef menu = (AXUIElementRef) CFArrayGetValueAtIndex(children, 0);
   
   CFRetain(menu);
   
   CFRelease(children);
   
   CFRelease(menubaritem);
   
   return menu;
   
}


AXUIElementRef axuielement_menu_bar_item_menu_item_with(AXUIElementRef axuielement, ::index i, const char * psz)
{
   
   AXUIElementRef menu = axuielement_menu_bar_item_menu(axuielement, i);
   
   CFArrayRef children = nil;
   
   AXUIElementCopyAttributeValue(menu, kAXChildrenAttribute, (CFTypeRef*)&children);
   
   if (children == nil)
   {
      
      CFRelease(menu);
   
      return nil;
      
   }
   
   CFIndex count = CFArrayGetCount(children);
   
   if(i >= count)
   {
      
      CFRelease(children);
      
      CFRelease(menu);
    
      return nil;
      
   }
   
   AXUIElementRef itemRef = nil;
   
   for(::index i = 0; i < count; i++)
   {
      
      AXUIElementRef menuitemChild = (AXUIElementRef) CFArrayGetValueAtIndex(children, i);
      
      CFArrayRef * title = nil;
      
      AXUIElementCopyAttributeValue(menuitemChild, kAXTitleAttribute, (CFTypeRef*)&title);
      
      if(title != nil)
      {
         
         ::string strTitle;
         
         strTitle = cf_get_string_value(title);
         
         if(strTitle.case_insensitive_contains(psz))
         {
            
            itemRef = menuitemChild;
            
            CFRetain(itemRef);
            
         }
         
         CFRelease(title);
         
      }
      
      if(itemRef != nil)
      {
         
         break;
         
      }
      
   }
   
   CFRelease(children);
   
   CFRelease(menu);
   
   return itemRef;
   
}


AXUIElementRef axuielement_first_window(AXUIElementRef axuielement)
{
   
   CFArrayRef windowArray = nil;
   AXUIElementCopyAttributeValue(axuielement, kAXWindowsAttribute, (CFTypeRef*)&windowArray);
   if (windowArray == nil) {
      CFRetain(axuielement);
      return axuielement;
   }
   
   CFIndex nItems = CFArrayGetCount(windowArray);
   if (nItems < 1) {
      CFRelease(windowArray);
      CFRetain(axuielement);
      return axuielement;
   }
   
   //for (int i = 0; i < nItems; i++)
   //{
   AXUIElementRef itemRef = (AXUIElementRef) CFArrayGetValueAtIndex(windowArray, 0);
   
   CFRetain(itemRef);
      
   CFRelease(windowArray);

   return itemRef;
   
}


::count axuielement_application_window_count(AXUIElementRef axuielement)
{
   
   CFArrayRef windowArray = nil;
   AXUIElementCopyAttributeValue(axuielement, kAXWindowsAttribute, (CFTypeRef*)&windowArray);
   if (windowArray == nil) {
      return 0;
   }
   
   CFIndex nItems = CFArrayGetCount(windowArray);
   if (nItems < 1) {
      return 0;
   }
   
   return nItems;
   
   //for (int i = 0; i < nItems; i++)
   //{
//   AXUIElementRef itemRef = (AXUIElementRef) CFArrayGetValueAtIndex(windowArray, 0);
//
//   CFRetain(itemRef);
//
//   CFRelease(windowArray);
//
//   return itemRef;
   
}


::string axuielement_first_window_title(AXUIElementRef axuielement)
{
   
   ::string strWindowTitle;
   
   auto elementFirstWindow = axuielement_first_window(axuielement);
   
   CFStringRef title = nil;
   AXUIElementCopyAttributeValue(elementFirstWindow, kAXTitleAttribute, (CFTypeRef *)&title);
   if (title == nil) {
      CFRelease(elementFirstWindow);
      return strWindowTitle;
   }
   strWindowTitle = CFStringGetCStringPtr(title, kCFStringEncodingUTF8);
   CFRelease(title);
   CFRelease(elementFirstWindow);
   
   return strWindowTitle;
   
}

::string cf_get_string_value(CFTypeRef t);

::string axuielement_application_name(AXUIElementRef axuielement)
{
   
   CFStringRef title = nil;
   
   AXUIElementCopyAttributeValue(axuielement, kAXTitleAttribute, (CFTypeRef *)&title);
   
   if (title == nil)
   {
      return {};
   }

   ::string str = cf_get_string_value(title);

   CFRelease(title);
   
   return str;
   
}
