//
//  macos_window.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
//
//
#include "framework.h"
#include "window_impl.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/box.h"
#include "aura/message/user.h"
//#include "aura_macos/interaction_impl.h"
#include "acme/parallelization/message_queue.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/message/user.h"
#include <CoreGraphics/CoreGraphics.h>


void * __nsacmewindow_osdata(CFTypeRef pnsacmewindow);


bool macos_get_cursor_position(::int_point * ppointCursor);


void ns_main_post(dispatch_block_t block);

void ns_set_cursor(::windowing::cursor * pwindowingcursor);
::windowing::cursor * ns_get_cached_cursor();

#define WHEEL_DELTA 120

void create_macos_nswindow(macos_window * papexwindow, CGRect rect, unsigned int uStyle);


namespace windowing_macos
{


   window::window()
   {
      m_pacmewindowbridge = this;
      m_pwindow = this;
      m_bIsActiveCached = false;
      int iMouseMoveTriggerDistance = 10;
      m_mouserepositionthrottling.m_iMouseMoveSkipSquareDistance = iMouseMoveTriggerDistance * iMouseMoveTriggerDistance;
      m_mouserepositionthrottling.m_timeMouseMoveIgnore = 20_ms;
      m_mouserepositionthrottling.m_iMouseMoveSkipCount = 0;
      m_mouserepositionthrottling.m_timeMouseMovePeriod = 5_ms;

      
      //m_pWindow4 = this;
      //m_pmacoswindowing = nullptr;
      m_pNSCursorLast = nullptr;
      m_pwindowCapture = nullptr;
      
   }


   window::~window()
   {
      
      
   }


#ifdef _DEBUG
      
      
   huge_integer window::increment_reference_count()
   {
      
      return ::acme::windowing::window::increment_reference_count();
      
   }
   
   
   huge_integer window::decrement_reference_count()
   {
      
      return ::acme::windowing::window::decrement_reference_count();
      
   }
   
   
   huge_integer window::release()
   {
      
      return ::acme::windowing::window::release();
      
   }


#endif

   void window::on_initialize_particle()
   {
      
      ::windowing::window::on_initialize_particle();
      
      ::appkit::acme::windowing::window::on_initialize_particle();
      
   }
      

   void window::on_message_create(::message::message * pmessage)
   {
      
      
      
   }


   void window::on_message_destroy(::message::message * pmessage)
   {
      
      ns_main_send(^{
         
         
         ::macos_window::macos_window_hide();
         
         ::macos_window::macos_window_destroy();
         
         
      });
      
      
   }

void window::_main_send(const ::procedure & procedure)
{

   __block auto p = procedure
   ;
   
   ns_main_send(^{
      p();
   });

   //m_puserinteraction->_main_send(procedure);

}

void window::_main_post(const ::procedure & procedure)
{
 
   ::appkit::acme::windowing::window::_main_post(procedure);
   
}

   void window::install_message_routing(channel * pchannel)
   {

      ::windowing::window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &window::on_message_create);

      auto puserinteraction = m_puserinteraction;

      auto pimpl = this;

      if (!puserinteraction->m_bMessageWindow)
      {

         //MESSAGE_LINK(e_message_redraw, pchannel, pimpl, &::user::interaction_impl::_001OnRedraw);
         //MESSAGE_LINK(e_message_apply_visual, pchannel, pimpl, &::user::interaction_impl::_001OnApplyVisual);


         //#ifndef LINUX
         //MESSAGE_LINK(e_message_reposition, pchannel, this, &window::_001OnMove);
         //MESSAGE_LINK(e_message_size, pchannel, this, &window::_001OnSize);
         //#endif


         //MESSAGE_LINK(e_message_show_window, pchannel, this, &window::_001OnShowWindow);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &window::_001OnKillFocus);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::_001OnSetFocus);
         //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &window::_001OnSetCursor);

      }

      //MESSAGE_LINK(e_message_destroy_window, pchannel, pimpl, &::user::interaction_impl::_001OnDestroyWindow);

   //   MESSAGE_LINK(WM_ACTIVATE, pchannel, this, &window::_001OnActivate);
     // MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &window::_001OnDwmNcRenderingChanged);

