//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "acme_window_bridge.h"
#include "acme/nano/graphics/device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
//#include "acme/platform/sequencer.h"
#include "acme/platform/node.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/frame_interaction.h"
#include "acme/user/user/mouse.h"
#include <CoreGraphics/CoreGraphics.h>

void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();

void ns_app_run();

void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const ::int_rectangle &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const ::int_point & point);

void screen_coordinates_aware_copy(::int_point & point, const CGPoint & cgpoint);

namespace appkit
{
//void acme_window_bridge::on_left_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
//{
//
//   auto pmouse = m_pwindow->øcreate_new <::user::mouse>();
//
//   pmouse->m_pointHost = {xHost, yHost};
//
//   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
//
//   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
//
//   pelemental->on_left_button_up(pmouse);
//
//}
//
//
//void acme_window_bridge::on_left_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
//{
//
//   auto pmouse = m_pwindow->øcreate_new <::user::mouse>();
//
//   pmouse->m_pointHost = {xHost, yHost};
//
//   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
//
//   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
//
//   pelemental->on_left_button_down(pmouse);
//
//}
//
//
//void acme_window_bridge::on_right_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
//{
//
//   auto pmouse = m_pwindow->øcreate_new <::user::mouse>();
//
//   pmouse->m_pointHost = {xHost, yHost};
//
//   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
//
//   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
//
//   pelemental->on_right_button_up(pmouse);
//
//}
//
//
//void acme_window_bridge::on_right_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
//{
//
//   auto pmouse = m_pwindow->øcreate_new <::user::mouse>();
//
//   pmouse->m_pointHost = {xHost, yHost};
//
//   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
//
//   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
//
//   pelemental->on_right_button_down(pmouse);
//
//}
//
//
//void acme_window_bridge::on_mouse_move(int xHost, int yHost, int xAbsolute, int yAbsolute)
//{
//
//   auto pmouse = m_pwindow->øcreate_new <::user::mouse>();
//
//   pmouse->m_pointHost = {xHost, yHost};
//
//   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
//
//   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
//
//   pelemental->on_mouse_move(pmouse);
//
//}


void acme_window_bridge::on_char(int iChar)
{
   
   //m_pwindow->on_char(iChar);
   
}


void acme_window_bridge::_on_draw_frame(CGContextRef cg, CGSize sizeFrame)
{
   
   //::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
   
   m_pwindow->_draw(cg);
   
}



void acme_window_bridge::on_layout(int x, int y, int w, int h)
{
   
   m_pwindow->_on_layout(x, y, w, h);
   
}


void acme_window_bridge::set_cg_window_id(CGWindowID cgwindowid)
{
   
   m_pwindow->m_macoswindow.m_struct.m_cgwindowid = cgwindowid;
   
}


bool acme_window_bridge::_is_top_most() const
{
   
   //   return m_pwindow->m_pacmeuserinteraction->m_bTopMost;
   
   ::cast<::acme::user::frame_interaction> pelemental = m_pwindow->m_pacmeuserinteraction;
   
   if(!pelemental)
   {
      
      return false;
      
   }
   
   return pelemental->m_bTopMost;
   
}


bool acme_window_bridge::_is_popup_window() const
{
   
   return m_pwindow->m_pacmeuserinteraction->is_popup_window();
   
}


void acme_window_bridge::macos_window_become_main()
{
   
   return m_pwindow->macos_window_become_main();
   
}


void acme_window_bridge::macos_window_resign_main()
{
   
   return m_pwindow->macos_window_resign_main();
   
}


void acme_window_bridge::macos_window_become_key()
{
   
   m_bIsActiveCached = true;
   return m_pwindow->macos_window_become_key();
   
}


void acme_window_bridge::macos_window_resign_key()
{
   m_bIsActiveCached = false;
   return m_pwindow->macos_window_resign_key();
   
}


void acme_window_bridge::do_tasks()
{
   
   ::task_run();
   
}


::acme::windowing::window * acme_window_bridge::acme_windowing_window()
{
 
   return m_pwindow;
   
}


void acme_window_bridge::on_control_box_close()
{
   
   auto pwindow = acme_windowing_window();
   
   if(::is_set(pwindow))
   {
    
      pwindow->on_control_box_close();
      
   }
   
}


void acme_window_bridge::on_control_box_minimize()
{
   
   auto pwindow = acme_windowing_window();
   
   if(::is_set(pwindow))
   {
    
      pwindow->on_control_box_minimize();
      
   }

}


void acme_window_bridge::on_control_box_zoom()
{
   
   auto pwindow = acme_windowing_window();
   
   if(::is_set(pwindow))
   {
    
      pwindow->on_control_box_zoom();
      
   }

}

   
   bool acme_window_bridge::should_use_desktop_ambient_like_control_box() const
   {
   
      auto pwindow = m_pwindow;
   
      if(::is_set(pwindow))
      {
    
         return pwindow->should_use_desktop_ambient_like_control_box();
      
      }
   
      return false;
   
   }


} // namespace appkit

///// what is osdata
//void * __ns_acme_window_osdata(CFTypeRef typeref);
//
//
//void * oswindow_osdata(oswindow hwnd)
//{
// 
//   auto pappkitacmewindowingwindow = dynamic_cast < ::appkit::acme::windowing::window * >(hwnd);
//   
//   auto pacmewindowbridge = pappkitacmewindowingwindow->m_pacmewindowbridge;
//   
//   return __nsacmewindow_osdata(pacmewindowbridge->m_pnsacmewindow);
//   
//}
//
//
//
