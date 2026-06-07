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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Clipboard2.h"
//#include "acme/operating_system/windows/window.h"
//#include "remoting/node_desktop/NamingDefs.h"
bool Clipboard2_writeToClipBoard(const char * pszText);
char * Clipboard2_readFromClipBoard();

namespace subsystem_macos
{


   ///const HINSTANCE Clipboard2::m_hinst = GetModuleHandle(0);


   Clipboard2::Clipboard2() :
GuiThread("Clpbrd2"),
      //m_hwndNextViewer(0),
       m_clipboardListener(nullptr), m_plogwriter(nullptr)
   {
      //createMessageWindow(    "subsystem::Clipboard2::MessageWindow");
   //   resume();
   }
   
   //Clipboard2::Clipboard2()
   //{
   ////   resume();
   //}

   Clipboard2::~Clipboard2()
   {
   }


void Clipboard2::destroy()
{
   
   ::subsystem::Thread::destroy();
   
   // terminateThread();
   // wait();

}

   void Clipboard2::initialize_clipboard2(::subsystem::ClipboardListener *clipboardListener, ::subsystem::LogWriter * plogwriter)
   {

      //initialize_message_window(m_hinst, "subsystem::Clipboard2::MessageWindow");
      
      //m_hwndNextViewer = nullptr;
      m_clipboardListener = clipboardListener;
      m_plogwriter = plogwriter;

      resumeThread();

   }


   bool Clipboard2::_writeToClipBoard(const ::scoped_string &scopedstrText)
   {
      ::string clipboard(scopedstrText);
      
      Clipboard2_writeToClipBoard(clipboard);
//      if (OpenClipboard((HWND)_HWND()))
//      {
//         EmptyClipboard();
//
//         size_t clipSize = clipboard.length();
//         HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, clipSize);
//         if (hglb)
//         {
//            TCHAR *buff = (TCHAR *)GlobalLock(hglb);
//            memcpy(buff, clipboard, clipSize);
//            GlobalUnlock(hglb);
//
//#ifdef _UNICODE
//            SetClipboardData(CF_UNICODETEXT, hglb);
//#else
//            SetClipboardData(CF_TEXT, hglb);
//
//            // Store locale information in the clipboard as well.
//            HGLOBAL hmemLocale = GlobalAlloc(GMEM_MOVEABLE, sizeof(LCID));
//            if (hmemLocale != NULL)
//            {
//               LCID *pLocale = (LCID *)GlobalLock(hmemLocale);
//               *pLocale = GetSystemDefaultLCID(); // or maybe GetUserDefaultLCID()?
//               GlobalUnlock(hmemLocale);
//               if (SetClipboardData(CF_LOCALE, hmemLocale) == NULL)
//               {
//                  GlobalFree(hmemLocale);
//               }
//            }
//#endif
//         }
//
//         CloseClipboard();
//      }

      return false;
   }

   void Clipboard2::readFromClipBoard(::string &clipDest)
   {
      
      clipDest.clear();
      
      char * p = Clipboard2_readFromClipBoard();
      
      if(!p)
      {
         
         return;
      }
      
      clipDest = p;
      
      free(p);

   }


//
//   void Clipboard2::onTermThread()
//   {
//
//
//
//   }



} // namespace subsystem_macos
 


