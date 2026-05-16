//
//  appkit.cpp
//  appkit
//
//  From appkit/appkit.cpp Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:15
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "appkit.h"


static ::appkit::appkit * g_pappkit = nullptr;

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


appkit::~appkit()
{
   
   
}



   ::pointer < ns_image > appkit::load_icon(enum_cursor ecursor)
{
      
      return {};
      
   }
   



} // namespace appkit




CLASS_DECL_APPKIT ::appkit::appkit & AppKit()
{
   
   if(!g_pappkit)
   {
      
      g_pappkit = new ::appkit::appkit();
      
      g_pappkit->initialize(::system());
      
   }
   
   return *g_pappkit;
   
}



::appkit::ns_window_t as_ns_window_t(const ::operating_system::window & operatingsystemwindow)
{
   
   return {(void *) ::as_u64(operatingsystemwindow)};
   
}
