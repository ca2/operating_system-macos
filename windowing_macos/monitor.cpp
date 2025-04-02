//
//  monitor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:48 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "monitor.h"
#include "acme/operating_system/apple/_apple.h"


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


   ::int_rectangle monitor::monitor_rectangle()
   {
   
      CGRect r;
      
      ns_monitor_cgrect((int) m_iIndex, &r);
      
      ::int_rectangle rectangle;
      
      copy(rectangle, r);
      
      return rectangle;
      
   }


   ::int_rectangle monitor::workspace_rectangle()
   {
      
      CGRect rectWorkspace;
      
      ns_workspace_cgrect((int) m_iIndex, &rectWorkspace);
      
      ::int_rectangle rectangle;
      
      copy(rectangle, rectWorkspace);
      
      return rectangle;
      
   }


} // namespace windowing_macos


// void ns_main_monitor_cgrect(CGRect * p);

// int get_main_screen_rectangle(INT_RECTANGLE * pr)
// {
   
//    CGRect r;
   
//    ns_main_monitor_cgrect(&r);
   
//    copy(pr, r);
   
//    return true;
   
// }
