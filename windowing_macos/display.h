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

      
      ::collection::count get_monitor_count() override;
   
      string impl_get_wallpaper(::collection::index iScreen) override;
      void impl_set_wallpaper(::collection::index iScreen, const ::scoped_string & strWallpaper) override;

      ::int_point _get_mouse_cursor_position() override;

   };



} // namespace windowing_macos



