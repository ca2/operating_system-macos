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

      
      ::count get_monitor_count() override;
   
   };



} // namespace windowing_macos



