//
//  display.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:43 BRT <3ThomasBS_!!
//
#pragma once


#include "aura/windowing/display.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS display :
      virtual public ::windowing::display
   {
   public:
      
   
      display();
      ~display() override;

      
      ::raw::count get_monitor_count() override;
   
      string impl_get_wallpaper(::raw::index iScreen) override;
      bool impl_set_wallpaper(::raw::index iScreen, string strWallpaper) override;

      ::point_i32 _get_mouse_cursor_position() override;

   };



} // namespace windowing_macos



