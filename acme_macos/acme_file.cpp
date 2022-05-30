//
//  acme_file.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//

#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme_file.h"


#include <sys/stat.h>
//#include <utime.h>

string apple_app_module_path();


namespace acme_macos
{

   
   acme_file::acme_file()
   {

      m_pplatformfile = this;

   }


   acme_file::~acme_file()
   {


   }


   ::file::path acme_file::module()
   {

      ::file::path path = apple_app_module_path();

      return path;

   }


   void acme_file::touch(const char* path)
   {

      ::e_status estatus = ::success;

      if(__builtin_available(macOS 10.13, *))
      {
         
         int fd = ::open(path, O_WRONLY|O_CREAT, 0666);
         
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
         
         acme_posix::acme_file::touch(path);
         
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


