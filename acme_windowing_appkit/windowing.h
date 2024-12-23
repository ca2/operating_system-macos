//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"


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
protected:
   
   
   /// map NSWindow * (bridge casted to void *) to a ::acme::windowing::window *
  map < void *, ::pointer < ::acme::windowing::window > > m_windowmap;


public:
    
    
    windowing();
    ~windowing() override;
    
    //::e_status defer_initialize_windowing() override;
    void initialize_windowing() override;
    ::acme::windowing::display * acme_display() override;
    void _main_send(const ::procedure & procedure) override;
    void _main_post(const ::procedure & procedure) override;
    void display_error_trap_push(int i) override;
    void display_error_trap_pop_ignored(int i) override;
    
    //   ::e_status x11_initialize() override;
    //   void * x11_get_display() override;
    //   void x11_sync(const ::procedure & procedure) override;
    //   void x11_async(const ::procedure & procedure) override;
    //   void x11_display_error_trap_push(int i) override;
    //   void x11_display_error_trap_pop_ignored(int i) override;
   
   
   void windowing_application_main_loop() override;
   void run() override;
   void windowing_post_quit() override;
   
   void application_handle(huge_integer l, void* p) override;

   bool handle_messages() override;
   
   virtual void defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler);

   virtual void set_osdata_acme_windowing_window(void *, ::acme::windowing::window *);
   virtual ::acme::windowing::window * osdata_acme_windowing_window(void *);
    
};


        } // namespace windowing


    } // namespace acme


} // namespace appkit



