//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "acme_window_bridge.h"
#include "acme/nano/graphics/device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/mouse.h"
#include <CoreGraphics/CoreGraphics.h>

void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();

void ns_app_run();

void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const ::rectangle_i32 &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const ::point_i32 & point);

void screen_coordinates_aware_copy(::point_i32 & point, const CGPoint & cgpoint);

//void macos_defer_initialize_nano_callbacks();
namespace appkit
{


   namespace acme
   {


      namespace windowing
   {
      
      
      window::window()
      {
         
         //macos_defer_initialize_nano_callbacks();
         
      }
      
      
      window::~window()
      {
         
         //delete_drawing_objects();
         
         m_pnanodevice.release();
         
      }
      
      
#ifdef _DEBUG
      
      
      i64 window::increment_reference_count()
      {
         
         return ::acme::windowing::window::increment_reference_count();
         
      }
      
      
      i64 window::decrement_reference_count()
      {
         
         return ::acme::windowing::window::decrement_reference_count();
         
      }
      
      
      i64 window::release()
      {
         
         return ::acme::windowing::window::release();
         
      }
      
      
#endif
      
      
      void window::on_initialize_particle()
      {
         
         ::acme::windowing::window::on_initialize_particle();
         
      }
      
      
      //   void window::on_char(int iChar)
      //   {
      //
      //      m_pinterface->on_char(iChar);
      //
      //   }
      
      
      void window::_draw(CGContextRef cgcontextref)
      {
         
         {
            
            //nano()->graphics();
            
            __construct(m_pnanodevice);
            
            m_pnanodevice->attach(cgcontextref);
            
            ::pointer < ::micro::elemental > pelemental;
            
            pelemental = m_pacmeuserinteraction;
            
            if (pelemental)
            {
               
               pelemental->draw(m_pnanodevice);
               
            }
            
         }
         //m_pinterface->draw(pnanodevice);
         
      }
      
      
      bool window::is_active_window()
      {
         
         //return m_pacmewindowbridge->is_active();
         return true;
         
      }
      
      
      //   void window::delete_drawing_objects()
      //   {
      //
      //      m_pinterface->delete_drawing_objects();
      //
      //   }
      
      
      //   bool window::get_dark_mode()
      //   {
      //
      //      return system()->dark_mode();
      //
      //   }
      
      
      //   void window::create_drawing_objects()
      //   {
      //
      //      m_pinterface->create_drawing_objects();
      //
      //   }
      
      
      //   void window::update_drawing_objects()
      //   {
      //
      //      m_pinterface->update_drawing_objects();
      //
      //   }
      
      
      void window::create_window()
      {
         
         main_send([this]()
                   {
            
            _create_window();
            
         });
         
      }
      
      
      void window::_create_window()
      {
         
         m_pacmewindowbridge = __allocate acme_window_bridge();
         
         CGRect cgrect;
         
         auto rectangle = m_pacmeuserinteraction->get_rectangle();
         
         screen_coordinates_aware_copy(cgrect, rectangle);
         
         m_pacmewindowbridge->m_pwindow = this;
         
         m_pacmewindowbridge->create_ns_acme_window(cgrect);
         
         //nano_window_on_create();
         
         //create_drawing_objects();
         
         ///on_create();
         
      }
      
      
      void window::handle(::topic* ptopic, ::context* pcontext)
      {
         
         if (ptopic->m_atom == id_set_application_dark_mode)
         {
            
            //update_drawing_objects();
            //m_pimplementation->handle(ptopic, pcontext);
            redraw();
            
         }
         
      }
      
      
      //   void window::on_left_button_down(::user::mouse * pmouse)
      //   {
      //
      //      m_pacmeuserinteraction->on_left_button_down(pmouse);
      //
      //   }
      //
      //
      //   void window::on_left_button_up(::user::mouse * pmouse)
      //   {
      //
      //      m_pacmeuserinteraction->on_left_button_up(pmouse);
      //
      //   }
      //
      //
      //   void window::on_right_button_down(::user::mouse * pmouse)
      //   {
      //
      //      m_pacmeuserinteraction->on_right_button_down(pmouse);
      //
      //   }
      //
      //
      //   void window::on_right_button_up(::user::mouse * pmouse)
      //   {
      //
      //      m_pacmeuserinteraction->on_right_button_up(pmouse);
      //
      //   }
      //
      //
      //   void window::on_mouse_move(::user::mouse * pmouse)
      //   {
      //
      //      m_pacmeuserinteraction->on_mouse_move(pmouse);
      //
      //   }
      //
      //
      //   ::payload window::get_result()
      //   {
      //
      //      return m_pacmeuserinteraction->get_result();
      //
      //   }
      //
      //
      //   ::nano::user::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
      //   {
      //
      //      return m_pacmeuserinteraction->hit_test(pmouse, ezorder);
      //
      //   }
      
      
      void window::show_window()
      {
         
         set_active_window();
         
         m_pacmewindowbridge->display();
         
      }
      
      
      void window::hide_window()
      {
         
         m_pacmewindowbridge->hide();
         
      }
      
      
      void window::set_active_window()
      {
         
         //m_pacmewindowbridge->set
         
      }
      
      
      void window::_update_window()
      {
         
         if(!m_pacmewindowbridge)
         {
            
            return;
            
         }
         
         m_pacmewindowbridge->redraw();
         
      }
      
      
      bool window::message_loop_step()
      {
         
         return false;
         
      }
      
      
      //   void window::message_loop()
      //   {
      //
      // ///     while(aaa_message_loop_step())
      //    //  {
      //
      //      //}
      //
      //      ns_main_post(^()
      //                    {
      //
      //         m_pacmewindowbridge->_run_modal_loop();
      //
      //      });
      //
      //
      //   }
      
      
      void window::redraw()
      {
         
         _update_window();
         
      }
      
      
      void window::destroy_window()
      {
         
         m_pacmewindowbridge->close();
         
         nano_window_on_destroy();
         
      }
      
      
      //
      //   void window::on_click(const ::payload & payload, ::user::mouse * pmouse)
      //   {
      //
      //      m_pinterface->on_click(payload, pmouse);
      //
      //   }
      //
      //
      //   void window::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
      //   {
      //
      //      m_pinterface->on_right_click(payload, pmouse);
      //
      //   }
      
      
      void window::set_position_unlocked(const ::point_i32 & point)
      {
         
         m_pacmewindowbridge->set_position(point.x(), point.y());
         
      }
      
      
      void window::set_capture()
      {
         
      }
      
      
      void window::release_capture()
      {
         
      }
      
      
      ::rectangle_i32 window::get_window_rectangle_unlocked()
      {
         
         auto cgrect = m_pacmewindowbridge->get_frame();
         ::rectangle_i32 r;
         copy(r, cgrect);
         return r;
         
      }
      
