//
//  macos_window.cpp
//  aura

//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
//
//

#include "framework.h"
#include "window_impl.h"
//#include "oswindow_data.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/_collection.h"
#include "acme/parallelization/message_queue.h"
#include <CoreGraphics/CoreGraphics.h>
//#include "aura/_defer.h"


INT_RECTANGLE get_main_screen_rectangle();


//oswindow_dataptra * g_poswindowdataptra = nullptr;
//
//::mutex * g_pmutexOsWindowData = nullptr;
//
//void ns_main_post(dispatch_block_t block);
//
//int oswindow_find(NSWindow * window)
//{
//
//   _synchronous_lock synchronouslock(g_pmutexOsWindowData);
//
//   for(int i = 0; i < g_poswindowdataptra->get_count(); i++)
//   {
//      if(g_poswindowdataptra->element_at(i)->m_nswindow == window)
//      {
//         return i;
//      }
//   }
//
//   return -1;
//
//}
//
//oswindow_data * oswindow_get(nswindow window)
//{
//
//   _synchronous_lock synchronouslock(g_pmutexOsWindowData);
//
//   iptr iFind = oswindow_find(window);
//
//   if(iFind >= 0)
//   {
//
//      return g_poswindowdataptra->element_at(iFind);
//
//   }
//
//   ::oswindow_data * pdata = new ::oswindow_data;
//
//   pdata->m_nswindow    = window;
//
//   g_poswindowdataptra->add(pdata);
//
//   return pdata;
//
//}
//
//
//oswindow_data::oswindow_data()
//{
//
//   m_nswindow  = nullptr;
//   m_pimpl       = nullptr;
//   m_plongmap  = new iptr_to_iptr;
//   m_bNsWindowRect = false;
//}
//
//
//oswindow_data::oswindow_data(nswindow window)
//{
//
//   m_nswindow  = window;
//   m_pimpl       = nullptr;
//   m_plongmap  = new iptr_to_iptr;
//   m_bNsWindowRect = false;
//}
//
//
//oswindow_data::oswindow_data(const oswindow_data & oswindow)
//{
//
//   m_nswindow  = oswindow.m_nswindow;
//   m_pimpl       = oswindow.m_pimpl;
//   m_plongmap  = oswindow.m_plongmap;
//   m_bNsWindowRect = false;
//}
//
//
//oswindow_data::~oswindow_data()
//{
//
//   ::acme::del(m_plongmap);
//
//}
//
//
//oswindow_data & oswindow_data::operator = (const oswindow_data & oswindow)
//{
//
//   if(&oswindow != this)
//   {
//
//      m_nswindow  = oswindow.m_nswindow;
//      m_pimpl       = oswindow.m_pimpl;
//      m_plongmap  = oswindow.m_plongmap;
//
//   }
//
//   return *this;
//
//}
//
//
//bool oswindow_erase(nswindow window)
//{
//
//   _synchronous_lock synchronouslock(g_pmutexOsWindowData);
//
//   iptr iFind = oswindow_find(window);
//
//   if(iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   g_poswindowdataptra->erase_at(iFind);
//
//   return true;
//
//}
//
//
//void oswindow_data::set_user_interaction_impl(::user::interaction_impl * pimpl)
//{
//
//   if(is_null())
//      throw ::exception(::exception::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));;
//
//   m_pimpl = pimpl;
//
//}
//
//
//::user::interaction * oswindow_data::get_user_interaction_base()
//{
//
//   if(is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   if(m_pimpl == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return m_pimpl->m_puserinteraction;
//
//}
//
//
//::user::interaction * oswindow_data::get_user_interaction_base() const
//{
//
//   if(is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   if(m_pimpl == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return m_pimpl->m_puserinteraction;
//
//}
//
//
//::user::interaction * oswindow_data::get_user_interaction()
//{
//
//   if(is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   if(m_pimpl == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return m_pimpl->m_puserinteraction;
//
//}
//
//
//::user::interaction * oswindow_data::get_user_interaction() const
//{
//
//   if(is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   if(m_pimpl == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return m_pimpl->m_puserinteraction;
//
//}
//
//
//oswindow oswindow_data::get_parent()
//{
//
//   if(is_null())
//      return nullptr;
//
//   return m_pimpl->m_puserinteraction->GetParentHandle();
//
//}
//
//
//oswindow oswindow_data::set_parent(oswindow oswindow)
//{
//
//   if(is_null())
//      return nullptr;
//
//   ::oswindow oswindowOldParent = get_parent();
//
//   if(oswindow == nullptr
//         || oswindow->m_pimpl == nullptr)
//   {
//
//      m_pimpl->SetParent(nullptr);
//
//   }
//   else
//   {
//
//      m_pimpl->SetParent(oswindow->m_pimpl->m_puserinteraction);
//
//   }
//
//   return oswindowOldParent;
//
//}
//
//
//
//bool oswindow_data::is_child(::oswindow oswindow)
//{
//
//   if (oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
//   {
//
//      return false;
//
//   }
//
//   return m_pimpl->m_puserinteraction->is_child(oswindow->m_pimpl->m_puserinteraction);
//
//}
//
//
//iptr oswindow_data::get_window_long_ptr(iptr iIndex)
//{
//
//   if(is_null())
//      return 0;
//
//   if(m_plongmap == nullptr)
//      return 0;
//
//   return m_plongmap->operator[]((int) iIndex);
//
//}
//
//
//iptr oswindow_data::set_window_long_ptr(iptr iIndex, iptr iNewLong)
//{
//
//   if(is_null())
//      return 0;
//
//   if(m_plongmap == nullptr)
//      return 0;
//
//   iptr iLong = m_plongmap->operator[]((int) iIndex);
//
//   m_plongmap->operator[]((int) iIndex) = (int) iNewLong;
//
//   return iLong;
//
//}
//
//
//static oswindow g_oswindowCapture;
//
//
//oswindow get_capture()
//{
//   return g_oswindowCapture;
//}
//
//oswindow set_capture(oswindow window)
//{
//
//   oswindow windowOld(g_oswindowCapture);
//
//   if(window->window() == nullptr)
//      return nullptr;
//
//   g_oswindowCapture = window;
//
//   return windowOld;
//
//}
//
//
//int_bool release_capture()
//{
//
//   int_bool bRet = true;
//
//   if(bRet)
//   {
//
//      g_oswindowCapture = nullptr;
//
//   }
//
//   return bRet;
//
//}
//
//
//oswindow get_focus();
//
//static oswindow g_oswindowFocus = nullptr;
//
//oswindow set_focus(oswindow window)
//{
//
//   if(!is_window(window))
//      return nullptr;
//
//   oswindow windowOld = ::get_focus();
//
//   g_oswindowFocus = window;
//
//   return windowOld;
//
//}
//
//oswindow get_focus()
//{
//
//   return g_oswindowFocus;
//
//}
//
//
//::user::interaction_impl * window_from_handle(oswindow oswindow)
//{
//
//   if(oswindow == nullptr)
//      return nullptr;
//
//   return oswindow->m_pimpl;
//
//}
//
//static oswindow g_oswindowActive = nullptr;
//
//
//
//oswindow get_active_window()
//{
//
//   return g_oswindowActive;
//
//}
//
//int_bool session_accepts_first_responder()
//{
//
//   return psession->m_bAcceptsFirstResponder ? 1 : 0;
//
//}
//
//void deactivate_window(oswindow window)
//{
//
//   _synchronous_lock synchronouslock(g_pmutexOsWindowData);
//
//   if(g_oswindowActive != window)
//   {
//
//      return false;
//
//   }
//
//   g_oswindowActive = nullptr;
//
//   return true;
//
//}
//
//
//
//oswindow set_active_window(oswindow window)
//{
//
//   _synchronous_lock synchronouslock(g_pmutexOsWindowData);
//
//   oswindow windowOld(g_oswindowActive);
//
//   if(window == nullptr)
//   {
//
//      g_oswindowActive = nullptr;
//
//      return windowOld;
//
//   }
//
//   g_oswindowActive = window;
//
//   return windowOld;
//
//}
//
//

