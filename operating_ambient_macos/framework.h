#ifndef __GNUC__
#pragma once
#endif

#include "acme/_start.h"

#ifdef __OBJC__

#ifdef MACOS

#include "aura/os/macos/_mm.h"

#else

#include "aura/os/ios/_mm.h"

#endif

#include <CoreText/CoreText.h>

#import <Foundation/Foundation.h>

#else

#include "_.h"

//#if BROAD_PRECOMPILED_HEADER
//
//#include "_library.h"
//
//#endif
//
////#include "aura/_defer.h"
////
#endif