      //pimpl->install_message_routing(pchannel);


      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);

      //MESSAGE_LINK(e_message_create, pchannel, pimpl, &::user::interaction_impl::_001OnPrioCreate);

   }


   void window::create_window()
   {
      
      ::windowing::window::create_window();
      
   }


   //void window::create_window(::user::interaction_impl * pimpl)
   void window::_create_window()
   {

      //if (::is_window(get_handle()))
      //{

      //   DestroyWindow();

      //}

//      //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
//      //       __is_valid_atom(lpszClassName));
//   //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));
//
//      // allow modification of several common create parameters
//      //::user::system createstruct;
//      //      pusersystem->m_createstruct.hwndParent = hWndParent;
//      //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
//      
//      auto puserinteraction = pimpl->m_puserinteraction;
//      
//      auto pusersystem = puserinteraction->m_pusersystem;
//      
//      //pusersystem->m_createstruct.hMenu = nullptr;
//      //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
//      //pusersystem->m_createstruct.lpCreateParams = lpParam;
//
//      if (!puserinteraction->pre_create_window(pusersystem))
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      //hook_window_create(puserinteraction);
//
//      //CGRect int_rectangle;
//
////      int_rectangle rectParam;
//
//   //      rectParam.left = m_pusersystem->m_createstruct.x;
//   //      rectParam.top = pusersystem->m_createstruct.y;
//   //      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx();
//   //      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy();
//
//   //      copy(rectangle, rectParam);
//   //
//   //      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
//   //      {
//   //
//   //         return true;
//   //
//   //      }
//   //      else
//   //      {

         //__todo?
         //windowing()->copy(cgrect, rectangle);
         //or
         //display()->copy(cgrect, rectangle);
         //because rectangle origin is top-left
         //and because cgrect origin is bottom-left and,
         //the origin of screen is at bottom.
      
//      m_puserinteractionimpl = pimpl;
//      
//      puserinteraction->m_puserinteractionTopLevel = puserinteraction;
//      
//      puserinteraction->m_pwindow = this;
//      
//      pimpl->m_pwindow = this;
//      
//      install_message_routing(puserinteraction);
//
//      
//      auto psession = m_pcontext->m_pacmesession->m_paurasession;
//
//      auto puser = psession->user();

//      auto pwindowing = (::windowing_macos::windowing *) puser->windowing()->m_pWindowing4;
      
      //m_pmacoswindowing = dynamic_cast < class windowing * >(m_pwindowing.m_p);
      
//      m_pwindowing = pwindowing;
//      
//      pimpl->m_pwindowing = pwindowing;

      unsigned uStyle = 0;
      
      auto puserinteraction = m_puserinteraction;

      if(puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
      {

#define NSWindowStyleMaskMiniaturizable (1 << 2)

         uStyle |= NSWindowStyleMaskMiniaturizable;

      }
   
      auto rectangle = puserinteraction-> const_layout().sketch().parent_raw_rectangle();
   
      CGRect cgrect;
   
      copy(cgrect, rectangle);
   
      create_macos_nswindow(this, cgrect, uStyle);
      
      if(m_pacmeuserinteractionOwner)
      {
         
         ::cast < ::windowing_macos::window > pwindowRelative = m_pacmeuserinteractionOwner->window();
         
         ::cast < macos_window > pmacoswindow = pwindowRelative->m_pacmewindowbridge;
       
         pmacoswindow->macos_window_order_front();

         macos_window_order_relative_to(pmacoswindow);
         
      }
      
//      puserinteraction->post_message(e_message_pos_create);
//      
   }


   //// for child windows
   //bool interaction_impl::pre_create_window(::user::system * pusersystem)
   //{
   //   /*      if (pusersystem->m_createstruct.lpszClass == nullptr)
   //    {
   ///xcore/app/aura/node/macos/macos_interaction_impl.cpp:712:44: No member named 'window_rectangle' in 'user::interaction_impl'       // make sure the default user::interaction class is registered
   //    VERIFY(__end_defer_register_class(__WND_REG, &pusersystem->m_createstruct.lpszClass));
   //
   //    // no WNDCLASS provided - use child user::interaction default
   //    ASSERT(pusersystem->m_createstruct.style & WS_CHILD);
   //    }*/
   //   return true;
   //}

   void window::macos_window_add_ref()
   {
    
      __refdbg_add_referer
      
      increment_reference_count();
      
//      auto puserinteraction = m_puserinteraction;
//
//      puserinteraction->increment_reference_count();

   }


   void window::macos_window_dec_ref()
   {
      
      auto puserinteraction = m_puserinteraction;

      puserinteraction->decrement_reference_count();

      decrement_reference_count();

   }


   void window::set_keyboard_focus()
   {

      macos_window_make_first_responder();

      //return ::success;

   }


   void window::set_active_window()
   {

      macos_window_make_key_window_and_order_front();
      
      ///auto pwindowing = (::windowing_macos::windowing *) m_pwindowing->m_pWindowing4;
      

      //return ::success;

   }


   void window::set_tool_window(bool bSet)
   {
      
//      auto pwindowing = (::windowing_macos::windowing *) m_pwindowing->m_pWindowing4;
      
      if(m_pacmeuserinteraction == get_app()->m_pacmeuserinteractionMain)
      {
         macos_windowing()->_defer_dock_application(!bSet);
         
      }

      //return ::success;
      
   }


   void window::show_task(bool bShowTask)
   {
      
      
   }
      
      


   void window::set_foreground_window(::user::activation_token * puseractivationtoken)
   {
      
      macos_window_order_front();
      
      //return ::success;
      
   }


   bool window::is_active_window()
   {

      return m_bIsActiveCached;

   }

   
   bool window::has_keyboard_focus()
   {
      
      //bool bHasKeyboardFocus = macos_window_is_key_window();
      
      bool bHasKeyboardFocus = m_bIsActiveCached;
   
      return bHasKeyboardFocus;
   
   }


//   void window::window_show()
//   {
//
//      //macos_window_show();
//
//      ::windowing::window::window_show();
//
//   }

//   void window::_window_request_presentation()
//   {
//
//      //macos_window_show();
//
//      ::windowing::window::_window_request_presentation();
//
//   }

//
//   void window::show_window(const ::e_display &edisplay, const ::e_activation &eactivation)
//   {
//
//      //windowing_output_debug_string("\n::windowing_macos::window::show_window 1");
//
//      if(edisplay == e_display_iconic)
//      {
//
//         macos_window_miniaturize();
//
//      }
//      else if(equivalence_sink(edisplay) == e_display_normal)
//      {
//
//         macos_window_show();
//
//         macos_window_make_key_window_and_order_front();
//
//         macos_window_make_main_window();
//
//         nsapp_activate_ignoring_other_apps(1);
//
//      }
////      else if(edisplay == e_display_normal)
////      {
////
////         macos_window_show();
////
////         macos_window_make_key_window_and_order_front();
////
////         macos_window_make_main_window();
////
////         nsapp_activate_ignoring_other_apps(1);
////
////      }
//      else if(edisplay == e_display_none || edisplay == e_display_hide)
//      {
//
//         macos_window_resign_key();
//         macos_window_hide();
//
//      }
//
//      //return ::success;
//
//   }
//

   void window::set_mouse_cursor(::windowing::cursor * pcursorParam)
   {
      
      ::pointer < ::windowing::cursor > pcursor = pcursorParam;

      if (::is_null(pcursor))
      {

         throw exception(error_invalid_parameter);

      }
      
      if(pcursor == m_pcursor)
      {
         
         return;
         
      }

      auto pcursorMacos = pcursor.cast < cursor >();

      if (::is_null(pcursorMacos))
      {

         throw exception(error_invalid_parameter);

      }
      
      if(::is_null(pcursorMacos->m_pNSCursor)
         && (pcursorMacos->m_pimage
             || pcursor->m_ecursor != e_cursor_none))
      {
         
         pcursorMacos->_create_os_cursor();
         
      }
      
//      if (ns_get_cached_cursor() == pcursor)
//      {
//
//         return;
//
//      }

      ns_set_cursor(pcursor);

   }


//   ::int_point window::get_mouse_cursor_host_position()
//   {
//      
//      return m_pointMouseCursorHost;
//      
//   }
//
//
//   ::int_point window::get_mouse_cursor_absolute_position()
//   {
//      
//      return m_pointMouseCursorHost;
//      
//   }


// void window::_window_request_presentation_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
//{
//
//    set_window_position(zorder, x, y, cx, cy, eactivation, bNoZorder, bNoMove,
//                        bNoSize, bShow, bHide);
//
// }


   bool window::_configure_window_unlocked(const class ::zorder& zorder, const ::user::activation& activationParam, bool bNoZorder, ::e_display edisplay)
   {
      
      if(edisplay == e_display_none)
      {
         
         information() << "window::_configure_window_unlocked";
         
      }
      
      auto activation = activationParam;
      
      ns_main_post(^()
      {
         
         if(edisplay == e_display_iconic)
         {
          
            macos_window_miniaturize();
            
         }
         else if(equivalence_sink(edisplay) == e_display_normal)
         {
            
            macos_window_show();
            
            if(activation.m_eactivation & ::user::e_activation_set_foreground)
            {
               
               macos_window_make_key_window_and_order_front();
               
               if(m_pacmeuserinteraction == get_app()->m_pacmeuserinteractionMain)
               {
                  
                  macos_window_make_main_window();
                  
                  nsapp_activate_ignoring_other_apps(1);
                  
               }
               
               macos_window_defer_show();
               
            }
            
         }
   //      else if(edisplay == e_display_normal)
   //      {
   //
   //         macos_window_show();
   //
   //         macos_window_make_key_window_and_order_front();
   //
   //         macos_window_make_main_window();
   //
   //         nsapp_activate_ignoring_other_apps(1);
   //
   //      }
         else if(edisplay == e_display_none || edisplay == e_display_hide)
         {
            
            if(m_bTest123)
            {
               
               printf("m_bTest123");
               
            }
            
            macos_window::macos_window_resign_key();
            macos_window_hide();
            
         }
         else
         {
            
            macos_window_defer_show();
            
         }
//         //return ::success;
//         
//         //bool bShow = windowing()->is_screen_visible(edisplay);
//         
//         //if(bShow)
//         {
//            
//            macos_window_defer_show();
//            
//         }
         
      });

      return true;
      
   }

   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {
      
      
      ns_main_post(^(){
         
         CGRect r;
         
         macos_window_get_frame(&r);
         
         if(!bNoMove)
         {
            
            if(x > 0)
            {
               
               r.origin.x = x;
               
               r.origin.y = y;
               
            }
            else{
               r.origin.x = x;
               
               r.origin.y = y;
               
               
            }
         }
         
         if(!bNoSize)
         {
            
            r.size.width = cx;
            
            r.size.height = cy;
            
         }
         
         macos_window_set_frame(r);
         
         m_puserinteraction->layout().m_statea[::user::e_layout_window].origin().x() = r.origin.x;
         m_puserinteraction->layout().m_statea[::user::e_layout_window].origin().y() = r.origin.y;
         m_puserinteraction->layout().m_statea[::user::e_layout_window].size().cx() = r.size.width;
         m_puserinteraction->layout().m_statea[::user::e_layout_window].size().cy() = r.size.height;

         //         if(bShow)
         //         {
         //
         //            macos_window_defer_show();
         //
         //         }
         
         //}
         
      });
      
      return true;

   }


//   bool window::set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
//   {
//
//      ns_main_post(^(){
//
//         CGRect r;
//
//         macos_window_get_frame(&r);
//
//         if(!bNoMove)
//         {
//
//            if(x > 0)
//            {
//
//               r.origin.x = x;
//
//               r.origin.y = y;
//
//            }
//            else{
//               r.origin.x = x;
//
//               r.origin.y = y;
//
//
//            }
//         }
//
//         if(!bNoSize)
//         {
//
//            r.size.width = cx;
//
//            r.size.height = cy;
//
//         }
//
//         macos_window_set_frame(r);
//
//         if(bShow)
//         {
//
//            macos_window_defer_show();
//
//         }
//
//      }
//
//      );
//
//      return true;
//
//   }


   void window::set_mouse_capture()
   {

       auto pwindowing = macos_windowing();
      if(!pwindowing)
      {
         
         throw exception(error_wrong_state);
         
      }
      
      pwindowing->m_pwindowCapture = this;

      //return ::success;

   }


   void window::__update_graphics_buffer()
   {
      
      macos_window_redraw();
      
   }


   void window::window_update_screen()
   {

     //      if(m_interlockedPostedScreenUpdate > 0)
     //      {
     //
     //         return;
     //
     //      }
     //
     //      m_interlockedPostedScreenUpdate++;

           //windowing()->windowing_post([this]()
             //                          {

      {

         //_synchronous_lock synchronouslock(user_synchronization());

         //display_lock displayLock(x11_display()->Display());

         //auto pimpl = m_puserinteractionimpl;

         //configure_window_unlocked();
         
         if(m_pgraphicsthread->get_message_queue()->m_eflagElement & (1ll<<36))
         {
            
            m_bTest123 = true;
            
         }
        
         //configure_window_unlocked();
        
        //bool bChangedPosition = false;
        
        //bool bChangedSize = false;
        
        //strict_set_window_position_unlocked(bChangedPosition, bChangedSize);

        set_window_position_unlocked();

        __update_graphics_buffer();

        //pbuffer->_update_screen_lesser_lock();

     }

     //auto pimpl = m_puserinteractionimpl;

     m_pgraphicsthread->on_graphics_thread_iteration_end();

     //                                  });

           //m_interlockedPostedScreenUpdate--;

  }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {
      
      ::string strTitle;
      
      strTitle = scopedstr;
      
      macos_window_set_title(strTitle);
      
   }


   ::string window::get_window_text()
   {
   
      ::string strTitle;
      
      auto p = strTitle.get_buffer(1024);
      
      macos_window_get_title(p, 1024);
      
      strTitle.release_buffer();
      
      return strTitle;
      
   }


   void window::macos_window_draw(CGContextRef cgc, CGSize sizeWindowParam)
   {

      ::int_size sizeWindow(sizeWindowParam.width, sizeWindowParam.height);

      #ifdef EXTRALOG

      static int s_iLastExact = -1;

      string str;

      string strFormat;

      strFormat.Format("|-> window int_size %d, %d", sizeWindow.cx(), sizeWindow.cy());

      string strSize;

      if(sizeLast != sizeWindow)
      {

         sizeLast = sizeWindow;

         strSize = strFormat;

      }

      str += strFormat;

      int_rectangle rect1 = puserinteraction->window_rectangle();

      if(rect1.size() != rectLast.size())
      {

         rectLast = rect1;

         // xxxlog output_debug_string("different window int_rectangle int_size (1)");

      }

   #endif

      auto tickNow = ::time::now();

      auto tickEllapsed = tickNow - m_timeLastDeviceDraw;

      if(tickEllapsed < 12_ms)
      {

         // xxxlog
         //output_debug_string("\n\nwarning: macos_window_draw more than 80FPS!!! Ellapsed: " + str::from(tickEllapsed) + "ms.\n\n");

      }

      m_timeLastDeviceDraw = tickNow;

      //::user::device_draw_life_time devicedrawlifetime(this);

      critical_section_lock slDisplay(cs_display());

      ::pointer < ::graphics::graphics > pbuffer = m_pgraphicsgraphics;

      if(!pbuffer)
      {

         return;

      }
      
      auto puserinteraction = m_puserinteraction;
      
      if(!puserinteraction)
      {
      
         return;

      }
         
      auto g = __øcreate < ::draw2d::graphics >();

      g->attach(cgc);
      
      //auto rectClient = puserinteraction->client_rectangle();

      g->set_alpha_mode(::draw2d::e_alpha_mode_set);

      synchronous_lock slGraphics(pbuffer->synchronization());
      
      auto pitem = pbuffer->get_screen_item();
      
      synchronous_lock sl1(pitem->m_pmutex);

      ::image::image_pointer & imageBuffer2 = pitem->m_pimage2;

      if (!imageBuffer2.ok())
      {

         output_debug_string("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

         return;

      }
      
      slGraphics.unlock();

   #ifdef EXTRALOG

      if(strSize.has_character())
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

      ::int_size sizeMin = imageBuffer2->size().minimum(sizeWindow);
      
      ::double_rectangle rectangleSource(sizeMin);
      
      ::image::image_source imagesource(imageBuffer2, rectangleSource);
      
      ::double_rectangle rectangleTarget(sizeMin);
      
      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);
       
      if(m_dOpacity < 1.0)
      {
          
          imagedrawingoptions.m_opacity = m_dOpacity;
          
      }
      
      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
       
       g->set_alpha_mode(draw2d::e_alpha_mode_set);

      g->draw(imagedrawing);
      
      m_bPendingRedraw = false;
      
      m_timeLastRedraw.Now();

   }


//   bool window::macos_window_key_down(unsigned int uiKeyCode)
//   {
//
//      auto puserinteraction = m_puserinteraction;
//
//      if(puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      auto pkey  = __create_new < ::message::key >();
//
//      pkey->m_id = e_message_key_down;
//
//      pkey->m_strText = pszUtf8;
//
//      pkey->m_nChar = uiKeyCode;
//
//      puserinteraction->send(pkey);
//
//      return true;
//
//   }
//
//
//   bool window::macos_window_key_up(unsigned int uiKeyCode)
//   {
//
//      ::pointer < ::user::message > spbase;
//
//      auto pkey  = __new(::message::key);
//
//      pkey->m_id = e_message_key_up;
//
//      pkey->m_nChar = uiKeyCode;
//
//      spbase = pkey;
//
//      auto puserinteraction = m_puserinteraction;
//
//      if(puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      puserinteraction->send(spbase);
//
//      return spbase->m_bRet;
//
//   }

#define _NEW_MESSAGE(pmessage, type, emessage) \
auto pmessage = __create_new < type >(); \
pmessage->m_oswindow = this->oswindow(); \
pmessage->m_pwindow = this; \
pmessage->m_atom = emessage

   bool window::macos_window_key_down(unsigned int virtualKey, unsigned int scanCode, const char * pszUtf8)
   {
      
      _NEW_MESSAGE(pkey, ::message::key, e_message_key_down);

      pkey->m_iVirtualKey = virtualKey;
      pkey->m_nScanCode = scanCode;
      
      ::pointer < keyboard > pkeyboard = windowing()->keyboard();
      
      pkey->m_ekey = pkeyboard->virtual_key_to_user_key(virtualKey);

      if(::is_set(pszUtf8) && ansi_len(pszUtf8) > 0)
      {

         pkey->m_strText = pszUtf8;
      
      }
       
      if(pkey->m_strText.length() == 1)
      {
          
          auto character = pkey->m_strText[0];
          
          if(character >= 'a' && character <= 'z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int)::user::e_key_a + character - 'a');
              
          }
          else if(character >= 'A' && character <= 'Z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_a + character - 'A');
              
          }
          else if(character >= '0' && character <= 'Z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_0 + character - '0');
              
          }

      }

      //post_message(pkey);
      send_message(pkey);
    
      if(::is_set(pszUtf8) && ansi_len(pszUtf8) > 0)
      {


         _NEW_MESSAGE(pkey, ::message::key, e_message_char);
           
         pkey->m_strText = pszUtf8;
           
         //post_message(pkey);
         send_message(pkey);

      }
    
      return true;

   }


   bool window::macos_window_key_up(unsigned int virtualKey, unsigned int scan)
   {

      auto puserinteraction = m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return false;

      }

      _NEW_MESSAGE(pkey, ::message::key, e_message_key_up);

      pkey->m_iVirtualKey = virtualKey;
      
      pkey->m_nScanCode = scan;
      
      ::pointer < keyboard > pkeyboard = windowing()->keyboard();

      pkey->m_ekey = pkeyboard->virtual_key_to_user_key(virtualKey);

      puserinteraction->send_message(pkey);

      return true;

   }


   void window::macos_window_mouse_down(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute)
   {
      
      m_pointMouseCursorHost.x() = xHost;
      
      m_pointMouseCursorHost.y() = yHost;

      m_pointMouseCursorAbsolute.x() = xAbsolute;
      
      m_pointMouseCursorAbsolute.y() = yAbsolute;

      //::pointer < ::user::message > spbase;

      if (!this->is_active_window())
      {

         try
         {

            _NEW_MESSAGE(pmouseactivate, ::message::mouse_activate, e_message_mouse_activate);

            pmouseactivate->m_wparam = 0;
            pmouseactivate->m_lparam = 0;

            send_message(pmouseactivate);

            if (pmouseactivate->m_lresult == e_mouse_activate || pmouseactivate->m_lresult == e_mouse_activate_no_activate_and_eat)
            {

               _NEW_MESSAGE(pactivate, ::message::activate, e_message_activate);

               pactivate->m_wparam = make_unsigned_int(e_activate_click_active, 0);
               pactivate->m_lparam = 0;

               //post_message(pactivate);
               send_message(pactivate);

            }

         }
         catch (...)
         {

         }

      }

      {

//         auto pmouse = __create_new < ::message::mouse > ();

//         ::atom id;
         
         if (iButton == 1)
         {
            
            _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_down);
            pmouse->m_pointHost.x() = xHost;
            pmouse->m_pointHost.y() = yHost;
            pmouse->m_pointAbsolute.x() = xAbsolute;
            pmouse->m_pointAbsolute.y() = yAbsolute;
            //post_message(pmouse);
            send_message(pmouse);

         }
         else
         {

            _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_down);
            pmouse->m_pointHost.x() = xHost;
            pmouse->m_pointHost.y() = yHost;
            pmouse->m_pointAbsolute.x() = xAbsolute;
            pmouse->m_pointAbsolute.y() = yAbsolute;
            //post_message(pmouse);
            send_message(pmouse);
         }
         
