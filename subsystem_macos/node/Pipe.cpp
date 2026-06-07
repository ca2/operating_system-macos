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
#include "Pipe.h"
#include "subsystem/platform/Exception.h"
#include "subsystem_macos/node/File.h"
//#include <crtdbg.h>
//#include "remoting/remoting/win_system/Environment.h"
//#include "remoting/remoting/thread/critical_section_lock.h"

#include <cerrno>
#include <cstring>
#include <unistd.h>

namespace
{

   void throw_io_errno(const char * pszWhat, int fd)
   {
      ::string strMessage;
      strMessage.format("{} failed for pipe fd {}, errno = {} ({})", pszWhat, fd, errno, strerror(errno));
      throw ::io_exception(error_io, strMessage);
   }

} // namespace

namespace subsystem_macos
{
      // Pipe::Pipe(unsigned int maxPortionSize)
      // : m_totalRead(0),
      //   m_totalWrote(0),
      //   m_maxPortionSize(maxPortionSize)
      // {
      // }

      Pipe::Pipe()
: m_totalRead(0),
  m_totalWrote(0),
  m_maxPortionSize(0)
      {
      }

      Pipe::~Pipe()
      {
      }


      void Pipe::initialize_pipe(unsigned int maxPortionSize)
      {
  m_maxPortionSize = maxPortionSize;
      }

      unsigned int Pipe::getMaxPortionSize()
      {
         return m_maxPortionSize;
      }

      memsize Pipe::writeByFile(const void *buffer, memsize len, ::subsystem::FileInterface * pfilePipe)
      {
         if (len <= 0)
         {
            return 0;
         }

         memsize length = len;
         if (m_maxPortionSize != 0 && length > m_maxPortionSize)
         {
            length = m_maxPortionSize;
         }

         memsize totalWritten = 0;

         while (totalWritten < length)
         {
            ssize_t result = 0;

            {
               critical_section_lock al(&m_criticalsectionPipe);
               checkPipeFile(pfilePipe);
               auto fd = ::as_fd(pfilePipe);
               result = ::write(fd, ((const unsigned char *) buffer) + totalWritten, (size_t) (length - totalWritten));

               if (result < 0 && errno != EINTR)
               {
                  throw_io_errno("write", fd);
               }
            }

            if (result < 0)
            {
               continue;
            }

            if (result == 0)
            {
               throw ::io_exception(error_io, "Pipe write returned zero bytes");
            }

            totalWritten += (memsize) result;
         }

         m_totalWrote += totalWritten;

         return totalWritten;
      }

      memsize Pipe::readByFile(void *buffer, memsize len, ::subsystem::FileInterface * pfilePipe)
      {
         if (len <= 0)
         {
            return 0;
         }

         memsize length = len;
         if (m_maxPortionSize != 0 && length > m_maxPortionSize)
         {
            length = m_maxPortionSize;
         }

         ssize_t result = 0;

         do
         {
            critical_section_lock al(&m_criticalsectionPipe);
            checkPipeFile(pfilePipe);
            auto fd = ::as_fd(pfilePipe);
            result = ::read(fd, buffer, (size_t) length);

            if (result < 0 && errno != EINTR)
            {
               throw_io_errno("read", fd);
            }
         }
         while (result < 0 && errno == EINTR);

         if (result == 0)
         {
            throw ::io_exception(error_io, "Pipe peer closed the connection");
         }

         m_totalRead += (memsize) result;

         return (memsize) result;
      }

      void Pipe::checkPipeFile(::subsystem::FileInterface * pfilePipe)
      {
         if (::is_null(pfilePipe) || ::as_fd(pfilePipe) < 0)
         {
            throw ::io_exception(error_io, "Invalid pipe file descriptor");
         }
      }
} // namespace subsystem_macos
