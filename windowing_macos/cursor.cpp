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
void ns_cursor_free(void * pNSCursor);


namespace windowing_macos
{


   cursor::cursor()
   {
      
      
   }


   cursor::~cursor()
   {
   
      if(m_pNSCursor)
      {
         
         ns_cursor_free(m_pNSCursor);
         
         m_pNSCursor = nullptr;
         
      }
   
   }


   void cursor::_create_os_cursor()
   {

      if(::is_ok(m_pimage))
      {
         
         try
         {

            _create_from_image(m_pimage, m_szHotspotOffset.cx, m_szHotspotOffset.cy);
          
            return;
            
         }
         catch (...)
         {

         }
         
      }
      
      _load_default_cursor();
      
   }


   void cursor::_load_default_cursor()
   {
      
      if(m_pNSCursor)
      {
         
         ns_cursor_free(m_pNSCursor);
         
         m_pNSCursor = nullptr;
         
      }

      m_pNSCursor = ns_get_default_system_cursor(m_ecursor);

      if(!m_pNSCursor)
      {
         
         throw ::exception(error_resource);
         
      }

   }


   void cursor::_create_from_image(const ::image * pimage, int xHotSpot, int yHotSpot)
   {
      
      if(m_pNSCursor)
      {
         
         ns_cursor_free(m_pNSCursor);
         
         m_pNSCursor = nullptr;
         
      }

      CGImageRef cgimageref = cgimageref_from_image(pimage);

      m_pNSCursor = nscursor_from_cgimageref(cgimageref, pimage->width(), pimage->height(), xHotSpot, yHotSpot);

   }


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



