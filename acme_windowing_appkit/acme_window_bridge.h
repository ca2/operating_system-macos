//
//  c_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/02/22.
//  23:26
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once

#include "operating_system-apple/acme_windowing_kit/_.h"
#include "operating_system-apple/acme_windowing_kit/acme_window_bridge.h"
#include "acme/constant/cursor.h"
#include "operating_system-apple/core_graphics/cg_context.h"


namespace macos
{

namespace nano
{
class window;
}
}


#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

namespace appkit{
namespace acme{
namespace windowing{
class window;
}
}
}

namespace appkit
{

   
   class acme_window_bridge :
      virtual public ::apple_kit::acme_window_bridge
{
public:
   
   
   bool                             m_bIsActiveCached;

   bool m_bRunningAppMainLoop;
   ::appkit::acme::windowing::window *     m_pappkitacmewindowingwindow;
   ::pointer < ::core_graphics::cg_context > m_pcgcontext;
   CFTypeRef                  m_pnsacmewindow;
   
   
   acme_window_bridge();
   ~acme_window_bridge() override;
   
   void create_ns_acme_window(CGRect cgrect, bool bMoreNative);
   
   void set_ns_window_uptr(::uptr u);
   
   void ns_show() override;
   
   void ns_hide() override;
   
   void do_tasks() override;
   
   void ns_redraw() override;
   
//   virtual void discard_all_cursor_rectangles();
//   virtual void add_cursor_rectangle(const ::i32_rectangle & r, ::enum_cursor ecursor);
//   virtual void on_set_cursor_rectangles();
//   virtual void invalidate_cursor_rectangles();
   

   virtual int control_box_right_when_at_left() const;
   
   virtual void on_control_box_close();
   virtual void on_control_box_minimize();
   virtual void on_control_box_zoom();
   
//   virtual void on_left_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute);
//   
//   virtual void on_left_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute);
//   
//   virtual void on_right_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute);
//   
//   virtual void on_right_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute);
//   
//   virtual void on_mouse_move(int xHost, int yHost, int xAbsolute, int yAbsolute);
   
   virtual void on_char(int iChar);
   
   //virtual void _on_draw_frame(CGContextRef cg, CGRect rectFrame);
   
   void redraw() override;
   
   //virtual void stop();
   
   void close() override;
   
   void set_position(int x, int y) override;
   
   virtual void on_move(int x, int y);
   
   virtual void on_size(int w, int h);

   //virtual void on_layout(int x, int y, int w, int h);
   
   virtual void macos_window_become_main();
   
   virtual void macos_window_resign_main();
   
   virtual void macos_window_become_key();
   
   virtual void macos_window_resign_key();
   
   virtual void toggle_fullscreen();
   
   CGRect get_frame() override;
   
   void _run_modal_loop() override;
   
   virtual bool _is_top_most() const;
   
   virtual bool _is_popup_window() const;
   
   ::acme::windowing::window * acme_windowing_window() override;
   
   virtual bool should_use_desktop_ambient_like_control_box() const;
   
};


} // namespace appkit



