// Copyright (C) 2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
//#include "util/CommonHeader.h"
#include "Window.h"
#include "drawing/Cursor.h"
#include "drawing/Icon.h"
#include "Menu.h"
#include "acme/nano/graphics/dib.h"
#include "acme/user/user/mouse.h"
#include "subsystem/node/SystemInformation.h"
#include "subsystem/platform/subsystem.h"
#include "innate_subsystem/drawing/Brush.h"
#include "drawing/Bitmap.h"
#include "drawing/Brush.h"
#include "drawing/DeviceContext.h"
#include "drawing/Graphics.h"
#include "acme/windowing/windowing.h"
#include "operating_system-apple/core_graphics/cg_color.h"
#include "operating_system-apple/core_graphics/cg_context.h"
#include "operating_system-apple/core_graphics/cg_image.h"
#include "operating_system-apple/nano_graphics_quartz2d/_.h"
#include "operating_system-apple/nano_graphics_quartz2d/image.h"
//#include "operating_system-apple/core_graphics/cg_dib.h"
#include "operating_system-macos/appkit/windowing.h"
#include "operating_system-macos/acme_windowing_appkit/windowing.h"
#include "operating_system-macos/acme_windowing_appkit/_interoperability.h"
//#include <commctrl.h>
// namespace macos
// {
namespace innate_subsystem_macos
{
   Window::Window()
      : // m_macoswindow.as_HWND()(0),
   //   m_hicon(0),
      m_bWndCreated(false),
   m_sizeIsChanged(false)
   {
      m_ecursor = e_cursor_unmodified;
   }

   Window::~Window()
   {
      // if (m_bWndCreated && m_macoswindow.as_HWND()) {
      //    DestroyWindow(m_macoswindow.as_HWND());
      // }
      // if (m_hicon) {
      //    DeleteObject(m_hicon);
      // }
   }
//
//
//   operating_ambient_window_t Window::operating_ambient_window() const
//{
//   
//   return {(::uptr)m_macoswindow.as_uptr()};
//
//   }
//
//
//   void Window::set_operating_ambient_window(operating_ambient_window_t operatingambientwindow)
//   {
//
//      m_macoswindow.m_eoperatingambient = ::windowing::e_operating_ambient_macos;
//      m_macoswindow.m_opaque.m_ulla[0] = operatingambientwindow.m_u;
//
//   }


   void *Window::_WNDPROC_default() const
   {
      
      throw ::not_implemented();
      
      return nullptr;

      //return m_wndprocDefault;

   }


   operating_system::window Window::operating_system_window() const
   {

      return m_macoswindow.as_operating_system_window();

   }


   void Window::set_operating_system_window(const operating_system::window &operatingsystemwindow)
   {

      m_macoswindow = operatingsystemwindow;

   }


   innate_subsystem::WindowInterface *Window::get_window_implementation()
   {

      return this;

   }

   void Window::setClipboardViewerInterest()
   {

      m_bHasClipboardViewerInterest = true;

   }


   void Window::setOnDrawInterest() { m_bHasOnDrawInterest = true; }


   bool Window::onDrawClipboard()
   {


      return m_pwindowCallback->onDrawClipboard();

   }

   //void Window::setClass(const ::scoped_string  & scopedstrWindowClassName)
   void Window::setClass(::innate_subsystem::enum_window_class ewindowclass)
   {

      if (ewindowclass == innate_subsystem::e_window_class_viewer)
      {
         //_setWindowClassViewer();
      }
      else
      {
         //_setWindowClassGeneric();

      }
      //;
      //m_strClassName = scopedstrWindowClassName;
   }
//
//   void Window::_setWindowClassViewer()
//   {
//
//      static bool s_bRegistered = false;
//      static WNDCLASSW s_wndclass{};
//
//      m_strClassName = "innate_subsystem_viewer_window";
//
//      if (!s_bRegistered)
//      {
//
//         s_bRegistered = true;
//
//         ::wstring wstrClassName(m_strClassName);
//         
//         s_wndclass.lpfnWndProc = ::macos::window::s_window_procedure;
//         s_wndclass.hInstance = (HINSTANCE) ::macos::hinstance_from_function(::macos::window::s_window_procedure);
//         s_wndclass.lpszClassName = wstrClassName.c_str();
//         s_wndclass.style = CS_HREDRAW | CS_VREDRAW;
//         s_wndclass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
//         
//         RegisterClass(&s_wndclass);
//          
//      }
//
//   }
//
//   void Window::_setWindowClassGeneric()
//   {
//
//      static bool s_bRegistered = false;
//      static WNDCLASSW s_wndclass{};
//
//      m_strClassName = "innate_subsystem_window";
//
//      if (!s_bRegistered)
//      {
//
//         s_bRegistered = true;
//
//         ::wstring wstrClassName(m_strClassName);
//
//         s_wndclass.lpfnWndProc = ::macos::window::s_window_procedure;
//         s_wndclass.hInstance = (HINSTANCE)::macos::hinstance_from_function(::macos::window::s_window_procedure);
//         s_wndclass.lpszClassName = wstrClassName.c_str();
//         s_wndclass.style = CS_HREDRAW | CS_VREDRAW;
//         s_wndclass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
//
//         RegisterClass(&s_wndclass);
//      }
//   }