//         pmouse->set(this, this, id, 0, __MAKE_LPARAM(x, y));


      }

   }


   void window::macos_window_mouse_up(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute)
   {
      
      m_pointMouseCursorHost.x() = xHost;
      
      m_pointMouseCursorHost.y() = yHost;

      m_pointMouseCursorAbsolute.x() = xAbsolute;
      
      m_pointMouseCursorAbsolute.y() = yAbsolute;

      //auto pmouse = __create_new < ::message::mouse >();

      //::atom id;

      if (iButton == 1)
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_up);
         pmouse->m_pointHost.x() = xHost;
         pmouse->m_pointHost.y() = yHost;
         pmouse->m_pointAbsolute.x() = xAbsolute;
         pmouse->m_pointAbsolute.y() = yAbsolute;
         //post_message(pmouse);
         send_message(pmouse);

      }
      else
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_up);
         pmouse->m_pointHost.x() = xHost;
         pmouse->m_pointHost.y() = yHost;
         pmouse->m_pointAbsolute.x() = xAbsolute;
         pmouse->m_pointAbsolute.y() = yAbsolute;
         //post_message(pmouse);
         send_message(pmouse);


      }
      
//      pmouse->set(this, this, id, (wparam) 0, __MAKE_LPARAM(x, y));
//
//      post_message(pmouse);

   }


   void window::macos_window_double_click(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute)
   {

      m_pointMouseCursorHost.x() = xHost;
      
      m_pointMouseCursorHost.y() = yHost;

      m_pointMouseCursorAbsolute.x() = xAbsolute;
      
      m_pointMouseCursorAbsolute.y() = yAbsolute;

      //auto pmouse = __create_new < ::message::mouse >();
      
      //::atom id;

      if (iButton == 1)
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_double_click);
         pmouse->m_pointHost.x() = xHost;
         pmouse->m_pointHost.y() = yHost;
         pmouse->m_pointAbsolute.x() = xAbsolute;
         pmouse->m_pointAbsolute.y() = yAbsolute;
         //post_message(pmouse);
         send_message(pmouse);

         //id = e_message_right_button_double_click;

      }
      else
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_double_click);
         pmouse->m_pointHost.x() = xHost;
         pmouse->m_pointHost.y() = yHost;
         pmouse->m_pointAbsolute.x() = xAbsolute;
         pmouse->m_pointAbsolute.y() = yAbsolute;
         //post_message(pmouse);
         send_message(pmouse);
         //id = e_message_left_button_double_click;

      }

