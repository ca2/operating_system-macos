#pragma once
#pragma once


#include "acme_macos/_.h"
#include "apex_apple/_.h"


#if defined(_APEX_MACOS_LIBRARY)
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_IMPORT
#endif


