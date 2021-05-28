//
//  monitor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:48 BRT <3ThomasBS_!!
//
#include "framework.h"

void ns_monitor_cgrect(int i, CGRect * p);
void ns_workspace_cgrect(int i, CGRect * p);


namespace windowing_macos
{


   monitor::monitor()
   {

      //m_pMonitor2 = this;
   
   }


   monitor::~monitor()
   {
      

   }


::e_status monitor::get_monitor_rectangle(::RECTANGLE_I32 * prectangle)
{
   
   CGRect r;
   
   ns_monitor_cgrect(m_iIndex, &r);
   
   __copy(prectangle, r);
   
   return ::success;
   
}

::e_status monitor::get_workspace_rectangle(::RECTANGLE_I32 * prectangle)
{
   CGRect r;
   
   ns_workspace_cgrect(m_iIndex, &r);
   
   __copy(prectangle, r);
   
   return ::success;
   
}


} // namespace windowing_macos


