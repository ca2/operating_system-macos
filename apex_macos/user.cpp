#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "_library.h"
//#endif
#include <Carbon/Carbon.h>


int_bool GetCursorPos(POINT_I32 * ppointCursor)
{

   HIPoint point;

   HICoordinateSpace space = kHICoordSpaceScreenPixel;

   HIGetMousePosition(space, nullptr, &point);

   ppointCursor->x = point.x;

   ppointCursor->y = point.y;

   return true;

}


char * mm_browse_folder(void * pSystem, const char * pszStartDir, bool bCanCreateDirectories);


string apple_browse_folder(class ::system * psystem, const char * pszStartDir, bool bCanCreateDirectories)
{

   return ::string_from_strdup(mm_browse_folder(psystem, pszStartDir, bCanCreateDirectories));

}


char** mm_browse_file_open(void * psystem, const char ** pszStartDir, bool bMulti);


string_array apple_browse_file_open(class ::system * psystem, const char ** pszStartDir, bool bMulti)
{
   
   string_array stra;
   
   stra.from_strdup(mm_browse_file_open(psystem, pszStartDir, bMulti));

   return stra;

}



