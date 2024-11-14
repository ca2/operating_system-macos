// Create on 2021-03-21 20:00 <3ThomasBS_ // for Linux(question)
// Recreated on 2021-05-16 15:05 <3ThomasBS_ // for macOS
#include "framework.h"
#include "directory_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_system.h"


::string macos_get_home();

namespace acme_macos
{

   
   directory_system::directory_system()
   {

      m_pplatformdir = this;

   }


   directory_system::~directory_system()
   {


   }


   void directory_system::initialize(::particle * pparticle)
   {
      
      //auto estatus =
      
      ::directory_system::initialize(pparticle);
      
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      return estatus;

   }


   void directory_system::init_system()
   {

      //auto estatus =
      
      ::directory_system::init_system();
      
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      auto psystem= m_psystem->m_papexsystem;
      
   //      ::file::path pathModule = psystem->m_pfilesystem->m_pathModule;
      
      m_pathHome = getenv("HOME");
      
   //      auto pathCa2 = pathModule - 2;
   //
   //      ::str::case_insensitive_ends_eat(pathCa2, ".app");
   //
   //      m_pathCa2 = pathCa2;
      
      m_pathCa2Config = m_pathHome / "Library/Application Support/ca2";

      //return estatus;
      
   }


   string directory_system::dir_root()
   {

      return home() / ".config/ca2";

   }


   ::file::path directory_system::get_memory_map_base_folder_path() 
   {

      return home() / ".config/ca2/memory_map";

   }


//   ::file::path directory_system::home()
//   {
//
//      return getenv("HOME");
//
//   }


   ::file::path directory_system::program_data()
   {

      return home() / "application";

   }


   ::file::path directory_system::roaming()
   {
      
      auto pathHome = this->home();

      return home() / "Library/Application Support";

   }


   ::file::path directory_system::appdata()
   {

      return roaming() / appid();

   }


//   ::file::path directory_system::public_system()
//   {
//
//      return public_root() / "system";
//
//   }


   ::file::path directory_system::userconfig()
   {

      return ca2roaming() / "system";

   }


   ::file::path directory_system::config()
   {

      return ca2roaming() / "config";

   }


   ::file::path directory_system::local()
   {

      return ca2roaming() / "local";

   }


   ::file::path directory_system::sensitive()
   {

   #ifdef LINUX

      return "C:\\sensitive\\sensitive";

   #else

      return "/sensitive/sensitive";

   #endif

   }







   string directory_system::system_short_name()
   {

   #ifdef _UWP

      return "metro";

   #else

      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

      return file_system()->as_string(pathSystemShortName).trimmed();

   #endif

   }


   ::file::path directory_system::relative(::file::path path)
   {

      path.find_replace(":", "");

      path.case_insensitive_ends_eat(".exe");

      return path;

   }


//   #ifdef _UWP
//
//
//   ::file::path directory_system::app_relative()
//   {
//
//      return "";
//
//   }
//
//
//   #else
//
//
//   ::string directory_system::appid()
//   {
//
//      ::file::path path = file_system()->module();
//
//      path = relative(path);
//
//      return ::transfer(path);
//
//   }
//
//
//   #endif



   ::file::path directory_system::inplace_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef LINUX_DESKTOP

      ::file::path path;

      string strFolder;

      character_count iFind = strAppId.find('/');

      if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
      {

         path = program_files_x86();

      }
      else
      {
         path = program_files_x86();


         path = program_files();

      }

      if (iFind < 0)
      {

         path /= strAppId;

      }
      else
      {

         path /= strAppId.Left(iFind);

         path /= strAppId.Mid(iFind + 1);

      }

      return path;

   #elif defined(ANDROID)

      return pdirectorysystem->roaming();

   #else

      return file_system()->module().folder(4);

