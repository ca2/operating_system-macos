//
//  node.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:19 BRT <3ThomasBS_!!
//
#pragma once


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS node :
      virtual public ::aura::macos::node
   {
   public:
      
      
      node();
      ~node() override;

      
      void os_menu_item_enable(void * pitem, bool bEnable) override;
      void os_menu_item_check(void * pitem, bool bCheck) override;

      ::e_status defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId) override;
      
      ::e_status implement(__transport(::acme::node) & pnode, __transport(class ::system) & psystem) override;
      
      
      ::e_status _will_finish_launching() override;
      
      
      ::e_status is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt) override;

      
      ::e_status install_keyboard_hook(::matter * pmatterListener) override;
      ::e_status uninstall_keyboard_hook(::matter * pmatterListener) override;

      ::e_status install_mouse_hook(::matter * pmatterListener) override;
      ::e_status uninstall_mouse_hook(::matter * pmatterListener) override;


      
   };



} // namespace windowing_macos