//
//oswindow get_window(oswindow window, int iParentHood)
//{
//
//   return nullptr;
//
//}



//
//int_bool destroy_window(oswindow w)
//{
//
//   if(is_null(w))
//   {
//
//      return false;
//
//   }
//
//   if(is_null(w->m_pimpl))
//   {
//
//      return false;
//
//   }
//
//   w->m_pimpl->set_destroying();
//
//   if(!w->m_pimpl->m_bDestroyImplOnly)
//   {
//
//      w->m_pimpl->m_puserinteraction->post_message(e_message_destroy);
//
//      w->m_pimpl->m_puserinteraction->post_message(e_message_ncdestroy);
//
//   }
//   else
//   {
//
//      ns_main_post(^()
//      {
//
//         w->m_pimpl->call_message_handler(e_message_destroy, 0, 0);
//
//         w->m_pimpl->call_message_handler(e_message_ncdestroy, 0, 0);
//
//      });
//
//   }
//
//   return 1;
//
//}
//
//
//bool oswindow_data::is_null() const
//{
//
//   return ::is_null(this);
//
//}
//
//
//
////
////  c_os_cross_win_user.cpp
////  c
////
////  Created by Snow Leopard User on 06/11/2011.
////  Copyright 2011 __MyCompanyName__. All rights reserved.
////
//#include "framework.h"
//

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

