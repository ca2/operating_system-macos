//
//  file_system.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//

#include "framework.h"
#include "file_system.h"
#include "acme/platform/application.h"


#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


string apple_app_module_path();


namespace acme_macos
{

   
   file_system::file_system()
   {

      m_pplatformfile = this;

   }


   file_system::~file_system()
   {


   }


   void file_system::initialize(::particle * pparticle)
   {
      
      //auto estatus =
      
      ::acme_apple::file_system::initialize(pparticle);
      
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }

   }


void file_system::init_system()
{
   
   ::acme_apple::file_system::init_system();
   
   string str = getenv("HOME");
   
   auto psystem = system();
   
   auto pdirectorysystem = psystem->directory_system();

   ::file::path strRelative = pdirectorysystem->install();

   string strUserFolderShift;

   if(psystem->has_property("user_folder_relative_path"))
   {

      strUserFolderShift = strRelative / get_app()->payload("user_folder_relative_path").as_string();

   }
   else
   {

      strUserFolderShift = strRelative;

   }

   m_strUserFolder = str / "ca2" / strUserFolderShift;

   //return true;

}


   ::file::path file_system::module()
   {

      ::file::path path = apple_app_module_path();

      return path;

   }


   void file_system::touch(const ::file::path & path)
   {

      ::e_status estatus = ::success;

      if(__builtin_available(macOS 10.13, *))
      {
         
         int fd = ::open(path, O_WRONLY|O_CREAT | O_CLOEXEC, 0666);
         
         if (fd < 0)
         {
            
            estatus = error_io;
            
         }
         else
         {

            int rc = ::futimens(fd, nullptr);
            
            if (rc)
            {
            
               estatus = error_failed;

            }
            
            ::close(fd);
            
         }

      }
      else
      {
         
         acme_posix::file_system::touch(path);
         
      }
      
   }
    

} // namespace acme_macos


//char * ns_get_executable_path();


//string apple_app_module_path()
//{
//
//   return ::string_from_strdup(ns_get_executable_path());
//
//}
//


