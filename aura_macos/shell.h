#pragma once


namespace aura_macos
{


   class CLASS_DECL_AURA shell :
      virtual public ::aura_posix::shell
   {
   public:


      shell();
      ~shell() override;


//      virtual bool _get_file_image_by_type_identifier(_get_file_image_ & getfileimage);

      bool _get_file_image(_get_file_image_ & getfileimage) override;
      
      
   };


} // namespace aura_macos



