//
//  macos_window_impl.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-18.
//
//

#pragma once
//
//
//#ifdef cplusplus
//
//
//typedef comparable_array < oswindow_data * > oswindow_dataptra;
//
//
//#endif



namespace windowing_macos
{


    class CLASS_DECL_WINDOWING_MACOS window :
      virtual public ::windowing::window,
      virtual public ::aura_window
   {
   public:
      
      
      window();
      ˜window() override;
      

      virtual void aura_window_add_ref() override;
      virtual void aura_window_dec_ref() override;


      virtual void aura_window_draw(CGContextRef cgc, CGSize sizeWindow) override;
      virtual void aura_window_mouse_down(int iButton, double x, double y) override;
      virtual void aura_window_mouse_up(int iButton, double x, double y) override;
      virtual void aura_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton) override;
      virtual void aura_window_mouse_dragged(double x, double y, unsigned long iAppleMouseButton) override;
      virtual void aura_window_mouse_wheel(double deltaY, double x, double y) override;
      virtual void aura_window_double_click(int iButton, double x, double y) override;
      virtual bool aura_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8) override;
      virtual bool aura_window_key_up(unsigned int vk, unsigned int scan) override;
      virtual bool aura_window_key_down(unsigned int uiKeyCode) override;
      virtual bool aura_window_key_up(unsigned int uiKeyCode) override;


      virtual void aura_window_did_become_key() override;
      virtual void aura_window_activate() override;
      virtual void aura_window_deactivate() override;


      virtual void aura_window_resized(CGRect rectangle_i32) override;
      virtual void aura_window_moved(CGPoint point_i32) override;
      virtual void aura_window_iconified() override;
      virtual void aura_window_deiconified() override;





      virtual void aura_window_on_show() override;
      virtual void aura_window_on_hide() override;
      virtual void aura_window_on_miniaturize() override;



   };

void window::aura_window_draw(CGContextRef cgc, CGSize sizeWindowParam)
{

   ::size_i32 sizeWindow(sizeWindowParam.width, sizeWindowParam.height);

   #ifdef EXTRALOG

   static int s_iLastExact = -1;

   string str;

   string strFormat;

   strFormat.Format("|-> window size_i32 %d, %d", sizeWindow.cx, sizeWindow.cy);

   string strSize;

   if(sizeLast != sizeWindow)
   {

      sizeLast = sizeWindow;

      strSize = strFormat;

   }

   str += strFormat;

   rectangle_i32 rect1 = m_puserinteraction->get_window_rect();

   if(rect1.size() != rectLast.size())
   {

      rectLast = rect1;

      // xxxlog output_debug_string("different window rectangle_i32 size_i32 (1)");

   }

#endif

   millis tickNow = millis::now();

   millis tickEllapsed = tickNow - m_millisLastAuraWindowDraw;

   if(tickEllapsed < 12)
   {

      // xxxlog
      //output_debug_string("\n\nwarning: aura_window_draw more than 80FPS!!! Ellapsed: " + str::from(tickEllapsed) + "ms.\n\n");

   }

   m_millisLastAuraWindowDraw = tickNow;

   aura_window_draw_life_time roundwindowdrawlifetime(this);

   critical_section_lock slDisplay(cs_display());

   __pointer(::graphics::graphics) pbuffer = m_pgraphics;

   if(!pbuffer)
   {

      return;

   }
   
   if(!m_puserinteraction)
   {
   
      return;

   }
      
   ::draw2d::graphics_pointer g(e_create);

   g->attach(cgc);

   auto rectClient = m_puserinteraction->get_client_rect();

   g->set_alpha_mode(::draw2d::alpha_mode_set);

   synchronous_lock slGraphics(pbuffer->mutex());
   
   synchronous_lock sl1(pbuffer->get_screen_sync());

   ::image_pointer & imageBuffer2 = pbuffer->get_screen_image();

   if (!imageBuffer2)
   {

      output_debug_string("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

      return;

   }
   
   slGraphics.unlock();

#ifdef EXTRALOG

   if(strSize.has_char())
   {

      s_iLastExact = -1;

   }

   if(s_iLastExact > 0)
   {


      if(s_iLastExact % 10 == 0)
      {

         str = "\n.";

      }
      else
      {

         str = ".";

      }
      
      strFormat.Format("%d", iAge);

      str += strFormat;
      
      output_debug_string(str);
      
   }
   else
   {
      
      INFO(str);
      
   }
   
#endif

   ::size_i32 sizeMin = imageBuffer2->size().minimum(sizeWindow);

   g->draw(sizeMin, imageBuffer2);
   
   m_bPendingRedraw = false;
   
   m_millisLastRedraw.Now();

}


bool window::aura_window_key_down(unsigned int uiKeyCode)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->m_id = e_message_key_down;

   pkey->m_nChar = uiKeyCode;

   spbase = pkey;

   if(m_puserinteraction == nullptr)
   {

      return false;

   }

   m_puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::aura_window_key_up(unsigned int uiKeyCode)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->m_id = e_message_key_up;

   pkey->m_nChar = uiKeyCode;

   spbase = pkey;

   if(m_puserinteraction == nullptr)
   {

      return false;

   }

   m_puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::aura_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->set(get_oswindow(), m_pwindow, e_message_key_down, vk, (lparam)(scan << 16), ::point_i32());

   if(::is_set(pszUtf8))
   {
   
      

      string * pstringText = new string(pszUtf8);

      auto lparam = (::lparam) (iptr) (string *) (pstringText);

      printf("aura_window_key_down e_message_text_composition\n");

      m_puserinteraction->post_message(e_message_text_composition, 0, lparam);
      
      
//         pkey->m_strText = pszUtf8;
//
//         if(pkey->m_strText.has_char())
//         {
//
//            pkey->m_ekey = ::user::e_key_refer_to_text_member;
//
//         }
      
   }
   
   spbase = pkey;

   if(m_puserinteraction == nullptr)
   {

      return false;

   }

   m_puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::aura_window_key_up(unsigned int vk, unsigned int scan)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->set(get_oswindow(), m_pwindow, e_message_key_up, vk, (::lparam)(scan << 16), point_i32());

   spbase = pkey;

   if(m_puserinteraction == nullptr)
   {

      return false;

   }

   m_puserinteraction->send(spbase);

   return spbase->m_bRet;

}


