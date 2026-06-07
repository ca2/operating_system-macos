// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
#include "Dialog.h"

//#include "util/CommonHeader.h"

//#include <commctrl.h>
//#include <crtdbg.h>

#include "Window.h"
#include "acme/windowing/windowing.h"
#include "operating_system-macos/appkit/windowing.h"
#include "operating_system-macos/acme_windowing_appkit/windowing.h"

::uptr ns_show_dialog(const char * psz, ::acme::windowing::window * pacmewindowingwindow);
::uptr ns_create_offscreen_child_dialog(const char * psz, ::acme::windowing::window * pacmewindowingwindow);
void ns_end_dialog(::appkit::ns_window_t nswindow, int iDialogResult);
void ns_end_attached_modal(::appkit::ns_window_t nswindow, int iDialogResult);
int ns_do_modal_dialog(const char * psz, ::acme::windowing::window * pacmewindowingwindow);
void ns_do_attached_modal_dialog(const char * pszResourceName,
                                 ::acme::windowing::window * pacmewindowingwindow,
                            const ::operating_system::window & operatingsystemwindowParent,
                                 const ::function < void(int) > & callback);
::appkit::ns_window_t as_ns_window_t(const ::operating_system::window & operatingsystemwindow);
namespace innate_subsystem_macos
{

   Dialog::Dialog()
//   : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   //: m_resourceName(0), m_resourceId(0), m_hicon(0)
:  m_hicon(0),
m_isAttachedModal(false),
m_isModal(false),
m_isCreated(false)
   {
   }

   // Dialog::Dialog(DWORD resourceId)
   // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
   // {
   // }
   //
   // Dialog::Dialog(const TCHAR *resourceName)
   // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   // {
   //    setResourceName(resourceName);
   // }

   Dialog::~Dialog()
   {
//      if (m_hicon) {
//         DeleteObject(m_hicon);
//      }
//      if (m_resourceName != 0) {
//         free(m_resourceName);
//      }
   }

   void Dialog::initialize_dialog(unsigned int resourceId)
   //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
   {

      setResourceId(resourceId);
      
      ///m_resourceName = m_papplication->getResourceName(resourceId);
   }
void
   Dialog::initialize_dialog(const char *resourceName)
   //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   {
      setResourceName(resourceName);
   }

