//
//  _.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 02:41 BRT <3ThomasBS_!!
//
#pragma once


#include "aura_macos/_.h"


#if defined(_WINDOWING_MACOS_LIBRARY)
   #define CLASS_DECL_WINDOWING_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_MACOS  CLASS_DECL_IMPORT
#endif


#include "_c_mm.h"
