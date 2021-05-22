//
//  node.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:22 BRT <3ThomasBS_!!
//
#include "framework.h"


void windowing_macos_application_main(int argc, char *argv[]);


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


   ::e_status node::main()
   {
      
      auto psystem = m_psystem;
      
      auto argc = psystem->m_argc;
      
      auto argv = psystem->m_argv;
      
      windowing_macos_application_main(argc, argv);
      
      return psystem->m_estatus;
      
   }


} // namespace windowing_macos




