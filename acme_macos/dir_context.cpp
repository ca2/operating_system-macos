#include "framework.h"
#include "dir_context.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/international.h"
//#include "apex/os/_.h"
//#include "apex/os/_os.h"
//#include "apex/xml/_.h"
#include "acme/constant/id.h"

//#include "_.h"

char * ns_user_local_desktop_folder();
char * ns_user_local_documents_folder();
char * ns_user_local_downloads_folder();
char * ns_user_local_music_folder();
char * ns_user_local_image_folder();
char * ns_user_local_video_folder();


namespace acme_macos
{


   dir_context::dir_context()
   {


   }


   dir_context::~dir_context()
   {
   
   
   }


   void dir_context::initialize(::particle * pparticle)
   {
      
      //auto estatus =
      
      ::dir_context::initialize(pparticle);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
      
      auto psystem = system();
      
      //estatus =
      
//      __refer(m_psystem->m_papexsystem->m_pdirsystem, psystem->m_psystem->m_papexsystem->m_pdirsystem);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
      
      //estatus =
      
      m_pfilesystem = psystem->m_pfilesystem;
//      
//      if(!estatus)
//      {
//         
//         return estatus;
//         
//      }
//      
//      return estatus;
      
   }


   void dir_context::init_system()
   {
      
      //auto estatus =
      
      ::dir_context::init_system();
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      ::file::path pathHome;

      pathHome = ::file::path(getenv("HOME"));

      ::file::path str;

      if(pathHome.is_empty())
      {

         pathHome = "~/Library";

         pathHome /= ".default_user";

         str =  pathHome / "ca2";

      }
      else
      {

         str =  pathHome / "Library" / "ca2";

      }

      auto psystem = system();
      
      auto pacmedirectory = psystem->m_pacmedirectory;

      auto strRelative = pacmedirectory->install();
      
      //m_psystem->m_papexsystem->m_pdirsystem->m_strCommonAppData = str / strRelative / "commonappdata";

//      xml::document doc;
//
//      string strPath = ::dir::appdata() / "configuration\\directory.xml";
//
//      string strDocument = pcontext->m_papexcontext->file().as_string(strPath);
//
//      if(doc.load(strDocument))
//      {
//
//         if(doc.root()->get_name() == "directory_configuration")
//         {
//
//            m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder = doc.root()->get_child_value("time");
//
//            m_psystem->m_papexsystem->m_pdirsystem->m_strNetSeedFolder = doc.root()->get_child_value("netseed");
//
//         }
//
//      }

//      if(m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder.is_empty())
//      {
//
//         m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder = ::file::path(getenv("HOME")) /"Library" / "ca2"/"time";
//
//      }

//      if(m_psystem->m_papexsystem->m_pdirsystem->m_strNetSeedFolder.is_empty())
//      {
//
//         m_psystem->m_papexsystem->m_pdirsystem->m_strNetSeedFolder = pacmedirectory->install() / "net";
//
//      }
      
//      pacmedirectory->create(m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder);
//
//      if(!pacmedirectory->is(m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder))
//      {
//
//         throw exception(error_resource);
//
//      }
//
//      ::file::path strTime;
//
//      strTime = m_psystem->m_papexsystem->m_pdirsystem->m_strTimeFolder;
//
//      strTime /= "time";
//
//      pacmedirectory->create(strTime);
//
//      if(!pacmedirectory->is(strTime))
//      {
//
//         throw ::exception(error_resource);
//
//      }

      //str = "/usr/bin";

      //m_psystem->m_papexsystem->m_pdirsystem->m_pathPrograms = str;

      //str = "/usr/share/";

      //m_psystem->m_papexsystem->m_pdirsystem->m_pathCommonAppData = str;
      
      //return estatus;

   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {
      
      ::file::path path;
      
      path = "/";
      
      path.m_etype = ::file::e_type_existent_folder;

      listing.defer_add(path);

      listing.m_straTitle.add("File System");

      return listing;

   }


   bool dir_context::enumerate(::file::listing & listing)
   {
      
      if(::dir_context::enumerate(listing))
      {
         
         return true;
         
      }
      
      auto pacmedirectory = system()->m_pacmedirectory;
      
      if(!pacmedirectory->enumerate(listing))
      {
       
         return false;
         
      }
      
      return true;
      

//      if(listing.m_bRecursive)
//      {
//
//         index iStart = listing.get_size();
//
//         {
//
//            __scoped_restore(listing.m_pathUser);
//
//            __scoped_restore(listing.m_pathFinal);
//
//            __scoped_restore(listing.m_eextract);
//
//            if(::dir_context::ls(listing))
//            {
//
//               return true;
//
//            }
//
//            ::file::listing dira;
//
//            get_app()->m_papplication->dir().ls_dir(dira, listing.m_pathFinal);
//
//            for(i32 i = 0; i < dira.get_count(); i++)
//            {
//
//               ::file::path dir_context = dira[i];
//
//               if(dir_context == listing.m_pathFinal)
//                  continue;
//
//               listing.m_pathUser.Empty();
//               listing.m_pathFinal = dir_context;
//
//               if(listing.m_eextract != extract_all)
//               {
//
//                  listing.m_eextract = extract_none;
//
//               }
//
//               get_app()->m_papplication->dir().ls(listing);
//
//            }
//
//         }
//
//         ::file::path_array  straPath;
//
//         auto pacmedirectory = m_psystem->m_pacmedirectory;
//
//         pacmedirectory->ls(straPath, listing.m_pathFinal);
//
////            file_find file_find;
//
//         //          bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;
//
//         for(auto & strPath : straPath)
//         {
//
//            bool bDir = is(strPath);
//
//            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
//            {
//
//               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
//                  continue;
//
//               listing.add(strPath);
//
//               listing.last().m_iDir = bDir ? 1 : 0;
//
//            }
//
//         }
//
//         for(index i = iStart; i < listing.get_size(); i++)
//         {
//
//            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;
//
//         }
//
//      }
//      else
//      {
//
//         if(::dir_context::ls(listing))
//         {
//
//            return true;
//
//         }
//
//         ::file::path_array  straPath;
//
//         auto pacmedirectory = m_psystem->m_pacmedirectory;
//
//         pacmedirectory->ls(straPath, listing.m_pathFinal);
//
//         // file_find file_find;
//
//         // bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;
//
//         for(auto & strPath : straPath)
//         {
//
//            bool bDir = is(strPath);
//
//            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
//            {
//
//               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
//                  continue;
//
//               listing.add(strPath);
//
//               listing.last().m_iDir = bDir ? 1 : 0;
//
//            }
//
//         }
//
//      }
//
//      return listing;

   }


//   bool dir_context::is(const ::file::path & pathParam)
//   {
//
//      return ::dir_context::is(pathParam);
////      ::file::path path;
////
////      auto pcontext = m_pcontext;
////
////      path = pcontext->m_papexcontext->defer_process_path(pathParam);
////
////      if(::dir_context::is(path))
////      {
////
////         return true;
////
////      }
////
////      auto pacmedirectory = m_psystem->m_pacmedirectory;
////
////      return pacmedirectory->_is(path);
//
//   }


//   bool dir_context::is(const string & strPath)
//   {
//
//      if(::file::system_dir::is(strPath, papp))
//         return true;
//
//      bool bIsDir;
//
//      ::u32 dwLastError;
//
//      if(m_isdirmap.lookup(strPath, bIsDir, dwLastError))
//      {
//
//         if(!bIsDir)
//         {
//
//            set_last_error(dwLastError);
//
//         }
//
//         return bIsDir;
//
//      }
//
//
//      wstring wstrPath;
//
//      //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
//      //wstrPath.alloc(iLen + 32);
//      wstrPath = ::str::international::utf8_to_unicode(strPath);
//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, L"\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }
//
//      bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));
//
//      m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());
//
//      return bIsDir;
//   }


   bool dir_context::name_is(const ::file::path & str)
   {
      //output_debug_string(str);
      strsize iLast = str.length() - 1;
      while(iLast >= 0)
      {
         if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            break;
         iLast--;
      }
      while(iLast >= 0)
      {
         if(str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
            break;
         iLast--;
      }
      if(iLast >= 0)
      {
         while(iLast >= 0)
         {
            if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            {
               iLast++;
               break;
            }
            iLast--;
         }
      }
      else
      {
         return true; // assume empty string is root_ones directory
      }


      bool bIsDir;

      //::u32 dwLastError;

      if(::task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3  && !case_insensitive_ansi_count_compare(&((const char *) str)[iLast - 3], ".zip", 4))
      {
         //m_isdirmap.set(str.Left(iLast + 1), true, 0);
         return true;
      }

      wstring wstrPath;

      //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);

      //wstrPath.alloc(iLen + 32);

      wstrPath = utf8_to_unicode(str(0, iLast + 1));

      //output_debug_string(wstrPath);

//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, unitext("\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }

      bIsDir = ::dir_context::is(unicode_to_utf8(wstrPath));

      //m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? //0 : ::get_last_error());

      return bIsDir;
   }


//   void dir_context::create(const ::file::path & pcsz)
//   {
//
//      if(is(pcsz))
//      {
//
//         return;
//
//      }
//
//      ::file::path_array stra;
//
//      pcsz.ascendants_path(stra);
//
//      for(i32 i = 0; i < stra.get_size(); i++)
//      {
//
//         if(!is(stra[i]))
//         {
//            
//            auto pacmedirectory = m_psystem->m_pacmedirectory;
//            
//            try
//            {
//               
//               pacmedirectory->create(stra[i]);
//               
//            }
//            catch (exception & e)
//            {
//               
//               auto estatus = e.m_estatus;
//
//               if(estatus == error_already_exists)
//               {
//
//                  string str;
//                  str = stra[i];
//                  str.trim_right("\\/");
//                  try
//                  {
//                     
//                     auto pcontext = m_pcontext;
//
//                     pcontext->m_papexcontext->file().erase(str);
//
//                  }
//                  catch(...)
//                  {
//
//                  }
//
//                  str = stra[i];
//
//                  str.trim_right("\\/");
//
//                  try
//                  {
//                     
//                     auto pcontext = m_pcontext;
//
//                     pcontext->m_papexcontext->file().erase(str);
//
//                  }
//                  catch(...)
//                  {
//
//                  }
//
//                  //if(::CreateDirectory(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), nullptr))
//                  
//                  auto pacmedirectory = m_psystem->m_pacmedirectory;
//
//                  pacmedirectory->create(stra[i]);
////                  {
////
////                     //m_isdirmap.set(stra[i], true, 0);
////
////                     goto try1;
////
////                  }
////                  else
////                  {
////
////                     estatus = ::get_last_status();
////
////                  }
//
////
//            //}
//
//               }
//
////               char * pszError;
//////               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *) &pszError, 8, nullptr);
////                              FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *) &pszError, 8, nullptr);
////
////               //information("dir_context::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
////               // xxx               ::LocalFree(pszError);
////               //m_isdirmap.set(stra[i], false);
////            }
////            else
////            {
////               //m_isdirmap.set(stra[i], true, 0);
////            }
//try1:
//
//            if(!is(stra[i]))
//            {
//
//               throw exception(error_failed);
//
//            }
//
//         }
//
//      }
//         
//      }
//      
//      
//
////      return true;
//
//   }


//   bool dir_context::rm(::object * const ::file::path & psz, bool bRecursive)
//   {
//      if(bRecursive)
//      {
//         string_array straPath;
//         string_array straTitle;
//         ls(papp, psz, &straPath, &straTitle);
//         for(i32 i = 0; i < straPath.get_count(); i++)
//         {
//            if(is(straPath[i], papp))
//            {
//               rm(papp, path(psz, straTitle[i]), true);
//            }
//            else
//            {
//               ::unlink(straPath[i]);
//            }
//         }
//      }
//      return ::rmdir(psz) != false;
//   }
//
//
//   string dir_context::name(const char * path1)
//   {
//      const char * psz = path1 + strlen(path1) - 1;
//      while(psz >= path1)
//      {
//         if(*psz != '\\' && *psz != '/' && *psz != ':')
//            break;
//         psz--;
//      }
//      while(psz >= path1)
//      {
//         if(*psz == '\\' || *psz == '/' || *psz == ':')
//            break;
//         psz--;
//      }
//      if(psz >= path1) // strChar == "\\" || strChar == "/"
//      {
//         const char * pszEnd = psz;
//         /*while(psz >= path1)
//          {
//          if(*psz != '\\' && *psz != '/' && *psz != ':')
//          break;
//          psz--;
//          }*/
//         return string(path1, pszEnd - path1 + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//   string dir_context::name(const string & str)
//   {
//
//      strsize iLast = str.get_length() - 1;
//
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//            break;
//         iLast--;
//      }
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//            break;
//         iLast--;
//      }
//      if(iLast >= 0)
//      {
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               break;
//            iLast--;
//         }
//         return str.Left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//
//   class ::file::path & dir_context::path()
//   {
//      return m_path;
//   }



   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & path)
   {
      
      if(path.is_empty())
      {
         
         return "";
         
      }

      if(path[1] == ':')
      {
         
         auto pathFolder = path.folder();
         
         auto pathFolderWithoutDriveLetter = pathFolder(2);
         
         auto pathDriveLetter = pathFolder(0, 2);
         
         ::string str;
         
         str = pathDriveLetter + "\\trash_that_is_not_trash\\";
         
         string strFormat;
         
         ::earth::time time;
         
         time = ::earth::time::now();
         
         strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.year(), time.month(), time.day(), time.hour(), time.minute(), time.second());
         
         str += strFormat;
         
         str += pathFolderWithoutDriveLetter;
         
         return str;
         
      }

      return "";
   }




//   string dir_context::usersystemappdata(::object * const char * lpcszPrefix, const char * pcsz, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      return path(appdata(lpcszPrefix), pcsz, lpcsz2);
//   }
//
//   string dir_context::appdata(::object * const char * pcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "appdata"), pcsz, lpcsz2);
//   }
//
//   string dir_context::userdata(::object * const char * pcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "data"), pcsz, lpcsz2);
//   }

//   ::file::path dir_context::userfolder(::object * pobject)
//   {
//
//      return App(papp).dir_context().userfolder();
//
//   }


//   ::file::path dir_context::default_os_user_path_prefix(::object * pobject)
//   {
//
//      return ::getlogin();
//
//   }


//   string dir_context::default_userappdata(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
//   }
//
//   string dir_context::default_userdata(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "data"), pszRelativePath);
//   }
//
//   string dir_context::default_userfolder(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//
//      return userfolder(papp, pszRelativePath);
//
//      /*      UNREFERENCED_PARAMETER(pobject);
//       string str;
//       SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_APPDATA,
//       false);
//       return path(path(str, "ca2\\user", lpcszPrefix), lpcszLogin, pszRelativePath);*/
//   }
//
//   string dir_context::userquicklaunch(::object * const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      string str;
//      /*SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_APPDATA,
//       false);*/
//      str = path(getenv("HOME"), "Microsoft\\Internet Explorer\\Quick Launch");
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   string dir_context::userprograms(::object * const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      string str;
//      /*      SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_PROGRAMS,
//       false);*/
//
//      str = "/usr/bin";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }
//
//   string dir_context::commonprograms(const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      string str;
//      /*      SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_COMMON_PROGRAMS,
//       false);*/
//      str = "/usr/share/";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   bool dir_context::is_inside_time(const char * pszPath)
//   {
//      return is_inside(time(), pszPath, papp);
//   }
//
//   bool dir_context::is_inside(const char * pszDir, const char * pszPath)
//   {
//      return ::str::case_insensitive_begins(pszDir, pszPath);
//   }
//


   bool dir_context::has_subdir(const ::file::path & pathFolder)
   {
      
      return ::dir_context::has_subdir(pathFolder);

//      ::file::listing stra;
//
//      get_app()->m_papplication->dir().ls_dir(stra, pszDir);
//
//      return stra.has_elements();

   }





//    bool dir_context::is(const ::file::path & lpcszPath)
//    {
//
//        if(::file::system_dir::is(lpcszPath, papp))
//            return true;
//
//        string strPath(lpcszPath);
//
//        if(strPath.get_length() >= MAX_PATH)
//        {
//
//            if(::str::begins(strPath,astr.DoubleBackSlash))
//            {
//
//                strPath = "\\\\?\\UNC" + strPath.Mid(1);
//
//            }
//            else
//            {
//
//                strPath = "\\\\?\\" + strPath;
//
//            }
//
//        }
//
//        ::u32 dwAttrib;
//
//        dwAttrib = windows_get_file_attributes(::str::international::utf8_to_unicode(strPath));
//
//        bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//
//        m_isdirmap.set(lpcszPath, bIsDir, bIsDir ? 0 : ::get_last_error());
//
//        return bIsDir;
//
//    }


   //bool dir_context::is(const ::file::path & strPath)
   //{
   //
   //   if(::file::system_dir::is(strPath, papp))
   //      return true;

   //   bool bIsDir;

   //   u32 uiLastError;

   //   if(m_isdirmap.lookup(strPath, bIsDir, uiLastError))
   //   {
   //      if(!bIsDir)
   //      {
   //         ::set_last_error(uiLastError);
   //      }
   //      return bIsDir;
   //   }

   //   wstring wstrPath;
   //
   //   //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
   //   //wstrPath.alloc(iLen + 32);
   //   wstrPath = ::str::international::utf8_to_unicode(strPath);
   //   if(wstrPath.get_length() >= MAX_PATH)
   //   {
   //      if(::str::begins(wstrPath, L"\\\\"))
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\UNC");
   //      }
   //      else
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\");
   //      }
   //   }
   //   ::u32 dwAttrib;
   //   dwAttrib = windows_get_file_attributes(wstrPath);
   //   /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
   //   {
   //      dwAttrib = GetFileAttributes(strPath);
   //   }*/
   //
   //   bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
   //
   //   m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());

   //   return bIsDir;
   //}

//    bool dir_context::name_is(const ::file::path & str)
//    {
//        //output_debug_string(str);
//        strsize iLast = str.get_length() - 1;
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                break;
//            iLast--;
//        }
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//                break;
//            iLast--;
//        }
//        if(iLast >= 0)
//        {
//            while(iLast >= 0)
//            {
//                if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                {
//                    iLast++;
//                    break;
//                }
//                iLast--;
//            }
//        }
//        else
//        {
//            return true; // assume empty string is root_ones directory
//        }
//
//
//        bool bIsDir;
//
//
//        u32 uiLastError;
//
//        if(m_isdirmap.lookup(str, bIsDir, uiLastError, (i32) iLast))
//        {
//            if(!bIsDir)
//            {
//                ::set_last_error(uiLastError);
//            }
//            return bIsDir;
//        }
//
//
//        if(::get_task() != nullptr && ::get_task()->m_bZipIsDir && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
//        {
//            m_isdirmap.set(str.Left(iLast + 1), true, 0);
//            return true;
//        }
//
//
//
//
//        wstring wstrPath;
//
//        //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);
//
//        //wstrPath.alloc(iLen + 32);
//
//        wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);
//
//        //output_debug_string(wstrPath);
//
//        if(wstrPath.get_length() >= MAX_PATH)
//        {
//            if(::str::begins(wstrPath, L"\\\\"))
//            {
//                ::str::begin(wstrPath, L"\\\\?\\UNC");
//            }
//            else
//            {
//                ::str::begin(wstrPath, L"\\\\?\\");
//            }
//        }
//        ::u32 dwAttrib;
//        dwAttrib = windows_get_file_attributes(wstrPath);
//        /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
//         {
//         dwAttrib = GetFileAttributes(strPath);
//         }*/
//
//        bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//
//        m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::get_last_error());
//
//        return bIsDir;
//    }


   ::file::path dir_context::time()
   {
      
      return system()->m_pdirsystem->m_pathAppData / "time";
      
   }


   ::file::path dir_context::stage()
   {
      
      
      return install() / "stage";
      
   }


   ::file::path dir_context::stageapp()
   {
      
      return stage() / "basis";
      
   }


   ::file::path dir_context::netseed()
   {
      
      return system()->m_pdirsystem->m_pathHome / "netnodenet/net/seed";
      
   }

//   // stage in ca2os spalib
//   ::file::path dir_context::install()
//   {
//
//      single_lock synchronouslock(mutex(), true);
//
//      return m_psystem->m_papexsystem->m_pdirsystem->m_pathCa2;
//
//   }


   ::file::path dir_context::module()
   {

      return system()->acmedirectory()->module();

   }


//   ::file::path dir_context::ca2module()
//   {
//
//      return m_psystem->m_papexsystem->m_pdirsystem->m_pathCa2Module;
//
//   }


//   ::file::path dir_context::time_square(const string & strPrefix,const string & strSuffix)
//   {
//
//      UNREFERENCED_PARAMETER(strPrefix);
//      UNREFERENCED_PARAMETER(strSuffix);
//
//      return time() / "time";
//
//   }


//   ::file::path dir_context::time_log()
//   {
//
//      return appdata() / "log";
//
//   }


//   void dir_context::erase(const ::file::path & psz, bool bRecursive)
//   {
//
//      if(bRecursive)
//      {
//
//         ::file::listing patha;
//
//         get_app()->m_papplication->dir().ls(patha, psz);
//
//         for(auto & path : patha)
//         {
//
//            if(is(path))
//            {
//
//               erase(psz / path.name(), true);
//
//            }
//            else
//            {
//
//               ::unlink(path);
//
//            }
//
//         }
//
//      }
//
//      if(::rmdir(psz) != 0)
//      {
//
//         string strMessage;
//
//         strMessage.format("Failed to rmdir %s", psz.c_str());
//
//         throw exception(error_failed, strMessage);
//         
//      }
//
//   }


   //::file::path dir_context::name(const ::file::path & path1)
   //{
   //   const char * psz = path1 + strlen(path1) - 1;
   //   while(psz >= path1)
   //   {
   //      if(*psz != '\\' && *psz != '/' && *psz != ':')
   //         break;
   //      psz--;
   //   }
   //   while(psz >= path1)
   //   {
   //      if(*psz == '\\' || *psz == '/' || *psz == ':')
   //         break;
   //      psz--;
   //   }
   //   if(psz >= path1) // strChar == "\\" || strChar == "/"
   //   {
   //      const char * pszEnd = psz;
   //      /*while(psz >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }*/
   //      return string(path1, pszEnd - path1 + 1);
   //   }
   //   else
   //   {
   //      return "";
   //   }
   //}

//   ::file::path dir_context::name(const ::file::path & str)
//   {
//
//      strsize iLast = str.get_length() - 1;
//
//      while(iLast >= 0)
//      {
//         if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
//            break;
//         iLast--;
//      }
//      while(iLast >= 0)
//      {
//         if(str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
//            break;
//         iLast--;
//      }
//      if(iLast >= 0)
//      {
//         while(iLast >= 0)
//         {
//            if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
//               break;
//            iLast--;
//         }
//         return str.Left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }


   //class ::file::file_path & dir_context::path()
   //{
   //   return m_path;
   //}

   /*!
    * Print a known folder.
    */
//    ::file::path get_known_folder(REFKNOWNFOLDERID kfid)
//    {
//        ::file::path str;
//        PWSTR pszPath = nullptr;
//        HANDLE hToken = nullptr;
//        ::OpenProcessToken(::GetCurrentProcess(),TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE,&hToken);
//        HRESULT hr = SHGetKnownFolderPath(kfid,0,hToken,&pszPath);
//        if(SUCCEEDED(hr))
//        {
//            str = pszPath;
//            // The calling application is responsible for calling CoTaskMemFree
//            // to free this resource after use.
//            CoTaskMemFree(pszPath);
//        }
//        else
//        {
//        }
//        return str;
//    }




//    ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
//    {
//        if(psz.is_empty())
//            return "";
//
//        if(psz[1] == ':')
//        {
//            string strDir = name(psz);
//            string str;
//            str = strDir.Left(2);
//            str += "\\trash_that_is_not_trash\\";
//            string strFormat;
//            ::datetime::time time;
//            time = ::datetime::time::get_current_time();
//            strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//            str += strFormat;
//            if(strDir.m_pszData[2] == '\\')
//            {
//                str += strDir.Mid(3);
//            }
//            else
//            {
//                str += strDir.Mid(2);
//            }
//            return str;
//        }
//
//        return "";
//    }

   ::file::path dir_context::appdata(const string & strAppId)
   {
      
      return system()->m_pdirsystem->m_pathAppData / strAppId;
      
//      auto psystem = m_psystem;
//
//      auto pacmedirectory = psystem->m_pacmedirectory;
//
//      return pacmedirectory->appdata();

   }


   ::file::path dir_context::commonappdata_root()
   {

      return system()->m_pdirsystem->m_pathAppData;

   }


   ::file::path dir_context::commonappdata()
   {

      return system()->m_pdirsystem->m_pathAppData;

   }


//    ::file::path dir_context::usersystemappdata(::object * pobject,const char * lpcszPrefix)
//    {
//        UNREFERENCED_PARAMETER(pobject);
//        return appdata() / lpcszPrefix;
//    }
//
//    ::file::path dir_context::appdata(::object * pobject)
//    {
//        return userfolder(pobject) / "appdata";
//    }
//
//    ::file::path dir_context::userdata(::object * pobject)
//    {
//        return userfolder(pobject) / "data";
//    }

//    ::file::path dir_context::userfolder(::object * pobject)
//    {
//
//
//
//    }
//
//    ::file::path dir_context::default_os_user_path_prefix(::object * pobject)
//    {
//        UNREFERENCED_PARAMETER(pobject);
//        unichar buf[MAX_PATH];
//        ULONG ulSize = sizeof(buf) / sizeof(unichar);
//        if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
//        {
//            if(!::GetUserNameW(buf, &ulSize))
//            {
//                __memset(buf, 0, sizeof(buf));
//            }
//        }
//        return ::str::international::unicode_to_utf8(buf);
//    }

//    ::file::path dir_context::default_userappdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//        return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata" ;
//    }
//
//    ::file::path dir_context::default_userdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//        return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
//    }
//
//    ::file::path dir_context::default_userfolder(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//
//        return userfolder(pobject);
//
//    }

   ::file::path dir_context::userquicklaunch()
   {

      return system()->m_pdirsystem->m_pathAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path dir_context::userprograms()
   {

      return system()->m_pdirsystem->m_pathAppData;

   }


   ::file::path dir_context::commonprograms()
   {

      return system()->m_pdirsystem->m_pathAppData;

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pathLonger, const ::file::path & pathShorter)
   {

      return pathLonger.case_insensitive_begins(pathShorter);

   }


//    bool dir_context::has_subdir(::object * const ::file::path & pszDir)
//    {
//
//        file_find file_find;
//
//        bool bWorking;
//
//        bWorking = file_find.FindFile(pszDir / "*.*");
//
//        while(bWorking)
//        {
//
//            bWorking = file_find.FindNextFileA();
//
//            if(file_find.IsDirectory() && !file_find.IsDots())
//            {
//
//                return true;
//
//            }
//
//        }
//
//        return false;
//
//    }

   //bool file::GetStatus(const char * lpszFileName,::file::file_status& rStatus)
   //{
   //   // attempt to fully qualify path first
   //   wstring wstrFullName;
   //   wstring wstrFileName;
   //   wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
   //   if(!vfxFullPath(wstrFullName,wstrFileName))
   //   {
   //      rStatus.m_strFullName.Empty();
   //      return false;
   //   }
   //   ::str::international::unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

   //   WIN32_FIND_DATA findFileData;
   //   HANDLE hFind = FindFirstFile((char *)lpszFileName,&findFileData);
   //   if(hFind == INVALID_HANDLE_VALUE)
   //      return false;
   //   VERIFY(FindClose(hFind));

   //   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //   rStatus.m_attribute = (::u8)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //   // get just the low ::u32 of the file size_i32
   //   ASSERT(findFileData.nFileSizeHigh == 0);
   //   rStatus.m_size = (::i32)findFileData.nFileSizeLow;

   //   // convert times as appropriate
   //   rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
   //   rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
   //   rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);

   //   if(rStatus.m_ctime.get_time() == 0)
   //      rStatus.m_ctime = rStatus.m_mtime;

   //   if(rStatus.m_atime.get_time() == 0)
   //      rStatus.m_atime = rStatus.m_mtime;

   //   return true;
   //}


   ::file::path dir_context::home()
   {

      return system()->m_pdirsystem->m_pathHome;

   }


   ::file::path dir_context::desktop()
   {

      return ::string_from_strdup(ns_user_local_desktop_folder());


   }


   ::file::path dir_context::document()
   {

      return ::string_from_strdup(ns_user_local_documents_folder());


   }

   ::file::path dir_context::download()
   {

      return ::string_from_strdup(ns_user_local_downloads_folder());

   }


   ::file::path dir_context::music()
   {

      return ::string_from_strdup(ns_user_local_music_folder());

   }


   ::file::path dir_context::video()
   {

      return ::string_from_strdup(ns_user_local_video_folder());

   }


   ::file::path dir_context::image()
   {

      return ::string_from_strdup(ns_user_local_image_folder());

   }


} // namespace acme_macos



