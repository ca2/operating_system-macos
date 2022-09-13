#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"

#include <fcntl.h>


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


   bool file_get_status(::file::file_status & status, const ::file::path & path)
   {

      struct ::stat st;
   
      if(stat(path, &st) == -1)
      {
      
         return false;
      
      }

      status.m_attribute = 0;

      status.m_filesize = st.st_size;

      status.m_ctime = ::earth::time(st.st_mtime);
      status.m_atime = ::earth::time(st.st_atime);
      status.m_mtime = ::earth::time(st.st_ctime);

      if (status.m_ctime.get_time() == 0)
      {
      
         status.m_ctime = status.m_mtime;
      
      }

      if (status.m_atime.get_time() == 0)
      {
      
         status.m_atime = status.m_mtime;
      
      }

      return true;
   
   }


   file::file()
   {

      m_iFile = (::u32) hFileNull;
      //m_iPutCharacterBack = -1;

   }


   file::~file()
   {

      if (m_iFile != hFileNull)
      {
         
         close();
         
      }

   }


   void file::open(const ::file::path & lpszFileName, const ::file::e_open & efileopenParam)
   {
      
      ::file::e_open eopen(efileopenParam);

      if(m_iFile != hFileNull)
      {
       
         close();
         
      }

      ASSERT_VALID(this);
      
      ASSERT(__is_valid_string(lpszFileName));

      //eopen -= ::file::e_open_binary;

      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {
         
         m_psystem->m_pacmedirectory->create(file_path_folder(lpszFileName));
         
      }

      m_iFile = (::u32)hFileNull;
      
      m_path.Empty();

      m_path     = lpszFileName;

      ASSERT(::file::e_open_share_compat == 0);

      // ::collection::map read/write mode
      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
      
      ::u32 dwFlags =  0;
      
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwFlags |=  O_RDONLY;
         break;
      case ::file::e_open_write:
         dwFlags |=  O_WRONLY ;
         break;
      case ::file::e_open_read_write:
         dwFlags |=  O_RDWR;
         break;
      default:
         dwFlags |=  O_RDONLY;
         break;
      }

      switch (eopen & 0x70)    // ::collection::map compatibility mode to exclusive
      {
      default:
         ASSERT(false);  // invalid share mode?
      case ::file::e_open_share_compat:
      case ::file::e_open_share_exclusive:
         break;
      case ::file::e_open_share_deny_write:
         break;
      case ::file::e_open_share_deny_read:
         break;
      case ::file::e_open_share_deny_none:
         break;
      }

      if (eopen & ::file::e_open_create)
      {
         
         dwFlags |= O_CREAT;
         
         if(!(eopen & ::file::e_open_no_truncate))
         {
            
            dwFlags |= O_TRUNC;
            
         }
         
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;
      dwPermission |= S_IROTH | S_IXOTH;

      i32 hFile;

      hFile = ::open(m_path, dwFlags, dwPermission);

      if(hFile == hFileNull)
      {

         m_estatus = errno_to_status(errno);
         
         if(!(eopen & ::file::e_open_no_exception_on_open))
         {

//            if(m_estatus != error_file_not_found && m_estatus != error_path_not_found)
//            {
//
//               throw ::exception(::error_io);
//
//            }
//
//         if (hFile == -1)
//         {
//
//            estatus = ::get_last_status();

//            return estatus;
            throw ::exception(m_estatus);

//         }
         }
         
         m_iFile = hFileNull;
         
         set_nok();
         
         return;

      }

      m_iFile = (i32)hFile;
      
      m_eopen = eopen;
      
      set_ok();
      
      m_estatus = ::success;

      //return ::success;

   }


   memsize file::read(void * lpBuf, memsize nCount)
   {
      
      ASSERT_VALID(this);
      
      //ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
      {
         
         return 0;   // avoid Win32 "null-read"
         
      }
      
//      if(m_iPutCharacterBack >= 0)
//      {
//
//         auto p = (byte *) lpBuf;
//
//         *p = (::byte) m_iPutCharacterBack;
//         
//         nCount--;
//
//         m_iPutCharacterBack = -1;
//
//         if(nCount <= 0)
//         {
//
//            return 1;
//
//         }
//
//         p++;
//
//         lpBuf = p;
//
//      }

      ASSERT(lpBuf != nullptr);
      
      ASSERT(__is_valid_address(lpBuf, nCount));

      memsize pos = 0;
      
      memsize sizeRead = 0;
      
      memsize readNow;
      
      while(nCount > 0)
      {

         readNow = (size_t) minimum(0x7fffffff, nCount);

         auto iRead = ::read(m_iFile, &((byte *)lpBuf)[pos], readNow);

         if(iRead < 0)
         {

            i32 iError = errno;

            if(iError == EAGAIN)
            {

            }

            throw ::file::exception(errno_to_status(errno), -1, errno,m_path);

         }
         else if(iRead == 0)
         {
            
            break;
            
         }
         
         if(iRead > nCount)
         {
            
            nCount = 0;
            
         }
         else
         {
            
            nCount -= iRead;
            
         }
         
         pos += iRead;
         
         sizeRead += iRead;
         
      }

      return sizeRead;
      
   }


   void file::write(const void * lpBuf, memsize nCount)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
      {

         return;

      }

      ASSERT(lpBuf != nullptr);
      
      ASSERT(__is_valid_address(lpBuf, nCount, false));

      memsize pos = 0;
      
      while(nCount > 0)
      {
         
         auto iWrite = ::write(m_iFile, &((const byte *)lpBuf)[pos], (size_t) minimum(0x7fffffff, nCount));
         
         if(iWrite < 0)
         {
            
            throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
            
         }
         
         nCount -= iWrite;
         
         pos += iWrite;
         
      }

   }


   filesize file::translate(filesize offset, ::enum_seek nFrom)
   {

      if(m_iFile == (::u32)hFileNull)
      {
         
         throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
         
      }

      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);
      
      ASSERT(nFrom == ::e_seek_set || nFrom == ::e_seek_from_end || nFrom == ::e_seek_current);
      
      ASSERT(::e_seek_set == SEEK_SET && ::e_seek_from_end == SEEK_END && ::e_seek_current == SEEK_CUR);

      ::i32 lLoOffset = offset & 0xffffffff;

      filesize posNew = ::lseek(m_iFile, lLoOffset, (::u32)nFrom);

      if(posNew  == (filesize)-1)
      {
         
         throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
         
      }

      return posNew;
      
   }


   filesize file::get_position() const
   {

      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

      ::i32 lLoOffset = 0;

      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);

      if(pos  == (filesize)-1)
      {
         
         throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
         
      }

      return pos;
      
   }


   void file::flush()
   {

   }


   void file::close()
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      bool bError = false;
      
      if (m_iFile != (::u32)hFileNull)
      {
         
         bError = ::close(m_iFile) != 0;
         
      }

      m_iFile = (::u32) hFileNull;
      
      m_path.Empty();

      if (bError)
      {
         
         throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
         
      }
      
   }


   void file::lock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

   }


   void file::set_size(filesize dwNewLen)
   {

      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

      if (::ftruncate(m_iFile, dwNewLen) == -1)
      {
         
         throw ::file::exception(errno_to_status(errno), -1, errno,m_path);
         
      }
      
   }


   filesize file::get_size() const
   {

      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      file * pFile = (file*)this;
      
      dwCur = pFile->increment_position(0);
      
      dwLen = pFile->seek_to_end();
      
      if(dwCur != (u64)pFile->set_position((filesize) dwCur))
      {

         throw ::exception(error_io, "failed to seek back to the original position on get_length");;

      }

      return (filesize) dwLen;
      
   }


   void file::assert_ok() const
   {

      ::file::file::assert_ok();

   }


   void file::dump(dump_context & dumpcontext) const
   {

      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_iFile;
      dumpcontext << " and name \"" << m_path << "\"";
      dumpcontext << "\n";

   }