//      pmouse->set(this, this, id, (wparam) 0, __MAKE_LPARAM(x, y));
//
//      post_message(pmouse);

   }


   void window::macos_window_mouse_repositioned(double xHost, double yHost, double xAbsolute, double yAbsolute, unsigned long ulAppleMouseButton)
   {
      
      
      m_pointMouseCursorHost.x() = xHost;
      
      m_pointMouseCursorHost.y() = yHost;

      m_pointMouseCursorAbsolute.x() = xAbsolute;
      
      m_pointMouseCursorAbsolute.y() = yAbsolute;

      
//      if(is_destroying())
//      {
//
//         return;
//
//      }
      
//      m_pointMouseCursor.x() = x;
//
//      m_pointMouseCursor.y() = y;
      
      bool bOk = true;

//      auto puserinteraction = m_puserinteraction;
//
//      if(!puserinteraction)
//      {
//
//         return;
//
//      }
      
      if(m_mouserepositionthrottling.m_timeMouseMove.elapsed() < m_mouserepositionthrottling.m_timeMouseMoveIgnore)
      {
         
         //printf("mouse_move_ignored %f, %f\n", x, y);

         bOk = false;

      }

      if(bOk)
      {

//            printf("mouse_move_\"accepted\" %f, %f\n", x, y);

         m_mouserepositionthrottling.m_timeMouseMove.Now();

         m_mouserepositionthrottling.m_pointMouseMove.x() = xAbsolute;

         m_mouserepositionthrottling.m_pointMouseMove.y() = yAbsolute;

//            if(false)
//            {
//
//               if(pinteraction->m_millisMouseMovePeriod > 0)
//               {
//
//                  ::int_size sizeDistance((pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
//                     (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));
//
//                  if(!pinteraction->m_millisMouseMoveSkip.timeout(pinteraction->m_millisMouseMovePeriod)
//                     && sizeDistance.cx() * sizeDistance.cx() + sizeDistance.cy() * sizeDistance.cy() < pinteraction->m_iMouseMoveSkipSquareDistance)
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

      if(!bOk)
      {

         return;

      }
      
      
      _NEW_MESSAGE(pmouse, ::message::mouse, e_message_mouse_move);
      pmouse->m_pointHost.x() = xHost;
      pmouse->m_pointHost.y() = yHost;
      pmouse->m_pointAbsolute.x() = xAbsolute;
      pmouse->m_pointAbsolute.y() = yAbsolute;

      //::atom id = e_message_mouse_move;
      
      //wparam wparam = 0;
      
      //lparam lparam = __MAKE_LPARAM(x, y);
      
      if(ulAppleMouseButton & 1)
      {

         pmouse->m_ebuttonstate |= ::user::e_button_state_left;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_ebuttonstate |= ::user::e_button_state_right;

      }
      
//      auto pmouse = __create_new < ::message::mouse >();
//
//      pmouse->set(this, this, id, wparam, lparam);

      //post_message(pmouse);
      
      send_message(pmouse);
      
   }


   void window::macos_window_mouse_dragged(double xHost, double yHost, double xAbsolute, double yAbsolute, unsigned long ulAppleMouseButton)
   {
      
      _NEW_MESSAGE(pmouse, ::message::mouse, e_message_mouse_move);
      pmouse->m_pointHost.x() = xHost;
      pmouse->m_pointHost.y() = yHost;
      pmouse->m_pointAbsolute.x() = xAbsolute;
      pmouse->m_pointAbsolute.y() = yAbsolute;

      
//      atom id = e_message_mouse_move;

  //    wparam wparam = 0;

    //  lparam lparam = __MAKE_LPARAM(x, y);

      if(ulAppleMouseButton & 1)
      {

         pmouse->m_ebuttonstate |= ::user::e_button_state_left;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_ebuttonstate |= ::user::e_button_state_right;

      }
//
//      auto pmouse = __create_new < ::message::mouse >();
//
//      pmouse->set(this, this, id, wparam, lparam);

      //post_message(pmouse);
      
      send_message(pmouse);

   }


   void window::macos_window_mouse_wheel(double deltaY, double xHost, double yHost, double xAbsolute, double yAbsolute)
   {

      
      _NEW_MESSAGE(pwheel, ::message::mouse_wheel, e_message_mouse_wheel);
      pwheel->m_pointHost.x() = xHost;
      pwheel->m_pointHost.y() = yHost;
      pwheel->m_pointAbsolute.x() = xAbsolute;
      pwheel->m_pointAbsolute.y() = yAbsolute;

      //atom id = e_message_mouse_wheel;

      pwheel->m_Δ = deltaY * WHEEL_DELTA / 3.0;

      //wparam wparam = pwheel-delta << 16;

      //lparam lparam = __MAKE_LPARAM(x, y);

      //auto pwheel  = __create_new < ::message::mouse_wheel > ();
      
      //pwheel->set(this, this, id, wparam, lparam);

      //post_message(pwheel);
      
      send_message(pwheel);

   }


   void window::macos_window_resized(CGRect rectangle)
   {
      
      {
      
         auto p = m_puserinteraction->const_layout().window().origin();
         
         if(p.x() != rectangle.origin.x || p.y() != rectangle.origin.y)
         {
            
            _NEW_MESSAGE(preposition, ::message::reposition, e_message_reposition);
            preposition->m_point.x() = rectangle.origin.x;
            preposition->m_point.y() = rectangle.origin.y;
            
            
            //         atom id = e_message_reposition;
            //
            //         wparam wparam = 0;
            //
            //         lparam lparam = __MAKE_LPARAM(rectangle.origin.x, rectangle.origin.y);
            //
            //         auto pmove  = __create_new < ::message::reposition > ();
            //
            //         pmove->set(this, this, id, wparam, lparam);
            
            //post_message(preposition);
            send_message(preposition);
            
         }
         
      }
      
      {
         
         m_puserinteraction->set_position({rectangle.origin.x, rectangle.origin.y}, ::user::e_layout_window);
         
         m_puserinteraction->set_size({rectangle.size.width, rectangle.size.height}, ::user::e_layout_window);

         auto s = m_puserinteraction->const_layout().window().size();
         
         if(s.cx() != rectangle.size.width || s.cy() != rectangle.size.height)
         {
            
            _NEW_MESSAGE(psize, ::message::size, e_message_size);
            psize->m_size.cx() = rectangle.size.width;
            psize->m_size.cy() = rectangle.size.height;
            
            //         atom id = e_message_size;
            //
            //         wparam wparam = 0;
            //
            //         lparam lparam = __MAKE_LPARAM(rectangle.size.width, rectangle.size.height);
            //
            //         auto psize  = __create_new < ::message::size > ();
            //
            //         psize->set(this, this, id, wparam, lparam);
            
            //post_message(psize);
            send_message(psize);
            
            
         }
         
      }

      ::int_rectangle rectangleWindow;
      
      rectangleWindow = rectangle;
      
      _on_configure_notify_unlocked(rectangleWindow);
      
      //return;

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
   //         information("window::macos_window_resized effective position is different from requested position");
   //
   //         puserinteraction->post_message(e_message_reposition, 0, puserinteraction->window_state().m_point.lparam());
   //
   //      }
   //
   //      if(puserinteraction->m_sizeRequest != rectangle.int_size)
   //      {
   //
   //         puserinteraction->m_sizeRequest = rectangle.int_size;
   //
   //         information("window::macos_window_resized effective position is different from requested position");
   //
   //         puserinteraction->post_message(e_message_size, 0, puserinteraction->m_sizeRequest.lparam());
   //
   //      }
   //
   //      puserinteraction->m_point = rectangle.origin;
   //
   //      puserinteraction->m_size = rectangle.int_size;
   //
   ////      ::int_size sz;
   ////
   ////      huge_integer_point pt(rectangle.origin.x, rectangle.origin.y);
   ////
   ////      bool bMove = false;
   ////
   ////      {
   ////
   ////         _synchronous_lock synchronouslock(puserinteraction->mutex());
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
   ////         puserinteraction->set_size(rectangle.int_size);
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
   ////         puserinteraction->post_message(e_message_reposition, 0, pt.lparam());
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
   //      ::int_rectangle rectSize;
   //
   //      copy(rectSize, rectangle);
   //
   //      if(puserinteraction->window_state().int_rectangle() != rectSize)
   //      {
   //
   //         puserinteraction->window_state().m_point = rectSize.origin();
   //
   //         puserinteraction->window_state().m_size = rectSize.size();
   //
   //      }
   //
   //
   //      if (puserinteraction->layout().sketch().int_rectangle() != rectSize)
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


   void window::macos_window_repositioned(CGPoint point)
   {
      
      if(m_bEatMoveEvent)
      {
         
         m_bEatMoveEvent = false;
         
         return;
         
      }

      {
         
         m_puserinteraction->set_position({point.x, point.y}, ::user::e_layout_window);

         _NEW_MESSAGE(preposition, ::message::reposition, e_message_reposition);
         preposition->m_point.x() = point.x;
         preposition->m_point.y() = point.y;

//         atom id = e_message_reposition;
//
//         wparam wparam = 0;
//
//         lparam lparam = __MAKE_LPARAM(point.x, point.y);
//
//         auto pmove  = __create_new < ::message::reposition > ();
//
//         pmove->set(this, this, id, wparam, lparam);

         //post_message(preposition);
         
         send_message(preposition);
         
      }
   //      if(puserinteraction == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //
   //      ::int_point pointMove;
   //
   //      copy(pointMove, point);
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
   //      ///::pointer < ::message::move > pmove(pmessage);
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
   ////      if(puserinteraction->m_pointRequest != int_point)
   ////      {
   ////
   ////         puserinteraction->m_pointRequest = point;
   ////
   ////         information("window::macos_window_resized effective position is different from requested position");
   ////
   ////      }
   ////
   ////      puserinteraction->m_point = point;
      ///
      _on_reposition_notify_unlocked(::int_point(point.x, point.y))
      ;
   }


   void window::macos_window_become_key()
   {

//      if(is_destroying())
//      {
//
//         return;
//
//      }
      
      m_bIsActiveCached = true;
      
      macos_windowing()->m_pwindowActive = this;
      
      m_timeLastExposureAddUp.Now();
      
      window_on_set_keyboard_focus();

   }


   void window::macos_window_resign_key()
{
      
      if(macos_windowing()->m_pwindowActive == this)
      {
         
         macos_windowing()->m_pwindowActive = this;
         
      }

      m_bIsActiveCached = false;
   //      if(is_destroying())
   //      {
   //
   //         return;
   //
   //      }
      
      //m_timeLastExposureAddUp.Now();
      
      window_on_kill_keyboard_focus();

   }


   void window::macos_window_on_activate()
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      window_on_activate();
      
      //this->set_active_window();

      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }

//      puserinteraction->set_need_redraw();
      puserinteraction->send_message(e_message_activate, 1);

   }


   void window::macos_window_on_deactivate()
   {

      if(is_destroying())
      {
         
         //return;
         
         output_debug_string("destroying");
         
      }
      
      window_on_deactivate();
      
       auto pwindowing = macos_windowing();
      
//      
//      auto puserinteractionimpl = m_puserinteractionimpl;
//      
//      if(!puserinteractionimpl)
//      {
//       
//         return;
//         
//      }
      
      auto puserinteraction = m_puserinteraction;
      
      if(!puserinteraction)
      {
       
         return;
         
      }
      
//      auto pwindowActive = pwindowing->get_active_window(puserinteraction->m_pthreadUserInteraction);
//
//      if(::is_null(pwindowActive))
//      {
//
//         return;
//
//      }
//
//      if(pwindowActive != this)
//      {
//
//         return;
//
//      }
//
//      pwindowing->clear_active_window(puserinteraction->m_pthreadUserInteraction);
      
      //::deactivate_window(get_handle());

   //      if(puserinteraction == nullptr)
   //      {
   //
   //         return;
   //
   //      }
      
      puserinteraction->send_message(e_message_activate, 0);

//      if(!is_destroying())
//      {
//
//         puserinteraction->set_need_redraw();
//
//      }

   }


   void * window::macos_window_get_mouse_cursor()
   {
      
      if(::is_null(m_pcursor))
      {
         
         return nullptr;
         
      }
      
      auto poscursor = m_pcursor->get_os_data();
      
      if(::is_null(poscursor))
      {
       
         return nullptr;
         
      }
      
      return poscursor;
      
   }

   
   void window::profiling_on_start_draw_rectangle()
   {
      
//      auto pimpl = m_puserinteractionimpl;
//      
//      if(::is_null(pimpl))
//      {
//       
//         return;
//         
//      }

//      auto pimpl2 = pimpl->m_pImpl2;
//
//      if(::is_null(pimpl2))
//      {
//       
//         return;
//         
//      }
//      
      auto pgraphicsthread = m_pgraphicsthread;
      
      if(::is_null(pgraphicsthread))
      {
       
         return;
         
      }
      
      pgraphicsthread->profiling_on_before_update_screen();

   }


   void window::profiling_on_end_draw_rectangle()
   {
      
//      auto pimpl = m_puserinteractionimpl;
//      
//      if(::is_null(pimpl))
//      {
//       
//         return;
//         
//      }
//
//      auto pimpl2 = pimpl->m_pImpl2;
//
//      if(::is_null(pimpl2))
//      {
//       
//         return;
//         
//      }
//      
      auto pprodevian = m_pgraphicsthread;
      
      if(::is_null(pprodevian))
      {
       
         return;
         
      }
      
      pprodevian->profiling_on_after_update_screen();
      
   }


   void window::macos_window_iconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }
      
