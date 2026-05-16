//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/constant/lightui.h"

class command_handler;


namespace appkit
{

namespace acme
{

namespace windowing
{


class CLASS_DECL_ACME_WINDOWING_APPKIT windowing :
virtual public ::acme::windowing::windowing
{
public:
   
   
   /// map NSWindow * (bridge casted to void *) to a ::acme::windowing::window *
  map < ::appkit::ns_window_t, ::pointer < ::acme::windowing::window > > m_windowmap;


//public:
    
    
    windowing();
    ~windowing() override;
    
    //::e_status defer_initialize_windowing() override;
    void initialize_windowing() override;
    ::acme::windowing::display * acme_display() override;
    void main_send(const ::procedure & procedure) override;
    void main_post(const ::procedure & procedure) override;
   void post(const ::procedure & procedure) override;
    void display_error_trap_push(int i) override;
    void display_error_trap_pop_ignored(int i) override;
   void on_user_command(::uptr u, ::lightui::enum_notification enotification, ::uptr uControl) override;
    //   ::e_status x11_initialize() override;
    //   void * x11_get_display() override;
    //   void x11_sync(const ::procedure & procedure) override;
    //   void x11_async(const ::procedure & procedure) override;
    //   void x11_display_error_trap_push(int i) override;
    //   void x11_display_error_trap_pop_ignored(int i) override;
   
   
   //void windowing_application_main_loop() override;
   void run() override;
   void windowing_post_quit() override;
   
   void application_handle(::i64 l, void* p) override;

   bool handle_messages() override;
   
   virtual void defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler);

   virtual void set_osdata_acme_windowing_window(void *, ::acme::windowing::window *);
   virtual ::acme::windowing::window * osdata_acme_windowing_window(void *);
   
   bool dark_mode() override;
   void set_dark_mode(bool bDarkMode) override;
   
   void each_window(const ::function < void(::acme::windowing::window*) > & function) override;
   
   virtual ::operating_system::window __cross_windows__get_dlg_item(const ::operating_system::window & operatingsystemwindow, int iDlgItem);
    
};


        } // namespace windowing


    } // namespace acme


} // namespace appkit


namespace cross_windows
{

   ::operating_system::window get_dlg_item(const ::operating_system::window & operatingsystemwindow, int iDlgItem);
   ::string get_window_text(const ::operating_system::window & operatingsystemwindow);
} // namespace cross_windows
