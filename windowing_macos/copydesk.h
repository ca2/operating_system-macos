#pragma once


#include "aura/user/user/copydesk.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS copydesk :
      virtual public ::user::copydesk
   {
   public:

      
      long        m_lTicket;
      bool        m_bHasFile;
      bool        m_bHasText;
      bool        m_bHasDib;

      
      dispatch_source_t m_ds;

      copydesk();
      ~copydesk() override;


      void initialize(::particle * pparticle) override;
      void destroy() override;

      bool _set_filea(const ::file::path_array_base & stra, enum_op eop) override;
      bool _get_filea(::file::path_array_base & stra, enum_op & eop) override;
      bool _has_filea() override;

      virtual bool _os_has_filea();
      
      virtual bool _os_clipboard_has_changed();

      bool _set_plain_text(const ::scoped_string & str) override;
      bool _get_plain_text(string & str) override;
      bool _has_plain_text() override;

      virtual bool _os_has_plain_text();


      bool _desk_to_image(::image::image * pimage) override;
      bool _image_to_desk(const ::image::image * pimage) override;
      bool _has_image() override;

      virtual bool _os_has_image();


      virtual void _os_step();
      virtual void _on_os_clipboard_changed();


   };


} // namespace windowing_macos



