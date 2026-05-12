//
//  ns_window.cpp
//  core_graphics
//
//  From early core_graphics/ns_window.cpp by
//  Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_window.h"
#include "_mm.h"


namespace appkit
{

   ns_window::ns_window()
   {
   
      //m_pNS = nullptr;
      
   }


   ns_window::~ns_window()
   {
   
      ns_window_release(m_nswindow);
   
   }


} //  namespace appkit



