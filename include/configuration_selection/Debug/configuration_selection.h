// Created by camilo on 2023-10-19 19:35 <3ThomasBorregaardSorensen!!
#pragma once


//#ifndef _DEBUG
//#define _DEBUG
//#endif // _DEBUG

#define NDEBUG


//#ifndef NDEBUG
//#define NDEBUG
//#endif // NDEBUG


#define MEMDLEAK 0
#define MEMDLEAK_DEFAULT 0


#ifdef __ASAN_ON__

#define REFERENCING_DEBUGGING 0

#else

#define REFERENCING_DEBUGGING 1

#endif



