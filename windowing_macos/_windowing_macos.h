//
//  _windowing_macos.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:23 BRT <3ThomasBS_!!
//
#pragma once


void os_menu_item_enable(void * pitem, bool bEnable);
void os_menu_item_check(void * pitem, bool bCheck);


namespace windowing_macos
{


   node::node()
   {
      
   }


   node::˜node()
   {
      
      
   }


   void node::os_menu_item_enable(void * pitem, bool bEnable)
   {
    
      ::os_menu_item_enable(pitem, bEnable)
      
   }
   

   void node::os_menu_item_check(void * pitem, bool bCheck)
   {
   
      ::os_menu_item_check(pitem, bCheck);
      
   }
   }


} // namespace windowing_macos
