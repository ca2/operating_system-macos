#include "framework.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"


#include "acme/_operating_system.h"


#include <fcntl.h>

#include <unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>

#define hFileNull -1
//::e_status translate_unix_error(int error)
//{
//
//   switch(error)
//   {
//   case 0:
//      return ::success;
//   case ENOENT:
//      return error_file_not_found;
//   default:
//      return error_failed;
//   }
//
//}


namespace acme_macos
{


//   bool file_get_status(::file::file_status & status, const ::file::path & path)
//   {
//
//      struct ::stat st;
//
//      if(stat(path, &st) == -1)
//      {
//
//         return false;
//
//      }
//
//       ::copy(&status, &st);
//
////      status.m_attribute = 0;
////
////      status.m_filesize = st.st_size;
////
////      ::copy(&status.m_timeModification, &st.st_mtimespec);
////      ::copy(&status.m_timeAccess, &st.st_atimespec);
////      ::copy(&status.m_timeCreation, st.st_ctimespec);
////
////      if (status.m_timeCreation < 0_s)
////      {
////
////         status.m_timeCreation = status.m_timeModification;
////
////      }
////
////      if (status.m_timeAccess < 0_s)
////      {
////
////         status.m_timeAccess = status.m_timeModification;
////
////      }
//
//      return true;
//
//   }


   file::file()
   {

//      m_iFile = (::u32) hFileNull;
//      //m_iPutCharacterBack = -1;

   }