//      if(m_puserbox != nullptr)
//      {
//         
//         auto edisplay =  m_puserbox->m_windowdisplayandlayout.m_edisplay;
//
//         m_puserbox->m_windowdisplayandlayout.m_edisplayPrevious = edisplay;
//         
//      }

      puserinteraction->set_display(::e_display_iconic, ::user::e_layout_window);

   }


   void window::macos_window_deiconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return;

      }
      
      if(m_puserbox)
      {
         
         auto & edisplayPrevious = m_puserbox->m_windowdisplayandlayout.m_edisplayPrevious;

         if(edisplayPrevious == ::e_display_iconic)
         {

            edisplayPrevious = ::e_display_normal;

         }
         
         puserinteraction->_001OnDeiconify(nullptr, edisplayPrevious);
         
      }

   }

   ::oswindow window::oswindow() const
   {
   
      return (::oswindow) this;
      
   }


   void window::_set_oswindow(::oswindow oswindow)
   {

   }


   void * window::get_os_data() const
   {
   
      return __nsacmewindow_osdata((CFTypeRef) m_pnsacmewindow);
   
   }

   void window::macos_window_on_create()
   {
      
      //set_os_data(m_pnswindow);
      
      set_oswindow(this);
      
      auto pwindowing = macos_windowing();
      
      auto osdata = __nsacmewindow_osdata(m_pnsacmewindow);

      pwindowing->set_osdata_acme_windowing_window(osdata, this);
      
      auto puserinteraction = m_puserinteraction;
      
      auto rectangle = puserinteraction-> const_layout().sketch().parent_raw_rectangle();
   
      puserinteraction->set_position(rectangle.top_left(), ::user::e_layout_window);

      puserinteraction->set_size(rectangle.size(), ::user::e_layout_window);
      
      //auto & layoutWindow = puserinteraction->const_layout().window();
      
      //auto & sizeWindow = layoutWindow.m_size;
      
      //auto ptask = ::get_task();
      
      //puserinteraction->m_pthreadUserInteraction = ptask;

         //puserinteraction->place(rectParam);



         //oswindow_assign(m_oswindow, this);

      //}

      auto lresult = puserinteraction->send_message(e_message_create); //
      //, 0, //(lparam)&cs);

      ///bool bOk = true;

      //if (!unhook_window_create() || lresult == -1)
      if (lresult == -1)
      {

         //bOk = false;
         
         set_finish();

         //children_post_quit();

         //children_wait_quit(one_minute());

         //PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
         
         throw exception(error_resource);

      }

//      //if(pusersystem->m_createstruct.style & WS_VISIBLE)
//      //if(pusersystem->m_.style & WS_VISIBLE)
//      if(puserinteraction->const_layout().sketch().is_screen_visible())
//      {
//
//         puserinteraction->display();
//
//         puserinteraction->set_need_redraw();
//
//         puserinteraction->post_redraw();
//
//         //;//macos_window_show();
//
//      }

      puserinteraction->set_need_layout();

//      puserinteraction->increment_reference_count();
      
      puserinteraction->on_finished_window_creation();

//      if(!bOk)
//      {
//         
//         throw ::exception(error_resource);
//         
//      }

   }


   void window::macos_window_on_show()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return;

      }

      m_timeLastExposureAddUp.Now();

      puserinteraction->send_message(e_message_show_window, 1);

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
      
      informationf("macos::window::macos_window_on_hide");

      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         warningf("macos::window::macos_window_on_hide (2) puserinteraction == nullptr");

         return;

      }
      
      if(puserinteraction->has_destroying_flag())
      {
         
         return;
         
      }
      
      if(puserinteraction->const_layout().window().is_screen_visible())
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
      
      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }

      //puserinteraction->message_call(e_message_show_window, 0);

      //puserinteraction->user_interaction_update_visibility_cache(false);

   }


