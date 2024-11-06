//
//  file_context.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#include "framework.h"
#include "directory_system.h"
#include "file_context.h"
#include "file_system.h"
#include "acme/platform/system.h"
#include <sys/stat.h>
#include <ctype.h>
#include <mach-o/dyld.h>


//#include "macos.h"
//#include "apex/os/_.h"
//#include "apex/os/_os.h"


string macos_resource_folder();


struct PROCESS_INFO_t
{
   string csProcess;
   u32 dwImageListIndex;
};


namespace acme_macos
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }

   ::payload file_context::length(const ::file::path & pszPath)
   {

      ::payload varRet;


      struct stat stat;

      if(::stat(pszPath, &stat)  == -1)
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = stat.st_size;
      }

      return varRet;

   }


   void file_context::initialize(::particle * pparticle)
   {
      
      //auto estatus =
      
      ::file_context::initialize(pparticle);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      auto psystem = system();

       m_pdirsystem = psystem->directory_system();
      
//      if(!estatus)
//      {
//
//         throw exception(error_wrong_type);
//
//      }
      
      //estatus =
      m_pfilesystem = psystem->m_pfilesystem;
      
//      if(!estatus)
//      {
//         
//         throw exception(error_wrong_type);
//         //return estatus;
//         
//      }
      
//      string str = getenv("HOME");
//
//      ::file::path strRelative = ::dir::install();
//
//      string strUserFolderShift;
//
//      if(get_application()->has_property("user_folder_relative_path"))
//      {
//
//         strUserFolderShift = strRelative / get_application()->command_value("user_folder_relative_path").as_string();
//
//      }
//      else
//      {
//
//         strUserFolderShift = strRelative;
//
//      }
//
//      m_strUserFolder = str / "ca2" / strUserFolderShift;

//      return estatus;

   }




//   ::e_status file_context::update_module_path()
//   {
//
//
////      m_pathModule = apple_app_module_path();
////
////      m_pathCa2Module = ca2_module_dup();
//
//      return true;
//
//   }


   file_pointer file_context::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception)
   {

      return ::file_context::get_file(payloadFile, eopen, ppfileexception);

   }


   void file_context::calculate_main_resource_memory()
   {
      
      ::file::path pathFolder;
      
      pathFolder = macos_resource_folder();
      
      ::file::path pathMatter;
      
      pathMatter = pathFolder / "_matter.zip";

      m_memoryMainResource = as_memory(pathMatter);

   }


} // namespace acme_macos


char * ns_resource_folder();


string macos_resource_folder()
{
   
   return ::string_from_strdup(ns_resource_folder());
   
}