   bool Window::createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent,
                                 int xPos, int yPos, int width, int height)
   {
      if (m_macoswindow.is_set()) {
         return false;
      }
      ::system()->acme_windowing()->send([&]()
         {
      m_strWindowName = scopedstrWindowName;
      //auto hwndParent = ::as_u64(operatingsystemwindowParent);
         
         m_pappkitacmewindowingwindow = this;
         
         m_pacmeuserinteraction = m_pwindowCallback;
         
         m_pacmewindowbridge = this;
         
         auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;
         
         pacmeuserinteraction->m_pacmewindowingwindow = this;
         
         auto pacmewindowingwindow = pacmeuserinteraction->m_pacmewindowingwindow.m_p;
         
         auto operatingsystemwindow = ::cross_windows::create_window(xPos, yPos, width, height, operatingsystemwindowParent, this, this);
         
         set_operating_system_window(operatingsystemwindow);
//      HWND hwnd = CreateWindow(::wstring(m_strClassName),
//                            ::wstring(m_strWindowName),
//                            style,
//                            xPos, yPos,
//                            width, height,
//                            hwndParent, 0, (HINSTANCE) ::macos::hinstance_from_function(::macos::window::s_window_procedure),
//                            reinterpret_cast<LPVOID>((::macos::window *)this));
//      m_bWndCreated = (hwnd == 0 ? false : true);
//      if (m_bWndCreated) {
//
//         //m_wndprocDefault = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
//         SetWindowLongPtr(hwnd,
//                          GWLP_USERDATA,
//                          reinterpret_cast<LONG_PTR>(this));
//      }
         });
      return true;
   }

   void Window::loadIcon(unsigned int id)
   {
//      if (m_hicon) {
//         DeleteObject(m_hicon);
//         m_hicon = 0;
//      }
//      if (IS_INTRESOURCE(id)) {
//         m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
//         SetClassLongPtr(m_macoswindow.as_HWND(), GCLP_HICON, reinterpret_cast<LONG_PTR>(m_hicon));
//      } else {
//         SetClassLongPtr(m_macoswindow.as_HWND(), GCLP_HICON, static_cast<LONG_PTR>(id));
//      }
   }

   void Window::enableWindow(bool bEnable)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      EnableWindow(m_macoswindow.as_HWND(), bEnable);
   }

   void Window::setEnabled(bool enabled)
   {
//      if (enabled) {
//         SendMessage(m_macoswindow.as_HWND(), WM_ENABLE, TRUE, NULL);
//         removeStyle(WS_DISABLED);
//      } else {
//         if (isStyleEnabled(WS_DISABLED)) {
//            return ;
//         } // if already disabled
//         SendMessage(m_macoswindow.as_HWND(), WM_ENABLE, FALSE, NULL);
//         addStyle(WS_DISABLED);
//      }
//      invalidate();
   }


   bool Window::destroyWindow()
   {
      //if (m_macoswindow.as_CGWindowID()) {
      
      auto operatingsystemwindow = this->operating_system_window();
      
      ::cross_windows::destroy_window(operatingsystemwindow);
//         DestroyWindow(m_macoswindow.as_CGWindowID());
//         return true;
//      }
      return false;
   }


   void Window::setCursor(enum_cursor ecursor)
   {

      if (is_different(ecursor, m_ecursor))
      {

         m_ecursor = ecursor;

      }

   }


   enum_cursor Window::getCursor()
   {

      return m_ecursor;

   }


   void Window::setDoubleBuffering(bool bDoubleBuffering)
   {

      m_bDoubleBuffering = bDoubleBuffering;

   }


   bool Window::isDoubleBuffering()
   {

      return m_bDoubleBuffering;

   }

   void Window::show()
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      ShowWindow(m_macoswindow.as_HWND(), SW_SHOW);
      
      auto operatingsystemwindow = operating_system_window();
      
      ::cross_windows::show_window_show(operatingsystemwindow);
      
   }

   void Window::hide()
   {
//      if (m_macoswindow.as_HWND() != 0)
//      {
//         ShowWindow(m_macoswindow.as_HWND(), SW_HIDE);
//      }
      
      auto operatingsystemwindow = operating_system_window();
      
      if(operatingsystemwindow.is_set())
      {
         
         ::cross_windows::show_window_hide(operatingsystemwindow);
         
      }

      
   }

   bool Window::setSize(const ::i32_size & size)
   {
      ASSERT(isWindow());
      auto operatingsystemwindow = operating_system_window();
      return !!::cross_windows::set_window_pos(operatingsystemwindow, 0, 0, 0, size.cx, size.cy,
                            ::lightui::e_SWP_NOMOVE | ::lightui::e_SWP_NOZORDER | ::lightui::e_SWP_NOACTIVATE);
//      return false;
   }

   bool Window::setPosition(const ::i32_point & point)
   {
      ASSERT(isWindow());
      auto operatingsystemwindow = operating_system_window();
      return !!::cross_windows::set_window_pos(operatingsystemwindow, 0, point.x, point.y, 0, 0,
                            ::lightui::e_SWP_NOSIZE | ::lightui::e_SWP_NOZORDER | ::lightui::e_SWP_NOACTIVATE);
      //return false;
   }

   bool Window::setPlacement(const ::i32_rectangle & rectangle)
   {
      ASSERT(isWindow());
      auto operatingsystemwindow = operating_system_window();
      return !!::cross_windows::set_window_pos(operatingsystemwindow, 0,
         rectangle.left, rectangle.top,
         rectangle.width(), rectangle.height(),
                            ::lightui::e_SWP_NOZORDER | ::lightui::e_SWP_NOACTIVATE);
    ////  return false;
   }

   void Window::setParent(::innate_subsystem::WindowInterface * pwindow)
   {
       if (!isWindow())
       {

           m_pwindowDeferredParent = pwindow;
      }
       else
       {
//          if (::is_null(pwindow))
//             SetParent(m_macoswindow.as_HWND(), nullptr);
//          else
//          {
//             auto hwndParent = (HWND)pwindow->_HWND();
//             SetParent(m_macoswindow.as_HWND(), hwndParent);
//          }
       }
   }


   ::operating_system::window Window::dialog_item_operating_system_window(int iDlgItem)
   {

      ASSERT(m_macoswindow.is_set());

      auto operatingsystemwindowChild = ::cross_windows::get_dlg_item(m_macoswindow.as_operating_system_window(), iDlgItem);
      
      return operatingsystemwindowChild;
      
   }

   void Window::subclassControlById(::Particle * pWindowControl, unsigned int id)
   {
      
      auto operatingsystemwindow = dialog_item_operating_system_window(id);
      
      auto pimpl = pWindowControl->impl < ::innate_subsystem::WindowInterface >();

      pimpl->set_operating_system_window(operatingsystemwindow);


//       auto pwindow = pWindowControl->impl<innate_subsystem_macos::Window>();
//
//      auto operatingsystemwindow = dialog_item_operating_system_window(id);
//
//      pwindow->subclassWindow(operatingsystemwindow);

   }


   void Window::subclassWindow(const ::operating_system::window & operatingsystemwindow)
   {

//      HWND hwnd = ::as_HWND(operatingsystemwindow);
//       m_macoswindow = hwnd;
//      m_wndprocDefault = (WNDPROC) ::GetWindowLongPtr(hwnd, GWLP_WNDPROC);
//      //::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LPARAM)(::uptr) (::macos::window *) this);
//      ::cast < ::macos::windowing > pwindowing = ::system()->acme_windowing();
//      pwindowing->m_windowmap[hwnd] = this;
//      ::SetWindowLongPtr(hwnd, GWLP_WNDPROC,(LPARAM)(::uptr)(::macos::window::s_window_procedure));
//      ::SendMessage(hwnd, WM_APP + 125, 0, 0);
   }


   ::innate_subsystem::WindowInterface * Window::getParent()
   {

//      auto hwnd = m_macoswindow.as_HWND();
//
//      auto hwndParent = ::GetParent(hwnd);
//
//      if (!hwndParent)
//      {
//
//         return nullptr;
//
//      }
//
//      ::cast < ::macos::windowing > pwindowing = ::system()->acme_windowing();
//      auto pwindow=pwindowing->m_windowmap[hwndParent];
//
//      ::cast < Window > pwindowSubsystem = pwindow;
//
//      if (!pwindowSubsystem)
//      {
//
//         return nullptr;
//
//      }
//
//      return pwindowSubsystem;
      return nullptr;

   }


   void Window::_addChildNotification(int iControl, int iNotification)
   {

      auto & notification = m_mapControlNotification[iControl];

      notification.m_iaNotification.add(iNotification);


   }


   void Window::_setChildControlType(int iControl, innate_subsystem::enum_control econtrol)
   {

      auto & notification = m_mapControlNotification[iControl];

      notification.m_econtrol = econtrol;

   }


   void Window::unsubclassWindow()
   {

//      auto hwnd = m_macoswindow.as_HWND();
//      ASSERT(hwnd != 0);
//
//
//      ::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LPARAM) (::uptr) nullptr);
//      ::SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<iptr>(m_wndprocDefault));
//
//      m_wndprocDefault = nullptr;
//      m_macoswindow = nullptr;
//

   }