      //
      //   void window::get_window_rectangle(::rectangle_i32 & rectangle)
      //   {
      //
      //   }
      
      
      ::payload window::wait_for_dialog_result(const class ::time & timeTimeout)
      {
         
         m_pacmewindowbridge->_run_modal_loop();
         
         ::pointer < ::micro::elemental > pelemental;
         
         pelemental = m_pacmeuserinteraction;
         
         if (pelemental)
         {
            
            return pelemental->get_dialog_result();
            
         }
         
         return {};
         
      }
      
      
      //   ::size_i32 window::get_main_screen_size()
      //   {
      //
      //      int cx = 800;
      //
      //      int cy = 600;
      //
      //      ns_get_main_screen_size(cx, cy);
      //
      //      return { cx, cy };
      //
      //   }
      
      
      ::payload window::do_synchronously()
      {
         
         //      if(ns_app_is_running())
         //      {
         //
         //         return ::nano::user::window_implementation::do_synchronously();
         //
         //      }
         //
         //      atom atomResult;
         //
         //      m_pinterface->m_psequencer->then([ &atomResult ](auto psequence)
         //      {
         //
         //         atomResult = psequence->m_payloadResult;
         //
         //         ns_app_stop();
         //
         //      });
         //
         //      ns_app_run();
         //
         //      //   auto pmessagebox = pparticle->__create_new < ::nano::user::message_box >();
         //      //
         //      //   atom idResult;
         //      //
         //      //   manual_reset_event event;
         //      //
         //      //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
         //      //
         //      //   pmessagebox->m_functionClose = [&idResult, &event](window * pwindow)
         //      //   {
         //      //
         //      //      idResult = pwindow->m_atomResult;
         //      //
         //      //      event.SetEvent();
         //      //
         //      //   };
         //      //
         //      //   if(is_single_main_user_thread() && is_main_thread())
         //      //   {
         //      //
         //      //      pmessagebox->_run_modal_loop();
         //      //
         //      //   }
         //      //   else
         //      //   {
         //      //      event.wait();
         //      //
         //      //   }
         //      //
         //      //   //auto idResult = pmessagebox->get_result();
         //      //
         //      //   return idResult;
         //
         //      return atomResult;
         return {};
         
         
      }
      
      
      void window::macos_window_become_main()
      {
         
         application()->application_menu_update();
         
      }
      
      
      void window::macos_window_resign_main()
      {
         
         
      }
      
      
      void window::macos_window_become_key()
      {
         
         //application()->application_menu_update();
         
      }
      
      
      void window::macos_window_resign_key()
      {
         
         
      }


      } //namespace windowing


   } //namespace acme


} // namespace appkit