//
//int_bool set_need_redraw(oswindow hWnd, const INT_RECTANGLE * pcrect, HRGN hrgnUpdate, unsigned int flags)
//{
//
//   return true;
//
//}
//

const char * mm_keyboard_input_source();


string keyboard_input_source()
{

   const char * psz = mm_keyboard_input_source();

   string str =psz;

   free((void *) psz);

   return str;

}


CLASS_DECL_AURA ::acme::windowing::window * oswindow_get(oswindow oswindow)
{

   if(oswindow == nullptr)
   {

      return nullptr;

   }

   return oswindow;

}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}
//int_bool axis_TranslateMessage(const MESSAGE * pmessage);

//LRESULT axis_DispatchMessage(const MESSAGE * pmessage);

void mm_init_workspace_rect();

//int_bool os_init_windowing()
//{
//
////   set_TranslateMessage(&axis_TranslateMessage);
//
////   set_DispatchMessage(&axis_DispatchMessage);
//
//   g_pmutexOsWindowData = new ::mutex();
//
//   g_poswindowdataptra = new oswindow_dataptra;
//
//   mm_init_workspace_rect();
//
//   return true;
//
//}
//
//
//void os_term_windowing()
//{
//
//   ::acme::del(g_poswindowdataptra);
//
//   ::acme::del(g_pmutexOsWindowData);
//
//}


// front first
int_rectangle_array cg_get_window_rect_list_above(CGWindowID windowid)
{
   
   int_rectangle_array recta;
   
   CFArrayRef windowa = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenAboveWindow, windowid);

   ::int_rectangle rMainScreen = get_main_screen_rectangle();

   long c = CFArrayGetCount(windowa);

   for(int i = 0; i < c; i++)
   {

      CFDictionaryRef dict = (CFDictionaryRef)CFArrayGetValueAtIndex(windowa, i);
      
      CFNumberRef cfnumberAlpha = (CFNumberRef) CFDictionaryGetValue(dict, kCGWindowAlpha);
      
      if(cfnumberAlpha)
      {
         
         float fAlpha = 0.f;
         
         CFNumberGetValue(cfnumberAlpha, kCFNumberFloatType, &fAlpha);
         
         CFRelease(cfnumberAlpha);
         
         if(fAlpha <= 0.f)
         {
            
            continue;
            
         }
         
      }

      CFStringRef cfstrName = (CFStringRef) CFDictionaryGetValue(dict, kCGWindowName);

      if(cfstrName)
      {
         
         CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
         string strName = CFStringGetCStringPtr(cfstrName, encodingMethod);

         CFRelease(cfstrName);
         
         if(strName.case_insensitive_equals("cursor"))
         {
            
            continue;
            
         }
         
      }
      
      CFDictionaryRef dictRect = (CFDictionaryRef) CFDictionaryGetValue(dict, kCGWindowBounds);
      
      if(dictRect)
      {

         CGRect rect = {};
      
         CGRectMakeWithDictionaryRepresentation(dictRect, &rect);

         if(rect.size.width > 0 && rect.size.height > 0)
         {

            ::int_rectangle rectCopy;

            rectCopy.left() = rect.origin.x;
            rectCopy.top() = rMainScreen.height() - (rect.origin.y + rect.size.height);
            rectCopy.bottom() = rectCopy.top() + rect.size.height;
            rectCopy.right() = rect.origin.x + rect.size.width;

            recta.add(rectCopy);

         }
         
         CFRelease(dictRect);
         
      }

   }

   CFRelease(windowa);

   return recta;

}


