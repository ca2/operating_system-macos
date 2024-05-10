//
//  main_window.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-05-02 22:44.
//
#include "framework.h"
#include "application.h"
#include "axuielement.h"
#include "main_window.h"


#import <Carbon/Carbon.h>


[[nodiscard]] bool cf_is_string(CFTypeRef t);


::string cf_get_string_value(CFTypeRef t)
{
   
   if(cf_is_string(t))
   {
      
      auto len = CFStringGetLength((CFStringRef) t);
      
      ::string str;
      
      auto psz = str.get_buffer(len * 6);
      
      CFStringGetCString((CFStringRef) t, psz, len * 6, kCFStringEncodingUTF8);
      
      str.release_buffer();
      
      return ::transfer(str);
      
   }

   return {};
   
}


namespace acme_macos
{


main_window::main_window()
{
   
   m_axuielement = nullptr;
   
}


main_window::~main_window()
{
   
   if(m_axuielement)
   {
      
      CFRelease(m_axuielement);
      
      m_axuielement = nullptr;
      
   }
   
}


void main_window::from_application(::operating_system::application * papplication)
{
   
   m_axuielement = AXUIElementCreateApplication((pid_t) papplication->m_processidentifier);
   
}


void main_window::post_close()
{
   
   axuielement_post_close(m_axuielement);
   
//   CFArrayRef windowArray = nil;
//
//   AXUIElementCopyAttributeValue(m_axuielement, kAXWindowsAttribute, (CFTypeRef*)&windowArray);
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
//      AXUIElementPerformAction(buttonRef, kAXPressAction);
//
//      CFRelease(buttonRef);
//
//   }
//
//   CFRelease(windowArray);
   
}


::string main_window::get_window_text(const ::iptr_array & idPath)
{
   
   throw ::exception(error_not_supported);
   
   return {};
   
}


   ::string main_window::collection::indexed_get_window_text(const ::iptr_array & idPath)
   {
      
      ::string str;
      
      CFArrayRef windowArray = nil;
      
      AXUIElementCopyAttributeValue(m_axuielement, kAXWindowsAttribute, (CFTypeRef*)&windowArray);
      
      if (windowArray == nil)
      {
         
         return str;
         
      }
      
      CFIndex nItems = CFArrayGetCount(windowArray);
      
      if (nItems < 1)
      {
         
         CFRelease(windowArray);
         
         return str;
         
      }
      
      AXUIElementRef itemRef = nil;
      
      AXUIElementRef itemChildRef = nil;
      
      itemRef = (AXUIElementRef) CFArrayGetValueAtIndex(windowArray, 0);
      
      for(int j = 0; j < idPath.size(); j++)
      {
         
         CFArrayRef children = nil;
         
         AXUIElementCopyAttributeValue(itemRef, kAXChildrenAttribute, (CFTypeRef*)&children);
         
         if(itemChildRef)
         {
            
            CFRelease(itemChildRef);
            
         }
         
         if(children == nil)
         {
            
            CFRelease(windowArray);
            
            return str;
            
         }
         
         CFIndex nChildrenCount = CFArrayGetCount(children);
         
         if (nChildrenCount < 1)
         {
            
            CFRelease(windowArray);
            
            CFRelease(children);
            
            return str;
            
         }
         
         if(itemChildRef != nil)
         {
            
            CFRelease(itemChildRef);
            
         }
         
         itemChildRef = (AXUIElementRef) CFArrayGetValueAtIndex(children, idPath[j]);
         
         if(itemChildRef == nil)
         {
            
            CFRelease(children);
            
            return str;
            
         }
         
         CFRetain(itemChildRef);
         
         CFRelease(children);
         
         itemRef = itemChildRef;
         
      }
         
      CFTypeRef value = nil;
               
      AXUIElementCopyAttributeValue(itemRef, kAXValueAttribute, (CFTypeRef *)&value);
               
      if(value != nil)
      {
         
         str = cf_get_string_value(value);
         
         if(str.has_char())
         {
            
            if(str == "Ready")
            {
               
               ::output_debug_string("Ready found?!?!");
               
            }
            
         }
         
         CFRelease(value);
         
      }
      
      CFRelease(itemRef);
      
      return str;

   }


} // namespace acme_macos


