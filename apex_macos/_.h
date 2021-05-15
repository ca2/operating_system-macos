#pragma once
#pragma once


#include "apex_apple/_.h"
#include "acme_macos/_.h"


#if defined(_APEX_MACOS_LIBRARY)
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_MACOS  CLASS_DECL_IMPORT
#endif


namespace apex
{


   namespace macos
   {


      class node;


   } // namespace macos


} // namespace apex