// Set resource name for the window
void Window::setResourceName(const ::scoped_string & scopedstr)
{
   
   m_strResourceName = scopedstr;
   m_uResourceId = m_papplication->getResourceId(m_strResourceName);
   
}
// Set resource id for the window
void Window::setResourceId(::u32 uId)
{
   
   m_uResourceId = uId;
   m_strResourceName = m_papplication->getResourceName(uId);
   
}
// Get resource name for the window
::string Window::getResourceName()
{
   
   return m_strResourceName;
   
}
// Get resource id for the window
::u32 Window::getResourceId()
{
   
   return m_uResourceId;

}


   void Window::setClassStyle(unsigned int style)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetClassLong(m_macoswindow.as_HWND(), GCL_STYLE, style);
   }

   void Window::setClassCursor(::innate_subsystem::CursorInterface * pcursor)
   {
//      auto hcursor = pcursor->_HCURSOR();
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetClassLongPtr(m_macoswindow.as_HWND(), GCLP_HCURSOR, (LONG_PTR)hcursor);
   }

   void Window::setClassBackground(::innate_subsystem::BrushInterface *)
   {
//      //auto pbrushWin32 = pbrush->impl<::innate_subsystem_macos::Brush>();
//      //auto hbrush = (HBRUSH) (HGDIOBJ) pbrush->_HGDIOBJ();
//      //auto hbrush = pbrushWin32->m_pbrush->Get
//      auto hbrush = (HBRUSH) ::CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetClassLongPtr(m_macoswindow.as_HWND(), GCLP_HBRBACKGROUND, (LONG_PTR) hbrush);
   }

   void Window::setClassMenu(::innate_subsystem::MenuInterface * pmenu)
   {
//      auto hmenu = (HMENU) pmenu->_HMENU();
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetClassLongPtr(m_macoswindow.as_HWND(), GCLP_MENUNAME,(LONG_PTR) hmenu);
   }


   bool Window::we_want_WM_KEYDOWN_when_enter_is_pressed() const
   {

      return m_pwindowCallback->we_want_WM_KEYDOWN_when_enter_is_pressed();

   }


   long long Window::getStyle()
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      return GetWindowLong(m_macoswindow.as_HWND(), GWL_STYLE);
      return 0;
   }


   void Window::setStyle(unsigned int style)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetWindowLong(m_macoswindow.as_HWND(), GWL_STYLE, style);
   }


   void Window::addStyle(unsigned int styleFlag)
   {
      if (!isWindow())
      {
         m_uAddStyleOffline |= styleFlag;
         m_uEraseStyleOffline &= ~styleFlag;
          return;

      }
      ::u32 flags = getStyle();
      flags |= styleFlag;
      setStyle(flags);
   }



   void Window::removeStyle(unsigned int  styleFlag)
   {
      ::uptr flags =  getStyle();
      flags &= ~styleFlag;
      setStyle(flags);
   }

   bool Window::isStyleEnabled(unsigned int  styleFlag)
   {
      ::uptr flags = getStyle();
      return (flags & styleFlag) == styleFlag;
   }



   long long Window::getExStyle()
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      return GetWindowLong(m_macoswindow.as_HWND(), GWL_EXSTYLE);
      return 0;
   }

   void Window::setExStyle(unsigned int exstyle)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetWindowLong(m_macoswindow.as_HWND(), GWL_EXSTYLE, exstyle);
   }



   void Window::addExStyle(unsigned int styleFlag)
   {
      if (!isWindow())
      {
         m_uAddStyleExOffline |= styleFlag;
         m_uEraseStyleExOffline &= styleFlag;

         return;

      }
      ::uptr flags = getExStyle();
      flags |= styleFlag;
      setExStyle((::u32) flags);
   }



   void Window::removeExStyle(unsigned int  styleFlag)
   {
      ::uptr flags = getExStyle();
      flags &= ~styleFlag;
      setExStyle((::u32)flags);
   }

   bool Window::isExStyleEnabled(unsigned int  styleFlag)
   {
      unsigned int  flags = getExStyle();
      return (flags & styleFlag) == styleFlag;
   }


   void Window::updateWindow()
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      UpdateWindow(m_macoswindow.as_HWND());
   }

   void Window::setTimer(::uptr ident, unsigned int time)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      SetTimer(m_macoswindow.as_HWND(), ident, time, 0);
   }

   void Window::killTimer(::uptr ident)
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//      KillTimer(m_macoswindow.as_HWND(), ident);
   }

   bool Window::_onWmCommand(::wparam wparam, ::lparam lparam)
   {

    return onCommand(wparam.loword(), wparam.hiword());
    //  return false;
     

   }

   bool Window::onCommand(unsigned int controlID, unsigned int notificationID)
   {
       if (m_pwindowCallback)
       {

           if (m_pwindowCallback->onCommand(controlID, notificationID))
           {

               return true;

           }

      }
      return false;
   }

   // bool Window::onNotify(int idCtrl, LPNMHDR pnmh)
   // {
   //    return false;
   // }
   //
   //bool Window::onSysCommand(::wparam wparam, ::lparam lparam)
bool Window::on_user_system_command(::user::enum_system_command esystemcommand)
   {
      return false;
   }

   bool Window::onMessage(::user::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

       if (m_pwindowCallback)
       {

           if (m_pwindowCallback->onMessage(emessage, wparam, lparam))
           {

               return true;

           }

       }

      return false;
   }

   // void * Window::_HWND() const
   // {
   //
   //    return m_macoswindow.as_HWND();
   //
   // }
   //
   //
   // void Window::_setHWND(void * p)
   // {
   //
   //    m_macoswindow = (HWND) p;
   //
   // }
   //
   //
   // void Window::_setHen(HWND hwnd)
   // {
   //    m_macoswindow.as_HWND() = hwnd;
   // }
   //
   // HWND Window::getHWnd() const
   // {
   //    return m_macoswindow.as_HWND();
   // }

   void Window::setWindowText(const ::scoped_string & scopedstr)
   {
      if (m_macoswindow.is_null())
      {

         m_strWindowTextOffline = scopedstr;

         return;

      }
//      ::wstring wstr(scopedstr);
//      ASSERT(m_macoswindow.as_CGWindowID()() != 0);
//
//      SetWindowText(m_macoswindow.as_CGWindowID()(), wstr);
      
      auto operatingsystemwindows = operating_system_window();
      
      ::cross_windows::set_window_text(operatingsystemwindows, scopedstr);

   }

   void Window::redraw(const ::i32_rectangle &rcArea)
   {
      auto r = rcArea;
      post([this, r]()
           {
         ASSERT(isWindow());
         auto operatingsystemwindow = operating_system_window();
         if (r.is_empty()) {
            ::cross_windows::invalidate_rect(operatingsystemwindow, NULL, TRUE);
         } else {
            
            //RECT rc;
            //::copy(rc, rcArea);
            ::cross_windows::invalidate_rect(operatingsystemwindow, &r, FALSE);
         }
      });
   }

   bool Window::onMouseEx(unsigned int uMessage, int mouseButtons, unsigned short wspeed, const ::i32_point &point,
                          bool &bDoDefaultProcessing)
   {
      if (m_pwindowCallback)
      {
         if (m_pwindowCallback->onMouseEx(uMessage,  mouseButtons, wspeed, point, bDoDefaultProcessing))
         {

            return true;
         }
      }
      return false;
   }

   bool Window::onMouse(unsigned char mouseButtons, unsigned short wspeed, const ::i32_point &point)
   {
       if (m_pwindowCallback)
       {
          if (m_pwindowCallback->onMouse(mouseButtons, wspeed, point))
           {

               return true;

          }

       }
      return false;
   }

   bool Window::onKey(::user::enum_message emessage, const ::user::e_key & euserkey)
{
      
      if (m_pwindowCallback)
      {
         if (m_pwindowCallback->onKey(emessage, euserkey))
          {

              return true;

         }

      }
     return false;
   }