string MYCFStringCopyUTF8String(CFStringRef aString)
{
   
   if (aString == NULL)
   {
   
      return "";
      
   }
   
   CFIndex length = CFStringGetLength(aString);
   
   string str;
   
   CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
   
   char *buffer = str.get_buffer(maxSize);
   
   if (CFStringGetCString(aString, buffer, maxSize, kCFStringEncodingUTF8))
   {
      
      str.release_buffer();
      
      return str;
      
   }
   
   return "";
   
}


//#define FUNCTION_TRACE(...) strFormat.Format(__VA_ARGS__); str+=strFormat;
#undef FUNCTION_TRACE


int_rectangle_array cg_get_window_rect_list_intersect_above(CGWindowID windowid)
{
   
   bool bFound = false;

#ifdef FUNCTION_TRACE
   
   string str;
   
   string strFormat;

   bool bFullTrace = false;

#endif
   
   int_rectangle_array recta;
   
   CFArrayRef windowa = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);

   CGRect rect1 = {};
   
   //int_rectangle rMainScreen;
   
   //get_main_screen_rectangle(rMainScreen);
   
   // "CG" Window Rects are like Windows (R) GDI Coordinates (Y down)
   
   long c = CFArrayGetCount(windowa);
   
   //CGWindowID windowidTopic = -1;
   
   string strName;
   
   string strAppName;
   
   if(c <= 1)
   {
      
      goto end1;
      
   }
   
#ifdef FUNCTION_TRACE

   FUNCTION_TRACE("-\n");
   FUNCTION_TRACE("---\n");
   FUNCTION_TRACE("-----\n");
   FUNCTION_TRACE("Windows Above------------------------------------------\n");
   
#endif
   
   for(::collection::index i = c - 1; i >= 0; i--)
   {
      
#ifdef FUNCTION_TRACE
      
      if(bFullTrace && (i + 1) % 10 != 0 && (i + 1) != c)
      {
         
         FUNCTION_TRACE("\n     ");
         
      }
      else
      {
         
         FUNCTION_TRACE("\n%3d. ", i + 1);
         
      }
      
      bFullTrace = false;
         
#endif

      CFDictionaryRef dict = (CFDictionaryRef)CFArrayGetValueAtIndex(windowa, i);
      
      if (!dict) continue;
      
      CFNumberRef window_id = (CFNumberRef) CFDictionaryGetValue(dict, kCGWindowNumber);
      
      if (!window_id) continue;
      
      int iWindowId = -1;
         
      CFNumberGetValue(window_id, kCFNumberSInt32Type, &iWindowId);
         
      CFRelease(window_id);
      
      if(!bFound)
      {
      
         if(iWindowId == windowid)
         {
         
            bFound = true;
         
         }
         else
         {
            
            continue;
            
         }
         
      }
         
      CFNumberRef alpha = (CFNumberRef) CFDictionaryGetValue(dict, kCGWindowAlpha);
   
      if(alpha)
      {
      
         float fAlpha = 0.f;
         
         CFNumberGetValue(alpha, kCFNumberFloatType, &fAlpha);
         
         if(fAlpha <= 0.f) continue;
         
#ifdef FUNCTION_TRACE
         
         int iAlpha = (int) (fAlpha * 255.f);
         
         if(iAlpha == 255)
         {
         
            FUNCTION_TRACE("            ");
            
         }
         else
         {
            
            FUNCTION_TRACE("Alpha: %3d; ", iAlpha);
            
         }
            
#endif
         
      }

      CFStringRef name = (CFStringRef) CFDictionaryGetValue(dict, kCGWindowName);
      
      strName.empty();

      if(name)
      {

         strName =  MYCFStringCopyUTF8String(name);

      }
      
      CFStringRef appname = (CFStringRef) CFDictionaryGetValue(dict, kCGWindowOwnerName);
      
      strAppName.empty();
      
      if(appname)
      {
         
         strAppName =  MYCFStringCopyUTF8String(appname);
         
      }
      
      if(strAppName.case_insensitive_equals("window server"))
      {

         if(strName.case_insensitive_equals("cursor"))
         {
            
            continue;
            
         }
         
      }
      
      if(strAppName.case_insensitive_equals("Dock"))
      {
         
         if(strName.is_empty())
         {
            
            continue;
            
         }
         
      }

      CFDictionaryRef dictRect = (CFDictionaryRef) CFDictionaryGetValue(dict, kCGWindowBounds);
   
      if(dictRect)
      {
         
         CGRect rect= {};
   
         CGRectMakeWithDictionaryRepresentation(dictRect, &rect);
      
#ifdef FUNCTION_TRACE
         
         FUNCTION_TRACE("  %5.0f,%5.0f - %5.0f,%5.0f  ",
              rect.origin.x,
              rect.origin.y,
              rect.size.width,
              rect.size.height);
         
#endif

         if(rect.size.width > 0 && rect.size.height > 0)
         {
            
            if(iWindowId == windowid)
            {
               
               rect1 = rect;
               
            }
            else if(bFound)
            {
            
               if(CGRectIntersectsRect(rect1, rect))
               {

                  ::int_rectangle rectCopy;

                  rectCopy.left() = rect.origin.x;
                  rectCopy.right() = rect.origin.x + rect.size.width;
                  rectCopy.top() = rect.origin.y;
                  rectCopy.bottom() = rect.origin.y + rect.size.height;

                  recta.add(rectCopy);

               }
               
            }
            
         }
         
         CFRelease(dictRect);
         
      }
      
#ifdef FUNCTION_TRACE
      
      FUNCTION_TRACE("Owner: \"%s\"; ", strAppName.c_str());
      FUNCTION_TRACE("Name: \"%s\"; ", strName.c_str());
      
      bFullTrace = true;
      
#endif
   
   }
   
