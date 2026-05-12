//
//  appkit.cpp
//  appkit
//
//  From appkit/appkit.cpp Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:15
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "appkit.h"


static ::appkit::appkit * g_pcoregraphics = nullptr;

namespace appkit
{

   appkit::appkit()
   {
      
      if(::system()->has_property("appkit::appkit"))
      {
         
         throw ::exception(error_wrong_state);
         
      }
      
      ::system()->property("appkit::appkit") = this;
      
      
   }


} // namespace appkit




CLASS_DECL_APPKIT ::appkit::appkit * CoreGraphics()
{
   
   if(!g_pcoregraphics)
   {
      
      g_pcoregraphics = new ::appkit::appkit();
      
      g_pcoregraphics->initialize(::system());
      
   }
   
   return g_pcoregraphics;
   
}