   file::~file()
   {

//      if (m_iFile != hFileNull)
//      {
//
//         close();
//
//      }

   }


//   void file::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception)
//   {
//
//      if(m_iFile != hFileNull)
//      {
//
//         close();
//
//      }
//
//      ASSERT_VALID(this);
//
//      //ASSERT(__is_valid_string(lpszFileName));
//
//      //eopen -= ::file::e_open_binary;
//
//      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
//      {
//
//         acmedirectory()->create(path.folder());
//
//      }
//
//      m_iFile = (::u32)hFileNull;
//
//      m_path.empty();
//
//      m_path     = path;
//
//      ASSERT(::file::e_open_share_compat == 0);
//
//      // ::collection::map read/write mode
//      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
//
//      ::u32 dwFlags =  0;
//
//      switch (eopen & 3)
//      {
//      case ::file::e_open_read:
//         dwFlags |=  O_RDONLY;
//         break;
//      case ::file::e_open_write:
//         dwFlags |=  O_WRONLY ;
//         break;
//      case ::file::e_open_read_write:
//         dwFlags |=  O_RDWR;
//         break;
//      default:
//         dwFlags |=  O_RDONLY;
//         break;
//      }
//
//      switch (eopen & 0x70)    // ::collection::map compatibility mode to exclusive
//      {
//      default:
//         ASSERT(false);  // invalid share mode?
//      case ::file::e_open_share_compat:
//      case ::file::e_open_share_exclusive:
//         break;
//      case ::file::e_open_share_deny_write:
//         break;
//      case ::file::e_open_share_deny_read:
//         break;
//      case ::file::e_open_share_deny_none:
//         break;
//      }
//
//      if (eopen & ::file::e_open_create)
//      {
//
//         dwFlags |= O_CREAT;
//
//         if(!(eopen & ::file::e_open_no_truncate))
//         {
//
//            dwFlags |= O_TRUNC;
//
//         }
//
//      }
//
//      ::u32 dwPermission = 0;
//
//      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
//      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;
//      dwPermission |= S_IROTH | S_IXOTH;
//
//      i32 hFile;
//
//      hFile = ::open(m_path, dwFlags, dwPermission);
//
//      if(hFile == hFileNull)
//      {
//
//         int iErrNo = errno;
//
//         m_estatus = errno_status(iErrNo);
//
//          auto errorcode = errno_error_code(iErrNo);
//
//          m_iFile = hFileNull;
//
//          set_nok();
//
//          RETURN_OR_THROW(
//eopen & ::file::e_open_no_exception_on_open,
//                          ppfileexception,  ::file::exception,
//                          m_estatus, {errorcode}, m_path, m_eopen, "!open");
//
//         //if(!(eopen & ::file::e_open_no_exception_on_open))
//         //{
//
////            if(m_estatus != error_file_not_found && m_estatus != error_path_not_found)
////            {
////
////               throw ::exception(::error_io);
////
////            }
////
////         if (hFile == -1)
////         {
////
////            estatus = ::get_last_status();
//
////            return estatus;
//            //throw ::file::exception(m_estatus, errorcode, m_path, "!open");
//
//             //throw_errno_exception(m_path, m_eopen, "!open");
//
////         }
//         //}
//
//         //return;
//
//      }
//
//      m_iFile = (i32)hFile;
//
//      m_eopen = eopen;
//
//      set_ok_flag();
//
//      m_estatus = ::success;
//
//      //return ::success;
//
//   }
//
//
//   memsize file::read(void * lpBuf, memsize nCount)
//   {
//
//      ASSERT_VALID(this);
//
//      //ASSERT(m_iFile != (::u32)hFileNull);
//
//      if (nCount == 0)
//      {
//
//         return 0;   // avoid Win32 "null-read"
//
//      }
//
////      if(m_iPutCharacterBack >= 0)
////      {
////
////         auto p = (byte *) lpBuf;
////
////         *p = (::byte) m_iPutCharacterBack;
////
////         nCount--;
////
////         m_iPutCharacterBack = -1;
////
////         if(nCount <= 0)
////         {
////
////            return 1;
////
////         }
////
////         p++;
////
////         lpBuf = p;
////
////      }
//
//      ASSERT(lpBuf != nullptr);
//
//      ASSERT(::is_memory_segment_ok(lpBuf, nCount));
//
//      memsize pos = 0;
//
//      memsize sizeRead = 0;
//
//      memsize readNow;
//
//      while(nCount > 0)
//      {
//
//         readNow = (size_t) minimum(0x7fffffff, nCount);
//
//         auto iRead = ::read(m_iFile, &((byte *)lpBuf)[pos], readNow);
//
//         if(iRead < 0)
//         {
//
//            i32 iErrNo = errno;
//
//            auto errorcode = errno_error_code(iErrNo);
//
//            auto estatus = errno_status(iErrNo);
//
//            if(iErrNo == EAGAIN)
//            {
//
//            }
//
//            throw ::file::exception(estatus, errorcode, m_path, "::read < 0");
//
//         }
//         else if(iRead == 0)
//         {
//
//            break;
//
//         }
//
//         if(iRead > nCount)
//         {
//
//            nCount = 0;
//
//         }
//         else
//         {
//
//            nCount -= iRead;
//
//         }
//
//         pos += iRead;
//
//         sizeRead += iRead;
//
//      }
//
//      return sizeRead;
//
//   }
//
//
//   void file::write(const void * lpBuf, memsize nCount)
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      if (nCount == 0)
//      {
//
//         return;
//
//      }
//
//      ASSERT(lpBuf != nullptr);
//
//      ASSERT(::is_memory_segment_ok(lpBuf, nCount, false));
//
//      memsize pos = 0;
//
//      while(nCount > 0)
//      {
//
//         auto iWrite = ::write(m_iFile, &((const byte *)lpBuf)[pos], (size_t) minimum(0x7fffffff, nCount));
//
//         if(iWrite < 0)
//         {
//
//            i32 iErrNo = errno;
//
//            auto errorcode = errno_error_code(iErrNo);
//
//            auto estatus = errno_status(iErrNo);
//
//            throw ::file::exception(estatus, errorcode, m_path, "::write < 0");
//
//         }
//
//         nCount -= iWrite;
//
//         pos += iWrite;
//
//      }
//
//   }
//
//
//   void file::translate(filesize offset, ::enum_seek nFrom)
//   {
//
//      if(m_iFile == (::u32)hFileNull)
//      {
//
//         i32 iErrNo = errno;
//
//         auto errorcode = errno_error_code(iErrNo);
//
//         auto estatus = errno_status(iErrNo);
//
//         throw ::file::exception(estatus, errorcode, m_path, "m_iFile == hFileNull");
//
//      }
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      ASSERT(nFrom == ::e_seek_set || nFrom == ::e_seek_from_end || nFrom == ::e_seek_current);
//
//      ASSERT(::e_seek_set == SEEK_SET && ::e_seek_from_end == SEEK_END && ::e_seek_current == SEEK_CUR);
//
//      ::i32 lLoOffset = offset & 0xffffffff;
//
//      filesize posNew = ::lseek(m_iFile, lLoOffset, (::u32)nFrom);
//
//      if(posNew < 0)
//      {
//
//
//         i32 iErrNo = errno;
//
//         auto errorcode = errno_error_code(iErrNo);
//
//         auto estatus = errno_status(iErrNo);
//
//         throw ::file::exception(estatus, errorcode, m_path, "lseek < 0");
//
//      }
//
//      //return posNew;
//
//   }
//
//
//   filesize file::get_position() const
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      ::i32 lLoOffset = 0;
//
//      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);
//
//      if(pos < 0)
//      {
//
//         i32 iErrNo = errno;
//
//         auto errorcode = errno_error_code(iErrNo);
//
//         auto estatus = errno_status(iErrNo);
//
//         throw ::file::exception(estatus, errorcode, m_path, "lseek < 0");
//
//      }
//
//      return pos;
//
//   }
//
//
//   void file::flush()
//   {
//
//   }
//
//
//   void file::close()
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      bool bError = false;
//
//      if (m_iFile != (::u32)hFileNull)
//      {
//
//         bError = ::close(m_iFile) != 0;
//
//      }
//
//      m_iFile = (::u32) hFileNull;
//
//      m_path.empty();
//
//      if (bError)
//      {
//
//         i32 iErrNo = errno;
//
//         auto errorcode = errno_error_code(iErrNo);
//
//         auto estatus = errno_status(iErrNo);
//
//         throw ::file::exception(estatus, errorcode, m_path, "close != 0");
//
//      }
//
//   }
//
//
//   void file::lock(filesize dwPos, filesize dwCount)
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//   }
//
//
//   void file::unlock(filesize dwPos, filesize dwCount)
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//   }
//
//
//   void file::set_size(filesize dwNewLen)
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      int iFtruncateResult = ::ftruncate(m_iFile, dwNewLen);
//
//      if(iFtruncateResult != 0)
//      {
//
//         i32 iErrNo = errno;
//
//         auto errorcode = errno_error_code(iErrNo);
//
//         auto estatus = errno_status(iErrNo);
//
//         throw ::file::exception(estatus, errorcode, m_path, "ftruncate != 0");
//
//      }
//
//   }
//
//
//   filesize file::size() const
//   {
//
//      ASSERT_VALID(this);
//
//      filesize dwLen, dwCur;
//
//      // seek is a non const operation
//      file * pFile = (file*)this;
//
//      dwCur = pFile->get_position();
//
//      pFile->seek_to_end();
//
//      dwLen = pFile->get_position();
//
//      pFile->set_position(dwCur);
//
//      return dwLen;
//
//   }
//
//
////   void file::assert_ok() const
////   {
////
////      ::file::file::assert_ok();
////
////   }
////
////
////   void file::dump(dump_context & dumpcontext) const
////   {
////
////      ::file::file::dump(dumpcontext);
////
////      dumpcontext << "with handle " << (::u32)m_iFile;
////      dumpcontext << " and name \"" << m_path << "\"";
////      dumpcontext << "\n";
////
////   }
//
//
////   static const char * rgszFileExceptionCause[] =
////   {
////
////      "none",
////      "matter",
////      "fileNotFound",
////      "badPath",
////      "tooManyOpenFiles",
////      "accessDenied",
////      "invalidFile",
////      "eraseCurrentDir",
////      "directoryFull",
////      "badSeek",
////      "hardIO",
////      "sharingViolation",
////      "lockViolation",
////      "diskFull",
////      "endOfFile",
////
////   };
////
////
////   static const char szUnknown[] = "unknown";
////
//
//   ::file::path file::get_file_path() const
//   {
//
//      ASSERT_VALID(this);
//
//      return m_path;
//
//   }
//
//
//   ::file::file_status file::get_status() const
//   {
//
//      ASSERT_VALID(this);
//
//      rStatus.m_strFullName = m_path;
//
//      if (m_iFile != hFileNull)
//      {
//
//         struct ::stat st;
//
//         if(fstat(m_iFile, &st) == -1)
//         {
//
//            return false;
//
//         }
//
//
//          ::copy(&status,  &st);
//
//
//      }
//
//      return true;
//
//   }
//
//
//   bool file::is_opened() const
//   {
//
//      return m_iFile != hFileNull;
//
//   }
//
//
//   void file::set_file_path(const ::file::path & path)
//   {
//
//      ASSERT_VALID(this);
//
//      ASSERT(__is_valid_string(path));
//
//      m_path = path;
//
//   }
//
//
////   int file::put_character_back(int iCharacter)
////   {
////
////      m_iPutCharacterBack = iCharacter;
////
////      return m_iPutCharacterBack;
////
////   }
//

} // namespace acme_macos



