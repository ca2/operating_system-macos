//
//  display.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:43 BRT <3ThomasBS_!!
//
#include "framework.h"


int ns_monitor_count();


namespace windowing_macos
{


   display::display()
   {
   
      m_pDisplay2 = this;
   
   }


   display::~display()
   {
      

   }


   ::count display::get_monitor_count()
   {
    
      return ns_monitor_count();
      
   }


} // namespace windowing_macos


