//
//  _.mm
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-03-19.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//
#include <Cocoa/Cocoa.h>
#include "acme/operating_system/macos/keyboard.h"
#import "acme/operating_system/winpr_input.h"



unsigned int event_num_pad_key_code(NSEvent * event)
{

   NSString * arrow = [event charactersIgnoringModifiers];
   
   if([arrow length] == 1)
   {
      
      unichar key = [arrow characterAtIndex:0];
      
      if(key == NSLeftArrowFunctionKey)
      {
         
         return VK_LEFT; //::user::key_left;
         
      }
      else if(key == NSRightArrowFunctionKey)
      {
         
         return VK_RIGHT; //::user::key_right;
         
      }
      else if(key == NSUpArrowFunctionKey)
      {
         
         return VK_UP; // ::user::key_up;
         
      }
      else if(key == NSDownArrowFunctionKey)
      {
         
         return VK_DOWN; // ::user::key_down;
         
      }
      else if(key >= L'0' && key <= L'9')
      {
         
         //return 3000 + key - L'0';
         
         return 0;
         
      }
      
   }
   
   return 0;

}


unsigned int event_key_code(NSEvent * event)
{

   unsigned int uiModifierFlags = (unsigned int) [event modifierFlags];

   if(uiModifierFlags & NSEventModifierFlagNumericPad)
   {

      return event_num_pad_key_code(event);
   
   }
   
   unsigned int uiKeyCode = [event keyCode];
 
   return uiKeyCode;
   
}