//
//   void Dialog::setResourceName(const char * resourceName)
//   {
////      if (m_resourceName != 0) {
////         free(m_resourceName);
////      }
//
//      //m_resourceName = _strdup(resourceName);
//   }
//
//   void Dialog::setResourceId(unsigned int id)
//   {
//      m_resourceId = id;
//   }

   void Dialog::setDefaultPushButton(unsigned int buttonId)
   {
      //SendMessage((HWND) _HWND(), DM_SETDEFID, buttonId, 0);
   }

   // void Dialog::setParent(Control *ctrlParent)
   // {
   //    m_ctrlParent = ctrlParent;
   // }

   void Dialog::show()
   {
      
      if (!isWindow()) {
         if(getParent())
         {
            create(true);
         }
         else
         {
            create(false);
         }
      } else {
         Window::show();
         setForeground();
      }
//      //return 0;
   }

   void Dialog::hide()
   {
      Window::hide();
   }

   void Dialog::closeDialog(int code)
   {
//      // Destroy dialog
      if(m_isAttachedModal)
      {
         
         ns_end_attached_modal(::as_ns_window_t(operating_system_window()), code);
         
      }
      else if (!m_isModal)
      {

         hide();
         //         DestroyWindow((HWND) _HWND());
         
      } else {
         ns_end_dialog(::as_ns_window_t(operating_system_window()), code);
//         EndDialog((HWND) _HWND(), code);
      }
//      // We have no valid hwnd, so forse set hwnd to NULL
//      _setHWND(NULL);
   }

   void Dialog::create(bool bChild)
   {

      ::system()->acme_windowing()->send([&]()
      {
         if(bChild)
         {
            ::cast < ::acme::windowing::window > pacmewindowingwindow = this;
            auto u = ns_create_offscreen_child_dialog(m_strResourceName, pacmewindowingwindow);
         }
         else
         {
            ::cast < ::acme::windowing::window > pacmewindowingwindow = this;
            auto u = ns_show_dialog(m_strResourceName, pacmewindowingwindow);

         }
         
//         ::cast < ::appkit::acme::windowing::windowing> pwindowing =        ::system()->acme_windowing();
//         ::cast < ::acme::windowing::window > pwindow = this;
//         pwindowing->m_windowmap[(void*)u] = pwindow;
//         m_macoswindow.m_eoperatingambient = ::windowing::e_operating_ambient_macos;
//         m_macoswindow.m_opaque.m_ulla[0] = u;
//         pwindow->send_message(::user::e_message_initialize_dialog);
//         HWND window, parentWindow = NULL;
//
//         auto pwindow = this->impl<Window>();
//
//         if (pwindow->m_pwindowDeferredParent != NULL) {
//            parentWindow = ::as_HWND(pwindow->m_pwindowDeferredParent->operating_system_window());
//         }
//
//         auto hinstanceResource = (HINSTANCE)MainSubsystem().m_hinstanceResource;
//
//         //window = CreateDialogParam(GetModuleHandle(NULL), (LPCWSTR) getResouceName(),
//         window = CreateDialogParam(hinstanceResource, (LPCWSTR)getResouceName(), parentWindow,
//                                    dialogProc, (::lparam)(::uptr)(::innate_subsystem_macos::Dialog *)this);
//
//         m_isModal = false;
//
//         ASSERT(window != NULL);
     });
   }

   int Dialog::showModal()
   {

      int result = 0;
      if (!isWindow()) {

         ::system()->acme_windowing()->send([&]()
         {
            m_isModal = true;
            ::cast < ::acme::windowing::window > pacmewindowingwindow = this;
//            if(m_pwindowDeferredParent)
//            {
//               
//               auto operatingsystemwindow = m_pwindowDeferredParent->operating_system_window();
//               
//               [parentWindow beginSheet:sheetWindow
//                      completionHandler:^(NSModalResponse returnCode)
//               {
//                   // finished
//               }];
//               
//            }
//            else
            {
             
               result = ns_do_modal_dialog(m_strResourceName, pacmewindowingwindow);
               
            }
//            auto pwindow = this->impl<Window>();
//
//            HWND parentWindow = (pwindow->m_pwindowDeferredParent != NULL)
//                                   ? (HWND)pwindow->m_pwindowDeferredParent->_HWND()
//                                   : (HWND) nullptr;
//            //result = (int)DialogBoxParam(GetModuleHandle(NULL),
//            result = (int)DialogBoxParam((HINSTANCE) MainSubsystem().m_hinstanceResource,
//                                         (LPCWSTR) getResouceName(), parentWindow,
//                                         dialogProc,(::lparam) (::uptr)(::innate_subsystem_macos::Dialog * )this);
//
//            information("Dialog box result is {}", result);
         });

      } 
      else
      {
         
         setVisible(true);
         
         setForeground();

      }

      return result;
      return 0;

   }


void Dialog::doAttachedModal(const ::function < void(int) > & callback){

   //int result = 0;
   if (!isWindow()) {

      //::system()->acme_windowing()->send([&]()
      //{
         m_isAttachedModal = true;
         ::cast < ::acme::windowing::window > pacmewindowingwindow = this;
      ASSERT(m_pwindowDeferredParent);
//            {
               
      auto operatingsystemwindowParent = m_pwindowDeferredParent->operating_system_window();

      //
      ns_do_attached_modal_dialog(m_strResourceName, pacmewindowingwindow,
                                  operatingsystemwindowParent, callback);
//       [parentWindow beginSheet:sheetWindow
//                      completionHandler:^(NSModalResponse returnCode)
//               {
//                   // finished
//               }];
//
//            }
//            else
//         {
          
    //        result = ns_do_modal_dialog(m_strResourceName, pacmewindowingwindow);
            
  //       }
//            auto pwindow = this->impl<Window>();
//
//            HWND parentWindow = (pwindow->m_pwindowDeferredParent != NULL)
//                                   ? (HWND)pwindow->m_pwindowDeferredParent->_HWND()
//                                   : (HWND) nullptr;
//            //result = (int)DialogBoxParam(GetModuleHandle(NULL),
//            result = (int)DialogBoxParam((HINSTANCE) MainSubsystem().m_hinstanceResource,
//                                         (LPCWSTR) getResouceName(), parentWindow,
//                                         dialogProc,(::lparam) (::uptr)(::innate_subsystem_macos::Dialog * )this);
//
//            information("Dialog box result is {}", result);
//      });

   }
   else
   {
      
      setVisible(true);
      
      setForeground();

   }

   //return result;
   //return 0;

}


   bool Dialog::isCreated()
   {
//      bool isInit = (HWND) _HWND() != 0;
//
//      if (!isInit) {
//         return false;
//      }
//
//      return !!IsWindow((HWND) _HWND());
      return true;
   }

   bool Dialog::onDrawItem(::wparam controlID, innate_subsystem::draw_item_t * pdrawitem)
   {
      return TRUE;
   }