::f32 Window::getWindowScale()
{
   
   return 1.0f;
   
}

   void Window::setForegroundWindow()
   {
//      ASSERT(m_macoswindow.as_HWND() != 0);
//
//      SetForegroundWindow(m_macoswindow.as_HWND());
   }


   void Window::setFocus()
   {
      //::SetFocus(m_macoswindow.as_HWND());
   }

   bool Window::hasFocus()
   {
//      return (::GetFocus() == m_macoswindow.as_HWND()) || (GetForegroundWindow() == m_macoswindow.as_HWND());
      return true;
   }

   bool Window::setForeground()
   {
      //return SetForegroundWindow(m_macoswindow.as_HWND()) != 0;
      return true;
   }

   bool Window::isEnabled()
   {
      //return (!isStyleEnabled(WS_DISABLED));
      return true;
   }

   bool Window::isVisible()
   {
      //return ::IsWindowVisible(m_macoswindow.as_HWND()) != FALSE;
      return true;
   }

   bool Window::isWindow()
   {
      return (m_macoswindow.as_uptr()!= 0);
//      && (m_macoswindow.as_HWND() != INVALID_HANDLE_VALUE)
//      && (::IsWindow(m_macoswindow.as_HWND()) != FALSE);
//      return true;
   }

   bool Window::isIconic()
   {
      //return ::IsIconic(m_macoswindow.as_HWND()) != FALSE;
      return false;
   }

   bool Window::isMinimized()
   {
      return m_bMinimized;
   }

   bool Window::isFullScreen()
   {
      return m_isFullScr;
   }

   void Window::invalidate()
   {
      //InvalidateRect(m_macoswindow.as_HWND(), NULL, TRUE);
   }

   ::string Window::getText()
   {
      ASSERT(m_macoswindow.is_set());

      //int length = (int)::cross_windows::send_message(m_macoswindow, ::user::e_message_get_text_length, 0, 0);

      //::wstring wstr;
      
      auto str = ::cross_windows::get_window_text(m_macoswindow.as_operating_system_window());

      //GetWindowText(m_macoswindow.as_HWND(), wstr.auto_release_buffer(length), length + 1);

      return str;
      //return {};
      
   }


   void Window::postMessage(unsigned int Msg, ::wparam wparam, ::lparam lparam)
   {

//      ASSERT(m_macoswindow.as_HWND() != 0);
//
//      PostMessage(m_macoswindow.as_HWND(), Msg, wparam, lparam);
      
      ::system()->acme_windowing()->post([this, Msg, wparam, lparam]()
                                         {
         
         message_call((::user::enum_message)Msg, wparam, lparam,  {});
      });

   }


   void Window::post(const ::procedure& procedure)
   {
//
//       postMessage(WM_APP + 876, 0, procedure);
      ::system()->acme_windowing()->post(procedure);

   }


   ::i32_rectangle Window::getClientRect()
   {

      ASSERT(isWindow());

      ::i32_rectangle rectangle;
      
      auto operatingsystemwindow = operating_system_window();

      ::cross_windows::get_client_rect(operatingsystemwindow, &rectangle);


      //::copy(rectangle, rect);

      return rectangle;
      //return {};

   }

   
   void Window::toggle_fullscreen()
   {
      
//      if (m_isFullScr)
//      {
//         
//         doUnFullScreen();
//         
//      }
//      else
//      {
//         
//         doFullScreen();
//         
//      }
      
      auto operatingsystemwindow = operating_system_window();

      ::cross_ns::toggle_immersive_fullscreen(operatingsystemwindow);
      
   }
   


   ::i32_rectangle Window::getFullScreenRect()
   {

      auto operatingsystemwindow = this->operating_system_window();
      
      auto rectangleFullscreen = ::cross_windows::get_window_monitor_rect(operatingsystemwindow);

//      // Get size of desktop.
//      HMONITOR hmon = MonitorFromWindow(m_macoswindow.as_HWND(), MONITOR_DEFAULTTONEAREST);
//      MONITORINFO mi;
//      mi.cbSize = sizeof(mi);
//
//      RECT fullScreenWindowsRect;
//      if (!!GetMonitorInfo(hmon, &mi)) {
//         fullScreenWindowsRect = mi.rcMonitor;
//      }
//      else {
//         warning("Get monitor info is failed. Use second method (no multi-screen).");
//         GetWindowRect(GetDesktopWindow(), &fullScreenWindowsRect);
//      }
//      ::i32_rectangle fullScreenRect;
//      fullScreenRect = fullScreenWindowsRect;
//
//
//      return fullScreenRect;
      return rectangleFullscreen;
   }


   ::i32_rectangle Window::getScreenWorkArea()
   {
//
//      // Get work area.
//      ::i32_rectangle rectangleScreenWorkArea;
//
//      HMONITOR hmon = MonitorFromWindow(m_macoswindow.as_HWND(), MONITOR_DEFAULTTONEAREST);
//      MONITORINFO mi;
//      mi.cbSize = sizeof(mi);
//
//      if (!!GetMonitorInfo(hmon, &mi)) {
//         rectangleScreenWorkArea = mi.rcWork;
//      } else {
//         debug("Get monitor info is failed. Use second method (no multi-screen).");
//         ::i32_rectangle desktopRc;
//         if (!MainSubsystem().SystemInformation().getDesktopArea(desktopRc)) {
//            MainSubsystem().SystemInformation().getDesktopAllArea(desktopRc);
//         }
//         rectangleScreenWorkArea  = desktopRc;
//      }
//
//
//      return rectangleScreenWorkArea;
      return {};
   }

   void Window::_setSizeFullScreenWindow()
   {
//      // Save position of window.
//      GetWindowPlacement(m_macoswindow.as_HWND(), &m_windowplacementWorkArea);
//
      //auto fullScreenRect = getFullScreenRect();
//
//      setStyle((getStyle() | WS_MAXIMIZE) & ~(WS_CAPTION | WS_BORDER | WS_THICKFRAME  | WS_MAXIMIZEBOX));
//      setExStyle(getExStyle() | WS_EX_TOPMOST);
//
      
      
      auto operatingsystemwindow = operating_system_window();

      ::cross_ns::enter_immersive_fullscreen(operatingsystemwindow);
      
      //::cross_windows::set_window_pos(operatingsystemwindow,
        /*           0,
                   fullScreenRect.left, fullScreenRect.top,
                   fullScreenRect.width(), fullScreenRect.height(),
                   0);*/
      
   }


   void Window::_doRestoreFromFullScreen()
   {
      
      auto operatingsystemwindow = operating_system_window();

      ::cross_ns::exit_immersive_fullscreen(operatingsystemwindow);

//      // Restore position, style and exstyle of windowed window.
//      setStyle(getStyle() | WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_MAXIMIZEBOX);
//      setExStyle(getExStyle() & ~WS_EX_TOPMOST);
//      ::i32_rectangle workArea;
//      workArea = m_windowplacementWorkArea.rcNormalPosition;
//      if (m_rectangleNormal.height() == workArea.height() ||
//          m_rectangleNormal.width() == workArea.width()) {
//         SetWindowPlacement(m_macoswindow.as_HWND(), &m_windowplacementWorkArea);
//          } else {
//             setStyle(getStyle() & ~WS_MAXIMIZE);
//             setPlacement(m_rectangleNormal);
//          }
//

   }


   void Window::_doRestoreToFullScreen()
   {
      if (m_isFullScr) {
         return;
      }


      onBeforeFullScreen(true);

      // m_pconnectionconfig->enableFullscreen(true);
      // m_pconnectionconfig->saveToStorage(&m_ccsm);
      //
      // //auto config = ::remoting::ViewerConfig::getInstance();
      // //m_bToolBar = m_toolbar.isVisible();
      // //m_toolbar.hide();
      //
      // //m_menu.checkedMenuItem(IDS_TB_FULLSCREEN, true);
      // //m_menu.checkedMenuItem(IDS_TB_TOOLBAR, false);
      // //m_menu.enableMenuItem(IDS_TB_TOOLBAR, 1);

      _setSizeFullScreenWindow();

      //SetFocus(m_desktopwindow.getHWnd());
      //m_desktopwindow.setFocus();
      _applyScreenChanges(true);


      onAfterFullScreen(true);
      // try {
      //    // Registration of keyboard hook.
      //    m_operatingsystemhook.registerKeyboardHook(this);
      //    // Switching off ignoring win key.
      //    m_desktopwindow.setWinKeyIgnore(false);
      // }
      // catch (::exception& e) {
      //    m_plogwriter->error("{}", e.get_message());
      // }
   }


   bool Window::_applyScreenChanges(int isFullScreen)
   {
       m_isFullScr = isFullScreen;
       onSize();
       redraw();
      return true;
   }


