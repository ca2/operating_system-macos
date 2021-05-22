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

      
      ::e_status main() override;
      
      
   };



} // namespace windowing_macos






