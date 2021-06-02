//
//  cursor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21  00:26 BRT <3ThomasBS_!!
//
#include "framework.h"


void * ns_get_default_system_cursor(enum_cursor ecursor);
CGImageRef cgimageref_from_image(const ::image * pimage);
void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);


namespace windowing_macos
{


   cursor::cursor()
   {
      
      
   }


   cursor::~cursor()
   {
   
   
   }


   ::e_status cursor::load_default_cursor(enum_cursor ecursor)
   {

      m_pNSCursor = ns_get_default_system_cursor(ecursor);

      if(!m_pNSCursor)
      {
         
         return error_failed;
         
      }

     return ::success;
      
   }


   ::e_status cursor::create_from_image(const ::image * pimage, int xHotSpot, int yHotSpot)
   {
      
      CGImageRef cgimageref = cgimageref_from_image(pimage);

      m_pNSCursor = nscursor_from_cgimageref(cgimageref, pimage->width(), pimage->height(), xHotSpot, yHotSpot);

      return ::success;
      
   }


//   HCURSOR context_image::load_default_cursor(e_cursor ecursor)
//   {
//
//   #ifdef MACOS
//
//      return nscursor_system(ecursor);
//
//   #else
//
//      return nullptr;
//
//   #endif
//
//   }


//void context_image::set_cursor_image(const ::image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   if(pimage)
//   {
//
//#ifdef MACOS
//      
//      ns_set_cursor_cgimageref(cgimageref_from_image(pimage), pimage->width(), pimage->height(), xHotSpot, yHotSpot);
//      
//#endif
//
//   }
//   else
//   {
//
//#ifdef MACOS
//      
//      ns_set_cursor_cgimageref(nullptr, 0, 0, 0, 0);
//      
//#endif
//
//   }
//
//}
//



} // namespace windowing_macos






bool macos_get_cursor_position(POINT_I32 * ppointCursor)
{
 
   HIPoint point;
 
   HICoordinateSpace space = kHICoordSpaceScreenPixel;
 
   HIGetMousePosition(space, nullptr, &point);
 
 
   ppointCursor->x = point.x;
 
   ppointCursor->y = point.y;
 
 
 
   return TRUE;
 
}
