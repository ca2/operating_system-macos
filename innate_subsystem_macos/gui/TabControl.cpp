// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "TabControl.h"
#include "innate_subsystem/gui/Tab.h"
#include "operating_system-macos/acme_windowing_appkit/_interoperability.h"
//#include <commctrl.h>

namespace innate_subsystem_macos
{
   TabControl::TabControl()
   {
   }

   TabControl::~TabControl()
   {
      deleteAllTabs();
   }

   innate_subsystem::TabContainer &TabControl::getTabs()
   {

      return m_tabContainer;

   }
   int TabControl::getTabCount()
   {

      return m_tabContainer.size();

   }

   innate_subsystem::TabInterface *TabControl::getTab(int index)
   {
      if ((index < 0) || ((size_t)index > m_tabContainer.size() - 1)) {
         return NULL;
      }
      return m_tabContainer[index];
   }

   void TabControl::addTab(innate_subsystem::WindowInterface *pwindow, const char *caption)
   {
      auto ptab = createø<::innate_subsystem::TabInterface>();
      ptab->initialize_tab(pwindow, caption);
      m_tabContainer.add(ptab);

      //if(pwindow)
      {

         //::cross_windows::tab_control_set_page_caption(
           // operating_system_window(),
            //pwindow->operating_system_window(),
         //caption);
         //::cast < ::innate_subsystem::WindowInterface > pwindowTab = ptab;
         
         
         ::cross_windows::tab_control_add_page(
            operating_system_window(),
            pwindow->operating_system_window(),
            caption);

      }
//      TCITEM tcitem = {0};
//      tcitem.mask = TCIF_TEXT;
//      TCHAR fixedCaption[255];
//      ::wstring wstr(ptab->getCaption());
//      _tcscpy(&fixedCaption[0], wstr.c_str());
//      tcitem.pszText = fixedCaption;
//      if (TabCtrl_InsertItem((HWND) _HWND(), m_tabContainer.size() - 1, &tcitem) == FALSE) {
//         //
//         // Handle error
//         // ...
//         //
//      }
   }

//void TabControl::addTab( const char *caption)
//{
//   auto ptab = createø<::innate_subsystem::TabInterface>();
//   ptab->initialize_tab(pwindow, caption);
//   m_tabContainer.add(ptab);
//
//   if(pwindow)
//   {
//
//      //::cross_windows::tab_control_set_page_caption(
//        // operating_system_window(),
//         //pwindow->operating_system_window(),
//      //caption);
//      ptab->set_operating_system_window(::cross_windows::tab_control_add_page(
//         operating_system_window(),
//      caption));
//
//   }
////      TCITEM tcitem = {0};
////      tcitem.mask = TCIF_TEXT;
////      TCHAR fixedCaption[255];
////      ::wstring wstr(ptab->getCaption());
////      _tcscpy(&fixedCaption[0], wstr.c_str());
////      tcitem.pszText = fixedCaption;
////      if (TabCtrl_InsertItem((HWND) _HWND(), m_tabContainer.size() - 1, &tcitem) == FALSE) {
////         //
////         // Handle error
////         // ...
////         //
////      }
//}


   void TabControl::showTab(int index)
   {

      auto ptab = getTab(index);

      if (!ptab)
      {
      
         return;
         
      }

      auto iSelectedTab = getSelectedTabIndex();
      
      auto ptabSelected = getTab(iSelectedTab);

      if (ptabSelected && ptabSelected != ptab)
      {
      
         ptabSelected->setVisible(false);
         
      }
      
      ::cross_windows::tab_control_select_item(operating_system_window(), index);
      
      ptab->setVisible(true);
      
      m_iSelectedTab = index;
      
   }


   void TabControl::showTab(innate_subsystem::WindowInterface *pwindow)
   {
      for (size_t i = 0; i < m_tabContainer.size(); i++) {
         if (m_tabContainer[i]->getWindow() == pwindow) {
            showTab((int)i);
            return;
         }
      }
      ASSERT(FALSE);
   }