end1:
   
#ifdef FUNCTION_TRACE
   
   output_debug_string(str);
   
#endif
   
   return recta;

}


#ifdef FUNCTION_TRACE
#undef FUNCTION_TRACE
#endif


//#define FUNCTION_TRACE(...) strFormat.Format(__VA_ARGS__); str+=strFormat;
#undef FUNCTION_TRACE


void cg_get_window_rect_list(int_rectangle_array & recta, array < CGWindowID > & windowida)
{

   //bool bFound = false;

#ifdef FUNCTION_TRACE
   
   string str;
   
   string strFormat;
   
   bool bFullTrace = false;
   
#endif

   CFArrayRef windowa = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
   
   long c = CFArrayGetCount(windowa);
   
   //CGRect rect1={};
   
   //int_rectangle rMainScreen;

   string strName;
   
   string strAppName;
   
   //get_main_screen_rectangle(rMainScreen);
   
   // "CG" Window Rects are like Windows (R) GDI Coordinates (Y down)
   
#ifdef FUNCTION_TRACE
   
   FUNCTION_TRACE("-\n");
   FUNCTION_TRACE("---\n");
   FUNCTION_TRACE("-----\n");
   FUNCTION_TRACE("Windows Rect List------------------------------------------\n");
   
#endif

   for(int i = 0; i < c; i++)
   {
      
#ifdef FUNCTION_TRACE
      
      if(bFullTrace && (i + 1) % 10 != 0 && (i + 1) != c)
      {
         
         FUNCTION_TRACE("\n     ");
         
      }
      else
      {
         
         FUNCTION_TRACE("\n%3d. ", i + 1);
         
      }
      
      bFullTrace = false;
      
#endif
      
      CFDictionaryRef dict = (CFDictionaryRef)CFArrayGetValueAtIndex(windowa, i);
      
      if (!dict) continue;
      
      CFNumberRef window_id = (CFNumberRef) CFDictionaryGetValue(dict, kCGWindowNumber);
      
      if (!window_id) continue;
      
      int iWindowId = -1;
      
      CFNumberGetValue(window_id, kCFNumberSInt32Type, &iWindowId);
      
      CFRelease(window_id);
      
      CFNumberRef alpha = (CFNumberRef) CFDictionaryGetValue(dict, kCGWindowAlpha);
      
      if(alpha)
      {
         
         float fAlpha = 0.f;
         
         CFNumberGetValue(alpha, kCFNumberFloatType, &fAlpha);
         
         if(fAlpha <= 0.f) continue;
         
#ifdef FUNCTION_TRACE
         
         int iAlpha = (int) (fAlpha * 255.f);
         
         if(iAlpha == 255)
         {
            
            FUNCTION_TRACE("            ");
            
         }
         else
         {
            
            FUNCTION_TRACE("Alpha: %3d; ", iAlpha);
            
         }
         
#endif
         
      }
      
      CFStringRef name = (CFStringRef) CFDictionaryGetValue(dict, kCGWindowName);
      
      strName.empty();
      
      if(name)
      {
         
         strName =  MYCFStringCopyUTF8String(name);
         
      }
      
      CFStringRef appname = (CFStringRef) CFDictionaryGetValue(dict, kCGWindowOwnerName);
      
      strAppName.empty();
      
      if(appname)
      {
         
         strAppName =  MYCFStringCopyUTF8String(appname);
         
      }
      
      if(strAppName.case_insensitive_equals("window server"))
      {
         
         if(strName.case_insensitive_equals("cursor"))
         {
            
            continue;
            
         }
         
      }
      
      if(strName.case_insensitive_equals("dock"))
      {
         
         continue;
         
      }

      CFDictionaryRef dictRect = (CFDictionaryRef) CFDictionaryGetValue(dict, kCGWindowBounds);
      
      if(dictRect)
      {
         
         CGRect rect= {};
         
         CGRectMakeWithDictionaryRepresentation(dictRect, &rect);
         
         ::int_rectangle rectCopy;
         
         //rectCopy.left = rectangle.origin.x;
         //rectCopy.top = rMainScreen.height() - (rectangle.origin.y + rectangle.size.height);
         //rectCopy.bottom = rectCopy.top + rectangle.size.height;
         //rectCopy.right = rectangle.origin.x + rectangle.size.width;

         rectCopy.left() = rect.origin.x;
         rectCopy.right() = rect.origin.x + rect.size.width;
         rectCopy.top() = rect.origin.y;
         rectCopy.bottom() = rect.origin.y + rect.size.height;

         recta.add(rectCopy);
         windowida.add(iWindowId);
         
         CFRelease(dictRect);
         
      }
      
#ifdef FUNCTION_TRACE
      
      FUNCTION_TRACE("Owner: \"%s\"; ", strAppName.c_str());
      FUNCTION_TRACE("Name: \"%s\"; ", strName.c_str());
      
      bFullTrace = true;
      
#endif
      
   }
   
end1:;
   
#ifdef FUNCTION_TRACE
   
   output_debug_string(str);
   
#endif
   
   //return recta;
   
}

