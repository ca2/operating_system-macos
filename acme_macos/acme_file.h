//
//  acme_file.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//
#pragma once


#include "acme_posix/acme_file.h"


namespace acme_macos
{


   class CLASS_DECL_ACME_MACOS acme_file :
      virtual public ::acme_posix::acme_file
   {
   public:
      
      
      //__creatable_from_library(acme_file, ::acme_file, "acme_macos");
      
      
      acme_file();
      ~acme_file() override;

      
      ::file::path module() override;

      
      void touch(const char* path) override;

   };


} // namespace acme_macos



