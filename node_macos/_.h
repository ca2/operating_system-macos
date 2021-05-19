//
//  _.h
//  node_macos
//
//  Created by Camilo Sasuke on 2021-05-21. 14:00 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "aura/_.h"


#if defined(_NODE_MACOS_LIBRARY)
   #define CLASS_DECL_NODE_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_MACOS  CLASS_DECL_IMPORT
#endif
