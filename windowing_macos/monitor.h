//
//  monitor.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:47 BRT <3ThomasBS_!!
//

#pragma once


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS monitor :
      virtual public ::windowing::monitor
   {
   public:
      

      monitor();
      ~monitor() override;
      
      
      void get_monitor_rectangle(::RECTANGLE_I32 * prectangle) override;
      void get_workspace_rectangle(::RECTANGLE_I32 * prectangle) override;

      
   };



} // namespace windowing_macos



