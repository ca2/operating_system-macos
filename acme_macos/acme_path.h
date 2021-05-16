// Create on 2021-03-22 09:12 <3ThomasBS_ // at Linux(Question.)
// Recreated on 2021-05-16 15:07 <3ThomasBS_ // for macOS
#pragma once


namespace macos
{


   class CLASS_DECL_ACME_MACOS acme_path :
      virtual public ::acme_path
   {
   public:


      acme_path();
      virtual ~acme_path();


      virtual ::file::path app_module() override;


   };


} // namespace macos



