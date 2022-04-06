//
//  cursor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21.
//
#import <AppKit/AppKit.h>
#include "acme/constant/cursor.h"


#define __IS_NULL(p) (((uintptr_t) (p)) < 65'536)


void __ns_cursor_hide()
{
   
   [ NSCursor hide ];
   
}


void __ns_cursor_unhide()
{
   
   
   [ NSCursor unhide ];
   
}


void __ns_set_cursor(void * pNSCursor)
{
   
   NSCursor * pcursor = (__bridge NSCursor *) pNSCursor;
   
   [pcursor set];
   
}


void * __ns_get_cursor()
{
   
   NSCursor * pnscursor = [NSCursor currentSystemCursor];
   
   void * pcursor = (__bridge void *) pnscursor;
   
   return pcursor;
   
}


void * __ns_get_default_system_cursor(enum_cursor ecursor)
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
         
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"

      case e_cursor_size_bottom_right:
         pcursor = [[NSCursor class] performSelector:@selector( _bottomRightResizeCursor)];
         break;
      case e_cursor_size_bottom_left:
         pcursor = [[NSCursor class] performSelector:@selector(_bottomLeftResizeCursor)];
         break;
      case e_cursor_size_top_right:
         pcursor = [[NSCursor class] performSelector:@selector(_topRightResizeCursor)];
         break;
      case e_cursor_size_top_left:
         pcursor = [[NSCursor class] performSelector:@selector(_topLeftResizeCursor)];
         break;
         
#pragma clang diagnostic pop
      case e_cursor_size_vertical:
         pcursor = [NSCursor resizeUpDownCursor];
         break;
      case e_cursor_size_horizontal:
         pcursor = [NSCursor resizeLeftRightCursor];
         break;
      case e_cursor_size_bottom:
         pcursor = [NSCursor resizeDownCursor];
         break;
      case e_cursor_size_top:
         pcursor = [NSCursor resizeUpCursor];
         break;
      case e_cursor_size_right:
         pcursor = [NSCursor resizeRightCursor];
         break;
      case e_cursor_size_left:
         pcursor = [NSCursor resizeLeftCursor];
         break;
      default:
         break;
         
   };
   
   return (__bridge_retained void *) pcursor;
   
}


NSImage * nsimage_from_cgimageref(CGImageRef image, int cx, int cy);


void * __nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot)
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


void ___ns_cursor_free(NSCursor *)
{
   
   
}


void __ns_cursor_free(void * pNSCursor)
{
   
   NSCursor * pnscursor = (__bridge_transfer NSCursor *) pNSCursor;
   
   ___ns_cursor_free(pnscursor);
   
}



