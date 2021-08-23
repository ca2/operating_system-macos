#pragma once


namespace macos
{


   class CLASS_DECL_AURA shell :
      virtual public ::aura::posix::shell
   {
   public:


      shell();
      ~shell() override;


//      virtual bool _get_file_image_by_type_identifier(_get_file_image_ & getfileimage);

      bool _get_file_image(_get_file_image_ & getfileimage) override;
      
      
   };


} // namespace macos



