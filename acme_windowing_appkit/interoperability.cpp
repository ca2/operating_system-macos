
//
//  ns_interoperability.cpp
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on May 2026.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "interoperability.h"
#include "acme/operating_system/macos/window.h"


namespace cross_windows
{


void destroy_window(const ::operating_system::window & operatingsystemwindow)
{
   
   if(operatingsystemwindow.is_impact())
   {
      ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
      return ns_impact_destroy_window(nsimpact);
      
   }
   else
   {
      ::appkit::ns_window_t nswindow(operatingsystemwindow);
      return ns_window_destroy_window(nswindow);
      
   }
   
}


void show_window_show(const ::operating_system::window & operatingsystemwindow)
{
   
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   ns_window_show(nswindow);
}
void show_window_hide(const ::operating_system::window & operatingsystemwindow)
{
   
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   ns_window_hide(nswindow);

}

void get_client_rect(const ::operating_system::window & operatingsystemwindow, ::i32_rectangle * prectangle)
{
   
   ::core_graphics::cg_rect cgrect{};
   
   if(operatingsystemwindow.is_impact())
   {
      ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
      ns_impact_get_client_rect(nsimpact, &cgrect);
      
   }
   else
   {
      ::appkit::ns_window_t nswindow(operatingsystemwindow);
      ns_window_get_client_rect(nswindow, &cgrect);
      
   }
   
   prectangle->left = cgrect.origin.x;
   prectangle->top = cgrect.origin.y;
   prectangle->right = cgrect.origin.x + cgrect.size.w;
   prectangle->bottom = cgrect.origin.y + cgrect.size.h;
   
}
void invalidate_rect(const ::operating_system::window & operatingsystemwindow,
                     const ::i32_rectangle * prectangle, bool bErase)
{
   
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   if(prectangle)
   {
      ::core_graphics::cg_rect cgrect;
      cgrect.origin.x = prectangle->left;
      cgrect.origin.y = prectangle->top;
      cgrect.size.w = prectangle->width();
      cgrect.size.h = prectangle->height();
      ns_window_redraw(nswindow, &cgrect, bErase);
   }
   else
   {
      ns_window_redraw(nswindow, nullptr, bErase);
      
   }

}



int set_window_pos(const ::operating_system::window & operatingsystemwindow,
                    const ::operating_system::window & operatingsystemwindowOther,
                    int x, int y, int w, int h, int flags)
{

   if(operatingsystemwindow.is_impact())
   {
      ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
      ::appkit::ns_impact_t nsimpactOther(operatingsystemwindowOther);
      return ns_impact_set_window_pos(nsimpact, nsimpactOther, x, y, w, h, flags);
      
   }
   else
   {
      ::appkit::ns_window_t nswindow(operatingsystemwindow);
      ::appkit::ns_window_t nswindowOther(operatingsystemwindowOther);
      return ns_window_set_window_pos(nswindow, nswindowOther, x, y, w, h, flags);
      
   }
   

}


::i32_rectangle get_window_monitor_rect(const ::operating_system::window & operatingsystemwindow)
{
   
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   auto cgrect = ns_window_monitor_rect(nswindow);
   ::i32_rectangle r;
   r.left = cgrect.origin.x;
   r.top = cgrect.origin.y;
   r.right = r.left+cgrect.size.w;
   r.bottom = r.top + cgrect.size.h;
   return r;
   

}


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
      
      auto p = ns_get_impact_text(operatingsystemwindow);
      
      if(!p)
      {
         
         return {};
         
      }
      
      str = p;
      
      ::free(p);
      
   }
   else if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos)
   {
      
      auto p = ns_get_window_text(NSWINDOW(operatingsystemwindow));
      
      if(!p)
      {
         
         return {};
         
      }
      
      str = p;
      
      ::free(p);

   }
   
   return str;

}

void set_window_text(const ::operating_system::window & operatingsystemwindow, const ::scoped_string & scopedstr)
{
   
   ::string str(scopedstr);
   
   if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos_impact)
   {
      
      ns_set_impact_text(operatingsystemwindow, str);
      
   }
   else if(operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_macos)
   {
      
      ns_set_window_text(NSWINDOW(operatingsystemwindow), str);
      
   }
   
   return str;

}

