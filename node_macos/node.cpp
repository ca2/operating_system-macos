//
//  node.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:22 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "apex/input/input.h"
/////#include "apex/user/menu_shared.h"
//#include "keyboard_hook.h"
//#include "mouse_hook.h"

void ns_app_run();
void defer_create_windowing_application_delegate(void * pApplication, ::application_menu * papplicationmenu, ::application_menu_callback * papplicationmenucallback);


void ns_application_handle(long long l, void * p);


namespace node_macos
{


   node::node()
   {
      
   }


   node::~node()
   {
      
      
   }




//   void node::implement(::pointer < ::acme::node > & pnode, __pointer(class ::system) & psystem)
//   {
//       
//      m_pelementquit = new element_quit(pnode, psystem);
//      
//      auto argc = psystem->m_argc;
//      
//      auto argv = psystem->m_argv;
//      
//      auto papp = psystem->m_pappStartup;
//      
//      void * pApplication = (void *) (::app *) papp;
//      
//      windowing_macos_application_main(pApplication, argc, argv);
//      
//      //return psystem->m_estatus;
//      
//   }




//
//
//
//   void node::_will_finish_launching()
//   {
//
//      auto psystem = m_psystem->m_papexsystem;
//
//      if(::is_null(psystem->m_htask))
//      {
//
//         ///auto estatus =
//
//         psystem->branch_synchronously();
//
////         if(!estatus)
////         {
////
////            return estatus;
////
////         }
//
//         // release the initial allocation from platform_create_system as
//         // task::begin_synch holds a reference to the running system task.
//         psystem->release();
//
//      }
//
//      m_psystem->post_initial_request();
//
//      //return ::success;
//
//   }


//   ::e_status node::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
//   {
//      
//      auto estatus = ::keyboard_hook::is_enabled(false);
//
//      if(::is_null(puserinteractionEnablePrompt) || estatus == ::success)
//      {
//         
//         return estatus;
//         
//      }
//      
//      manual_reset_event ev;
//      
//      puserinteractionEnablePrompt->message_box("You gonna be prompted to enable Accessibility for \""+m_psystem->m_pappMain->m_strAppName+"\" to enable keyboard monitoring.",
//                     "Aura Click", e_message_box_ok)->then(
//                                                           [this, &ev,puserinteractionEnablePrompt](auto & sequence)
//                                                           {
//                        
//                        auto estatus = ::keyboard_hook::is_enabled(true);
//                        
//                        if(estatus.succeeded())
//                        {
//                           
//                           ev.set_event();
//                           
//                           return;
//                            
//                        }
//                        else
//                        {
//                           
//                           while(estatus == error_need_restart_application_to_activate_feature)
//                           {
//                              
//                              ::preempt(1_s);
//                              
//                              estatus = ::keyboard_hook::is_enabled(false);
//                              
//                              //output_debug_string("todo restart application");
//                              
//                              //m_psystem->m_papplicationMain->_001TryCloseApplication();
//                              
//                           }
//                              
//                        }
//                        
//                        output_debug_string("loop ended");
//                        
//                        ev.set_event();
//                        
//                     });
//   
//      //}
//
//      ev.wait();
//      
//      estatus = ::keyboard_hook::is_enabled(false);
//      
//      return estatus;
//      
////      auto estatus = keyboard_hook::check_system_permission(::is_set(puserinteractionEnablePrompt));
////
////      if(estatus == error_need_restart_application_to_activate_feature)
////      {
////
////         message_box(puserinteractionEnablePrompt, "Restart Aura Click?\n\nIf you have just enabled Accessibility and want the setting to be effective, Aura Click should be restarted.",
////                     "Aura Click", e_message_box_yes_no).then(
////                                                           [](auto & sequence)
////                                                           {
////
////                        output_debug_string("todo restart application");
////
////                     });
////
////      }
//      
//   }
//
//
//   void node::install_keyboard_hook(::matter * pmatterListener)
//   {
//      
//      //auto estatus =
//      
//      ::keyboard_hook::install(pmatterListener);
//      
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//      
//   }
//
//
//   void node::uninstall_keyboard_hook(::matter * pmatterListener)
//   {
//   
//      ///auto estatus =
//      
//      ::keyboard_hook::uninstall(pmatterListener);
//   
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//      
//   }
//
//
//   void node::install_mouse_hook(::matter * pmatterListener)
//   {
//      
//      //auto estatus =
//      
//      ::mouse_hook::install(pmatterListener);
//      
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//      
//   }
//
//
//   void node::uninstall_mouse_hook(::matter * pmatterListener)
//   {
//
//      //auto estatus =
//      
//      ::mouse_hook::uninstall(pmatterListener);
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//      
//   }



   void node::acme_application_main(class ::acme::system * psystem)
   {

//      auto argc = psystem->m_pplatform->m_argc;
//
//      auto argv = psystem->m_pplatform->m_argv;

      auto papp = platform()->application();

      void * pApplication = (void *) (::acme::application *) papp;

      defer_create_windowing_application_delegate(pApplication, papp->application_menu(), papp);
      
      ns_app_run();

      //return psystem->m_estatus;

   }


   void node::application_handle(long long l, void * p)
   {
   
      ns_application_handle(l, p);
      
   }


   ::pointer < ::input::input > node::create_input()
   {

      auto & pfactory = platform()->factory("input", "appkit");

      auto pinput = pfactory->create < ::input::input >(this);

      return pinput;

   }


} // namespace node_macos