bool Window::on_key_down(::user::e_key  euserkey)
{
   
   bool bRet= onKey(::user::e_message_key_down, euserkey);
   
   if(bRet)
   {
      
      return true;
      
   }
   
   return false;
   
//   auto pacmewindowingwindow = acme_windowing_window();
//   
//   auto pkey = pacmewindowingwindow->create_newø <::user::key>();
//   
//   //::user::enum_key ekey = ::user::e_key_none;
//   
//   pkey->m_eusermessage = ::user::e_message_key_down;
//   
//   pkey->m_ekey = euserkey;
//   //throw "todo";
//   
//   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
//   
//   pelemental->on_key_down(pkey);

   
}


 bool Window::on_key_up(::user::e_key euserkey)
{
   
    bool bRet = onKey(::user::e_message_key_up, euserkey);
    
    if(bRet)
    {
       
       return true;
       
    }
    
    return false;
//   auto pacmewindowingwindow = acme_windowing_window();
//   
//   auto pkey = pacmewindowingwindow->create_newø <::user::key>();
//    
//    //throw "todo";
//    pkey->m_ekey = euserkey;
//    
//    pkey->m_eusermessage = ::user::e_message_key_up;
//   
//   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
//   
//   pelemental->on_key_up(pkey);
   
}

   void Window::doUnFullScreen()
    {
        if (!m_isFullScr) {
            return;
        }

      onBeforeUnFullScreen(false);

       _doRestoreFromFullScreen();

//        m_desktopwindow.setScale(m_scale);
        _applyScreenChanges(false);

      onAfterUnFullScreen(false);

    }


   void Window::adjustWindowSize()
   {
      // If size isn't changed by user, then adjust size.
      if (!m_sizeIsChanged) {
         ::i32_rectangle defaultSize;
         bool bHasDefaultSize = onCalculateDefaultSize(defaultSize);

         bool bDefaultSizeIsChanged = false;

         if (bHasDefaultSize)
         {
            bDefaultSizeIsChanged = defaultSize.width() != m_rectangleNormal.width() ||
                                     defaultSize.height() != m_rectangleNormal.height();
         }
         // If size is changed, isn't full screen, if window isn't maximized,
         // then set new position and size.
         if (!m_isFullScr && bDefaultSizeIsChanged) {
            m_rectangleNormal = defaultSize;
            setPlacement(m_rectangleNormal);
//            setSize(m_rcNormal.width(), m_rcNormal.height());
         }

         onAdjustWindowSize();
      }
   }


