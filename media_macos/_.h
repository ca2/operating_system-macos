#pragma once


#include "windowing_macos/_.h"
#include "media_apple/_.h"


#ifdef _MEDIA_IOS_STATIC
#define CLASS_DECL_MEDIA_IOS
#elif defined(_MEDIA_IOS_LIBRARY)
#define CLASS_DECL_MEDIA_IOS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_MEDIA_IOS  CLASS_DECL_IMPORT
#endif



