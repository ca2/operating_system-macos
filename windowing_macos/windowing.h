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
      
      
      __pointer(::windowing::display)        m_pdisplay;
      
      __pointer(class window)                m_pwindowActive;
      
      
      windowing();
      ~windowing() override;
      
      
      ::e_status initialize(::object * pobject) override;
      
      
      ::e_status windowing_branch(const ::routine & routine) override;
      
      ::windowing::window * window(oswindow oswindow) override;

      
      ::windowing::display * display() override;
      
      
      ::windowing::window * get_active_window(::thread * pthread) override;

      
      virtual bool post_ui_message(const MESSAGE &message);


   };
      

} // namespace windowing_macos