void window::aura_window_mouse_down(int iButton, double x, double y)
{

   __pointer(::user::message) spbase;

   if (!m_pwindow->is_active_window())
   {

      try
      {

         auto pmouseactivate = __new(::message::mouse_activate);

         pmouseactivate->m_id = e_message_mouse_activate;

         spbase = pmouseactivate;

         m_puserinteraction->send(spbase);

         if (spbase->m_lresult == e_mouse_activate || spbase->m_lresult == e_mouse_activate_no_activate_and_eat)
         {


            m_puserinteraction->post_message(e_message_activate, MAKELONG(e_activate_click_active, 0), 0);

         }

      }
      catch (...)
      {

      }

   }

   {

      int message;

      if (iButton == 1)
      {

         message = e_message_right_button_down;

      }
      else
      {

         message = e_message_left_button_down;

      }

      lparam lparam = MAKELPARAM(x, y);
      
      if(m_puserinteraction)
      {

         m_puserinteraction->post_message(message, 0, lparam);
         
      }

   }

}


void window::aura_window_mouse_up(int iButton, double x, double y)
{

   int message;

   if (iButton == 1)
   {

      message = e_message_right_button_up;

   }
   else
   {

      message = e_message_left_button_up;

   }

   lparam lparam = MAKELPARAM(x, y);
   
   if(!m_puserinteraction)
   {
      
      return;
      
   }

   m_puserinteraction->post_message(message, 0, lparam);


}


void window::aura_window_double_click(int iButton, double x, double y)
{

   int message;

   if (iButton == 1)
   {

      message = e_message_right_button_double_click;

   }
   else
   {

      message = e_message_left_button_double_click;

   }

   lparam lparam = MAKELPARAM(x, y);
   
   if(!m_puserinteraction)
   {
      
      return;
      
   }

   m_puserinteraction->post_message(message, 0, lparam);

}


