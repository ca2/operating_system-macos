//
//  file_system.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//
#pragma once


#include "acme_apple/file_system.h"


namespace acme_macos
{


   class CLASS_DECL_ACME_MACOS file_system :
      virtual public ::acme_apple::file_system
   {
   public:
      
      
       ::file::path            m_strUserFolder;

      //__creatable_from_library(file_system, ::file_system, "acme_macos");
      
      
       file_system();
      ~file_system() override;

      
      void initialize(::particle * pparticle) override;

      void init_system() override;
      ::file::path module() override;

      
      void touch(const ::file::path & path) override;

   };


} // namespace acme_macos



