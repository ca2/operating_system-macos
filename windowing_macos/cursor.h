//
//  cursor.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21 00:26 BRT <3ThomasBS_!!
//
#pragma once


#include "aura/windowing/cursor.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS cursor :
      virtual public ::windowing::cursor
   {
   public:

      
      void *    m_pNSCursor;
      
     
      cursor();
      ~cursor() override;
      
      
      void _create_os_cursor() override;

      void _load_default_cursor();

      void _create_from_image(const ::image::image * pimage, int xHotSpot, int yHotSpot);

      
   };


} // namespace windowing_macos




