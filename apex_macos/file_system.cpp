#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "acme/filesystem/filesystem/acme_directory.h"


#include <sys/stat.h>
#include <ctype.h>
#include <mach-o/dyld.h>


struct PROCESS_INFO_t
{
   
   
   string csProcess;
   u32 dwImageListIndex;
   
   
};


namespace apex_macos
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   void file_system::initialize(::object * pobject)
   {
      
      //auto estatus =
      
      ::file_system::initialize(pobject);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
      
      string str = getenv("HOME");
      
      auto psystem = m_psystem;
      
      auto pacmedirectory = psystem->m_pacmedirectory;

      ::file::path strRelative = pacmedirectory->install();

      string strUserFolderShift;

      if(psystem->has_property("user_folder_relative_path"))
      {

         strUserFolderShift = strRelative / get_app()->payload("user_folder_relative_path").get_string();

      }
      else
      {

         strUserFolderShift = strRelative;

      }

      m_strUserFolder = str / "ca2" / strUserFolderShift;

      //return true;

   }


//   ::e_status file_system::update_module_path()
//   {
//      
//      auto estatus = ::file_system::update_module_path();
//      
//      if(!estatus)
//      {
//         
//         return estatus;
//         
//      }
//
//      m_pathModule = apple_app_module_path();
//
//      m_pathCa2Module = apple_app_module_path();
//
//      return estatus;
//
//   }


} // namespace apex_macos



