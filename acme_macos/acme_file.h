//
//  acme_file.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//

#pragma once


namespace macos
{


   class CLASS_DECL_ACME_MACOS acme_file :
      virtual public ::posix::acme_file
   {
   public:
      
      
      __creatable_from_library(acme_file, ::acme_file, "acme_macos");
      
      
      acme_file();
      ~acme_file() override;

      
      ::file::path module() override;
      

   };


} // namespace macos