   #endif

   }


   ::file::path directory_system::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef LINUX_DESKTOP

      ::file::path path;

      string strFolder;

      character_count iFind = strAppId.find('/');

      path = ca2roaming();

      path /= "_matter";

      return path;

   #elif defined(ANDROID)

      return pdirectorysystem->roaming();

   #else

      return file_system()->module().folder(4);

   #endif


   }


   ::file::path directory_system::install()
   {

      if (m_pathInstallFolder.is_empty())
      {

         return default_install();

      }

      return m_pathInstallFolder;

   }


   ::file::path directory_system::default_install()
   {

   #ifdef ANDROID

      return pdirectorysystem->roaming();

   #elif defined(__APPLE__)

      return file_system()->module().folder(3);

   #else

      return m_psystem->m_pacmepath->app_module().folder(4);

   #endif

   }


   ::file::path directory_system::beforeca2()
   {

      return file_path_folder(install());

   }






   #ifdef LINUX_DESKTOP


   #include <Shlobj.h>


   ::file::path directory_system::program_files_x86()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      return string(wstrModuleFolder);

   }


   ::file::path directory_system::program_files()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);



   }


   #else


   ::file::path directory_system::program_files_x86()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   ::file::path directory_system::program_files()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   #endif


   ::file::path directory_system::stage(string strAppId, string strPlatform, string strConfiguration)
   {

      return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / node()->time_binary_platform(strPlatform) / strConfiguration;

   }


//   #ifdef LINUX


   ::file::path directory_system::home()
   {

      return macos_get_home();

   }


//   #endif


   #if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)


//   ::file::path directory_system::bookmark()
//   {
//
//      auto psystem = m_psystem;
//
//      auto pdirectorysystem = psystem->directory_system();
//
//      return pdirectorysystem->localconfig() / "bookmark";
//
//   }


   #endif


   #ifdef _UWP


   ::file::path directory_system::home()
   {

      return "";

   }


   #endif




   void directory_system::set_path_install_folder(const ::string & strPath)
   {

      m_pathInstallFolder = strPath;

   }


   ::file::path directory_system::bookmark()
   {

      return localconfig() / "bookmark";

   }





   ::file::path directory_system::sys_temp()
   {

      return appdata() / "time";

   }


   //::string directory_system::dir_root()
   //{

   //   return "";

   //}


   //::file::path directory_system::home()
   //{

   //   return "";

   //}


   //::file::path directory_system::program_data()
   //{

   //   return "";

   //}


   ::file::path directory_system::ca2appdata()
   {

      return ca2roaming() / "appdata";

   }



   ::file::path directory_system::public_root()
   {

      return program_data() / "ca2";

   }

   ::file::path directory_system::ca2roaming()
   {

      return roaming() / "ca2";

   }


   ::file::path directory_system::localconfig()
   {

      return ca2roaming() / "localconfig";

   }


   ::file::path directory_system::module()
   {

      return ::directory_system::module();

   }

   //
   //::file::path directory_system::base_module()
   //{
   //
   //   return "";
   //
   //}
   //

   //::file::path directory_system::ca2_module()
   //{
   //
   //   return "";
   //
   //}
   //
   ::file::path directory_system::archive()
   {

      return "";

   }



   ::file::path directory_system::tool()
   {

      return "";

   }


   //::file::path directory_system::roaming()
   //{

   //   return "";

   //}


   ::file::path directory_system::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   {

      ::file::path_array stra;

      stra.add_tokens(pszEnv, ":", false);

      string strCandidate;

      for (int i = 0; i < stra.get_count(); i++)
      {

         strCandidate = stra[i] / pszTopic;

         //if (m_pcontext->m_papexcontext->file().exists(strCandidate))
         if (file_exists(strCandidate))
         {

            return strCandidate;

         }

      }

      return "";

   }


   //::file::path directory_system::get_memory_map_base_folder_path()
   //{

   //   return "";

   //}


   ::file::path directory_system::user_appdata_local()
   {

      //return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

      return home() / ".config";

   }


} // namespace acme_macos


char * ns_get_home();

::string macos_get_home()
{
   
   return ::string_from_strdup(ns_get_home());
   
}
   


