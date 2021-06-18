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


void ns_screen_translate(CGRect * prect)
{
   
   CGRect rectMainMonitor;

   ns_main_monitor_cgrect(&rectMainMonitor);
   
   auto nsBottom = prect->origin.y + prect->size.height;
   
   auto top = rectMainMonitor.origin.y + rectMainMonitor.size.height;

   prect->origin.y = top - nsBottom;

}


void ns_monitor_cgrect(int i, CGRect * prect)
{

   auto screenArray = [NSScreen screens];

   auto pscreen = [screenArray objectAtIndex:i];
   
   *prect = [pscreen frame];
   
   ns_screen_translate(prect);
   
}


void ns_workspace_cgrect(int i, CGRect * prect)
{

   auto screenArray = [NSScreen screens];

   auto pscreen = [screenArray objectAtIndex:i];
   
   *prect = [pscreen visibleFrame];
   
   ns_screen_translate(prect);
   
}


void ns_main_monitor_cgrect(CGRect * prect)
{

   auto pscreen = [NSScreen mainScreen];

   *prect = [pscreen frame];
   
}