//   bool Dialog::_onDrawItem(::wparam controlID, LPDRAWITEMSTRUCT pdrawitem)
//   {
//
//      return true;
//
//   }

   bool Dialog::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
{
      
      switch (message) {
         case ::user::e_message_initialize_dialog:
            lresult = onInitDialog();
            break;
         default:
            break;
      }
      return Window::on_window_procedure(lresult, message, wparam, lparam);
      
   }

   void Dialog::onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam)
   {


   }

//   INT_PTR CALLBACK Dialog::dialogProc(HWND hwnd, unsigned int uMsg, WPARAM wparam, LPARAM lparam)
//   {
////      ::innate_subsystem_macos::Dialog * _this = nullptr;
////
////      ::lresult lresult = 0;
////
////      if (::macos::pre_process_window_procedure(lresult, hwnd, uMsg, wparam, lparam))
////      {
////
////          return lresult;
////
////      }
////      BOOL bResult = FALSE;
////
////      if (uMsg == WM_INITDIALOG) {
////         _this = (::innate_subsystem_macos::Dialog *)lparam;
////         //SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)_this);
////         ::cast < ::macos::windowing > pwindowing = ::system()->acme_windowing();
////
////         pwindowing->m_windowmap[hwnd] = _this;
////         _this->_setHWND(hwnd);
////         _this->updateIcon();
////      } else {
////         //_this = (::innate_subsystem_macos::Dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
////         ::cast < ::macos::windowing > pwindowing = ::system()->acme_windowing();
////         ::cast < ::innate_subsystem_macos::Dialog > pdialog = pwindowing->m_windowmap[hwnd];
////         _this = pdialog;
////         if (_this == 0) {
////            return FALSE;
////         }
////      }
////
////      //if (uMsg == WM_APP + 876)
////      //{
////
////      //    ::macos::handle_procedure_message(uMsg, wparam, lparam);
////
////      //    return TRUE;
////
////      //}
////
////      _this->onMessageReceived(uMsg, wparam, lparam);
////
////      switch (uMsg) {
////         case WM_INITDIALOG:
////            bResult = _this->onInitDialog();
////            break;
////         case WM_NOTIFY:
////         {
////            LRESULT lresult = 0;
////            if (_this->_000OnNotify(lresult, wparam, lparam))
////            {
////
////               return lresult;
////
////            }
////         }
////            break;
////         case WM_COMMAND:
////               bResult = _this->onCommand(LOWORD(wparam), HIWORD(wparam));
////            break;
////         case WM_CLOSE:
////            bResult = _this->onClose();
////            break;
////         case WM_DESTROY:
////            bResult = _this->onDestroy();
////            break;
////         case WM_DRAWITEM:
////            bResult = _this->_onDrawItem(wparam, (LPDRAWITEMSTRUCT)lparam);
////            break;
////      }
////
////      return bResult;
//      
//      return 1;
//   }
//
//   char *Dialog::getResouceName()
//   {
////      if (m_resourceId != 0) {
////         return (char *)MAKEINTRESOURCE(m_resourceId);
////      }
//      return m_resourceName;
//   }

   // void Dialog::subControlById(ControlInterface *control, unsigned int id)
   // {
   //    control = GetDlgItem((HWND) _HWND(), id);
   // }

   void Dialog::updateIcon()
   {
//      if (m_hicon) {
//         SetClassLongPtr((HWND) _HWND(), GCLP_HICON, (LONG_PTR)m_hicon);
//      }
   }

   void Dialog::loadIcon(unsigned int id)
   {
//      if (m_hicon) {
//         DeleteObject(m_hicon);
//      }
//      m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
   }

   bool Dialog::setForeground()
   {
      //return this->setForeground();
      return Control::setForeground();
   }

   bool Dialog::onInitDialog()
   {

      auto pcomposite = m_pdialogCallback.m_p;

      return pcomposite->onInitDialog();
   }

   // bool Dialog::_onNotify(int iControl, LPNMHDR lpnmhdr)
   // {
   //    return FALSE;
   // }

   bool Dialog::onCommand(unsigned int controlID, unsigned int notificationID)
   {
      return m_pwindowCallback->onCommand(controlID, notificationID);
      //return FALSE;
   }

   bool Dialog::onDestroy()
   {
      return FALSE;
   }

   bool Dialog::onClose()
   {
      return FALSE;
   }


   bool Dialog::dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      return false;

   }

} // namespace innate_subsystem_macos
