//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/nano/nano.h"
//#include "acme/nano/user/user.h"
#include "acme/parallelization/manual_reset_happening.h"
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
void ns_app_stop();
void ns_main_post(dispatch_block_t block);

void acme_defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::application_menu_callback * papplicationmenucallback);


void apple_defer_nano_application_create(::platform::system * psystem);


namespace appkit
{

namespace acme
{


namespace windowing
{


windowing::windowing()
{
    
    
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
   
   apple_defer_nano_application_create(system());
   
  
   system()->defer_post_initial_request();
   
   main();
   //ns_app_run();
   
}


void windowing::windowing_post_quit()
{
 
   ns_main_post(^()
                 {
      ns_app_stop();
      
   }
      );
   
}


bool windowing::handle_messages()
{
   
   ns_app_do_tasks();
   
   return true;
   
}


void  windowing::run()
{
   
   ns_app_run();
   
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

void windowing::defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::application_menu_callback * papplicationmenucallback)
{

   ::acme_defer_create_windowing_application_delegate(
                                                 papplication,
                                                 papplicationmenu, papplicationmenucallback);

}


} // namespace windowing


} // namespace acme


} // namespace windowing_appkit



