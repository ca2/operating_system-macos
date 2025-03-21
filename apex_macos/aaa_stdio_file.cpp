#include "framework.h"
#include "_.h"


#include <fcntl.h>


namespace macos
{


   stdio_file::stdio_file()
   {
      
      m_pStream = nullptr;
      
   }


   stdio_file::~stdio_file()
   {

      if (m_pStream != nullptr)
      {

         close();
         
      }
      
   }


   ::extended::status stdio_file::open(const ::file::path & lpszFileName, unsigned int nOpenFlags)
   {

      if ((nOpenFlags & ::file::e_open_defer_create_directory) && (nOpenFlags & ::file::e_open_write))
      {
         
         papplication->dir().mk(::file::path(lpszFileName).folder());
         
      }

      m_pStream = nullptr;
      //if (!::lnx::file::open(lpszFileName, (nOpenFlags & ~::file::e_open_text)))
      // return false;

      //   ASSERT(m_hFile != hFileNull);
      // ASSERT(m_bCloseOnDelete);

      char szMode[4]; // C-runtime open string
      int nMode = 0;

      // determine read/write mode depending on ::ca2::filesp mode
      if (nOpenFlags & ::file::e_open_create)
      {
         if (nOpenFlags & ::file::e_open_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (nOpenFlags & ::file::e_open_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';

      // add '+' if necessary (when read/write modes mismatched)
      if ((szMode[0] == 'r' && (nOpenFlags & ::file::e_open_read_write)) ||
            (szMode[0] != 'r' && !(nOpenFlags & ::file::e_open_write)))
      {
         // current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      int nFlags = O_RDONLY;
      if (nOpenFlags & (::file::e_open_write | ::file::e_open_read_write))
         nFlags ^= O_RDONLY;

      if (nOpenFlags & ::file::e_open_binary)
         szMode[nMode++] = 'b'; // , nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      //int nHandle = _open_osfhandle(m_hFile, nFlags);

      // open a C-runtime stream from that handle
      //if (nHandle != -1)
      m_pStream = fopen(lpszFileName, szMode);


      if (m_pStream == nullptr)
      {
         //::file::exception * pe = get_Fileexception(::error_file, errno, m_strFileName);
         // an error somewhere along the way...
         //if (pException != nullptr)
         {
            //         pException->m_lOsError = errno;
            //         pException->m_cause = ::file::exception::OsErrorToException(errno);
         }

         //::macos::file::Abort(); // close m_hFile

         return ::error_failed;

      }

      m_strFileName = lpszFileName;

      return ::success;

   }


   memsize stdio_file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      //   ASSERT(fx_is_valid_address(lpBuf, nCount));

      size_t nRead = 0;

      if ((nRead = fread(lpBuf, sizeof(unsigned char), nCount, m_pStream)) == 0 && !feof(m_pStream))
         throw ::file::exception(error_file, -1, errno, m_strFileName);
      if (ferror(m_pStream))
      {
         clearerr(m_pStream);
         throw ::file::exception(error_file, -1, errno, m_strFileName);
      }
      return nRead;
   }

   void stdio_file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
      //   ASSERT(fx_is_valid_address(lpBuf, nCount, false));

      if (fwrite(lpBuf, sizeof(unsigned char), nCount, m_pStream) != nCount)
         throw ::file::exception(error_file, -1, errno, m_strFileName);
   }

   void stdio_file::write_string(const char * lpsz)
   {
      ASSERT(lpsz != nullptr);
      ASSERT(m_pStream != nullptr);

      if (fputs(lpsz, m_pStream) == EOF)
         throw ::file::exception(error_disk_full, -1, errno, m_strFileName);
   }

   char * stdio_file::read_string(char * lpsz, unsigned int nMax)
   {
      ASSERT(lpsz != nullptr);
      //   ASSERT(fx_is_valid_address(lpsz, nMax));
      ASSERT(m_pStream != nullptr);

      char * lpszResult = fgets(lpsz, nMax, m_pStream);
      if (lpszResult == nullptr && !feof(m_pStream))
      {
         clearerr(m_pStream);
         throw ::file::exception(error_file, -1, errno, m_strFileName);
      }

      return lpszResult;
   }


   bool stdio_file::read_string(string & rString)
   {

      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const int nMaxSize = 128;
      char * lpsz = rString.get_buffer(nMaxSize);
      char * lpszResult;
      character_count nLen = 0;
      for (;;)
      {
         
         lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
         
         rString.release_buffer();

         // handle error/eof case
         if (lpszResult == nullptr && !feof(m_pStream))
         {
            
            clearerr(m_pStream);
            
            throw ::file::exception(error_file, -1, errno, m_strFileName);
         }

         // if string is read completely or EOF
         if (lpszResult == nullptr ||
               (nLen = strlen(lpsz)) < nMaxSize ||
               lpsz[nLen-1] == '\n')
            break;

         nLen = rString.get_length();
         
         lpsz = rString.get_buffer(nMaxSize + nLen) + nLen;
         
      }

      // remov '\n' from end of string if present
      lpsz = rString.get_buffer(0);
      
      nLen = rString.get_length();
      
      if (nLen != 0 && lpsz[nLen-1] == '\n')
      {
         
         rString.get_buffer(nLen-1);
         
      }

      return lpszResult != nullptr;
      
   }


   filesize stdio_file::seek(filesize lOff, ::enum_seek eseek)
   {
      ASSERT_VALID(this);
      ASSERT(eseek == ::e_seek_set || eseek== ::e_seek_from_end || eseek== ::e_seek_current);
      ASSERT(m_pStream != nullptr);

      int nFrom;
      switch(eseek)
      {
      case ::e_seek_set:
         nFrom = SEEK_SET;
         break;
      case ::e_seek_from_end:
         nFrom = SEEK_END;
         break;
      case ::e_seek_current:
         nFrom = SEEK_CUR;
         break;
      default:
         ::file::throw ::exception(error_bad_seek, -1, m_strFileName);
      }

      if (fseek(m_pStream, lOff, nFrom) != 0)
         throw ::file::exception(error_bad_seek, -1, errno, 
                              m_strFileName);

      long pos = ftell(m_pStream);
      return pos;
   }

   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos == -1)
         throw ::file::exception(error_invalid_file, -1, errno, 
                              m_strFileName);
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
         throw ::file::exception(error_disk_full, -1, errno, 
                              m_strFileName);
   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      int nErr = 0;

      if (m_pStream != nullptr)
         nErr = fclose(m_pStream);

      //   m_hFile = (unsigned int) hFileNull;
//      m_bCloseOnDelete = false;
      m_pStream = nullptr;

      if (nErr != 0)
         throw ::file::exception(error_disk_full, -1, errno, 
                              m_strFileName);
   }