void Window::setMouseCursor(::enum_cursor ecursor)
{
   
   auto operatingsystemwindow = this->operating_system_window();
   
   ::cross_ns::set_mouse_cursor(operatingsystemwindow, ecursor);
   
}


    void Window::_doMinimizeFromFullScreen()
    {
        if (!m_isFullScr) {
            return;
        }

      onBeforeUnFullScreen(true);
        // m_pconnectionconfig->enableFullscreen(false);
        // m_pconnectionconfig->saveToStorage(&m_ccsm);

        //m_menu.checkedMenuItem(IDS_TB_FULLSCREEN, false);
        //m_menu.checkedMenuItem(IDS_TB_TOOLBAR, m_bToolBar);

        //if (m_bToolBar) {
        //    m_toolbar.show();
        //}
        //else {
        //    m_toolbar.hide();
        //}

        //unsigned int isEnable = static_cast<unsigned int>(m_pconnectionconfig->isViewOnly());
        //m_menu.enableMenuItem(IDS_TB_TOOLBAR, isEnable);

        //// Restore position, style and exstyle of windowed window.
        //set_style(get_style() | WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_MAXIMIZEBOX);
       
       
       
       
       //setExStyle(getExStyle() & ~WS_EX_TOPMOST);
       
       
       doUnFullScreen();
       
       //mini
       
        //::i32_rectangle workArea;
        //workArea = m_workArea.rcNormalPosition;
        //if (m_rcNormal.height() == workArea.height() ||
        //    m_rcNormal.width() == workArea.width()) {
        //    SetWindowPlacement(m_hwnd, &m_workArea);
        //}
        //else {
        //    set_style(get_style() & ~WS_MAXIMIZE);
        //    setPosition(m_rcNormal.left, m_rcNormal.top);
        //    setSize(m_rcNormal.width(), m_rcNormal.height());
        //}

        //    m_desktopwindow.setScale(m_scale);
        _applyScreenChanges(false);

      onAfterUnFullScreen(true);
        //// Unregistration of keyboard hook.
        //m_winHooks.unregisterKeyboardHook(this);
        //// Switching on ignoring win key.
        //m_desktopwindow.setWinKeyIgnore(true);
    }


   void Window::minimizeWindow()
   {

      //m_pdesktopwindow->m_viewerCore->ge
      m_bMinimized = true;
      if (m_isFullScr)
      {
         m_isMinimizedFromFullScreen = true;
         _doMinimizeFromFullScreen();

      }
      
      auto operatingsystemwindow = this->operating_system_window();
      
      ::cross_ns::minimize_window(operatingsystemwindow);


   }


   void Window::restoreWindow()
   {

      //ShowWindow(m_hwnd, SW_RESTORE);
      show();
      if (m_isMinimizedFromFullScreen)
      {

         _doRestoreToFullScreen();

      }


      m_bMinimized = false;


   }


   void Window::doFullScreen()
   {

      //void ViewerWindow::doFullScr()
      //{
         if (m_isFullScr) {
            return;
         }

         onBeforeFullScreen(false);

         _setSizeFullScreenWindow();

         _applyScreenChanges(true);


      onAfterFullScreen(false);
      //
      //    //SetFocus(m_desktopwindow.getHWnd());
      //    m_desktopwindow.setFocus();
      //
      //    if (config->isPromptOnFullscreenEnabled()) {
      //       postMessage(WM_USER_FS_WARNING);
      //    }
      //
      //    try {
      //       // Registration of keyboard hook.
      //       m_operatingsystemhook.registerKeyboardHook(this);
      //       // Switching off ignoring win key.
      //       m_desktopwindow.setWinKeyIgnore(false);
      //    } catch (::exception &e) {
      //       m_plogwriter->error("{}", e.get_message());
      //    }
      // }


   }


   ::i32_size Window::getBorderSize()
   {

      //ASSERT(m_macoswindow.as_CGWindowID()() != 0);
//
//      auto width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);
//
//      auto height = GetSystemMetrics(SM_CYSIZE) +
//                2 * GetSystemMetrics(SM_CYSIZEFRAME);
//
//      return {width, height};
      return {};

   }


   bool Window::onCreate(void * pCreateStruct)
   {

      return m_pwindowCallback->onCreate(pCreateStruct);;

   }



   void Window::_defer_update_double_buffering()
   {

      if (!m_bDoubleBuffering)
      {

         return;

      }
      
      m_clientArea = getClientRect();
      
      auto sizeClientArea = m_clientArea.size();
      
      ::i32_size sizeBuffer{};
      
      if(m_pbitmapBuffer && m_pbitmapBuffer->m_pdib)
      {
         
         sizeBuffer = m_pbitmapBuffer->m_pdib->size();
         
      }

      if (m_pgraphicsBuffer
          && m_pgraphicsBuffer->m_pdevicecontext && m_pbitmapBuffer
          && m_pbitmapBuffer->m_pdib && sizeBuffer == sizeClientArea)
      {

          return;
         
      }

      if (m_pgraphicsBuffer
          && m_pgraphicsBuffer->m_pdevicecontext && m_pgraphicsBuffer->m_pdevicecontext->m_pcontext)
      {
         m_pgraphicsBuffer->m_pdevicecontext->destroyDeviceContext();
//          if (m_hbitmapOld)
//          {
//              SelectObject(m_hdcBuffer, m_hbitmapOld);
//          }
//          ::DeleteDC(m_hdcBuffer);
      }
      
      defer_construct_newø(m_pbitmapBuffer);
      defer_constructø(m_pbitmapBuffer->m_pdib);
      
      m_pbitmapBuffer->m_pdib->create_image(sizeClientArea);

//      m_sizeBuffer = m_clientArea.size();
//
//      m_hdcBuffer = CreateCompatibleDC(m_paintStruct.hdc);
//      void *pBits = nullptr;
//
//      // 2️⃣ Create 32-bit DIB section (alpha preserved)
//      BITMAPINFO bi = {};
//      bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//      bi.bmiHeader.biWidth = m_sizeBuffer.cx;
//      bi.bmiHeader.biHeight = -m_sizeBuffer.cy; // top-down
//      bi.bmiHeader.biPlanes = 1;
//      bi.bmiHeader.biBitCount = 32;
//      bi.bmiHeader.biCompression = BI_RGB;
//      m_hbitmapBuffer = CreateDIBSection(m_paintStruct.hdc, &bi, DIB_RGB_COLORS, &pBits, nullptr, 0);
//      m_hbitmapOld = (HBITMAP)SelectObject(m_hdcBuffer, m_hbitmapBuffer);
//
//      // 1️⃣ Create memory DC
//      defer_construct_newø(m_pbitmapBuffer);
//      m_pbitmapBuffer->_initialize_bitmap(m_hbitmapBuffer, nullptr);

      defer_construct_newø(m_pgraphicsBuffer);
      defer_construct_newø(m_pgraphicsBuffer->m_pdevicecontext);
      m_pgraphicsBuffer->m_pdevicecontext->initialize_device_context(m_pbitmapBuffer);
      //auto p =
      //m_pgraphicsBuffer->m_pdevicecontext->impl<::innate_subsystem_macos::DeviceContext>();
      //m_pgraphicsBuffer->m_pdevicecontext->m_pcgcontext = m_pbitmapBuffer->m_pcgdib->m_cgdib.m_pcgcontext;
      //p->m_hdc2 = m_hdcBuffer;
      //p->m_pgraphics = new Gdiplus::Graphics(p->m_hdc2);
      // 3️⃣ Clear buffer (transparent black)
    //  ZeroMemory(pBits, m_sizeBuffer.area() * 4);
   }

   
   void Window::on_move(int x, int y)
   {
      
      ::appkit::acme::windowing::window::on_move(x, y);
      
   }


   void Window::on_size(int w, int h)
   {
      
      ::appkit::acme::windowing::window::on_size(w, h);
      
      onSize();

   }



   void Window::onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::i32_rectangle & rectangle)
   {

      m_pwindowCallback->onDraw(pgraphics, rectangle);


   }

   // void DesktopWindow::onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct)
   void Window::_doPaint(HDC hdc)
   {

//      //m_bIsDraw = true;
//      //DeviceContext dc(this);
//      //onPaint(&dc, &m_paintStruct);
//      //EndPaint(m_hWnd, &m_paintStruct);
//      //m_bIsDraw = false;
//      //return true;
//      ::i32_rectangle paintRect(m_paintStruct.rcPaint);
//
//
//      // 5️⃣ Blit to screen (alpha ignored in normal window)
//
//
//      // Cleanup
//      // SelectObject(hdcMem, hOld);
//      // DeleteObject(hBmp);
//      // DeleteDC(hdcMem);
//
//      // EndPaint(hwnd, &ps);
//      if (paintRect.is_empty())
//      {
//
//         return;
//      }
//
//      m_clientArea = getClientRect();
//
//      if (m_clientArea.is_empty())
//      {
//         return;
//      }
//
//
//      _defer_update_double_buffering();
//
//
//      if (m_pgraphicsBuffer->m_pdevicecontext)
//      {
//         // onDraw(m_hdcBuffer, m_paintStruct.rcPaint);
//
//         ::i32_rectangle r;
//
//         copy(r, m_paintStruct.rcPaint);
//
//         ::innate_subsystem_macos::Graphics g;
//
//         // defer_construct_newø(m_pgraphicsBuffer->m_pdevicecontext);
//
//         g.initialize_graphics(m_pgraphicsBuffer->m_pdevicecontext);
//
//
//         // g.m_pdevicecontext->_attachHDC(hdc);
//
//
//         onDraw(&g, r);
//
//         // g.m_pdevicecontext->_attachHDC(nullptr);
//
//         g.m_pdevicecontext = nullptr;
//      }
//
//      ::BitBlt(
//         m_paintStruct.hdc,
//         m_paintStruct.rcPaint.left,
//         m_paintStruct.rcPaint.top,
//         ::width(m_paintStruct.rcPaint),
//         ::height(m_paintStruct.rcPaint),
//         m_hdcBuffer,
//         m_paintStruct.rcPaint.left,
//         m_paintStruct.rcPaint.top,
//         SRCCOPY);
      
   }


