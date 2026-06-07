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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
//#include "subsystem_macos/_common_header.h"
#include "PipeServer.h"
#include "DynamicLibrary.h"
#include "File.h"
#include "acme/platform/node.h"
#include "subsystem/platform/Exception.h"
//#include "Environment.h"

#include <cerrno>
#include <cctype>
#include <cstring>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

namespace
{

   ::string macos_pipe_path(const ::scoped_string & scopedstrName)
   {
      ::string strName(scopedstrName);
      std::string name(strName.c_str());

      if (!name.empty() && name[0] == '/')
      {
         return strName;
      }

      for (auto & ch : name)
      {
         if (!(isalnum((unsigned char) ch) || ch == '_' || ch == '-' || ch == '.'))
         {
            ch = '_';
         }
      }

      ::string strPath;
      strPath.format("/tmp/subsystem_macos_{}.sock", name.c_str());
      return strPath;
   }

   void throw_errno(const char * pszWhat)
   {
      ::string strMessage;
      strMessage.format("{} failed, errno = {} ({})", pszWhat, errno, strerror(errno));
      throw ::subsystem::Exception(strMessage);
   }

} // namespace

namespace subsystem_macos
{
//   pointer < ::subsystem_macos::DynamicLibrary> PipeServer::s_pdynamiclibraryKernel32;
//
//   pGetNamedPipeClientProcessId PipeServer::s_GetNamedPipeClientProcessId = 0;
//   bool PipeServer::s_bInitialized = false;

   PipeServer::PipeServer()
   : //m_milliseconds(0),
     //m_serverPipe(INVALID_HANDLE_VALUE),
     m_bufferSize(0),
     m_bUnlinkPipeName(false)
   {


   }


   void PipeServer::initialize_pipe_server(const scoped_string& scopedstrName, unsigned int bufferSize, ::subsystem::SecurityAttributesInterface* secAttr, const class ::time & time)
   {
   //
   // }
   //
   //
   // const ::scoped_string & scopedstrName, unsigned int bufferSize,
   //                        ::subsystem::SecurityAttributesInterface *secAttr,
   //                        DWORD milliseconds)
    m_time = time;
     //m_psecurityattributes = secAttr;
     //m_serverPipe(INVALID_HANDLE_VALUE),
     m_bufferSize = bufferSize;
   //{
//      if (!s_bInitialized) {
//         s_initialize();
//      }

      m_pipeName = macos_pipe_path(scopedstrName);

      createServerPipe();
   }

   void PipeServer::createServerPipe()
   {
      if (m_pfileServerPipe && ::is_ok(m_pfileServerPipe))
      {
         return;
      }

      if (m_pipeName.is_empty())
      {
         throw ::subsystem::Exception("Cannot create pipe server without a pipe name");
      }

      sockaddr_un address;
      memset(&address, 0, sizeof(address));
      address.sun_family = AF_UNIX;

      if (m_pipeName.length() >= sizeof(address.sun_path))
      {
         ::string strMessage;
         strMessage.format("Pipe socket path is too long: {}", m_pipeName);
         throw ::subsystem::Exception(strMessage);
      }

      int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
      if (fd < 0)
      {
         throw_errno("socket");
      }

      try
      {
         strncpy(address.sun_path, m_pipeName.c_str(), sizeof(address.sun_path) - 1);
         ::unlink(address.sun_path);

         if (::bind(fd, (sockaddr *) &address, sizeof(address)) < 0)
         {
            throw_errno("bind");
         }

         m_bUnlinkPipeName = true;
         ::chmod(address.sun_path, 0600);

         if (::listen(fd, SOMAXCONN) < 0)
         {
            throw_errno("listen");
         }

         construct_newø(m_pfileServerPipe);
         m_pfileServerPipe->m_iFd = fd;
         m_pfileServerPipe->m_bOwned = true;
      }
      catch (...)
      {
         ::close(fd);
         throw;
      }
   }

   ::pointer < ::subsystem::NamedPipeInterface > PipeServer::accept()
   {
      if (!m_pfileServerPipe || !::is_ok(m_pfileServerPipe)) {
         createServerPipe();
      }

      int iTimeout = -1;
      if (!m_time.is_infinite())
      {
         iTimeout = (int) m_time.integral_millisecond();
      }

      pollfd pollfd;
      pollfd.fd = m_pfileServerPipe->m_iFd;
      pollfd.events = POLLIN;
      pollfd.revents = 0;

      int iPoll = 0;
      do
      {
         iPoll = ::poll(&pollfd, 1, iTimeout);
      }
      while (iPoll < 0 && errno == EINTR);

      if (iPoll == 0)
      {
         return {};
      }

      if (iPoll < 0)
      {
         throw_errno("poll");
      }

      int fd = -1;
      do
      {
         fd = ::accept(m_pfileServerPipe->m_iFd, nullptr, nullptr);
      }
      while (fd < 0 && errno == EINTR);

      if (fd < 0)
      {
         throw_errno("accept");
      }

      ::pointer < ::subsystem_macos::File > pfilePipe;
      construct_newø(pfilePipe);
      pfilePipe->m_iFd = fd;
      pfilePipe->m_bOwned = true;

      if (!checkOtherSideBinaryName(pfilePipe)) {
         throw ::subsystem::Exception("Pipe client process filename differs from current process");
      }

      // delete is inside ~NamedPipeTransport()
      auto pnamedpipe = createø < ::subsystem::NamedPipeInterface>();

      pnamedpipe->initialize_named_pipe(pfilePipe, m_bufferSize, true);

      return pnamedpipe;
   }

   void PipeServer::close()
   {
      if (m_pfileServerPipe)
      {
         m_pfileServerPipe.release();
      }

      if (m_bUnlinkPipeName && m_pipeName.has_character())
      {
         ::unlink(m_pipeName.c_str());
         m_bUnlinkPipeName = false;
      }

      m_happening.set_happening();
   }

   PipeServer::~PipeServer()
   {
      close();
   }

   void PipeServer::closeConnection()
   {
   }

   void PipeServer::waitForConnect(const class ::time & time)
   {
   }

   void PipeServer::s_initialize()
   {
   }

   bool PipeServer::checkOtherSideBinaryName(::subsystem::FileInterface * pfilePipe)
   {
      auto pfilePipeMacos = pfilePipe->impl<::subsystem_macos::File>();
      return pfilePipeMacos && pfilePipeMacos->m_iFd >= 0;
   }
} // namespace subsystem_macos

