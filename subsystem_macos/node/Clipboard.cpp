// Copyright (C) 2012 GlavSoft LLC.
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
#include "subsystem_macos/_common_header.h"
#include "Clipboard.h"

char * Clipboard_getString();
bool Clipboard_setString(const char * psz);


namespace subsystem_macos
{
//#import <AppKit/AppKit.h>

Clipboard::Clipboard() //:
   //m_hwnd(nullptr)
{

}


Clipboard::~Clipboard()
{

}


void Clipboard::initialize_clipboard(
   const ::operating_system::window & operatingsystemwindow)
{
   //m_hwnd = operatingsystemwindow;
}


void Clipboard::setHWnd(
   const ::operating_system::window & operatingsystemwindow)
{
   //m_hwnd = operatingsystemwindow;
}


bool Clipboard::getString(::string & str)
{
   
   auto p = Clipboard_getString();
   
   str =  (const char *) p;
   
   free(p);

   str = removeCR(str);

   return true;
}


bool Clipboard::setString(
   const ::scoped_string & scopedstr)
{
   ::string nativeClipboard =
      addCR(scopedstr);

   bool bOk = Clipboard_setString(nativeClipboard);

   return bOk;
}


::string Clipboard::addCR(
   const ::scoped_string & scopedstr)
{
   ::string chars(scopedstr);

   ::string newChars;

   size_t countLF = 0;

   auto p =
      newChars.get_buffer(chars.length() * 2 + 1);

   for(size_t i = 0; i < chars.size(); i++)
   {

      //
      // If LF without preceding CR,
      // insert CR first.
      //
      if((i == 0 || chars[i - 1] != '\r')
         && chars[i] == '\n')
      {

         p[i + countLF] = '\r';

         ++countLF;

      }

      p[i + countLF] = chars[i];

   }

   newChars.release_buffer(chars.size() + countLF);

   return newChars;
}


::string Clipboard::removeCR(
   const ::scoped_string & scopedstr)
{
   ::string chars(scopedstr);

   ::string newChars;

   auto p =
      newChars.get_buffer(chars.length() + 1);

   size_t j = 0;

   for(size_t i = 0; i < chars.size(); i++)
   {

      //
      // Remove CR when followed by LF
      //
      if(chars[i] != '\r'
         || i + 1 == chars.size()
         || chars[i + 1] != '\n')
      {

         p[j] = chars[i];

         ++j;

      }

   }

   newChars.release_buffer(j);

   return newChars;
}} // namespace subsystem_macos
