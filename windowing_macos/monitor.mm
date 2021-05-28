//
//  monitor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 20:48 BRT <3ThomasBS_!!
//
#import <AppKit/AppKit.h>

int ns_monitor_count()
{
   
   auto screenArray = [NSScreen screens];

   auto count = [screenArray count];

   return (int) count;
   
}

void ns_monitor_cgrect(int i, CGRect * p)
{

   auto screenArray = [NSScreen screens];

   auto pscreen = [screenArray objectAtIndex:i];
   
   *p =[pscreen frame];
   
}


void ns_workspace_cgrect(int i, CGRect * p)
{

   auto screenArray = [NSScreen screens];

   auto pscreen = [screenArray objectAtIndex:i];
   
   *p =[pscreen visibleFrame];
   
}



