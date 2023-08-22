//
//  file_context.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#pragma once


#include "acme_apple/file_context.h"


namespace acme_macos
{


   class CLASS_DECL_ACME file_context :
      virtual public ::acme_apple::file_context
   {
   public:

      
      ::pointer < dir_system >       m_pdirsystem;
      ::pointer < file_system >      m_pfilesystem;


      file_context();
      virtual ~file_context();
      
      
      void initialize(::particle * pparticle) override;

      virtual ::payload length(const ::file::path & path) override;

      //virtual ::e_status update_module_path() override;

      virtual file_pointer get_file(const ::payload & varFile, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception) override;


      void calculate_main_resource_memory() override;
      
      
   };


} // namespace acme_macos



