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
#include "subsystem_macos/_common_header.h"
#include "File.h"
#include "PipeClient.h"
#include "subsystem/node/SystemException.h"

#include "subsystem_macos/node/NamedPipe.h"

#include <cerrno>
#include <cctype>
#include <cstring>
#include <string>
#include <sys/socket.h>
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
      ::error(strMessage);
      throw ::subsystem::Exception(strMessage);
   }

} // namespace

namespace subsystem_macos
{
   PipeClient::PipeClient()
   {
   }

   PipeClient::~PipeClient()
   {


   }

   ::pointer < ::subsystem::NamedPipeInterface >PipeClient::connect(const ::scoped_string & scopedstrName, unsigned int maxPortionSize)
   {
      auto pipeName = macos_pipe_path(scopedstrName);

      sockaddr_un address;
      memset(&address, 0, sizeof(address));
      address.sun_family = AF_UNIX;

      if (pipeName.length() >= sizeof(address.sun_path))
      {
         ::string strMessage;
         strMessage.format("Pipe socket path is too long: {}", pipeName);
         throw ::subsystem::Exception(strMessage);
      }

      int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
      if (fd < 0)
      {
         throw_errno("socket");
      }

      try
      {
         int iNoSigPipe = 1;
         ::setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &iNoSigPipe, sizeof(iNoSigPipe));

         strncpy(address.sun_path, pipeName.c_str(), sizeof(address.sun_path) - 1);

         int iConnect = 0;
         do
         {
            iConnect = ::connect(fd, (sockaddr *) &address, sizeof(address));
         }
         while (iConnect < 0 && errno == EINTR);

         if (iConnect < 0)
         {
            throw_errno("connect");
         }

         ::pointer < ::subsystem_macos::File > pfilePipe;
         construct_newø(pfilePipe);
         pfilePipe->m_iFd = fd;
         pfilePipe->m_bOwned = true;

         auto pnamedpipe = createø < ::subsystem::NamedPipeInterface>();
         pnamedpipe->initialize_named_pipe(pfilePipe, maxPortionSize, false);

         return pnamedpipe;
      }
      catch (...)
      {
         ::close(fd);
         throw;
      }
   }

} // namespace subsystem_macos
