//
//  node.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:22 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "apex/user/menu_shared.h"


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


   ::e_status node::main()
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

      auto estatus = psystem->begin_synch();

      if(!estatus)
      {

         return estatus;

      }
      
      // release the initial allocation from platform_create_system as
      // task::begin_synch holds a reference to the running system task.
      psystem->release();
      
      m_psystem->post_initial_request();

      return ::success;
      
   }


} // namespace windowing_macos




