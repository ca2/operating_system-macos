//
//  cursor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21.
//

#import <AppKit/AppKit.h>
#include "acme/constant/cursor.h"


void ns_set_cursor(void * pNSCursor)
{
   
   NSCursor * pcursor = (__bridge NSCursor *) pNSCursor;
   
   [pcursor set];
   
}


void * ns_get_cursor()
{
   
   NSCursor * pnscursor = [NSCursor currentSystemCursor];
   
   void * pcursor = (__bridge void *) pnscursor;
   
   return pcursor;
   
}






void * ns_get_default_system_cursor(enum_cursor ecursor)
{
   
   NSCursor * pcursor = nullptr;
   
   switch(ecursor)
   {
      case e_cursor_hand:
         pcursor = [NSCursor openHandCursor];
         break;
      case e_cursor_move:
         pcursor = [NSCursor closedHandCursor];
         break;
      case e_cursor_arrow:
         pcursor = [NSCursor arrowCursor];
         break;
      case e_cursor_text_select:
         pcursor = [NSCursor IBeamCursor];
         break;
      default:
         break;
         
   };
   
   void * pNSCursor = (__bridge void *) pcursor;
   
   return pNSCursor;
   
   
}




//extern NSCursor * g_pcurrentNscursor;
//
//
//// int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
//int os_window_set_mouse_cursor(void *, void * p)
//{
//
//   NSCursor * pcursor = (__bridge NSCursor *) p;
//   
//   if(g_pcurrentNscursor != nullptr)
//   {
//      
//      if(p == NULL)
//      {
//         
//         [NSCursor hide];
//         
//      }
//      
//   }
//   else
//   {
//
//      if(p != NULL)
//      {
//         
//         [NSCursor unhide];
//         
//      }
//
//   }
//
//   g_pcurrentNscursor = pcursor;
//   
//   if(g_pcurrentNscursor != NULL)
//   {
//      
//      if(g_pcurrentNscursor != [NSCursor currentCursor])
//      {
//   
//         [g_pcurrentNscursor set];
//         
//      }
//      
//   }
//
//   return 1;
//   
//}


extern NSCursor * g_pcurrentNscursor;


//void ns_set_cursor_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
//{
//
//   if(g_pcurrentNscursor != nullptr)
//   {
//
//      [g_pcurrentNscursor pop];
//
//   }
//
//   if(image == nullptr)
//   {
//
//      return;
//
//   }
//
//   NSPoint point;
//
//   point.x = xHotSpot;
//
//   point.y = yHotSpot;
//
//   NSImage * pimage = nsimage_from_cgimageref(image, cx, cy);
//
//   g_pcurrentNscursor = [[NSCursor alloc] initWithImage: pimage hotSpot:point];
//
//   [g_pcurrentNscursor push];
//
//
//}


NSImage * nsimage_from_cgimageref(CGImageRef image, int cx, int cy);


void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
{
   
   if(image == nullptr)
   {
      
      return NULL;
      
   }
   
   NSPoint point;
   
   point.x = xHotSpot;
   
   point.y = yHotSpot;
   
   NSImage * pimage = nsimage_from_cgimageref(image, cx, cy);
   
   NSCursor * pcursor = [[NSCursor alloc] initWithImage: pimage hotSpot:point];

   return (__bridge_retained void *) pcursor;
   
}







