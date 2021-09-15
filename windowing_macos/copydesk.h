#pragma once


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


      ::e_status initialize(::object * pobject) override;
      ::e_status destroy() override;

      ::e_status _set_filea(const ::file::patha & stra, e_op eop) override;
      ::e_status _get_filea(::file::patha & stra, e_op & eop) override;
      bool _has_filea() override;

      virtual bool _os_has_filea();
      
      virtual bool _os_clipboard_has_changed();

      ::e_status _set_plain_text(const string & str) override;
      ::e_status _get_plain_text(string & str) override;
      bool _has_plain_text() override;

      virtual bool _os_has_plain_text();


      ::e_status _desk_to_image(::image * pimage) override;
      ::e_status _image_to_desk(const ::image * pimage) override;
      bool _has_image() override;

      virtual bool _os_has_image();


      virtual void _os_step();
      virtual void _on_os_clipboard_changed();


   };


} // namespace windowing_macos



