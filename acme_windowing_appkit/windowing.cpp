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

void ns_app_run();
void ns_app_do_tasks();
void ns_app_post_quit();
void ns_main_post(dispatch_block_t block);
bool ns_get_dark_mode();
bool ns_set_dark_mode(bool bDarkMode);
void acme_defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler);


//void apple_defer_nano_application_create(::platform::system * psystem);

void ns_application_handle(long long l, void * p);


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
    
    informationf("node_gtk3::node::x11_initialize");
    
    informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");
    
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
        
        __øconstruct(m_pacmedisplay);
        
        m_pacmedisplay->open_display();
        
    }
    
    return m_pacmedisplay;
    
}


void windowing::_main_send(const ::procedure & procedure)
{
    
    if(::is_main_thread())
    {
        
        procedure();
        
        return;
        
    }
    
    //__matter_send_procedure(this, this, &node::node_post, procedure);
    
    //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
    //      {
    
    auto pevent = __allocate manual_reset_happening();
    
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


void windowing::windowing_application_main_loop()
{
   
   main();
   
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


void windowing::_main_post(const ::procedure & procedure)
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


void windowing::application_handle(long long l, void* p)
{
   ns_application_handle(l, p);
   
}


void windowing::set_osdata_acme_windowing_window(void * posdata, ::acme::windowing::window * pacmewindowingwindow)
{
   
   _synchronous_lock synchronouslock(this->synchronization());
   
   if(::is_null(pacmewindowingwindow))
   {
      
      m_windowmap.erase_item(posdata);
      
   }
   else
   {
    
      m_windowmap.set_at(posdata, pacmewindowingwindow);
      
   }
      
}


::acme::windowing::window * windowing::osdata_acme_windowing_window(void * posdata)
{
   
   _synchronous_lock synchronouslock(this->synchronization());

   return m_windowmap[posdata];
   
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


} // namespace windowing


} // namespace acme


} // namespace windowing_appkit








