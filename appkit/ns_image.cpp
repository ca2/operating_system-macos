//
//  ns_image.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:23
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_image.h"
#include "acme/prototype/geometry2d/size.h"
#include "_mm.h"

namespace appkit
{

   ns_image::ns_image()
   {
   
      //m_pNS = nullptr;
      
   }


   ns_image::~ns_image()
   {
   
      ns_image_release(m_nsimage);
   
   }


   ::i32_size ns_image::get_size()
   {
   
      auto cgimage = ns_image_get_cg_image(m_nsimage);
      
      auto cgsize = cg_image_get_size(cgimage);
      
      return {cgsize.w, cgsize.h};
      
   }


} //  namespace core_graphics



