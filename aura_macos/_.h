//
//  _.h
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-18 14:27 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//


#include "operating_system-apple/aura_apple/_.h"
#include "apex_macos/_.h"


#if defined(_aura_macos_project)
   #define CLASS_DECL_AURA_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_MACOS  CLASS_DECL_IMPORT
#endif


#include "_c_mm.h"



