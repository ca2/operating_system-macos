#pragma once


#include "apex/filesystem/filesystem/file_system.h"


namespace apex_macos
{


   class CLASS_DECL_APEX file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;


      file_system();
      ~file_system() override;
      
      
      void initialize(::particle * pparticle) override;



      //virtual ::e_status update_module_path() override;




   };


} // namespace apex_macos



