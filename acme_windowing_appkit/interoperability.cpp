
//
//  ns_interoperability.cpp
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on May 2026.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "ns_interoperability.h"
#include "acme/operating_system/macos/window.h"




namespace cross_windows
{


   ::operating_system::window get_dlg_item(const ::operating_system::window & operatingsystemwindow, int iDlgItem)
   {
      
      auto u = ::as_u64(operatingsystemwindow);
      
      if(u == 0)
      {
         
         ::information("operating system window is not a window");
         
         return {};
         
      }
      
      //auto uChild = ns_get_dlg_item(u, iDlgItem);
      
      return {::windowing::e_operating_ambient_macos_impact, u, (::uptr) iDlgItem};
      
//      ::cast < ::appkit::acme::windowing::windowing > pwindowing = ::system()->acme_windowing();
//
//      return pwindowing->__cross_windows__get_dlg_item(operatingsystemwindow, iDlgItem);
      
   }


::string get_window_text(const ::operating_system::window & operatingsystemwindow)
{
   
   ::string str;
   
   if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact)
   {
      
      auto p = ns_get_impact_text(operatingsystemwindow.m_opaque.m_ulla[0], operatingsystemwindow.m_opaque.m_ulla[1]);
      
      if(!p)
      {
         
         return {};
         
      }
      
      str = p;
      
      ::free(p);
      
   }
   else if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos)
   {
      
      auto p = ns_get_window_text(operatingsystemwindow.m_opaque.m_ulla[0]);
      
      if(!p)
      {
         
         return {};
         
      }
      
      str = p;
      
      ::free(p);

   }
   
   return str;

}

#define NSIMPACT(o) (o).m_opaque.m_ulla[0], (o).m_opaque.m_ulla[1]

::collection::index combo_box_insert_string(const ::operating_system::window & operatingsystemwindow, ::collection::index i, const ::scoped_string & scopedstr)
{
   
   return ns_combo_box_insert_string(NSIMPACT(operatingsystemwindow), i, ::string(scopedstr));

}
void combo_box_reset_content(const ::operating_system::window & operatingsystemwindow)
{
   return ns_combo_box_reset_content(NSIMPACT(operatingsystemwindow));
}

} // namespace cross_windows


void throw_wrong_ns_type()
{
   
   throw ::exception(error_wrong_type, "Wrong NS type");
   
}
