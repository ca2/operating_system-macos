//
//  _.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 02:41 BRT <3ThomasBS_!!
//
#pragma once


#include "acme_windowing_appkit/_.h"
#include "aura_macos/_.h"
#include "acme/_operating_system.h"
//#include <Carbon/Carbon.h>


#if defined(_WINDOWING_MACOS_LIBRARY)
   #define CLASS_DECL_WINDOWING_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_MACOS  CLASS_DECL_IMPORT
#endif


namespace windowing_macos
{

   
   class window;
   class windowing;
   class display;
   class monitor;
   class window;


} // namespace windowing_macos


#include "_c_mm.h"



