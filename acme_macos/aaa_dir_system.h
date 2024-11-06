//
//  directory_system.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#pragma once


#include "acme/filesystem/filesystem/directory_system.h"


namespace acme_macos
{


   class CLASS_DECL_ACME directory_system :
      virtual public ::directory_system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCommonAppData;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;

      
      directory_system();


      void initialize(::particle * pparticle) override;

      void init_system() override;
      

   };


} // namespace acme_macos



