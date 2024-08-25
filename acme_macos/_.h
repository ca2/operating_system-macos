#pragma once


#include "operating_system-apple/acme_apple/_.h"


#if defined(_ACME_MACOS_LIBRARY)
   #define CLASS_DECL_ACME_MACOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_MACOS  CLASS_DECL_IMPORT
#endif


namespace acme
{


   namespace macos
   {


      class node;


   } // namespace macos


} // namespace acme