void window::aura_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   bool bOk = true;
   
   if(!m_puserinteraction)
   {
      
      return;
      
   }
   
   __pointer(::user::interaction) pinteraction = m_puserinteraction;

   if(pinteraction.is_set())
   {

      if(pinteraction->m_millisMouseMove.elapsed() < pinteraction->m_millisMouseMoveIgnore)
      {
         
         //printf("mouse_move_ignored %f, %f\n", x, y);

         bOk = false;

      }

      if(bOk)
      {

//            printf("mouse_move_\"accepted\" %f, %f\n", x, y);

         pinteraction->m_millisMouseMove.Now();

         pinteraction->m_pointMouseMove.x = x;

         pinteraction->m_pointMouseMove.y = y;

//            if(false)
//            {
//
//               if(pinteraction->m_millisMouseMovePeriod > 0)
//               {
//
//                  ::size_i32 sizeDistance((pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
//                     (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));
//
//                  if(!pinteraction->m_millisMouseMoveSkip.timeout(pinteraction->m_millisMouseMovePeriod)
//                     && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy < pinteraction->m_iMouseMoveSkipSquareDistance)
//                  {
//
//                     pinteraction->m_iMouseMoveSkipCount++;
//
//                     pinteraction->m_bMouseMovePending = true;
//
//                     if(pinteraction->m_iMouseMoveSkipCount == 2)
//                     {
//
//                        //output_debug_string("\nmmv>skip 2!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 5)
//                     {
//
//                        //output_debug_string("\nmmv>Skip 5!!!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 10)
//                     {
//
//                        //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");
//
//                     }
//
//                     return true;
//
//                  }
//
//                  pinteraction->m_iMouseMoveSkipCount = 0;
//
//                  pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;
//
//               }
//
//            }

      }

   }

   if(!bOk)
   {

      return;

   }

   if(m_puserinteraction == nullptr)
   {

      return;

   }

   lparam lparam = MAKELPARAM(x, y);

   wparam wparam = 0;

   if(ulAppleMouseButton & 1)
   {

      wparam |= ::user::e_button_state_left;

   }

   if(ulAppleMouseButton & 2)
   {

      wparam |= ::user::e_button_state_right;

   }
   
   //printf("mouse_move_\"posted\" %f, %f\n", x, y);
   
   m_puserinteraction->post_message(e_message_mouse_move, wparam, lparam);
   
}


void window::aura_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton)
{

   if(is_destroying())
   {
      
      return;
      
   }

   if(m_puserinteraction == nullptr)
   {

      return;

   }

   lparam lparam = MAKELPARAM(x, y);

   wparam wparam = 0;

   if(ulAppleMouseButton & 1)
   {

      wparam |= ::user::e_button_state_left;

   }

   if(ulAppleMouseButton & 2)
   {

      wparam |= ::user::e_button_state_right;

   }

   m_puserinteraction->post_message(e_message_mouse_move, wparam, lparam);

}


void window::aura_window_mouse_wheel(double deltaY, double x, double y)
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   __pointer(::user::message) spbase;
   
   if(!m_puserinteraction)
   {
      
      return;
      
   }

   {

      auto pwheel  = __new(::message::mouse_wheel);

      pwheel->m_id = e_message_mouse_wheel;

      pwheel->m_point.x = (::i32)x;
      pwheel->m_point.y = (::i32)y;
      pwheel->m_bTranslated = true;

      short delta = deltaY * WHEEL_DELTA / 3.0;

      pwheel->m_wparam = delta << 16;

      spbase = pwheel;

      if(m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->send(spbase);

   }

}


void window::aura_window_resized(CGRect rectangle)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   if(!m_puserinteraction)
   {
      
      return;
      
   }

   m_puserinteraction->post_message(e_message_move,0, MAKELPARAM(rectangle.origin.x, rectangle.origin.y));

   m_puserinteraction->post_message(e_message_size,0, MAKELPARAM(rectangle.size.width, rectangle.size.height));

   return;

