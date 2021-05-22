//
//  macos_window.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "framework.h"
#include "window_impl.h"
#include "oswindow_data.h"
#include "acme/parallelization/message_queue.h"
#include <CoreGraphics/CoreGraphics.h>


#define WHEEL_DELTA 120

void * new_macos_window(macos_window * papexwindow, CGRect rect, unsigned int uStyle);


namespace windowing_macos
{


window::window()
{
   
   
}


window::~window()
{
   
   
}


::e_status window::create_window(::user::interaction_impl * pimpl)
{

   //if (::is_window(get_handle()))
   //{

   //   DestroyWindow();

   //}

   //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
   //       __is_valid_atom(lpszClassName));
//      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));

   // allow modification of several common create parameters
   //::user::system createstruct;
   //      pusersystem->m_createstruct.hwndParent = hWndParent;
   //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
   
   auto puserinteraction = pimpl->m_puserinteraction;
   
   auto pusersystem = puserinteraction->m_pusersystem;
   
   //pusersystem->m_createstruct.hMenu = nullptr;
   //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
   //pusersystem->m_createstruct.lpCreateParams = lpParam;

   if (!puserinteraction->pre_create_window(pusersystem))
   {

      return false;

   }

   install_message_routing(puserinteraction);

   //hook_window_create(puserinteraction);

   CGRect rectangle_i32;

   RECTANGLE_I32 rectParam;

//      rectParam.left = m_pusersystem->m_createstruct.x;
//      rectParam.top = pusersystem->m_createstruct.y;
//      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx;
//      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy;

//      __copy(rectangle, rectParam);
//
//      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
//      {
//
//         return true;
//
//      }
//      else
//      {

      unsigned uStyle = 0;

      if(puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
      {

#define NSWindowStyleMaskMiniaturizable (1 << 2)

         uStyle |= NSWindowStyleMaskMiniaturizable;

      }
   
      auto rectangle = puserinteraction-> get_window_rect();
   
      CGRect cgrect;
   
      //__copy(cgrect, rectangle);
      //__todo?
      //windowing()->copy(cgrect, rectangle);
      //or
      //display()->copy(cgrect, rectangle);
      //because rectangle origin is top-left
      //and because cgrect origin is bottom-left and,
      //the origin of screen is at bottom.

      auto pNSWindow = new_macos_window(this, cgrect, uStyle);
   
      set_os_data(pNSWindow);

      puserinteraction->layout().window() = ::top_left(rectParam);

      puserinteraction->layout().window() = ::size_i32(rectParam);

      __refer(puserinteraction->m_pthreadUserInteraction, ::get_task());

      //puserinteraction->place(rectParam);



      m_pimpl = pimpl;

      //oswindow_assign(m_oswindow, this);

   //}

   auto lresult = puserinteraction->send_message(e_message_create); //
   //, 0, //(lparam)&cs);

   bool bOk = true;

   //if (!unhook_window_create() || lresult == -1)
   if (lresult == -1)
   {

      bOk = false;
      
      finalize();

      //children_post_quit();

      //children_wait_quit(one_minute());

      //PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
      
      return false;

   }

   //if(pusersystem->m_createstruct.style & WS_VISIBLE)
   //if(pusersystem->m_.style & WS_VISIBLE)
   if(puserinteraction->layout().design().is_screen_visible())
   {

      puserinteraction->display();

      puserinteraction->set_need_redraw();

      //puserinteraction->post_redraw();

      //;//macos_window_show();

   }

   puserinteraction->set_need_layout();

   puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "native_create_window"));

   puserinteraction->m_ewindowflag |= e_window_flag_window_created;
   
   return bOk;

}


//// for child windows
//bool interaction_impl::pre_create_window(::user::system * pusersystem)
//{
//   /*      if (pusersystem->m_createstruct.lpszClass == nullptr)
//    {
///xcore/app/aura/node/macos/macos_interaction_impl.cpp:712:44: No member named 'get_window_rect' in 'user::interaction_impl'       // make sure the default user::interaction class is registered
//    VERIFY(__end_defer_register_class(__WND_REG, &pusersystem->m_createstruct.lpszClass));
//
//    // no WNDCLASS provided - use child user::interaction default
//    ASSERT(pusersystem->m_createstruct.style & WS_CHILD);
//    }*/
//   return true;
//}

