//
//  monitor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:48 BRT <3ThomasBS_!!
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#include "aura/_defer.h"
#endif
#include "acme/operating_system/apple/_apple_no_templates.h"


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


#if 0


   ::rectangle_i32 monitor::monitor_rectangle()
   {
   
      CGRect r;
      
      ns_monitor_cgrect((int) m_iIndex, &r);
      
      ::rectangle_i32 rectangle;
      
      copy(rectangle, r);
      
      return rectangle;
      
   }


   ::rectangle_i32 monitor::workspace_rectangle()
   {
      
      CGRect rectWorkspace;
      
      ns_workspace_cgrect((int) m_iIndex, &rectWorkspace);
      
      ::rectangle_i32 rectangle;
      
      copy(rectangle, rectWorkspace);
      
      return rectangle;
      
   }


#endif


} // namespace windowing_macos


// void ns_main_monitor_cgrect(CGRect * p);

// int get_main_screen_rectangle(RECTANGLE_I32 * pr)
// {
   
//    CGRect r;
   
//    ns_main_monitor_cgrect(&r);
   
//    copy(pr, r);
   
//    return true;
   
// }