void window::frame_toggle_restore(::user::activation_token * puseractivationtoken)
{
      
      ns_main_post(^()
                     {
         
         auto puserinteraction = m_puserinteraction;

      if(puserinteraction->get_parent() == nullptr && puserinteraction->get_owner() == nullptr)
      {

         if(!puserinteraction->is_window_visible()
            || (!(puserinteraction->m_ewindowflag & e_window_flag_miniaturizable)
                && !puserinteraction->is_window_screen_visible()))
         {

            puserinteraction->display_previous_restore();

         }
         else if(puserinteraction->_001GetTopLeftWeightedOccludedOpaqueRate()  > 0.025)
         {

            puserinteraction->order(::e_zorder_top);

            puserinteraction->display(e_display_default, {::user::e_activation_set_foreground, puseractivationtoken});

         }
         else if(m_timeLastExposureAddUp.elapsed() < 300_ms)
         {

            informationf("Ignored minituarize request (by toggle intent) because of recent full exposure.");

         }
         else
         {

            puserinteraction->display(e_display_iconic, {::user::e_activation_no_activate});

         }

         puserinteraction->set_need_redraw();

         puserinteraction->post_redraw();

      }

      });

      //return ::success;
      
   }


   void window::non_top_most_upper_window_rects(::int_rectangle_array & recta)
   {
      
      auto osdata = __nsacmewindow_osdata(m_pnsacmewindow);
      
      recta = cg_get_window_rect_list_intersect_above(ns_get_window_id(osdata));
      
   }


   void window::post_message(::message::message * pmessage)
   {

//      oswindow oswindow = message.oswindow;
//
//      ASSERT(oswindow != nullptr);
//
//      auto pimpl = oswindow->m_puserinteractionimpl;
//
//      if(::is_null(pimpl))
//      {
//
//         return false;
//
//      }

      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return false;

      }
      
      puserinteraction->post_message(pmessage);

      //::thread * pthread = nullptr;

