//
//  file_context.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#pragma once


#include "apex_apple/file_context.h"


namespace apex_macos
{


   class CLASS_DECL_APEX file_context :
      virtual public ::apex_apple::file_context
   {
   public:

      
      ::pointer < dir_system >       m_pdirsystem;
      ::pointer < file_system >      m_pfilesystem;


      file_context();
      virtual ~file_context();
      
      
      void initialize(::particle * pparticle) override;

      virtual ::payload length(const ::file::path & path) override;

      //virtual ::e_status update_module_path() override;

      virtual file_pointer get_file(const ::payload & varFile, const ::file::e_open & eopen) override;


      void calculate_main_resource_memory() override;
      
      
   };


} // namespace apex_macos



