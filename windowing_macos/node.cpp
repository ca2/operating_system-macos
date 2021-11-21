//
//  node.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:22 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "apex/user/menu_shared.h"
#include "keyboard_hook.h"
#include "mouse_hook.h"


__pointer(menu_shared) create_menu_shared(const string_array & straParent, const string_array & straMenu, const string_array & straId);


void windowing_macos_application_main(void * pApplication, int argc, char *argv[]);


void ns_create_main_menu(menu_shared * pmenushared);


void os_menu_item_enable(void * pitem, bool bEnable);
void os_menu_item_check(void * pitem, bool bCheck);


namespace windowing_macos
{


   node::node()
   {
      
   }


   node::~node()
   {
      
      
   }


   void node::os_menu_item_enable(void * pitem, bool bEnable)
   {
    
      ::os_menu_item_enable(pitem, bEnable);
      
   }
   

   void node::os_menu_item_check(void * pitem, bool bCheck)
   {
   
      ::os_menu_item_check(pitem, bCheck);
      
   }


   ::e_status node::defer_create_main_menu(const string_array & straMenuParent, const string_array & straMenuName, const string_array & straMenuId)
   {
      
      auto pmenushared =
         create_menu_shared(
                            
                            straMenuParent,
                            straMenuName,
                            straMenuId
                            
                            );

      ns_create_main_menu(pmenushared);
      
      return success;
      
   }


   ::e_status node::implement()
   {
      
      auto psystem = m_psystem->m_papexsystem;
      
      auto argc = psystem->m_argc;
      
      auto argv = psystem->m_argv;
      
      auto papplication = psystem->m_papplicationStartup;
      
      void * pApplication = (void *) (::application *) papplication;
      
      windowing_macos_application_main(pApplication, argc, argv);
      
      return psystem->m_estatus;
      
   }


   ::e_status node::_will_finish_launching()
   {
      
      auto psystem = m_psystem->m_papexsystem;
      
      if(::is_null(psystem->m_htask))
      {

         auto estatus = psystem->begin_synch();

         if(!estatus)
         {

            return estatus;

         }
         
         // release the initial allocation from platform_create_system as
         // task::begin_synch holds a reference to the running system task.
         psystem->release();
         
      }
      
      m_psystem->post_initial_request();

      return ::success;
      
   }


   ::e_status node::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {
      
      auto estatus = ::keyboard_hook::is_enabled(false);

      if(::is_null(puserinteractionEnablePrompt) || estatus == ::success)
      {
         
         return estatus;
         
      }
      
      manual_reset_event ev;
      
      puserinteractionEnablePrompt->message_box("You gonna be prompted to enable Accessibility for \""+m_psystem->m_papplicationMain->m_strAppName+"\" to enable keyboard monitoring.",
                     "Aura Click", e_message_box_ok)->then(
                                                           [this, &ev,puserinteractionEnablePrompt](auto & sequence)
                                                           {
                        
                        auto estatus = ::keyboard_hook::is_enabled(true);
                        
                        if(estatus.succeeded())
                        {
                           
                           ev.set_event();
                           
                           return;
                            
                        }
                        else
                        {
                           
                           while(estatus == error_need_restart_application_to_activate_feature)
                           {
                              
                              ::preempt(1_s);
                              
                              estatus = ::keyboard_hook::is_enabled(false);
                              
                              //output_debug_string("todo restart application");
                              
                              //m_psystem->m_papplicationMain->_001TryCloseApplication();
                              
                           }
                              
                        }
                        
                        output_debug_string("loop ended");
                        
                        ev.set_event();
                        
                     });
   
      //}

      ev.wait();
      
      estatus = ::keyboard_hook::is_enabled(false);
      
      return estatus;
      
//      auto estatus = keyboard_hook::check_system_permission(::is_set(puserinteractionEnablePrompt));
//  
//      if(estatus == error_need_restart_application_to_activate_feature)
//      {
// 
//         message_box(puserinteractionEnablePrompt, "Restart Aura Click?\n\nIf you have just enabled Accessibility and want the setting to be effective, Aura Click should be restarted.",
//                     "Aura Click", e_message_box_yes_no).then(
//                                                           [](auto & sequence)
//                                                           {
//                        
//                        output_debug_string("todo restart application");
//                        
//                     });
//   
//      }
      
   }


   ::e_status node::install_keyboard_hook(::matter * pmatterListener)
   {
      
      auto estatus = ::keyboard_hook::install(pmatterListener);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


   ::e_status node::uninstall_keyboard_hook(::matter * pmatterListener)
   {
   
      auto estatus = ::keyboard_hook::uninstall(pmatterListener);
   
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


   ::e_status node::install_mouse_hook(::matter * pmatterListener)
   {
      
      auto estatus = ::mouse_hook::install(pmatterListener);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


   ::e_status node::uninstall_mouse_hook(::matter * pmatterListener)
   {

      auto estatus = ::mouse_hook::uninstall(pmatterListener);

      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


} // namespace windowing_macos




