//
//  node.hpp
//  windowing_macos
//
//  by Camilo Sasuke on 2024-11-23 23:00 BRT <3ThomasBS_!!
//
#pragma once


#include "node_macos/node.h"


namespace operating_ambient_macos
{


   class CLASS_DECL_OPERATING_AMBIENT_MACOS node :
      virtual public ::node_macos::node
   {
   public:


      node();
      ~node() override;


//      void os_menu_item_enable(void * pitem, bool bEnable) override;
//      void os_menu_item_check(void * pitem, bool bCheck) override;
//
//      void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId) override;
      
      
      //::pointer < ::element > create_quit_element(::pointer < ::platform::node > & pnode, __pointer(class ::system) & psystem) override;
  

//      void implement(::pointer < ::platform::node > & pnode, __pointer(class ::system) & psystem) override;


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

      //void acme_application_main(class ::platform::system * psystem) override;
      
      
      //void application_handle(long long l, void * p) override;
      
      
      ::pointer < ::input::input > create_input() override;
      
      
      //void do_windowing_factory() override;
      
      void defer_innate_ui() override;
      //void on_system_main() override;
      
//      
//      void defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::application_menu_callback * papplicationmenucallback) override;
//

      //void ns_app_run() override;
      

   };


} // namespace operating_ambient_macos