//   static const char * rgszFileExceptionCause[] =
//   {
//      
//      "none",
//      "matter",
//      "fileNotFound",
//      "badPath",
//      "tooManyOpenFiles",
//      "accessDenied",
//      "invalidFile",
//      "eraseCurrentDir",
//      "directoryFull",
//      "badSeek",
//      "hardIO",
//      "sharingViolation",
//      "lockViolation",
//      "diskFull",
//      "endOfFile",
//      
//   };
//
//
//   static const char szUnknown[] = "unknown";
//

   ::file::path file::get_file_path() const
   {
      
      ASSERT_VALID(this);

      return m_path;

   }


   bool file::get_status(::file::file_status& rStatus) const
   {

      ASSERT_VALID(this);

      rStatus.m_strFullName = m_path;

      if (m_iFile != hFileNull)
      {

         struct ::stat st;

         if(fstat(m_iFile, &st) == -1)
         {
            
            return false;
            
         }

         rStatus.m_filesize = st.st_size;

         rStatus.m_attribute = 0;

         rStatus.m_ctime = ::earth::time(st.st_mtime);
         rStatus.m_atime = ::earth::time(st.st_atime);
         rStatus.m_mtime = ::earth::time(st.st_ctime);

         if (rStatus.m_ctime.get_time() == 0)
         {
            
            rStatus.m_ctime = rStatus.m_mtime;
            
         }

         if (rStatus.m_atime.get_time() == 0)
         {
            
            rStatus.m_atime = rStatus.m_mtime;
            
         }
         
      }
      
      return true;
      
   }


   bool file::is_opened() const
   {

      return m_iFile != hFileNull;
      
   }


   void file::set_file_path(const ::file::path & path)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(__is_valid_string(path));
      
      m_path = path;
      
   }


//   int file::put_character_back(int iCharacter)
//   {
//
//      m_iPutCharacterBack = iCharacter;
//
//      return m_iPutCharacterBack;
//
//   }


} // namespace acme_macos



