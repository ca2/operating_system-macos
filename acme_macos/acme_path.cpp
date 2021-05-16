// Create on 2021-03-22 09:12 <3ThomasBS_ // at Linux(Question)
// Recreated on 2021-05-16 15:07 <3ThomasBS_ // for macOS
#include "framework.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_path.h"


string apple_app_module_path();


namespace macos
{

   
   acme_path::acme_path()
   {

      m_pplatformpath = this;

   }


   acme_path::~acme_path()
   {


   }


   ::file::path acme_path::app_module()
   {

      ::file::path path = apple_app_module_path();

      return path;

   }


} // namespace macos


char * ns_get_executable_path();


string apple_app_module_path()
{
   
   return ::str::from_strdup(ns_get_executable_path());
   
}



