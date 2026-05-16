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
#include "ComboBox.h"
#include "operating_system-macos/acme_windowing_appkit/_interoperability.h"
//#include <Windowsx.h>


//namespace macos
//{
   namespace  innate_subsystem_macos
   {
      ComboBox::ComboBox()
      {
      }

      ComboBox::~ComboBox()
      {
      }

      int ComboBox::addItem(const char *text)
      {
//         auto hwnd = ::as_HWND(operating_system_window());
//         return ComboBox_AddString(hwnd, text);
         return 0;
      }

      int ComboBox::addItem(const char *text, void *tag)
      {
//         int index = addItem(text);
//         setItemData(index, tag);
//         return index;
         return 0;
      }

      void ComboBox::insertItem(int index, const char *text)
      {
         
         auto operatingsystemwindows = operating_system_window();
         
         ::cross_windows::combo_box_insert_string(operatingsystemwindows, index, text);
         
      }

      void ComboBox::insertItem(int index, const char *text, void *tag)
      {
         insertItem(index, text);
         setItemData(index, tag);
      }

      int ComboBox::getItemsCount()
      {
//         auto hwnd = ::as_HWND(operating_system_window());
//         return ComboBox_GetCount(hwnd);
         
         auto operatingsystemwindows = operating_system_window();
         
         auto iCount = ::cross_windows::combo_box_get_count(operatingsystemwindows);

         return iCount;
      }

      void ComboBox::setItemData(int index, void *tag)
      {
//         auto hwnd = ::as_HWND(operating_system_window());
//         ComboBox_SetItemData(hwnd, index, (::lparam)tag);
         
         auto operatingsystemwindows = operating_system_window();
         
         ::cross_windows::combo_box_set_item_data(operatingsystemwindows, index, tag);

      }

      void *ComboBox::getItemData(int index)
      {
//         auto hwnd = ::as_HWND(operating_system_window());
//         return (void *)ComboBox_GetItemData(hwnd, index);
         
         auto operatingsystemwindows = operating_system_window();
         
         auto p = ::cross_windows::combo_box_get_item_data(operatingsystemwindows, index);

         return p;
         
      }

      ::string ComboBox::getItemText(int index)
      {

//         ::wstring wstr;
//
//         auto hwnd = ::as_HWND(operating_system_window());
//
//         size_t length = ComboBox_GetLBTextLen(hwnd, index);
//
//         ComboBox_GetLBText(hwnd, index, wstr.auto_release_buffer(length));
//
//         return wstr;
         
         auto operatingsystemwindows = operating_system_window();
         
         auto str = ::cross_windows::combo_box_get_lb_text(operatingsystemwindows, index);
         
         return str;

      }


      int ComboBox::getSelectedItemIndex()
      {

//         auto hwnd = ::as_HWND(operating_system_window());
//
//         return ComboBox_GetCurSel((HWND) _HWND());
         //return 0;
         auto operatingsystemwindows = operating_system_window();
         
         auto iCurSel = ::cross_windows::combo_box_get_cur_sel(operatingsystemwindows);
         
         return iCurSel;

      }
   

      void ComboBox::setSelectedItem(int index)
      {
         //ComboBox_SetCurSel((HWND) _HWND(), index);
         
         auto operatingsystemwindows = operating_system_window();
         
         ::cross_windows::combo_box_set_cur_sel(operatingsystemwindows, index);

      }

      void ComboBox::deleteItem(int index)
      {
         //ComboBox_DeleteString((HWND) _HWND(), index);
         auto operatingsystemwindows = operating_system_window();
         
         ::cross_windows::combo_box_delete_string(operatingsystemwindows, index);

      }

      void ComboBox::removeAllItems()
      {
         //ComboBox_ResetContent((HWND) _HWND());
         
         auto operatingsystemwindows = operating_system_window();
         
         ::cross_windows::combo_box_reset_content(operatingsystemwindows);

      }
   } // namespace subsystem
//
//} // namespace macos
