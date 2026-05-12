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


} // namespace core_graphics