void window::macos_window_add_ref()
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "macos_window_add_ref"));
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "macos_window_add_ref"));

}


void window::macos_window_dec_ref()
{
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   puserinteraction->dec_ref(OBJ_REF_DBG_P_NOTE(this, "macos_window_dec_ref"));

   dec_ref(OBJ_REF_DBG_P_NOTE(this, "macos_window_dec_ref"));

}



void window::macos_window_draw(CGContextRef cgc, CGSize sizeWindowParam)
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

   rectangle_i32 rect1 = puserinteraction->get_window_rect();

   if(rect1.size() != rectLast.size())
   {

      rectLast = rect1;

      // xxxlog output_debug_string("different window rectangle_i32 size_i32 (1)");

   }

#endif

   millis tickNow = millis::now();

   millis tickEllapsed = tickNow - m_pimpl->m_millisLastDeviceDraw;

   if(tickEllapsed < 12)
   {

      // xxxlog
      //output_debug_string("\n\nwarning: macos_window_draw more than 80FPS!!! Ellapsed: " + str::from(tickEllapsed) + "ms.\n\n");

   }

   m_pimpl->m_millisLastDeviceDraw = tickNow;

   ::user::device_draw_life_time devicedrawlifetime(m_pimpl);

   critical_section_lock slDisplay(m_pimpl->cs_display());

   __pointer(::graphics::graphics) pbuffer = m_pimpl->m_pgraphics;

   if(!pbuffer)
   {

      return;

   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;
   
   if(!puserinteraction)
   {
   
      return;

   }
      
   ::draw2d::graphics_pointer g(e_create);

   g->attach(cgc);
   
   auto rectClient = puserinteraction->get_client_rect();

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
   
   m_pimpl->m_bPendingRedraw = false;
   
   m_pimpl->m_millisLastRedraw.Now();

}


bool window::macos_window_key_down(unsigned int uiKeyCode)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->m_id = e_message_key_down;

   pkey->m_nChar = uiKeyCode;

   spbase = pkey;
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return false;

   }

   puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::macos_window_key_up(unsigned int uiKeyCode)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->m_id = e_message_key_up;

   pkey->m_nChar = uiKeyCode;

   spbase = pkey;

   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return false;

   }

   puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::macos_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->set(get_oswindow(), this, e_message_key_down, vk, (lparam)(scan << 16), ::point_i32());

   if(::is_set(pszUtf8))
   {
   
      

      string * pstringText = new string(pszUtf8);

      auto lparam = (::lparam) (iptr) (string *) (pstringText);

      printf("macos_window_key_down e_message_text_composition\n");

      auto puserinteraction = m_pimpl->m_puserinteraction;

      puserinteraction->post_message(e_message_text_composition, 0, lparam);
      
      
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
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return false;

   }

   puserinteraction->send(spbase);

   return spbase->m_bRet;

}


bool window::macos_window_key_up(unsigned int vk, unsigned int scan)
{

   __pointer(::user::message) spbase;

   auto pkey  = __new(::message::key);

   pkey->set(get_oswindow(), this, e_message_key_up, vk, (::lparam)(scan << 16), point_i32());

   spbase = pkey;
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return false;

   }

   puserinteraction->send(spbase);

   return spbase->m_bRet;

}


void window::macos_window_mouse_down(int iButton, double x, double y)
{

   __pointer(::user::message) spbase;

   if (!this->is_active_window())
   {

      try
      {

         auto pmouseactivate = __new(::message::mouse_activate);

         pmouseactivate->m_id = e_message_mouse_activate;

         spbase = pmouseactivate;
         
         auto puserinteraction = m_pimpl->m_puserinteraction;

         puserinteraction->send(spbase);

         if (spbase->m_lresult == e_mouse_activate || spbase->m_lresult == e_mouse_activate_no_activate_and_eat)
         {


            puserinteraction->post_message(e_message_activate, MAKELONG(e_activate_click_active, 0), 0);

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

      auto puserinteraction = m_pimpl->m_puserinteraction;
      
      if(puserinteraction)
      {

         puserinteraction->post_message(message, 0, lparam);
         
      }

   }

}


void window::macos_window_mouse_up(int iButton, double x, double y)
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
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(!puserinteraction)
   {
      
      return;
      
   }

   puserinteraction->post_message(message, 0, lparam);

}


void window::macos_window_double_click(int iButton, double x, double y)
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
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(!puserinteraction)
   {
      
      return;
      
   }

   puserinteraction->post_message(message, 0, lparam);

}


