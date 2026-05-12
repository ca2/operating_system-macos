//
//  ns_window.cpp
//  core_graphics
//
//  From early core_graphics/ns_window.cpp by
//  Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_window.h"

void ns_window_release(void * & pNS);

namespace appkit
{

   ns_window::ns_window()
   {
   
      m_pNS = nullptr;
      
   }


   ns_window::~ns_window()
   {
   
      ns_window_release(m_pNS);
   
   }


} //  namespace appkit



