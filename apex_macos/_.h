#pragma once
#pragma once


#include "operating_system-apple/apex_apple/_.h"
#include "operating_system-macos/acme_macos/_.h"


#if defined(_APEX_MACOS_LIBRARY)
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_IMPORT
#endif


