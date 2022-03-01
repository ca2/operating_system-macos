//
//  file_context.hpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#pragma once


namespace macos
{


   class CLASS_DECL_APEX file_context :
      virtual public ::apple::file_context
   {
   public:

      
      __reference(dir_system)       m_pdirsystem;
      __reference(file_system)      m_pfilesystem;


      file_context();
      virtual ~file_context();
      
      
      void initialize(::object * pobject) override;

      virtual ::payload length(const ::file::path & path) override;

      //virtual ::e_status update_module_path() override;

      virtual file_pointer get_file(const ::payload & varFile, const ::file::e_open & eopen) override;


      void calculate_main_resource_memory() override;
      
      
   };


} // namespace macos