void window::macos_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   bool bOk = true;
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(!puserinteraction)
   {
      
      return;
      
   }
   
   __pointer(::user::interaction) pinteraction = puserinteraction;

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

   if(puserinteraction == nullptr)
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
   
   puserinteraction->post_message(e_message_mouse_move, wparam, lparam);
   
}


void window::macos_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton)
{

   if(is_destroying())
   {
      
      return;
      
   }

   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
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

   puserinteraction->post_message(e_message_mouse_move, wparam, lparam);

}


void window::macos_window_mouse_wheel(double deltaY, double x, double y)
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   __pointer(::user::message) spbase;
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(!puserinteraction)
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

      if(puserinteraction == nullptr)
      {

         return;

      }

      puserinteraction->send(spbase);

   }

}


void window::macos_window_resized(CGRect rectangle)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(!puserinteraction)
   {
      
      return;
      
   }

   puserinteraction->post_message(e_message_move,0, MAKELPARAM(rectangle.origin.x, rectangle.origin.y));

   puserinteraction->post_message(e_message_size,0, MAKELPARAM(rectangle.size.width, rectangle.size.height));

   return;

//      if(puserinteraction == nullptr)
//      {
//
//         return;
//
//      }
//
//      //
//      if(puserinteraction->window_state().m_point != rectangle.origin)
//      {
//
//         puserinteraction->window_state().m_point = rectangle.origin;
//
//         TRACE("window::macos_window_resized effective position is different from requested position");
//
//         puserinteraction->post_message(e_message_move, 0, puserinteraction->window_state().m_point.lparam());
//
//      }
//
//      if(puserinteraction->m_sizeRequest != rectangle.size_i32)
//      {
//
//         puserinteraction->m_sizeRequest = rectangle.size_i32;
//
//         TRACE("window::macos_window_resized effective position is different from requested position");
//
//         puserinteraction->post_message(e_message_size, 0, puserinteraction->m_sizeRequest.lparam());
//
//      }
//
//      puserinteraction->m_point = rectangle.origin;
//
//      puserinteraction->m_size = rectangle.size_i32;
//
////      ::size_i32 sz;
////
////      point_i64 pt(rectangle.origin.x, rectangle.origin.y);
////
////      bool bMove = false;
////
////      {
////
////         synchronous_lock synchronouslock(puserinteraction->mutex());
////
////         if (pt != puserinteraction->m_rectParentClient.top_left())
////         {
////
////            bMove = true;
////
////         }
////
////         puserinteraction->m_rectParentClient.move_to(point);
////
////         puserinteraction->set_size(rectangle.size_i32);
////
////         sz = puserinteraction->m_rectParentClient.size();
////
////      }
////
////      if(puserinteraction == nullptr)
////      {
////
////         return;
////
////      }
////
////      puserinteraction->post_message(e_message_size, 0, sz.lparam());
////
////      if (bMove)
////      {
////
////         puserinteraction->post_message(e_message_move, 0, pt.lparam());
////
////      }

//      if (puserinteraction->m_eflagLayouting)
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
//      if(puserinteraction->window_state().rectangle_i32() != rectSize)
//      {
//
//         puserinteraction->window_state().m_point = rectSize.origin();
//
//         puserinteraction->window_state().m_size = rectSize.size();
//
//      }
//
//
//      if (puserinteraction->layout().sketch().rectangle_i32() != rectSize)
//      {
//
//         puserinteraction->place(rectSize);
//
//         if (puserinteraction->layout().design().display() != e_display_normal)
//         {
//
//            puserinteraction->display();
//
//         }
//
//         puserinteraction->set_need_layout();
//
//         puserinteraction->set_need_redraw();
//
//      }

}


void window::macos_window_moved(CGPoint point)
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   if(m_pimpl->m_bEatMoveEvent)
   {
      
      m_pimpl->m_bEatMoveEvent = false;
      
      return;
      
   }

   auto puserinteraction = m_pimpl->m_puserinteraction;

   puserinteraction->post_message(e_message_move,0, MAKELPARAM(point.x, point.y));

   return;