   void stdio_file::Abort()
   {
      ASSERT_VALID(this);

//      if (m_pStream != nullptr && m_bCloseOnDelete)
      if (m_pStream != nullptr)
         fclose(m_pStream);  // close but ignore errors
      //   m_hFile = (unsigned int) hFileNull;
      m_pStream = nullptr;
//      m_bCloseOnDelete = false;
   }


   ::pointer < ::file::file > stdio_file::Duplicate() const
   {

      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;

      return nullptr;

   }


   void stdio_file::LockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;
   }

   void stdio_file::UnlockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;
   }

   void stdio_file::dump(dump_context & dumpcontext) const
   {
      ::macos::file::dump(dumpcontext);

      dumpcontext << "m_pStream = " << (void *)m_pStream;
      dumpcontext << "\n";
   }



   filesize stdio_file::get_length() const
   {
      ASSERT_VALID(this);

      long nCurrent;
      long nLength;
      long nResult;

      nCurrent = ftell(m_pStream);
      if (nCurrent == -1)
         throw ::file::exception(error_invalid_file, -1, errno, 
                              m_strFileName);

      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         throw ::file::exception(error_bad_seek, -1, errno, 
                              m_strFileName);

      nLength = ftell(m_pStream);
      if (nLength == -1)
         throw ::file::exception(error_invalid_file, -1, errno, 
                              m_strFileName);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         throw ::file::exception(error_bad_seek, -1, errno, 
                              m_strFileName);

      return nLength;
   }


} // namespace macos
