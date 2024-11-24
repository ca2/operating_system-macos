//
//  _.h
//  node_macos
//
//  Created by Camilo Sasuke on 2021-05-21. 14:00 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//


#include "node_macos/_.h"


#if defined(_operating_ambient_macos_project)
   #define CLASS_DECL_OPERATING_AMBIENT_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_OPERATING_AMBIENT_MACOS  CLASS_DECL_IMPORT
#endif



