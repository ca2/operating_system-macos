//
//  _.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 02:41 BRT <3ThomasBS_!!
//
#pragma once


#include "aura_macos/_.h"
#include "acme/_operating_system.h"
//#include <Carbon/Carbon.h>


#if defined(_INPUT_APPKIT_LIBRARY)
   #define CLASS_DECL_INPUT_APPKIT CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_INPUT_APPKIT CLASS_DECL_IMPORT
#endif


namespace windowing_macos
{

   
   class window;
   class windowing;
   class display;
   class monitor;


} // namespace windowing_macos


#include "_c_mm.h"



