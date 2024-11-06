#pragma once


#include "acme/filesystem/filesystem/file_system.h"


namespace acme_macos
{


   class CLASS_DECL_ACME_MACOS file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;


      file_system();
      ~file_system() override;
      
      
      void initialize(::particle * pparticle) override;



      //virtual ::e_status update_module_path() override;




   };


} // namespace acme_macos