void Window::_draw(::core_graphics::cg_context * pcgcontext, const ::i32_rectangle & rectangle)
{
   
   _defer_update_double_buffering();
   
//   auto pcgcolorYellow = create_newø<::core_graphics::cg_color>();
//   
//   pcgcolorYellow->create_color(::color::yellow);
//   
//   pcgcontext->set_fill_color(pcgcolorYellow);
//   
//   ::i32_rectangle r;
//   
//   r.left = 23;
//   r.top = 23;
//   r.right = 1024 - 23;
//   r.bottom = 768 - 23;
//   
//   pcgcontext->fill_rect(r);

   onDraw(m_pgraphicsBuffer, rectangle);
   
   //m_pgraphicsBuffer->setBlendModeOn(true);
   //m_pgraphicsBuffer->fillRect({0, 0, 1024, 768}, argb(160, 100, 160, 255));

   //pcgcontext->set_blend_mode_on(false);
   
   auto r = get_rectangle();
   
   ::cast < ::quartz2d::nano::graphics::image > pimageQuartz2d = m_pbitmapBuffer->m_pdib->fetch_image();
   
   pcgcontext->draw_image(r, pimageQuartz2d->m_pcgimage);
   
}


   //bool Window::on_window_procedure(LRESULT & lresult, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   bool Window::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {
//
//      if (m_pwindowCallback)
//      {
//
//         if (m_pwindowCallback->on_window_procedure(lresult, message, wparam, lparam))
//         {
//
//            return true;
//
//         }
//
//      }
//
      switch (message)
      {
//         case WM_SIZING:
//            m_sizeIsChanged = true;
//            return false;
//         case WM_CREATE:
//         {
//
//            if (m_bHasClipboardViewerInterest)
//            {
//
//               m_hwndNextViewer = SetClipboardViewer((HWND)_HWND());
//
//            }
//
//            if (!onCreate((void*)lparam.m_lparam))
//            {
//
//               lresult = -1;
//               return true;
//
//            }
//
//            lresult = 0;
//            //return true;
//         }
//            break;
//         case WM_CHANGECBCHAIN:
//            {
//            if (m_bHasClipboardViewerInterest)
//            {
//               if (wparam == m_hwndNextViewer)
//               {
//                  m_hwndNextViewer = (HWND)lparam.m_lparam;
//               }
//               else if (m_hwndNextViewer != NULL)
//               {
//                  SendMessage(m_hwndNextViewer, message, wparam, lparam);
//               }
//            }
//            return true;
//      }
//         case WM_DRAWCLIPBOARD:
//         {
//            if (m_bHasClipboardViewerInterest)
//            {
//               bool ok = onDrawClipboard();
//               SendMessage(m_hwndNextViewer, message, wparam, lparam);
//               return ok;
//            }
//         }
//break;
//         case WM_PAINT:
//         {
//
//             if (m_bHasOnDrawInterest)
//             {
//
//                auto hwnd = ::as_HWND(operating_system_window());
//                
//                auto hdc = BeginPaint(hwnd, &m_paintStruct);
//                
//                m_bIsDraw = true;
//                // DeviceContext dc(this);
//                
//                //::i32_rectangle r;
//                
//                //copy(r, m_paintStruct.rcPaint);
//                
//                _doPaint(hdc);
//
//                EndPaint(hwnd, &m_paintStruct);
//
//                m_bIsDraw = false;
//                lresult = 0;
//                return true;
//             }
//            else
//            {
//
//               return false;
//
//            }
//
//         }
//         break;
//      case WM_GETDLGCODE:
//         {
//
//            bool bWeWantWMKEYDOWNWhenEnterIsPressed = this->we_want_WM_KEYDOWN_when_enter_is_pressed();
//
//            if (bWeWantWMKEYDOWNWhenEnterIsPressed)
//            {
//
//               lresult = CallWindowProc(m_wndprocDefault, m_macoswindow.as_HWND(), message, wparam, lparam);
//
//               auto pmsg = lparam.raw_cast<MSG*>();
//               // We want WM_KEYDOWN scopedstrMessage when enter is pressed
//               if (pmsg &&
//                  pmsg->message == WM_KEYDOWN &&
//                  pmsg->wParam == VK_RETURN)
//               {
//                  lresult = DLGC_WANTMESSAGE;
//               }
//               return true;
//
//            }
//            return false;
//
//         }
//            case WM_SETCURSOR:
//                //if (m_bShowCursor || m_timeStartDesktopWindow.elapsed() < 8_s)
//                if (m_ecursor == e_cursor_arrow)
//                {
//                    
//                    if (!m_hcursorArrow)
//                    {
//                    
//                        m_hcursorArrow = LoadCursor(nullptr, IDC_ARROW);
//
//                    }
//
//                    ::SetCursor(m_hcursorArrow);
//
//                    lresult = 1;
//
//                    return true;
//
//                }
//                else if (m_ecursor == e_cursor_none)
//                {
//
//                    ::SetCursor(nullptr);
//
//                    lresult = 1;
//
//                    return true;
//
//                }
//
//                lresult = 0;
//
//                break;
         case ::user::e_message_command:
        return  _onWmCommand(wparam, lparam);
//         
//      case WM_NOTIFY:
//      {
//
//         LPTOOLTIPTEXT toolTipText = reinterpret_cast<LPTOOLTIPTEXT>(lparam.m_lparam);
//         if (toolTipText->hdr.code == TTN_NEEDTEXT)
//         {
/////            ::string strTooltip;
//            if (onGetTooltip(toolTipText->hdr.idFrom, m_strTooltip))
//            {
//               m_wstrToolTip = m_strTooltip;
//               toolTipText->lpszText = const_cast<TCHAR *>(m_wstrToolTip.c_str());
//               return true;
//            }
//         }
//
//         if (_000OnNotify(lresult, wparam, lparam))
//         {
//
//            return true;
//
//         }
//         // auto hwndFrom = lpnmhdr->hwndFrom;
//         //
//         // if (hwndFrom)
//         // {
//         //    lresult = ::SendMessage(hwndFrom, WM_REFLECT_NOTIFY, wparam, lparam);
//         //    return true;
//         // }
//
//      }
//      case WM_SYSCOMMAND:
//         return onSysCommand(wparam, lparam);
//      case WM_SIZE:
//         onSize();
//         return false;
//      case WM_REFLECT_NOTIFY_EX:
//         {
//
//            auto pnotify = lparam.raw_cast<windows_reflect_notify_t *>();
//
//            _000OnNotifyReflect(*pnotify);
//
//            lresult = 0;
//
//            return true;
//
//         }
//         break;
//      case WM_LBUTTONDOWN:
//      case WM_LBUTTONUP:
//      case WM_MBUTTONDOWN:
//      case WM_MBUTTONUP:
//      case WM_RBUTTONDOWN:
//      case WM_RBUTTONUP:
//      case WM_MOUSEWHEEL:
//      case WM_MOUSEMOVE:
//      {
//         unsigned char mouseButtons = 0;
//
//         mouseButtons |= LOWORD(wparam) & MK_RBUTTON ? innate_subsystem::e_mouse_right : 0;
//         mouseButtons |= LOWORD(wparam) & MK_MBUTTON ? innate_subsystem::e_mouse_middle : 0;
//         mouseButtons |= LOWORD(wparam) & MK_LBUTTON ? innate_subsystem::e_mouse_left : 0;
//
//         // Translate position from ::lparam to POINT.
//         POINTS points = MAKEPOINTS(lparam);
//         ::i32_point point;
//         point.x = points.x;
//         point.y = points.y;
//
//         unsigned short wheelSpeed = 0;
//         if (message == WM_MOUSEWHEEL) 
//         {
//            // Get speed wheel and set mouse button.
//            signed short wheelSignedSpeed = static_cast<signed short>(HIWORD(wparam));
//            if (wheelSignedSpeed < 0) {
//               mouseButtons |= ::innate_subsystem::e_mouse_wheel_down;
//               wheelSpeed = -wheelSignedSpeed / WHEEL_DELTA;
//            }
//            else {
//               mouseButtons |= ::innate_subsystem::e_mouse_wheel_up;
//               wheelSpeed = wheelSignedSpeed / WHEEL_DELTA;
//            }
//
//            // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
//            // then wheelSpeed set to 1, but not 0.
//            if (wheelSpeed == 0) {
//               wheelSpeed = 1;
//            }
//
//            wheelSpeed *= 36;
//
//            // If macos-message is WHEEL, then need to translate screen coordinate to client.
//            POINT p;
//            ::copy(p, point);
//            if (!ScreenToClient(m_macoswindow.as_HWND(), &p)) {
//               p.x = -1;
//               p.y = -1;
//            }
//            ::copy(point, p);
//         }
//
//         bool bDoDefaultProcessing = false;
//
//         if (onMouseEx(message, mouseButtons, wheelSpeed, point, bDoDefaultProcessing))
//         {
//
//             return !bDoDefaultProcessing;
//
//         }
//
//         // Notify window about mouse-event.
//         return onMouse(mouseButtons, static_cast<unsigned short>(wheelSpeed), point);
//      }
//         case WM_CLOSE:
//      {
//         information("received WM_CLOSE");
//         break;
//      }
//         case WM_DESTROY:
//      {
//
//m_macoswindow = nullptr;
//      }break;
         default:
            break;
      }
      return onMessage((::user::enum_message)message, wparam, lparam);
   }