//      if(puserinteraction == nullptr)
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
//      if (puserinteraction->m_eflagLayouting)
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
//      if (puserinteraction->layout().sketch().m_point != pointMove)
//      {
//
//         puserinteraction->move_to(pointMove);
//
//         if (puserinteraction->layout().design().display() != e_display_normal)
//         {
//
//            puserinteraction->display();
//
//         }
//
//         puserinteraction->set_reposition();
//
//         puserinteraction->set_need_redraw();
//
//      }
//
//
////      if(puserinteraction->m_pointRequest != point_i32)
////      {
////
////         puserinteraction->m_pointRequest = point;
////
////         TRACE("window::macos_window_resized effective position is different from requested position");
////
////      }
////
////      puserinteraction->m_point = point;

}


void window::macos_window_did_become_key()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   m_pimpl->m_millisLastExposureAddUp.Now();

}


void window::macos_window_activate()
{
   
   if(is_destroying())
   {
      
      return;
      
   }
   
   this->set_active_window();

   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(::is_null(puserinteraction))
   {

      return;

   }

   puserinteraction->set_need_redraw();

}


void window::macos_window_deactivate()
{

   if(is_destroying())
   {
      
      //return;
      
      output_debug_string("destroying");
      
   }
   
   auto pwindowing = m_pwindowing;
   
   auto puserinteraction = m_pimpl->m_puserinteraction;
   
   auto pwindowActive = pwindowing->get_active_window(puserinteraction->m_pthreadUserInteraction);
   
   if(::is_null(pwindowActive))
   {
      
      return;
      
   }
   
   if(pwindowActive != this)
   {
      
      return;
      
   }
   
   pwindowing->clear_active_window(puserinteraction->m_pthreadUserInteraction);
   
   //::deactivate_window(get_handle());

//      if(puserinteraction == nullptr)
//      {
//
//         return;
//
//      }

   if(!is_destroying())
   {
   
      puserinteraction->set_need_redraw();
      
   }

}


void window::macos_window_iconified()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(::is_null(puserinteraction))
   {

      return;

   }
   
   if(m_pimpl->m_puserbox != nullptr)
   {

      m_pimpl->m_puserbox->m_windowrect.m_edisplayPrevious = m_pimpl->m_puserbox->m_windowrect.m_edisplay;
      
   }

   puserinteraction->layout().window() = ::e_display_iconic;

}


void window::macos_window_deiconified()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return;

   }
   
   if(m_pimpl->m_puserbox)
   {

      if(m_pimpl->m_puserbox->m_windowrect.m_edisplayPrevious == ::e_display_iconic)
      {

         m_pimpl->m_puserbox->m_windowrect.m_edisplayPrevious = ::e_display_normal;

      }
      
      puserinteraction->_001OnDeiconify(m_pimpl->m_puserbox->m_windowrect.m_edisplayPrevious);
      
   }

}


void window::macos_window_on_show()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(puserinteraction == nullptr)
   {

      return;

   }

   m_pimpl->m_millisLastExposureAddUp.Now();

   puserinteraction->message_call(e_message_show_window, 1);

   //puserinteraction->user_interaction_update_visibility_cache(true);

//      if(!(puserinteraction->m_ewindowflag & window_flag_miniaturizable))
//      {
//
//         if(puserinteraction->layout().sketch().display() == e_display_iconic)
//         {
//
//            puserinteraction->m_windowState3
//
//         }
//
//      }

   puserinteraction->set_need_layout();

   puserinteraction->set_need_redraw();

   puserinteraction->post_redraw();

}


void window::macos_window_on_hide()
{

//      if(is_destroying())
//      {
//
//         return;
//
//      }
   
   INFO("macos::window::macos_window_on_hide");

   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(::is_null(puserinteraction))
   {

      WARN("macos::window::macos_window_on_hide (2) puserinteraction == nullptr");

      return;

   }
   
   if(puserinteraction->layout().window().is_screen_visible())
   {

      puserinteraction->hide();

   }
   
   puserinteraction->message_call(e_message_show_window, 0);

}


void window::macos_window_on_miniaturize()
{

   if(is_destroying())
   {
      
      return;
      
   }
   
   auto puserinteraction = m_pimpl->m_puserinteraction;

   if(::is_null(puserinteraction))
   {

      return;

   }

   //puserinteraction->message_call(e_message_show_window, 0);

   //puserinteraction->user_interaction_update_visibility_cache(false);

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



