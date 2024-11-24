#include "framework.h"
#include "acme/filesystem/filesystem/path_array.h"
#include "acme/prototype/collection/str_array.h"
#include <Carbon/Carbon.h>


int_bool GetCursorPos(INT_POINT * ppointCursor)
{

   HIPoint point;

   HICoordinateSpace space = kHICoordSpaceScreenPixel;

   HIGetMousePosition(space, nullptr, &point);

   ppointCursor->x = point.x;

   ppointCursor->y = point.y;

   return true;

}





