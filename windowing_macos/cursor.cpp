//
//  cursor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 28/05/21  00:26 BRT <3ThomasBS_!!
//
#include "framework.h"


void * ns_get_default_system_cursor(enum_cursor ecursor);


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


} // namespace windowing_macos