#ifdef FUNCTION_TRACE
#undef FUNCTION_TRACE
#endif



CGWindowID get_os_window_window_number(oswindow oswindow);
//{
//   
//   auto pwindow = (::windowing_macos::window *) oswindow->m_pWindow2;
//   
//   auto pnswindow = pwindow->m_pnswindow;
//   
//   auto windowId = ns_get_window_id(pnswindow);
//   
//   return windowId;
//   
//}

int_bool is_window_occluded(oswindow oswindow)
{


   CGWindowID windowid = get_os_window_window_number(oswindow);

   if(windowid == 0)
   {

      return false;

   }

   int_rectangle_array recta = cg_get_window_rect_list_intersect_above(windowid);


   if(recta.is_empty())
   {

      return false;

   }
   
   return true;

//   ::int_rectangle rectangle;
//
//   rectangle = oswindow->m_pimpl->m_puserinteraction->parent_client_rect();
//
//   ::int_rectangle rectTest;
//
//   for(int i = 0; i < recta.get_size(); i++)
//   {
//      
//      auto rectAbove = recta[i];
//
//      if(rectTest.intersect(recta[i], rectangle))
//      {
//
//         return true;
//
//      }
//
//   }
//
//
//   return false;

}

void cg_get_window_rect_list(int_rectangle_array & recta, array < CGWindowID > & windowida);

int_bool point_is_window_origin(::int_point pointHitTest, oswindow oswindowExclude, int iMargin)
{
   
   CGWindowID windowidExclude = get_os_window_window_number(oswindowExclude);
   
   int_rectangle_array recta;
   
   array < CGWindowID > windowida;
   
   cg_get_window_rect_list(recta, windowida);
   
   ::int_rectangle rectTest;

   for(::collection::index i = 0; i < recta.get_size(); i++)
   {
   
      int wid = windowida[i];
      
      if(windowidExclude != 0 && wid == windowidExclude)
      {
         
         continue;
         
      }

      auto rectangle = recta[i];

      if(rectangle.contains(pointHitTest))
      {
         
         return true;
         
      }
      
   }
   
   return false;

}


void defer_term_ui()
{
   
   
   
}
