//
//  config.h
//  os
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


#if defined(DEBUG) && DEBUG > 0
#ifndef _DEBUG
#define _DEBUG
#endif
#endif


#define PARALLELIZATION_PTHREAD

#define CDECL

#define WCHAR_T_SIZE 32

#define BROAD_PRECOMPILED_HEADER 1

#define OPERATING_SYSTEM_NAMESPACE macos

#define PLATFORM_COMMON_NAMESPACE apple

#define PLATFORM_STRING "macos"

#define PLATFORM_COMMON_STRING "apple"

#define DEFAULT_DIR_SEPARATOR "/"

#define HAVE_UNISTD_H 1

#define _POSIX_C_SOURCE 200809L
#define _DARWIN_C_SOURCE

// #if defined(_DEBUG) && !defined(DEBUG)
// #define DEBUG 1
// #endif


#define HAVE_TERMIOS_H 1


#define OPERATING_SYSTEM_NAME "macos"
#define OPERATING_SYSTEM_NAMESPACE macos

//#ifdef __cplusplus
//typedef wchar_t unichar;
//#else
//#endif

//#define STORE_LAST_BLOCK 1
//#define MEMDFREE 1
//#define MEMDLEAK 1


//#define BSD_STYLE_SOCKETS
//#define HAVE_OPENSSL
#define VARIADIC_TEMPLATE_FORMAT2
#define MUTEX_COND_TIMED


#define __PLATFORM   "macos"



#ifndef APPLEOS
#define APPLEOS
#endif



#ifndef MACOS
#define MACOS
#endif

#if !defined(BSD_UNIX)
#define BSD_UNIX 1
#endif



#define CLASS_DECL_IMPORT
#define CLASS_DECL_EXPORT
#define CLASS_DECL_THREAD __thread
#define __FACTORY_EXPORT extern "C"
#define __FACTORY_IMPORT extern "C"


#ifdef __cplusplus

#define LOG_THIS_TAG (typeid(*this).name())
#define LOG_MEMBER_PREFIX __FUNCTION__

#define ALOG_FUNCTION __FUNCTION__
#define ALOG_LINE __LINE__
#define ALOG_FILE __FILE__

#endif



#define static_inline inline


#define AXIS_FREEIMAGE


#define FONT_SANS "Arial"
#define FONT_SERIF "Times New Roman"
#define FONT_SANS_EX "Geneva"
#define FONT_SERIF_EX "Georgia"
#define FONT_SANS_FX "Futura"
#define FONT_SERIF_FX "Palatino"
#define FONT_SANS_UI "Helvetica"
#define FONT_SERIF_UI "Times"
#define FONT_MONO "Menlo"




#define STR_NEWLINE "\r"




