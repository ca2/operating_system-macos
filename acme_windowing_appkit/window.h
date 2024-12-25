//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window.h"
#include <Carbon/Carbon.h>


namespace appkit
{

class acme_window_bridge;


   namespace acme
   {


      namespace windowing
      {


   class CLASS_DECL_ACME_WINDOWING_APPKIT window :
      virtual public ::acme::windowing::window
   {
   public:


      //bool                             m_bAppRunMainLoop;
      //Display *                        m_pdisplay;
      //Window                           m_window;
      //cairo_surface_t *                m_psurface;
      ::pointer<::appkit::acme_window_bridge>   m_pacmewindowbridge;
      ::pointer<::nano::graphics::device>          m_pnanodevice;
      //::pointer<::nano::graphics::font>         m_pfont;
      //color32_t                     m_colorText;
      //color32_t                     m_colorFocus;
      //color32_t                     m_colorWindow;
      //string                        m_strTitle;
      //bool                          m_bNcActive;

      //int_rectangle                 m_rectangle;
      //int_rectangle                 m_rectangleX;

      //pointer_array < ::nano::user::child >   m_childa;
      //::atom                          m_atomLeftButtonDown;
      //::atom                          m_atomLeftButtonUp;
      //::atom                             m_atomResult;
      //::pointer<::nano::user::child>        m_pchildFocus;


      window();
      ~window() override;


#ifdef _DEBUG

      huge_integer increment_reference_count() override;
      huge_integer decrement_reference_count() override;
      huge_integer release() override;

#endif

      void on_initialize_particle() override;

      void create_window() override;
      
      void _create_window() override;

      void destroy_window() override;

      void show_window() override;
      
      void hide_window() override;

      //virtual void _on_event(XEvent *pevent);
      
      void _main_post(const ::procedure & procedure) override;

      virtual void _update_window();

      //void message_loop() override;

      virtual bool message_loop_step();

      virtual void _draw(CGContextRef cgcontextref);

      //virtual void on_draw(::nano::graphics::device * pnanodevice);

      //void on_char(int iChar) override;

      bool is_active_window() override;

      void set_active_window() override;

      ///virtual void draw_children(::nano::graphics::device * pnanodevice);

//      void delete_drawing_objects() override;
//
//      bool get_dark_mode() override;
//
//      void create_drawing_objects() override;
//
//      void update_drawing_objects() override;
//
//      ::nano::user::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

      //virtual void add_child(::nano::user::child * pchild);

//      ::payload get_result() override;
//
//      void on_mouse_move(::user::mouse * pmouse) override;
//
//      void on_left_button_down(::user::mouse * pmouse) override;
//
//      void on_left_button_up(::user::mouse * pmouse) override;
//
//      void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
//
//      void on_right_button_down(::user::mouse * pmouse) override;
//
//      void on_right_button_up(::user::mouse * pmouse) override;
//
//      void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

      //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      void set_position_unlocked(const ::int_point & point) override;

      void redraw() override;

      //void get_client_rectangle(::int_rectangle & rectangle) override;

      ::int_rectangle get_window_rectangle_unlocked() override;

      void set_capture() override;

      void release_capture() override;

      //virtual void _wm_nodecorations(int iMap);
      
      ::payload wait_for_dialog_result(const class ::time & timeTimeout = ::time::infinity()) override;
      
//      ::int_size get_main_screen_size() override;
      
      
      virtual ::payload do_synchronously();
      
      void handle(::topic* ptopic, ::context* pcontext) override;
      
      virtual void macos_window_become_main();
      virtual void macos_window_resign_main();
      
      virtual void macos_window_become_key();
      virtual void macos_window_resign_key();

      
      virtual void _on_layout(int x, int y, int w, int h);
      
      
   };


      } //namespace windowing


   } //namespace acme


} // namespace appkit



