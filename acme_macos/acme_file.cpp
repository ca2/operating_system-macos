//
//  acme_file.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//

#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme_file.h"


string apple_app_module_path();


namespace macos
{

   
   acme_file::acme_file()
   {

      m_pplatformfile = this;

   }


acme_file::~acme_file()
   {


   }


   ::file::path acme_file::executable()
   {

      ::file::path path = apple_app_module_path();

      return path;

   }


} // namespace macos


char * ns_get_executable_path();


string apple_app_module_path()
{
   
   return ::string_from_strdup(ns_get_executable_path());
   
}