//      if(m_puserinteraction == nullptr)
//      {
//
//         return;
//
//      }
//
//      //
//      if(m_puserinteraction->window_state().m_point != rectangle.origin)
//      {
//
//         m_puserinteraction->window_state().m_point = rectangle.origin;
//
//         TRACE("window::aura_window_resized effective position is different from requested position");
//
//         m_puserinteraction->post_message(e_message_move, 0, m_puserinteraction->window_state().m_point.lparam());
//
//      }
//
//      if(m_puserinteraction->m_sizeRequest != rectangle.size_i32)
//      {
//
//         m_puserinteraction->m_sizeRequest = rectangle.size_i32;
//
//         TRACE("window::aura_window_resized effective position is different from requested position");
//
//         m_puserinteraction->post_message(e_message_size, 0, m_puserinteraction->m_sizeRequest.lparam());
//
//      }
//
//      m_puserinteraction->m_point = rectangle.origin;
//
//      m_puserinteraction->m_size = rectangle.size_i32;
//
////      ::size_i32 sz;
////
////      point_i64 pt(rectangle.origin.x, rectangle.origin.y);
////
////      bool bMove = false;
////
////      {
////
////         synchronous_lock synchronouslock(m_puserinteraction->mutex());
////
////         if (pt != m_puserinteraction->m_rectParentClient.top_left())
////         {
////
////            bMove = true;
////
////         }
////
////         m_puserinteraction->m_rectParentClient.move_to(point);
////
////         m_puserinteraction->set_size(rectangle.size_i32);
////
////         sz = m_puserinteraction->m_rectParentClient.size();
////
////      }
////
////      if(m_puserinteraction == nullptr)
////      {
////
////         return;
////
////      }
////
////      m_puserinteraction->post_message(e_message_size, 0, sz.lparam());
////
////      if (bMove)
////      {
////
////         m_puserinteraction->post_message(e_message_move, 0, pt.lparam());
////
////      }

//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         //pmessage->m_bRet = true;
//
//         return;
//
//      }
//
//      ::rectangle_i32 rectSize;
//
//      __copy(rectSize, rectangle);
//
//      if(m_puserinteraction->window_state().rectangle_i32() != rectSize)
//      {
//
//         m_puserinteraction->window_state().m_point = rectSize.origin();
//
//         m_puserinteraction->window_state().m_size = rectSize.size();
//
//      }
//
//
//      if (m_puserinteraction->layout().sketch().rectangle_i32() != rectSize)
//      {
//
//         m_puserinteraction->place(rectSize);
//
//         if (m_puserinteraction->layout().design().display() != e_display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_need_layout();
//
//         m_puserinteraction->set_need_redraw();
//
//      }

}


void window::aura_window_moved(CGPoint point)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_bEatMoveEvent)
   {
      
      m_bEatMoveEvent = false;
      
      return;
      
   }

   m_puserinteraction->post_message(e_message_move,0, MAKELPARAM(point.x, point.y));

   return;

//      if(m_puserinteraction == nullptr)
//      {
//
//         return;
//
//      }
//
//
//      ::point_i32 pointMove;
//
//      __copy(pointMove, point);
//
//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         //pmessage->m_bRet = true;
//
//         return;
//
//      }
//
//      ///__pointer(::message::move) pmove(pmessage);
//
//      if (m_puserinteraction->layout().sketch().m_point != pointMove)
//      {
//
//         m_puserinteraction->move_to(pointMove);
//
//         if (m_puserinteraction->layout().design().display() != e_display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_reposition();
//
//         m_puserinteraction->set_need_redraw();
//
//      }
//
//
////      if(m_puserinteraction->m_pointRequest != point_i32)
////      {
////
////         m_puserinteraction->m_pointRequest = point;
////
////         TRACE("window::aura_window_resized effective position is different from requested position");
////
////      }
////
////      m_puserinteraction->m_point = point;

}


void window::aura_window_did_become_key()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   m_millisLastExposureAddUp.Now();

}


void window::aura_window_activate()
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   m_pwindow->set_active_window();

   if(m_puserinteraction == nullptr)
   {

      return;

   }

   m_puserinteraction->set_need_redraw();

}


void window::aura_window_deactivate()
{

   if(is_destroying())
   {
      
      //return;
      
      output_debug_string("destroying");
      
   }
   
   auto pwindowing = m_pwindowing;
   
   auto pwindowActive = pwindowing->get_active_window(m_puserinteraction->m_pthreadUserInteraction);
   
   if(::is_null(pwindowActive))
   {
      
      return;
      
   }
   
   if(pwindowActive != m_pwindow)
   {
      
      return;
      
   }
   
   pwindowing->clear_active_window(m_puserinteraction->m_pthreadUserInteraction);
   
   //::deactivate_window(get_handle());

//      if(m_puserinteraction == nullptr)
//      {
//
//         return;
//
//      }

   if(!is_destroying())
   {
   
      m_puserinteraction->set_need_redraw();
      
   }

}


