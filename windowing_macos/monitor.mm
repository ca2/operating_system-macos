//
//  monitor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 20:48 BRT <3ThomasBS_!!
//
#include "framework.h"


int ns_monitor_count()
{
   
   auto screenArray = [NSScreen screens];

   auto count = [screenArray count];

   return (int) count;
   
}


void ns_screen_translate(CGRect * prect, int iIndex)
{
   
   CGRect rectMonitor;

   ns_monitor_cgrect(iIndex, &rectMonitor);
   
   auto nsBottom = prect->origin.y + prect->size.height;
   
   auto top = rectMonitor.origin.y + rectMonitor.size.height;

   prect->origin.y = top - nsBottom;

}


void ns_monitor_cgrect(int i, CGRect * prect)
{
   
   NSScreen * pscreen;
   
   if(i < 0)
   {
      
      auto screenArray = [NSScreen screens];

      pscreen = [screenArray objectAtIndex:i];
      
   }
   else
   {
      
      pscreen = [NSScreen mainScreen];
      
   }

   *prect = [pscreen frame];

   ns_screen_translate(prect, i);
   
}


void ns_workspace_cgrect(int i, CGRect * prect)
{

   NSScreen * pscreen;
   
   if(i < 0)
   {
      
      auto screenArray = [NSScreen screens];

      pscreen = [screenArray objectAtIndex:i];
      
   }
   else
   {
      
      pscreen = [NSScreen mainScreen];
      
   }

   *prect = [pscreen visibleFrame];
   
   ns_screen_translate(prect, i);
   
}


void ns_main_monitor_cgrect(CGRect * prect)
{

   auto pscreen = [NSScreen mainScreen];

   *prect = [pscreen frame];
   
}



