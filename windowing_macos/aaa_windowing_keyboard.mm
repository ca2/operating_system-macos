//
//  keyboard.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 31/05/21 16:29 BRT <3ThomasBS_!!
//
#include "framework.h"
//#include <Carbon/Carbon.h>


const char * mm_keyboard_input_source()
{
   
   TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
   NSString *s = (__bridge NSString *)(TISGetInputSourceProperty(source, kTISPropertyInputSourceID));
   
   if(s == nil)
      return strdup("");
   
   return strdup([s UTF8String]);
}