void window::aura_window_iconified()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_puserinteraction == nullptr)
   {

      return;

   }
   
   if(m_puserbox != nullptr)
   {

      m_puserbox->m_windowrect.m_edisplayPrevious = m_puserbox->m_windowrect.m_edisplay;
      
   }

   m_puserinteraction->layout().window() = ::e_display_iconic;

}


void window::aura_window_deiconified()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_puserinteraction == nullptr)
   {

      return;

   }
   
   if(m_puserbox)
   {

      if(m_puserbox->m_windowrect.m_edisplayPrevious == ::e_display_iconic)
      {

         m_puserbox->m_windowrect.m_edisplayPrevious = ::e_display_normal;

      }
      
      m_puserinteraction->_001OnDeiconify(m_puserbox->m_windowrect.m_edisplayPrevious);

      
   }


}


void window::aura_window_on_show()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_puserinteraction == nullptr)
   {

      return;

   }

   m_millisLastExposureAddUp.Now();

   m_puserinteraction->message_call(e_message_show_window, 1);

   //m_puserinteraction->user_interaction_update_visibility_cache(true);

//      if(!(m_puserinteraction->m_ewindowflag & window_flag_miniaturizable))
//      {
//
//         if(m_puserinteraction->layout().sketch().display() == e_display_iconic)
//         {
//
//            m_puserinteraction->m_windowState3
//
//         }
//
//      }

   m_puserinteraction->set_need_layout();

   m_puserinteraction->set_need_redraw();

   m_puserinteraction->post_redraw();

}


void window::aura_window_on_hide()
{

//      if(is_destroying())
//      {
//
//         return;
//
//      }
   
   INFO("macos::window::aura_window_on_hide");

   if(m_puserinteraction == nullptr)
   {

      WARN("macos::window::aura_window_on_hide (2) m_puserinteraction == nullptr");

      return;

   }
   
   if(m_puserinteraction->layout().window().is_screen_visible())
   {

      m_puserinteraction->hide();

   }
   
   m_puserinteraction->message_call(e_message_show_window, 0);

}


void window::aura_window_on_miniaturize()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_puserinteraction == nullptr)
   {

      return;

   }

   //m_puserinteraction->message_call(e_message_show_window, 0);

   //m_puserinteraction->user_interaction_update_visibility_cache(false);

}


//   void CLASS_DECL_AURA __pre_init_dialog(
//   ::user::interaction * pWnd, RECTANGLE_I32 * lpRectOld, ::u32* pdwStyleOld)
//   {
//      ASSERT(lpRectOld != nullptr);
//      ASSERT(pdwStyleOld != nullptr);
//
//      pWnd->get_window_rect(lpRectOld);
//      *pdwStyleOld = pWnd->GetStyle();
//   }

//   __STATIC void CLASS_DECL_AURA __post_init_dialog(
//      ::user::interaction * p, const RECTANGLE_I32& rectOld, ::u32 dwStyleOld)
//   {
//      // must be hidden to start with
//      if (dwStyleOld & WS_VISIBLE)
//         return;
//
//      // must not be visible after WM_INITDIALOG
//      if (pWnd->GetStyle() & (WS_VISIBLE | WS_CHILD))
//         return;
//
//      // must not move during WM_INITDIALOG
//      ::rectangle_i32 rectangle;
//      pWnd->get_window_rect(rectangle);
//      if (rectOld.left != rectangle.left || rectOld.top != rectangle.top)
//         return;
//
//      // must be unowned or owner disabled
//      ::user::interaction * pParent = pWnd->GetWindow(GW_OWNER);
//      if (pParent != nullptr && pParent->is_window_enabled())
//         return;
//
//      if (!pWnd->CheckAutoCenter())
//         return;
//
//      // center modal dialog boxes/message boxes
//      //MAC_WINDOW(pWnd)->CenterWindow();
//   }



} // namespace windowing_macos