//      if (::is_set(puserinteraction))
//      {
//
//         pthread = puserinteraction->m_pthreadUserInteraction;
//
//      }
//
//      if (::is_null(pthread))
//      {
//
//         return false;
//
//      }
//
//      class ::message_queue * pmq = pthread->m_pmq;
//
//      if (pmq == nullptr)
//      {
//
//         if (message.m_id == e_message_quit)
//         {
//
//            return false;
//
//         }
//
//         pmq = pthread->get_message_queue();
//
//      }
//
//      if (pmq == nullptr)
//      {
//
//         return false;
//
//      }
//
//      _synchronous_lock ml(pmq->mutex());
//
//      if (message.m_id == e_message_quit)
//      {
//
//         output_debug_string("e_message_quit thread");
//
//      }
//
//      if (message.m_id == e_message_left_button_down)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_down\n");
//
//      }
//      else if (message.m_id == e_message_left_button_up)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_up\n");
//
//      }
//
//      pmq->m_messagea.add(message);
//
//      pmq->m_eventNewMessage.set_event();

      return true;

   }


   lresult window::send_message(::message::message * pmessage)
   {

   //      oswindow oswindow = message.oswindow;
   //
   //      ASSERT(oswindow != nullptr);
   //
   //      auto pimpl = oswindow->m_puserinteractionimpl;
   //
   //      if(::is_null(pimpl))
   //      {
   //
   //         return false;
   //
   //      }

      auto puserinteraction = m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return false;

      }
      
      puserinteraction->message_handler(pmessage);

      //::thread * pthread = nullptr;

   //      if (::is_set(puserinteraction))
   //      {
   //
   //         pthread = puserinteraction->m_pthreadUserInteraction;
   //
   //      }
   //
   //      if (::is_null(pthread))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      class ::message_queue * pmq = pthread->m_pmq;
   //
   //      if (pmq == nullptr)
   //      {
   //
   //         if (message.m_id == e_message_quit)
   //         {
   //
   //            return false;
   //
   //         }
   //
   //         pmq = pthread->get_message_queue();
   //
   //      }
   //
   //      if (pmq == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      _synchronous_lock ml(pmq->mutex());
   //
   //      if (message.m_id == e_message_quit)
   //      {
   //
   //         output_debug_string("e_message_quit thread");
   //
   //      }
   //
   //      if (message.m_id == e_message_left_button_down)
   //      {
   //
   //         output_debug_string("post_ui_message::e_message_left_button_down\n");
   //
   //      }
   //      else if (message.m_id == e_message_left_button_up)
   //      {
   //
   //         output_debug_string("post_ui_message::e_message_left_button_up\n");
   //
   //      }
   //
   //      pmq->m_messagea.add(message);
   //
   //      pmq->m_eventNewMessage.set_event();

      return true;

   }


   void window::destroy_window()
   {


      ::pointer < ::user::interaction > puiThis = m_puserinteraction;

      try
      {

         puiThis->send_message(e_message_destroy);

      }
      catch (...)
      {

      }

      try
      {

         puiThis->send_message(e_message_non_client_destroy);

      }
      catch (...)
      {

      }

      //return ::success;

   }


   void window::bring_to_front()
   {

      macos_window_order_front();

      //return ::success;

   }


    void window::set_opacity(double dOpacity)
    {
        
        macos_window_set_opacity(minimum_maximum(dOpacity, 0.0, 1.0));
        
    }
class windowing * window::macos_windowing()
{
    
    return dynamic_cast < ::windowing_macos::windowing * >(::system()->windowing());
    
}


} // namespace windowing_macos




