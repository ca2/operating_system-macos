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
#include "File.h"




   namespace subsystem_macos
   {

      File::File()
      {
         m_iFd = -1;
         m_bOwned = false;
      }

      File::~File()
      {

         if (m_bOwned && m_iFd != -1)
         {

            auto ret = ::close(m_iFd);

            if (ret)
            {

               error("windows::subsystem::File Close Handle failed");

            }



         }
      }

   void *File::_HANDLE()
   {
      
      throw ::not_implemented();

      return nullptr;

   }

      int File::_fd()
      {

         return m_iFd;

      }


   } // namespace subsystem_macos


CLASS_DECL_SUBSYSTEM_MACOS int as_fd(::subsystem::FileInterface * pfile)
{

   ::cast < ::subsystem_macos::File > pmacossubsystemfile = pfile;

   auto fd = pmacossubsystemfile->m_iFd;

   return fd;

}

CLASS_DECL_SUBSYSTEM_MACOS bool is_ok(const ::subsystem_macos::File * pfile)
{

   if (!::is_set(pfile))
   {

      return false;

   }

   if (pfile->m_iFd < 0)
   {

      return false;

   }


   return true;

}


CLASS_DECL_SUBSYSTEM_MACOS bool is_ok(const ::pointer < ::subsystem_macos::File > & pfile)
{

   return ::is_ok(pfile.m_p);

}
