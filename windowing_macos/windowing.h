//
//  windowing.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-21 01:59 <3ThomasBS_!!
//
#pragma once


namespace windowing_macos
{


    class CLASS_DECL_WINDOWING_MACOS windowing :
      virtual public ::windowing::windowing
   {
   public:
      
      
      __pointer(::windowing::display)           m_pdisplay;
      
      __pointer(class window)                   m_pwindowActive;
      
      __pointer(class window)                   m_pwindowCapture;
      
      map < void *, __pointer(class window) >   m_nsmap;

      
      windowing();
      ~windowing() override;
      
      
      ::e_status initialize(::object * pobject) override;
      
      ::e_status windowing_branch(const ::routine & routine) override;
      
      ::windowing::window * window(oswindow oswindow) override;

      ::windowing::display * display() override;
      
      ::windowing::window * get_active_window(::thread * pthread) override;

      //virtual bool post_ui_message(::message::base * pbase);
      
      ::e_status release_mouse_capture() override;
      
      ::windowing::window * get_keyboard_focus(::thread *) override;

      
   };
      

} // namespace windowing_macos




