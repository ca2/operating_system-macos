//
//  cursor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21.
//

#import <AppKit/AppKit.h>
#include "acme/const/cursor.h"


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
