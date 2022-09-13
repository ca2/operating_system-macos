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


#include "aura/windowing/window.h"


namespace windowing_macos
{


    class CLASS_DECL_WINDOWING_MACOS window :
      virtual public ::windowing::window,
      virtual public ::macos_window
   {
   public:
      
      
      void *                           m_pNSCursorLast;
      class windowing *                m_pmacoswindowing;
      ::windowing::window *            m_pwindowCapture;
      ::point_i32                      m_pointMouseCursor;
      __pointer(::windowing::cursor)   m_pcursor;
      
      
      window();
      ~window() override;
      
      
      void create_window(::user::interaction_impl * pimpl) override;
      

      void macos_window_add_ref() override;
      void macos_window_dec_ref() override;
      
      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      
      void install_message_routing(channel * pchannel) override;
      
      void set_keyboard_focus() override;
      
      void set_active_window() override;
      
      void set_foreground_window() override;
      
      void set_tool_window(bool bSet) override;
      
      bool is_active_window() const override;
      
      bool has_keyboard_focus() const override;

      void window_show() override;
      
      void show_window(const ::e_display &edisplay, const ::e_activation &eactivation) override;
      
      void set_mouse_cursor(::windowing::cursor * pcursor) override;
      
      ::point_i32 get_mouse_cursor_position() override;
      
      bool set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags) override;

      void set_mouse_capture() override;

      void get_cursor_position(POINT_I32 * ppoint) override;
      
      void update_screen() override;
      

      virtual void macos_window_draw(CGContextRef cgc, CGSize sizeWindow) override;
      virtual void macos_window_mouse_down(int iButton, double x, double y) override;
      virtual void macos_window_mouse_up(int iButton, double x, double y) override;
      virtual void macos_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton) override;
      virtual void macos_window_mouse_dragged(double x, double y, unsigned long iAppleMouseButton) override;
      virtual void macos_window_mouse_wheel(double deltaY, double x, double y) override;
      virtual void macos_window_double_click(int iButton, double x, double y) override;
      virtual bool macos_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8) override;
      virtual bool macos_window_key_up(unsigned int vk, unsigned int scan) override;
//      virtual bool macos_window_key_down(unsigned int uiKeyCode) override;
//      virtual bool macos_window_key_up(unsigned int uiKeyCode) override;
      
      
      virtual void macos_window_did_become_key() override;
      virtual void macos_window_on_activate() override;
      virtual void macos_window_on_deactivate() override;

      
      void * macos_window_get_mouse_cursor() override;


      void profiling_on_start_draw_rectangle() override;
      void profiling_on_end_draw_rectangle() override;

      
      virtual void macos_window_resized(CGRect rectangle_i32) override;
      virtual void macos_window_moved(CGPoint point_i32) override;
      virtual void macos_window_iconified() override;
      virtual void macos_window_deiconified() override;





      virtual void macos_window_on_show() override;
      virtual void macos_window_on_hide() override;
      virtual void macos_window_on_miniaturize() override;

      void frame_toggle_restore() override;
      
      
      void non_top_most_upper_window_rects(::rectangle_i32_array & recta) override;


      bool post_message(::message::message * pmessage);
      bool send_message(::message::message * pmessage);

      
      void destroy_window() override;
      
      
      void bring_to_front() override;
      

   };


} // windowing_macos



