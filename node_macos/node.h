//
//  node.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:19 BRT <3ThomasBS_!!
//
#pragma once


#include "aura_macos/node.h"


namespace node_macos
{


   class CLASS_DECL_WINDOWING_MACOS node :
      virtual public ::aura_macos::node
   {
   public:


      node();
      ~node() override;


//      void os_menu_item_enable(void * pitem, bool bEnable) override;
//      void os_menu_item_check(void * pitem, bool bCheck) override;
//
//      void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId) override;
      
      
      //__pointer(::element) create_quit_element(__pointer(::acme::node) & pnode, __pointer(class ::system) & psystem) override;
  

//      void implement(__pointer(::acme::node) & pnode, __pointer(class ::system) & psystem) override;


      //void _will_finish_launching() override;


//      ::e_status is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt) override;
//
//
//      void install_keyboard_hook(::matter * pmatterListener) override;
//      void uninstall_keyboard_hook(::matter * pmatterListener) override;
//
//      void install_mouse_hook(::matter * pmatterListener) override;
//      void uninstall_mouse_hook(::matter * pmatterListener) override;
//
//

   };



} // namespace node_macos






