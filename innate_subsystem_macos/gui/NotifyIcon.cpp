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
//
#include "framework.h"
#include "NotifyIcon.h"
#include "drawing/Icon.h"
//#include <shellapi.h>

// namespace macos
// {
namespace innate_subsystem_macos
{
   NotifyIcon::NotifyIcon()
   : m_pStatusItem(nullptr),
     m_pStatusItemTarget(nullptr),
     m_visible(false)
   {
//      memset(&m_nid, 0, sizeof(NOTIFYICONDATA));
//
//#if (WINVER > 0x0500)
//      m_nid.cbSize = NOTIFYICONDATA_V2_SIZE;
//#else
//      m_nid.cbSize = NOTIFYICONDATA_V1_SIZE;
//#endif
      //if (showAfterCreation) {
        // show();
      //}
   }

   NotifyIcon::~NotifyIcon()
   {
      main_send([this]()
      {
         __destroy_status_item();
      });
   }


   void NotifyIcon::initialize_notify_icon(bool showAfterCreation)
//: NotifyIconWindow(), m_icon(0), m_visible(showAfterCreation)
   {
      if (showAfterCreation)
      {
         show();
      }
   }

   void NotifyIcon::show()
   {
      main_send([this]()
      {
         __create_status_item();
         m_visible = true;
      });
   }

   void NotifyIcon::hide()
   {
      main_send([this]()
      {
         __destroy_status_item();
         m_visible = false;
      });
   }

   // const IconI *NotifyIcon::getIcon() const
   // {
   //    return m_icon;
   // }

   bool NotifyIcon::isVisible()
   {
      return m_visible;
   }

   void NotifyIcon::setIcon(::innate_subsystem::IconInterface *picon)
   {
      m_picon = picon;

      if (!picon)
      {
         hide();
         return;
      }

      main_send([this]()
      {
         __set_icon();
      });
   }


   innate_subsystem::IconInterface *NotifyIcon::getIcon()
   {

      return m_picon;

   }


   void NotifyIcon::setText(const char *text)
   {
      m_strText = text;

      main_send([this]()
      {
         __set_text(m_strText);
      });
   }

   void
   NotifyIcon::showBalloon(const char *message, const char *caption,
                         unsigned int timeoutMillis)
   {
      ::string strMessage(message);
      ::string strCaption(caption);

      main_send([this, strMessage, strCaption]()
      {
         __show_balloon(strMessage, strCaption);
      });
   }


   void NotifyIcon::on_native_left_button_down()
   {
      onNotifyIconLeftButtonDown();
   }


   void NotifyIcon::on_native_right_button_up()
   {
      onNotifyIconRightButtonUp();
   }
} // namespace innate_subsystem_macos
//} // namespace macos
