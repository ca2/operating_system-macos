#include "framework.h"
#include "acme/filesystem/filesystem/path_array.h"
#include "acme/primitive/collection/str_array.h"
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





