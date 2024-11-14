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


void acme_window_bridge::on_left_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
   
   pelemental->on_left_button_up(pmouse);
   
}


void acme_window_bridge::on_left_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};

   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;
   
   pelemental->on_left_button_down(pmouse);
   
}


void acme_window_bridge::on_right_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;

   pelemental->on_right_button_up(pmouse);
   
}


void acme_window_bridge::on_right_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;

   pelemental->on_right_button_down(pmouse);
   
}


void acme_window_bridge::on_mouse_move(int xHost, int yHost, int xAbsolute, int yAbsolute)
{
   
   auto pmouse = m_pwindow->__create_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = m_pwindow->m_pacmeuserinteraction;

   pelemental->on_mouse_move(pmouse);
   
}


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
   
   ::int_rectangle r;
   r.left() = x;
   r.top() = y;
   r.right() = x+w;
   r.bottom() = y+h;

   m_pwindow->m_pacmeuserinteraction->set_rectangle(r);
   
}


bool acme_window_bridge::_is_top_most() const
{
   
   return m_pwindow->m_bTopMost;
   
//   ::cast<::micro::elemental> pelemental = m_pwindow->m_pacmeuserinteraction;
//   
//   if(!pelemental)
//   {
//    
//      return false;
//      
//   }
//   
//   return pelemental->m_bTopMost;
   
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
 
   return m_pwindow->macos_window_become_key();
   
}


void acme_window_bridge::macos_window_resign_key()
{
 
   return m_pwindow->macos_window_resign_key();
   
}


void acme_window_bridge::do_tasks()
{
   
   ::task_run();
   
}



