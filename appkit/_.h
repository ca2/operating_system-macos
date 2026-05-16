#pragma once


#include "acme/_.h"

#if defined(_appkit_project)
#define CLASS_DECL_APPKIT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APPKIT  CLASS_DECL_IMPORT
#endif


namespace appkit
{


   class ns_window;

   class ns_image;


} // namespace core_graphics


#include "operating_system-macos/appkit/_struct.h"

