//
//  ns_window.h
//  core_graphics
//
//  From early core_graphics/ns_bitmap.h by
//  Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:52 <3ThomasBorregaardSørensen!!
//
//
#pragma once


#include "operating_system-apple/acme_windowing_kit/window.h"
#include "acme/operating_system/macos/window.h"


namespace appkit
{




   class CLASS_DECL_APPKIT ns_window :
      virtual public ::apple_kit::acme::windowing::window
   {
   public:
      
      ns_window_t m_nswindow;
      
      ::operating_system::macos_window m_macoswindow;
      
      
      ns_window();
      ~ns_window();
      
      
      //virtual ::i32 get_size();
      
      
      
   };

} // namespace appkit




