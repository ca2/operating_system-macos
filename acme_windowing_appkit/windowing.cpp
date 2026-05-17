//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "windowing.h"
#include "acme/nano/nano.h"
//#include "acme/nano/user/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/display.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>
#include <Carbon/Carbon.h>

void ns_app_hide();
void ns_app_run();
void ns_app_do_tasks();
void ns_app_post_quit();
void ns_main_post(dispatch_block_t block);
bool ns_get_dark_mode();
bool ns_set_dark_mode(bool bDarkMode);
void acme_defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler);


//void apple_defer_nano_application_create(::platform::system * psystem);

void ns_application_handle(::i64 l, void * p);


namespace appkit
{

namespace acme
{


namespace windowing
{


windowing::windowing()
{
    
   m_bMessageThread = true;
   
}


windowing::~windowing()
{
    
    
}


//::e_status windowing::defer_initialize_windowing()
//{
//    
//    //      if (m_estatusInitializeX11 == error_not_initialized)
//    //      {
//    //
//    //         m_estatusInitializeX11 = initialize_windowing();
//    //
//    //      }
//    //
//    //      return m_estatusInitializeX11;
//    
//    return ::success;
//    
//}
//

void windowing::initialize_windowing()
{
    
    informationf("appkit::acme::windowing::windowing::initialize_windowing");
    
    //informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");
    
//    if (!nano()->user()->init_threads())
//    {
//        
//        return ::error_failed;
//        
//    }
//    
    // gdk_x11 does error handling?!?!?!
    //XSetErrorHandler(_c_XErrorHandler);
    
    //g_pmutexX11 = new ::pointer < ::mutex >();
    
    return ::success;
    
}



::acme::windowing::display  * windowing::acme_display()
{
    
    if(!m_pacmedisplay)
    {
        //return ::platform::node::x11_get_display();
        
        initialize_windowing();
        
        //      if(m_pvoidX11Display == NULL)
        //      {
        //
        //         m_pvoidX11Display = fetch_windowing_display();
        //
        //      }
        //
        //      return m_pvoidX11Display;
        
        constructø(m_pacmedisplay);
        
        m_pacmedisplay->open_display();
        
    }
    
    return m_pacmedisplay;
    
}



void windowing::post(const ::procedure & procedure)
{
   
   return main_post(procedure);

//   if (!procedure)
//   {
//
//      return;
//
//   }
//
//   //if (is_current_task())
//   //{
//
//   //   procedure();
//
//   //   return;
//
//   //}
//
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      m_procedurea2.add(procedure);
//
//      new_main_loop_happening()->set_happening();
//
//      //update_new_main_loop_happening();
//
//   }

}


void windowing::main_send(const ::procedure & procedure)
{
    
    if(::is_main_thread())
    {
        
        procedure();
        
        return;
        
    }
    
    //__matter_send_procedure(this, this, &node::node_post, procedure);
    
    //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
    //      {
    
    auto pevent = allocateø manual_reset_happening();
    
    user_post([ procedure, pevent ]
              {
        
        procedure();
        
        pevent->set_happening();
        
    });
    
    if(!pevent->wait(procedure.timeout()))
    {
        
        throw ::exception(error_timeout);
        //pevent.release();
        
        //return false;
        
    }
    
    ///return true;
    //
    //      }
    
    
}


//void windowing::windowing_application_main_loop()
//{
//   
//   main();
//   
//}


void windowing::each_window(const ::function < void(::acme::windowing::window*) > & function)
{

   for(auto & pacmewindowingwindow:m_windowmap.payloads())
   {
      
      if(pacmewindowingwindow)
      {
         
         function(pacmewindowingwindow);
         
      }
      
   }
 
}


void windowing::windowing_post_quit()
{
 
      ns_app_post_quit();
   
}


bool windowing::handle_messages()
{
   
   ns_app_do_tasks();
   
   return true;
   
}


void  windowing::run()
{
   
   system()->prepare_application();
   
   //apple_defer_nano_application_create(system());
   
   defer_create_windowing_application_delegate(
                                               application(),
                                               application()->application_menu(),
                                               application());
  
   //system()->defer_post_initial_request();
   
   ns_app_run();
   
//   if(::system()->m_pmanualresethappeningMainLoopEnd)
//   {
//
//      ::system()->m_pmanualresethappeningMainLoopEnd->set_happening();
//
//   }
   
}


void windowing::main_post(const ::procedure & procedure)
{
    
    node()->user_post(procedure);
    
}


void windowing::display_error_trap_push(int i)
{
    
    
    //node()->windowing_display_error_trap_push(i);
    
    //      if(system()->m_ewindowing == e_windowing_x11)
    //      {
    //
    //         GdkDisplay *gdkdisplay;
    //
    //         gdkdisplay = gdk_display_get_default ();
    //         gdk_x11_display_error_trap_push (gdkdisplay);
    //
    //      }
    
}


void windowing::display_error_trap_pop_ignored(int i)
{
    
    //node()->windowing_display_error_trap_pop_ignored(i);
    //      if(system()->m_ewindowing == e_windowing_x11)
    //      {
    //
    //         GdkDisplay *gdkdisplay;
    //         gdkdisplay = gdk_display_get_default ();
    //         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
    //
    //      }
    
}


//
//    void node::sync(const ::procedure & procedure)
//    {
//
//        nano()->user()->x11_sync(procedure);
//
//    }
//
//
//    void node::async(const ::procedure & procedure)
//    {
//
//        nano()->user()->x11_async(procedure);
//
//    }
//
//
//    void node::display_error_trap_push(int i)
//    {
//
//
//    }
//
//
//    void node::display_error_trap_pop_ignored(int i)
//    {
//
//
//    }

void windowing::defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler)
{

   ::acme_defer_create_windowing_application_delegate(
                                                 papplication,
                                                 papplicationmenu, pcommandhandler);

}


void windowing::application_handle(::i64 l, void* p)
{
   ns_application_handle(l, p);
   
}


void windowing::set_osdata_acme_windowing_window(void * posdata, ::acme::windowing::window * pacmewindowingwindow)
{
   
   _synchronous_lock synchronouslock(this->synchronization());
   
   if(::is_null(pacmewindowingwindow))
   {
      ::appkit::ns_window_t nswindow;
      nswindow.m_p = posdata;
      m_windowmap.erase(nswindow);
      
   }
   else
   {
      ::appkit::ns_window_t nswindow;
      nswindow.m_p = posdata;
      m_windowmap.set_at(nswindow, pacmewindowingwindow);
      
   }
      
}


::acme::windowing::window * windowing::osdata_acme_windowing_window(void * posdata)
{
   
   _synchronous_lock synchronouslock(this->synchronization());
   ::appkit::ns_window_t nswindow;
   nswindow.m_p = posdata;

   return m_windowmap[nswindow];
   
}


bool windowing::dark_mode()
{
 
   return ns_get_dark_mode();
   
}


// Don't forget to:
// add NSAppleEventsUsageDescription to Info.plist with System Events usage description
// add Apple Events Hardened Runtime entitlement

void windowing::set_dark_mode(bool bDarkMode)
{

   ns_set_dark_mode(bDarkMode);
   
}

void windowing::hide_application()
{
   
   ns_app_hide();
   
}

void windowing::on_user_command(::uptr u,::lightui::enum_notification enotification,       ::uptr uControl)
{
   
   ::operating_system::macos_window macoswindow((CGWindowID)u);
   
   if(macoswindow.is_null())
   {
      
      information("on user command : operating system window is not set");
      return;
      
   }
   
   ::appkit::ns_window_t nswindow;
   nswindow.m_p = (void *) u;
   
   auto pacmewindowingwindow = m_windowmap[nswindow];
   
   if(::is_null(pacmewindowingwindow))
   {
    
      information("didn't find acme windowing window with this operating system window : " + ::as_string((::uptr)u) );
      
      return;
      
   }
   ::wparam wparam;
   wparam = make_unsigned_int(uControl, enotification);
   pacmewindowingwindow->send_message(::user::e_message_command, wparam);
   
}


::operating_system::window windowing::__cross_windows__get_dlg_item(const ::operating_system::window & operatingsystemwindow, int iDlgItem)
{
   
//   auto u = ::as_u64(operatingsystemwindow);
//   
//   auto pacmewindowingwindow = m_windowmap[(void *)(::uptr)u];
//   
//   if(::is_null(pacmewindowingwindow))
//   {
//    
//      information("didn't find acme windowing window with this operating system window : " + ::as_string((::uptr)u) );
//      
//      return;
//      
//   }
//   
//   pacmewindowingwindow->post_message(::user::e_message_command, uControl & 0xffffu);
   return {};
}


} // namespace windowing


} // namespace acme


} // namespace windowing_appkit


void ns_send_message(::appkit::ns_window_t nswindow, ::user::enum_message emessage, ::uptr wparam, ::uptr lparam)
{
   
   ::cast < ::appkit::acme::windowing::windowing > pwindowing = ::system()->acme_windowing();
   
   auto pacmewindowingwindow = pwindowing->m_windowmap[nswindow];
   
   if(::is_null(pacmewindowingwindow))
   {
    
      information("didn't find acme windowing window with this operating system window : " + ::as_string((::uptr)nswindow.m_p) );
      
      return;
      
   }
   
   pacmewindowingwindow->send_message(emessage, wparam, lparam);
   
}


void set_acme_windowing_window_ns_window_uptr(::acme::windowing::window * pacmewindowingwindow, ::uptr u)
{
   
   ::cast < ::appkit::acme::windowing::windowing > pwindowing = ::system()->acme_windowing();
   ::cast < ::appkit::acme::windowing::window > pwindow =  pacmewindowingwindow;
   ::appkit::ns_window_t nswindow;
   nswindow.m_p = (void *) u;

   pwindow->m_nswindow = nswindow;
   
   pwindow->m_macoswindow = u;
   
   pwindowing->m_windowmap[nswindow] = pacmewindowingwindow;
   
   
}