::collection::index combo_box_insert_string(const ::operating_system::window & operatingsystemwindow, ::collection::index i, const ::scoped_string & scopedstr)
{
   
   return ns_combo_box_insert_string(operatingsystemwindow, i, ::string(scopedstr));

}
void combo_box_reset_content(const ::operating_system::window & operatingsystemwindow)
{
   ns_combo_box_reset_content(operatingsystemwindow);
}
::collection::count combo_box_get_count(const ::operating_system::window & operatingsystemwindow)
{
   return ns_combo_box_get_count(operatingsystemwindow);
}
::collection::index combo_box_get_cur_sel(const ::operating_system::window & operatingsystemwindow)
{
   
   return ns_combo_box_get_cur_sel(operatingsystemwindow);
}
void combo_box_set_cur_sel(const ::operating_system::window & operatingsystemwindow, ::collection::index i)
{
   
   ns_combo_box_set_cur_sel(operatingsystemwindow, i);
   
}

void combo_box_set_item_data(const ::operating_system::window & operatingsystemwindow, ::collection::index i, void * p)
{
   ns_combo_box_set_item_data(operatingsystemwindow, i, p);
   
}

void * combo_box_get_item_data(const ::operating_system::window & operatingsystemwindow, ::collection::index i)
{
   
   return ns_combo_box_get_item_data(operatingsystemwindow, i);
}
::string combo_box_get_lb_text(const ::operating_system::window & operatingsystemwindow, ::collection::index i)
{
   return ns_combo_box_get_lb_text(operatingsystemwindow, i);
}
void combo_box_delete_string(const ::operating_system::window & operatingsystemwindow, ::collection::index i)
{
   return ns_combo_box_delete_string(operatingsystemwindow, i);
}


} // namespace cross_windows


void throw_wrong_ns_type()
{
   
   throw ::exception(error_wrong_type, "Wrong NS type");
   
}


namespace cross_ns {

void minimize_window(const ::operating_system::window & operatingsystemwindow)
{
      ::appkit::ns_window_t nswindow(operatingsystemwindow);
      ns_window_minimize(nswindow);
   
}

void enter_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow)
{
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   ns_window_enter_immersive_fullscreen(nswindow);
}
void exit_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow)
{
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   ns_window_exit_immersive_fullscreen(nswindow);
}
bool is_in_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow)
{
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   return ns_window_is_in_immersive_fullscreen(nswindow);
}
void toggle_immersive_fullscreen(const ::operating_system::window & operatingsystemwindow)
{
   ::appkit::ns_window_t nswindow(operatingsystemwindow);
   ns_window_toggle_immersive_fullscreen(nswindow);
}

void set_mouse_cursor(const ::operating_system::window & operatingsystemwindow, ::enum_cursor ecursor)
{
   
   if(operatingsystemwindow.is_impact())
   {
      ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
      return ns_impact_set_mouse_cursor(nsimpact, ecursor);
      
   }
   else
   {
      ::appkit::ns_window_t nswindow(operatingsystemwindow);
      return ns_window_set_mouse_cursor(nswindow, ecursor);
      
   }
   

}
//void add_cursor_rectangle(const ::operating_system::window & operatingsystemwindow, const ::i32_rectangle & rectangle, ::enum_cursor ecursor)
//{
//   ::appkit::ns_window_t nswindow(operatingsystemwindow);
//   ::core_graphics::cg_rect cgrect;
//   cgrect.origin.x = rectangle.left;
//   cgrect.origin.y = rectangle.top;
//   cgrect.size.w = rectangle.width();
//   cgrect.size.h = rectangle.height();
//   ns_window_add_cursor_rectangle(nswindow, cgrect, ecursor);
//}

void set_progress_bar_range(const ::operating_system::window & operatingsystemwindow, int iMinimum, int iMaximum)
{
   
   ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
   return ns_progress_bar_set_range(nsimpact, iMinimum, iMaximum);

}

void set_progress_bar_position(const ::operating_system::window & operatingsystemwindow, int iPosition)
{
   
   ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
   return ns_progress_bar_set_position(nsimpact, iPosition);

}

bool check_box_is_checked(const ::operating_system::window & operatingsystemwindow)
{
   
   ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
   return ns_check_box_is_checked(nsimpact);

}
void check_box_set_checked(const ::operating_system::window & operatingsystemwindow, bool checked)
{
   
   ::appkit::ns_impact_t nsimpact(operatingsystemwindow);
   ns_check_box_set_checked(nsimpact, checked);

}


} // namespace cross_ns
