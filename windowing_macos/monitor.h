//
//  monitor.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:47 BRT <3ThomasBS_!!
//
#pragma once


#include "aura/windowing/monitor.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS monitor :
      virtual public ::windowing::monitor
   {
   public:
      

      monitor();
      ~monitor() override;
      
      
      ::int_rectangle monitor_rectangle() override;
      ::int_rectangle workspace_rectangle() override;

      
   };



} // namespace windowing_macos



