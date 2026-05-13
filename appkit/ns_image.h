//
//  ns_image.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:21
//  <3ThomasBorregaardSørensen!!
//
#pragma once


namespace appkit
{


   class CLASS_DECL_APPKIT ns_image :
      virtual public ::particle
   {
   public:
      
      
      ns_image_t m_nsimage;
      
      
      ns_image();
      ~ns_image();
      
      
      virtual ::i32_size get_size();
      
      
      
   };

} // namespace appkit





