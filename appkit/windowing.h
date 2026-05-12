//
//  windowing.h
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 06:06
//  <3ThomasBorregaardSørensen!!
//
//
// Created by camilo on 2024-12-05 17:05 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/_operating_system.h"
#include "operating_system-macos/appkit/ns_window.h"


namespace appkit
{



   class CLASS_DECL_ACME windowing :
      virtual public ::acme::windowing::windowing
   {
   public:

      
      ::map < ns_window_t, ::pointer < ::appkit::ns_window > > m_windowmap;


      windowing();
      ~windowing() override;

      ::acme::windowing::window *
      acme_windowing_window(const ::operating_system::window &operatingsystemwindow) override;
   
      void add_window(::acme::windowing::window * pacmewindowingwindow);

      void each_window(const ::function < void(::acme::windowing::window * pacmewindowingwindow) > & function) override;

      ::operating_system::window operating_system_window(const ::wparam &wparam) override;

      ::operating_system::window operating_system_window(const ::lparam &lparam) override;


   };


} // namespace appkit


//CLASS_DECL_ACME HWND get_task_main_hwnd(::task *ptask);
//CLASS_DECL_ACME HWND get_main_hwnd();



