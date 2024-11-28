//
//  macos_window.h
//  os
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once

#include "acme_windowing_appkit/acme_window_bridge.h"
//#include "app/axis/user/user/user_key_enum.h"

class macos_window :
   virtual public appkit::acme_window_bridge
{
public:
   

   double                        m_dOpacity;
   bool                          m_bDestroying;
   bool                          m_bDirty;
   bool                          m_bTest123;
   
   ::huge_integer                m_iNanosecondLastUpdateBeg;
   ::huge_integer                m_iNanosecondLastUpdateEnd;

   
   macos_window();
   virtual ~macos_window();

   
   virtual void macos_window_add_ref() = 0;
   virtual void macos_window_dec_ref() = 0;
   
   virtual void macos_window_draw(CGContextRef cgc, CGSize sizeWindow) = 0;
   virtual void macos_window_mouse_down(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute) = 0;
   virtual void macos_window_mouse_up(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute) = 0;
   virtual void macos_window_mouse_repositioned(double xHost, double yHost, double xAbsolute, double yAbsolutey, unsigned long ulAppleMouseButton) = 0;
   virtual void macos_window_mouse_dragged(double xHost, double yHost, double xAbsolute, double yAbsolute, unsigned long ulAppleMouseButton) = 0;
   virtual void macos_window_mouse_wheel(double deltaY, double xHost, double yHost, double xAbsolute, double yAbsolute) = 0;
   virtual void macos_window_double_click(int iButton, double xHost, double yHost, double xAbsolute, double yAbsolute) = 0;
   virtual bool macos_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8) = 0;
   virtual bool macos_window_key_up(unsigned int vk, unsigned int scan) = 0;
   //virtual bool macos_window_key_down(unsigned int uiKeyCode) = 0;
   //virtual bool macos_window_key_up(unsigned int uiKeyCode) = 0;
   
   virtual void macos_window_on_create() = 0;
   
   virtual void macos_window_resized(CGRect int_rectangle) = 0;
   virtual void macos_window_repositioned(CGPoint int_point) = 0;
   
   virtual void macos_window_iconified() = 0;
   virtual void macos_window_deiconified() = 0;

   virtual void macos_window_on_show() = 0;
   virtual void macos_window_on_hide() = 0;
   virtual void macos_window_on_miniaturize() = 0;
   
   virtual void macos_window_did_become_key() = 0;
   virtual void macos_window_did_resign_key() = 0;

   virtual void macos_window_on_activate() = 0;
   virtual void macos_window_on_deactivate() = 0;
   
   
   virtual void * macos_window_get_mouse_cursor() = 0;
   
   
   virtual void profiling_on_start_draw_rectangle() = 0;
   virtual void profiling_on_end_draw_rectangle() = 0;
   
   
   virtual void macos_window_set_frame(CGRect rect);
   virtual void macos_window_get_frame(CGRect * prect);
   virtual void macos_window_invalidate();
   virtual void macos_window_show();
   virtual void macos_window_defer_show();
   virtual void macos_window_hide();
   virtual void macos_window_miniaturize();
   virtual void macos_window_redraw();
   virtual void macos_window_redraw_sync();
   
   virtual void macos_window_make_first_responder();
   virtual bool macos_window_is_key_window() const;
   virtual void macos_window_resign_key();
   
   virtual void macos_window_order_front();
   virtual void macos_window_make_key_window();
   virtual void macos_window_make_key_window_and_order_front();
   virtual void macos_window_make_main_window();
   
   virtual void macos_window_set_title(const char * pszTitle);
   virtual void macos_window_get_title(char * pszTitle, int iSize);
   
   virtual void macos_window_destroy();
    
    virtual void macos_window_set_opacity(double dOpacity);
   
   //virtual void ns_main_post(dispatch_block_t block) = 0;
   
};




//NSWindow * get_os_window_ns_window(oswindow hwnd);