   void TabControl::moveWindowToTabControl(innate_subsystem::WindowInterface *pwindow)
   {

      if(!pwindow)
      {

         return;

      }

      auto operatingsystemwindowTabControl = operating_system_window();
      auto operatingsystemwindowPage = pwindow->operating_system_window();

      if(!operatingsystemwindowTabControl.is_set()
         || !operatingsystemwindowPage.is_set())
      {

         return;

      }

      ::cross_windows::move_window_to_tab_control(
         operatingsystemwindowTabControl,
         operatingsystemwindowPage);

//      POINT first, last;
//
//      this->adjustRect(rectangle);
//
//      first.x = rectangle.left;
//      first.y = rectangle.top;
//      last.x = rectangle.right;
//      last.y = rectangle.bottom;
//
//      HWND hwndFrom = ::as_HWND(this->operating_system_window());
//      HWND hwndTo = ::as_HWND(pwindow->operating_system_window());
//
//      MapWindowPoints(hwndFrom, hwndTo, &first, 1);
//      MapWindowPoints(hwndFrom, hwndTo, &last, 1);
//
//      MoveWindow(hwndTo,
//                 first.x, first.y, last.x - first.x, last.y - first.y, true);

   }


   void TabControl::deleteAllTabs()
   {
      // for (size_t i = 0; i < m_tabContainer.size(); i++) {
      //    Tab *tab = m_tabContainer.at(i);
      //    delete tab;
      // }
      m_tabContainer.clear();
      m_iSelectedTab = -1;
      //TabCtrl_DeleteAllItems((HWND) _HWND());
   }

   void TabControl::removeTab(int index)
   {
            auto ptab = getTab(index);

            if(ptab && ptab->getWindow())
            {

               ::cross_windows::tab_control_erase_page(
                  operating_system_window(),
                  ptab->getWindow()->operating_system_window());

            }

      //int i = 0;
      //for (TabContainer::iterator it = m_tabContainer.begin(); it != m_tabContainer.end(); it++) {
        // if (i == index) {
            //delete *it;
            m_tabContainer.erase_at(index);
            if (m_iSelectedTab == index) {
               m_iSelectedTab = -1;
            } else if (m_iSelectedTab > index) {
               --m_iSelectedTab;
            }
            //TabCtrl_DeleteItem((HWND) _HWND(), index);
        //    break;
         //}
         //i++;
      //}
   }

   int TabControl::getSelectedTabIndex()
   {
      //int page = TabCtrl_GetCurSel((HWND) _HWND());
      //return page;
      auto iSelectedTab =
         ::cross_windows::tab_control_get_selected_item(operating_system_window());

      return iSelectedTab >= 0 ? iSelectedTab : m_iSelectedTab;
   }

   void TabControl::adjustRect(::i32_rectangle &rect)
   {
//      RECT rc;
//      GetClientRect((HWND) _HWND(), &rc);
//      TabCtrl_AdjustRect((HWND) _HWND(), FALSE, &rc);
//      ::copy(&rect, &rc);

   }

   bool TabControl::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

//      if (message == WM_APP + 125)
//      {
//
//         int iId = (int) ::GetWindowLongPtr((HWND) this->_HWND(), GWLP_ID);
//
//         ::cast < ::innate_subsystem_macos::Window > pwindowParent = getParent();
//
//         pwindowParent->_setChildControlType(iId, ::innate_subsystem::e_control_tab);
//         pwindowParent->_addChildNotification(iId, TCN_SELCHANGE);
//         pwindowParent->_addChildNotification(iId, TCN_SELCHANGING);
//
//         lresult = 0;
//         return true;
//
//      }
//      else if (message == WM_DESTROY)
//      {
//
//         m_tabContainer.clear();
//
//      }

      return Control::on_window_procedure(lresult, message, wparam, lparam);

   }


   bool TabControl::onTabNotification(windows_reflect_notify_t & notify)
   {
//
//      switch (notify.m_lpnmhdr->code)
//   {
//      case TCN_SELCHANGE:
//      {
//         _001OnTabChanged();
//         break;
//      }
//      case TCN_SELCHANGING:
//      {
//
//         bool bOk = true;
//
//         bool bHandled = _001OnTabChanging(bOk);
//
//         if (bHandled)
//         {
//
//            notify.m_lresult = bOk ? TRUE : FALSE;
//
//            notify.m_bHandled = true;
//
//         }
//
//         break;
//      }
//         break;
//   }


      return false;
   }

   void TabControl::_000OnNotifyReflect(windows_reflect_notify_t & notify)
   {

//      switch (notify.m_lpnmhdr->code)
//      {
//         case TCN_SELCHANGE:
//         {
//            _001OnTabChanged();
//            break;
//         }
//         case TCN_SELCHANGING:
//         {
//
//            bool bOk = true;
//
//            bool bHandled = _001OnTabChanging(bOk);
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
//         break;
//        }

   }

} // namespace innate_subsystem_macos