lresult Window::message_call(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, const ::i32_point & point)
{
   
   ::lresult lresult = 0;
   
   on_window_procedure(lresult, eusermessage, wparam, lparam);

   return lresult;

}


   bool notification_handler::_000OnNotify(::lresult &lresult, wparam wparam, lparam lparam)
   {

//      auto iControl = LOWORD(wparam);
//
//      auto lpnmhdr = (LPNMHDR) lparam.m_lparam;
//
//      ::cast < ::innate_subsystem_macos::Window > pwindowWin32 = this->get_window_implementation();
//
//      auto &notification = pwindowWin32->m_mapControlNotification[iControl];
//
//      if (notification.m_econtrol != ::innate_subsystem::e_control_none)
//      {
//
//         int iOperatingSystemNotificationCode = lpnmhdr->code;
//
//         if (notification.m_iaNotification.contains(iOperatingSystemNotificationCode))
//         {
//
//            windows_reflect_notify_t notify(lresult, wparam, lparam);
//
//            notify.m_econtrol = notification.m_econtrol;
//
//            _000OnNotify(notify);
//
//         // }
//         //
//         //    bool bHandled = _this->_onNotify(iControl, lpnmhdr);
//            if (!notify.m_bHandled)
//            {
//               // windows_reflect_notify_t notify;
//               // notify.m_bHandled = false;
//               // notify.set_wparam(wparam);
//               // notify.m_lresult = 0;
//               // notify.m_lpnmhdr = lpnmhdr;
//               SendMessage(lpnmhdr->hwndFrom, WM_REFLECT_NOTIFY_EX, 0,(LPARAM) &notify);
//               //if (bHandled && notify.m_bHandled)
//               //{
//                  //bResult = notify.m_lresult;
//               //}
//               //bResult = true;
//            }
//
//            if (notify.m_bHandled)
//            {
//
//               return true;
//
//            }
//
//         }
//
//      }

      return false;

   }


   void notification_handler::_000OnNotify(windows_reflect_notify_t & notify)
   {

      if (notify.m_econtrol == innate_subsystem::e_control_list_view)
      {

         onListViewNotification(notify);

      }
      else if (notify.m_econtrol == innate_subsystem::e_control_tab)
      {

         onTabNotification(notify);

      }

   }


   void notification_handler::_000OnNotifyReflect(windows_reflect_notify_t & notify)
   {
      //return false;
   }


   bool notification_handler::onListViewNotification(windows_reflect_notify_t & notify)
   {

      return false;

   }


   bool notification_handler::onTabNotification(windows_reflect_notify_t & notify)
   {

      ::innate_subsystem::notification_handler * pcallback = nullptr;

      auto pwindow =  get_window_implementation();

      if (pwindow)
      {

         pcallback = pwindow->get_callback<::innate_subsystem::notification_handler>();

      }

      if (!pcallback)
      {

         return false;

      }
//
//      switch (notify.m_lpnmhdr->code)
//      {
//         case TCN_SELCHANGE:
//         {
//
//            return pcallback->_002OnTabChanged(notify.m_iControl);
//
//         }
//         case TCN_SELCHANGING:
//         {
//
//            bool bOk = true;
//
//            bool bHandled = pcallback->_002OnTabChanging(notify.m_iControl, bOk);
//
//            if (bHandled)
//            {
//
//               notify.m_lresult = bOk ? TRUE : FALSE;
//
//               notify.m_bHandled = true;
//
//            }
//
//            break;
//         }
//            break;
//      }

      return false;

   }

   void Window::onBeforeFullScreen(bool bRestore)
   {

      m_pwindowCallback->onBeforeFullScreen(bRestore);

   }

   void Window::onAfterFullScreen(bool bRestore)
   {

      m_pwindowCallback->onAfterFullScreen(bRestore);

   }

   void Window::onBeforeUnFullScreen(bool bMinimizing)
   {

      m_pwindowCallback->onBeforeUnFullScreen(bMinimizing);

   }

   void Window::onAfterUnFullScreen(bool bMinimizing)
   {

      m_pwindowCallback->onAfterUnFullScreen(bMinimizing);

   }


   bool Window::onGetTooltip(int iControl, ::string & strTooltip)
   {

      return m_pwindowCallback->onGetTooltip(iControl, strTooltip);

   }



   bool Window::onCalculateDefaultSize(::i32_rectangle & rectangleDefaultSize)
   {

      return m_pwindowCallback->onCalculateDefaultSize(rectangleDefaultSize);

   }


   void Window::onAdjustWindowSize()
   {

      return m_pwindowCallback->onAdjustWindowSize();

   }


   void Window::onSize()
   {

      return m_pwindowCallback->onSize();

   }


//void Window::on_set_cursor_rectangles()
//{
//   
//   
//   m_pwindowCallback->on_set_cursor_rectangles();
//   
//}
//
//void Window::invalidate_cursor_rectangles()
//{
//   
//   
//   ::appkit::acme::windowing::window::invalidate_cursor_rectangles();
//   
//}
//
//void Window::add_cursor_rectangle(const ::i32_rectangle &rectangle, ::enum_cursor ecursor)
//{
//   
//   auto operatingsystemwindow = operating_system_window();
//
//   ::cross_ns::add_cursor_rectangle(operatingsystemwindow, rectangle, ecursor);
//
//   
//}


void Window::post_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
{

   ::system()->acme_windowing()->post([this, eusermessage, wparam, lparam]()
      {
                                      ::lresult lresult = 0;
      this->on_window_procedure(lresult
                          , eusermessage,  wparam,  lparam);
      
   });

}

   


} // namespace innate_subsystem_macos
// } // namespace macos
//
